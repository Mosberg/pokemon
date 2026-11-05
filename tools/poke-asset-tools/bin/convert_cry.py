#!/usr/bin/env python3
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
convert_cry.py - Batch Pokémon Cry Resampler and GBA PCM Formatter
Converts audio samples into GBA-compatible signed 8-bit mono binary PCM.
"""

import argparse
import math
import struct
from pathlib import Path


def apply_high_pass_filter(samples: list[float], sample_rate: int, cutoff_freq: float = 120.0) -> list[float]:
    """Single-pole high-pass filter to remove DC bias and speaker-damaging sub-bass."""
    rc = 1.0 / (2.0 * math.pi * cutoff_freq)
    dt = 1.0 / sample_rate
    alpha = rc / (rc + dt)

    out = [0.0] * len(samples)
    out[0] = samples[0]
    for i in range(1, len(samples)):
        out[i] = alpha * (out[i - 1] + samples[i] - samples[i - 1])
    return out

def convert_wav_to_cry(
    input_wav: Path,
    output_bin: Path,
    target_rate: int = 13379,
    gain_db: float = 0.0,
    trim_silence: bool = True
):
    with open(input_wav, "rb") as f:
        riff = f.read(12)
        if riff[:4] != b"RIFF" or riff[8:] != b"WAVE":
            raise ValueError(f"Invalid WAV file: {input_wav}")

        audio_fmt, channels, orig_rate, bits_per_sample = 1, 1, 44100, 16
        raw_pcm = b""

        while True:
            chunk = f.read(8)
            if len(chunk) < 8:
                break
            c_id, c_sz = struct.unpack("<4sI", chunk)
            if c_id == b"fmt ":
                fmt_buf = f.read(c_sz)
                audio_fmt, channels, orig_rate, _, _, bits_per_sample = struct.unpack("<HHIIHH", fmt_buf[:16])
            elif c_id == b"data":
                raw_pcm = f.read(c_sz)
                break
            else:
                f.seek(c_sz, 1)

    if audio_fmt != 1:
        raise ValueError("Only uncompressed Linear PCM WAV is supported.")

    # Read to float mono (-1.0 to 1.0)
    b_sz = bits_per_sample // 8
    total_samples = len(raw_pcm) // (b_sz * channels)
    samples = []

    for i in range(total_samples):
        offset = i * b_sz * channels
        acc = 0.0
        for c in range(channels):
            co = offset + (c * b_sz)
            if bits_per_sample == 16:
                val = struct.unpack("<h", raw_pcm[co:co+2])[0] / 32768.0
            elif bits_per_sample == 8:
                val = (raw_pcm[co] - 128) / 128.0
            elif bits_per_sample == 24:
                b = raw_pcm[co:co+3]
                val = struct.unpack("<i", b + (b"\xff" if b[2] & 0x80 else b"\x00"))[0] / 8388608.0
            else:
                val = 0.0
            acc += val
        samples.append(acc / channels)

    # Trim leading/trailing silence below -42 dB
    if trim_silence and len(samples) > 0:
        threshold = 0.008
        start_idx = 0
        while start_idx < len(samples) and abs(samples[start_idx]) < threshold:
            start_idx += 1
        end_idx = len(samples) - 1
        while end_idx > start_idx and abs(samples[end_idx]) < threshold:
            end_idx -= 1
        samples = samples[start_idx:end_idx + 1]

    # Linear Sinc Resampling
    out_len = int(round(len(samples) * (target_rate / orig_rate)))
    resampled = []
    ratio = orig_rate / target_rate
    for i in range(out_len):
        pos = i * ratio
        idx = int(pos)
        frac = pos - idx
        if idx + 1 < len(samples):
            v = samples[idx] * (1.0 - frac) + samples[idx + 1] * frac
        elif idx < len(samples):
            v = samples[idx]
        else:
            v = 0.0
        resampled.append(v)

    # Filter low-end rumble
    resampled = apply_high_pass_filter(resampled, target_rate, cutoff_freq=100.0)

    # Apply gain and limiter
    linear_gain = 10.0 ** (gain_db / 20.0)
    out_bytes = bytearray()
    for s in resampled:
        s_gained = s * linear_gain
        # Soft-knee peak limiting
        if s_gained > 1.0:
            s_gained = 1.0
        elif s_gained < -1.0:
            s_gained = -1.0
        # Convert to signed 8-bit (-128 to 127)
        s8_val = int(round(s_gained * 127.0))
        s8_val = max(-128, min(127, s8_val))
        out_bytes.append(s8_val & 0xFF)

    output_bin.parent.mkdir(parents=True, exist_ok=True)
    output_bin.write_bytes(out_bytes)

    mon_name = output_bin.stem
    c_snippet = f"""
// --- Append to sound/direct_sound_data.inc ---
    .align 2
gCry_{mon_name}::
    .incbin "{output_bin.as_posix()}"

// --- Append to src/data/pokemon_graphics/cry_tables.h ---
// In gCryTable:
    [SPECIES_{mon_name.upper()}] = {{
        .wave = (const struct WaveData *)gCry_{mon_name},
        .size = {len(out_bytes)},
        .freq = {target_rate * 1024},
    }},
"""
    (output_bin.with_suffix(".txt")).write_text(c_snippet)

    print(f"[✓] Cry Converted: {output_bin} ({len(out_bytes)} bytes @ {target_rate} Hz)")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert WAV cries to GBA signed 8-bit mono PCM.")
    parser.add_argument("wav_file", type=Path, help="Input raw cry WAV file")
    parser.add_argument("out_bin", type=Path, help="Output destination (e.g., sound/direct_sound_samples/cries/mon.bin)")
    parser.add_argument("--rate", type=int, default=13379, help="GBA sample rate (default: 13379 Hz)")
    parser.add_argument("--gain", type=float, default=1.5, help="Gain in decibels (dB)")
    args = parser.parse_args()

    convert_wav_to_cry(args.wav_file, args.out_bin, args.rate, args.gain)
