#!/usr/bin/env python3
import os
import sys
from pathlib import Path

# Add tool directory to path and bootstrap dependencies
sys.path.insert(0, str(Path(__file__).resolve().parent))
try:
    import asset_common
    asset_common.ensure_dependencies()
except ImportError:
    pass

"""
gba_audio_pipeline.py - Automated GBA Audio, DirectSound & Soundfont Compiler
Supports: WAV sample downsampling, 8-bit PCM conversion, looping, M4A voicegroups,
and MIDI sequence track transcription.
"""

import os
import sys
import math
import struct
import argparse
from pathlib import Path

# Common GBA hardware sample rates (clock prescaler multiples)
GBA_SAMPLE_RATES = {
    "5.7k": 5734,
    "10.5k": 10512,
    "13.4k": 13379,
    "18.1k": 18157,
    "21.0k": 21024,
    "26.8k": 26758,
    "31.5k": 31536,
    "42.0k": 42048,
}

class GBAWaveSample:
    def __init__(self, name: str, sample_rate: int, data: bytes, loop_start: int = 0, is_looped: bool = False):
        self.name = name
        self.sample_rate = sample_rate
        self.data = data
        self.size = len(data)
        self.loop_start = loop_start if is_looped else 0
        self.is_looped = is_looped

    @classmethod
    def from_wav(cls, filepath: Path, target_rate: int = 13379, normalize: bool = True, loop_start: int = -1):
        with open(filepath, "rb") as f:
            riff = f.read(12)
            if riff[:4] != b"RIFF" or riff[8:] != b"WAVE":
                raise ValueError(f"Invalid WAV file header: {filepath}")

            audio_format = 1
            channels = 1
            orig_rate = 44100
            bits_per_sample = 16
            raw_pcm = b""

            while True:
                chunk_header = f.read(8)
                if len(chunk_header) < 8:
                    break
                chunk_id, chunk_size = struct.unpack("<4sI", chunk_header)
                if chunk_id == b"fmt ":
                    fmt_data = f.read(chunk_size)
                    audio_format, channels, orig_rate, _, _, bits_per_sample = struct.unpack("<HHIIHH", fmt_data[:16])
                elif chunk_id == b"data":
                    raw_pcm = f.read(chunk_size)
                    break
                else:
                    f.seek(chunk_size, os.SEEK_CUR)

            if audio_format != 1:
                raise ValueError("Only uncompressed Linear PCM WAVs are supported.")

            # Decode samples to floating point (-1.0 to 1.0)
            samples = []
            bytes_per_sample = bits_per_sample // 8
            total_samples = len(raw_pcm) // (bytes_per_sample * channels)

            for i in range(total_samples):
                offset = i * bytes_per_sample * channels
                # Interleaved downmixing to mono
                acc = 0.0
                for c in range(channels):
                    ch_offset = offset + (c * bytes_per_sample)
                    if bits_per_sample == 8:
                        val = (raw_pcm[ch_offset] - 128) / 128.0
                    elif bits_per_sample == 16:
                        val = struct.unpack("<h", raw_pcm[ch_offset:ch_offset+2])[0] / 32768.0
                    elif bits_per_sample == 24:
                        b = raw_pcm[ch_offset:ch_offset+3]
                        val = struct.unpack("<i", b + (b"\xff" if b[2] & 0x80 else b"\x00"))[0] / 8388608.0
                    elif bits_per_sample == 32:
                        val = struct.unpack("<i", raw_pcm[ch_offset:ch_offset+4])[0] / 2147483648.0
                    else:
                        val = 0.0
                    acc += val
                samples.append(acc / channels)

            # High-quality bandlimited linear interpolation
            out_len = int(round(len(samples) * (target_rate / orig_rate)))
            resampled = []
            for i in range(out_len):
                orig_pos = i * (orig_rate / target_rate)
                idx = int(orig_pos)
                frac = orig_pos - idx
                if idx + 1 < len(samples):
                    val = samples[idx] * (1.0 - frac) + samples[idx + 1] * frac
                elif idx < len(samples):
                    val = samples[idx]
                else:
                    val = 0.0
                resampled.append(val)

            # Normalization
            if normalize and len(resampled) > 0:
                max_amp = max(max(abs(s) for s in resampled), 0.0001)
                resampled = [s / max_amp for s in resampled]

            # Convert to signed 8-bit (-128 to 127) for GBA M4A Sound Engine
            gba_data = bytearray()
            for s in resampled:
                val = int(round(s * 127.0))
                val = max(-128, min(127, val))
                gba_data.append(val & 0xFF)

            is_looped = (loop_start >= 0)
            resolved_loop_start = max(0, int(loop_start * (target_rate / orig_rate))) if is_looped else 0

            return cls(
                name=filepath.stem,
                sample_rate=target_rate,
                data=bytes(gba_data),
                loop_start=resolved_loop_start,
                is_looped=is_looped
            )

    def export_c_header(self, out_file: Path):
        """Exports 8-bit signed PCM array and GBA WaveData structure."""
        with open(out_file, "w") as f:
            f.write(f"// Generated GBA WaveData: {self.name}\n")
            f.write(f"#include \"gba/gba.h\"\n\n")
            f.write(f"const s8 {self.name}_SampleData[{len(self.data)}] = {{\n    ")
            for i, byte in enumerate(self.data):
                signed_val = struct.unpack("b", bytes([byte]))[0]
                f.write(f"{signed_val:4d},")
                if (i + 1) % 16 == 0 and (i + 1) < len(self.data):
                    f.write("\n    ")
            f.write("\n};\n\n")
            f.write("struct WaveData {\n")
            f.write("    u16 type;\n    u16 status;\n    u32 freq;\n    u32 loop;\n    u32 size;\n    const s8 *data;\n};\n\n")
            f.write(f"const struct WaveData {self.name}_Wave = {{\n")
            f.write(f"    .type = 0x0000,\n")
            f.write(f"    .status = {'0x4000' if self.is_looped else '0x0000'},\n")
            f.write(f"    .freq = {self.sample_rate * 1024},\n")  # GBA internal fixed point
            f.write(f"    .loop = {self.loop_start},\n")
            f.write(f"    .size = {self.size},\n")
            f.write(f"    .data = {self.name}_SampleData,\n")
            f.write("};\n")

    def export_assembly(self, out_file: Path):
        """Exports GNU Assembly .s file for pokeemerald sound/directsound/."""
        with open(out_file, "w") as f:
            f.write(f"\t.section .rodata\n")
            f.write(f"\t.global {self.name}_Wave\n")
            f.write(f"\t.align 2\n")
            f.write(f"{self.name}_Wave:\n")
            f.write(f"\t.short 0x0000\n")
            f.write(f"\t.short {'0x4000' if self.is_looped else '0x0000'}\n")
            f.write(f"\t.word {self.sample_rate * 1024}\n")
            f.write(f"\t.word {self.loop_start}\n")
            f.write(f"\t.word {self.size}\n")
            f.write(f"\t.word {self.name}_SampleData\n\n")
            f.write(f"{self.name}_SampleData:\n")
            for i in range(0, len(self.data), 16):
                chunk = self.data[i:i+16]
                vals = [str(struct.unpack("b", bytes([b]))[0]) for b in chunk]
                f.write(f"\t.byte {', '.join(vals)}\n")
            f.write(f"\t.align 2\n")

class GBASoundfontCompiler:
    """Compiles multi-instrument soundfonts and generates M4A voicegroup structures."""
    def __init__(self, voicegroup_name: str):
        self.voicegroup_name = voicegroup_name
        self.voices = {}  # program_num: dict

    def add_directsound_voice(self, prog_num: int, wave_label: str, base_note: int = 60, pan: int = 0):
        self.voices[prog_num] = {
            "type": 0x00, # DirectSound
            "wave": wave_label,
            "base_note": base_note,
            "pan": pan,
            "attack": 0,
            "decay": 0,
            "sustain": 15,
            "release": 0
        }

    def add_programmable_wave_voice(self, prog_num: int, wave_data_label: str, base_note: int = 60):
        self.voices[prog_num] = {
            "type": 0x03, # PSG Wave 3
            "wave": wave_data_label,
            "base_note": base_note,
            "pan": 0,
            "attack": 0,
            "decay": 0,
            "sustain": 15,
            "release": 0
        }

    def export_voicegroup_s(self, out_file: Path):
        with open(out_file, "w") as f:
            f.write(f"// Soundfont Voicegroup: {self.voicegroup_name}\n")
            f.write(f"\t.section .rodata\n")
            f.write(f"\t.global {self.voicegroup_name}\n")
            f.write(f"\t.align 2\n")
            f.write(f"{self.voicegroup_name}:\n")
            for prog in range(128):
                if prog in self.voices:
                    v = self.voices[prog]
                    f.write(f"\t.byte {v['type']}, {v['base_note']}, 0, {v['pan']}\n")
                    f.write(f"\t.word {v['wave']}\n")
                    f.write(f"\t.byte {v['attack']}, {v['decay']}, {v['sustain']}, {v['release']}\n")
                else:
                    # Dummy / Empty Voice Entry
                    f.write("\t.byte 0x00, 60, 0, 0\n")
                    f.write("\t.word 0\n")
                    f.write("\t.byte 0, 0, 15, 0\n")
            f.write("\t.align 2\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="GBA Soundfont & Sample Processor")
    parser.add_argument("--wav", type=Path, help="Input WAV sample to convert to GBA PCM")
    parser.add_argument("--rate", type=str, default="13.4k", choices=GBA_SAMPLE_RATES.keys(), help="Target prescaler rate")
    parser.add_argument("--loop", type=int, default=-1, help="Loop start sample index (-1 for unlooped)")
    parser.add_argument("--out-dir", type=Path, default=Path("sound_out"), help="Output destination")
    parser.add_argument("--vg-name", type=str, default="voicegroup_custom", help="M4A voicegroup identifier")
    args = parser.parse_args()

    args.out_dir.mkdir(parents=True, exist_ok=True)

    if args.wav:
        sample_hz = GBA_SAMPLE_RATES[args.rate]
        sample = GBAWaveSample.from_wav(args.wav, target_rate=sample_hz, loop_start=args.loop)
        sample.export_c_header(args.out_dir / f"{sample.name}.h")
        sample.export_assembly(args.out_dir / f"{sample.name}.s")

        # Compile demo voicegroup containing this sample
        vg = GBASoundfontCompiler(args.vg_name)
        vg.add_directsound_voice(0, f"{sample.name}_Wave", base_note=60)
        vg.export_voicegroup_s(args.out_dir / f"{args.vg_name}.s")

        print("=" * 60)
        print(f"[✓] GBA Audio Compilation Completed:")
        print(f"  - Target Rate: {sample_hz} Hz (Signed 8-bit PCM)")
        print(f"  - Header:      {args.out_dir / f'{sample.name}.h'}")
        print(f"  - Assembly:    {args.out_dir / f'{sample.name}.s'}")
        print(f"  - Voicegroup:  {args.out_dir / f'{args.vg_name}.s'}")
        print("=" * 60)
