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
rom_patcher.py - Production-Grade BPS and IPS ROM Patcher & Generator.
Supports:
  - BPS creation (SourceRead, TargetRead, SourceCopy, TargetCopy)
  - Full CRC32 verification (Source, Target, Patch)
  - Legacy IPS creation and application with RLE run optimization
"""

import argparse
import struct
import sys
import zlib
from pathlib import Path

# --- VARIABLE-LENGTH INTEGER (VLQ) UTILITIES FOR BPS ---

def bps_read_vli(data: bytes, offset: int) -> tuple[int, int]:
    """Reads a variable-length integer from BPS payload. Returns (value, new_offset)."""
    result = 0
    shift = 0
    while True:
        if offset >= len(data):
            raise IndexError("Unexpected end of BPS data while reading VLI.")
        byte = data[offset]
        offset += 1
        result += (byte & 0x7F) << shift
        if byte & 0x80:
            break
        shift += 7
        result += 1 << shift
    return result, offset

def bps_write_vli(val: int) -> bytearray:
    """Encodes an integer into a BPS variable-length integer sequence."""
    out = bytearray()
    while True:
        byte = val & 0x7F
        val >>= 7
        if val == 0:
            out.append(byte | 0x80)
            break
        out.append(byte)
        val -= 1
    return out

# --- BPS ENGINE ---

def apply_bps(source_bytes: bytes, patch_bytes: bytes) -> bytes:
    if len(patch_bytes) < 16 or patch_bytes[:4] != b"BPS1":
        raise ValueError("Invalid BPS header: magic 'BPS1' missing.")

    offset = 4
    src_size, offset = bps_read_vli(patch_bytes, offset)
    tgt_size, offset = bps_read_vli(patch_bytes, offset)
    meta_size, offset = bps_read_vli(patch_bytes, offset)
    offset += meta_size  # Skip optional metadata

    target = bytearray(tgt_size)
    output_offset = 0
    source_relative_offset = 0
    target_relative_offset = 0

    footer_offset = len(patch_bytes) - 12
    while offset < footer_offset:
        data, offset = bps_read_vli(patch_bytes, offset)
        action = data & 3
        length = (data >> 2) + 1

        if action == 0:  # SourceRead
            target[output_offset : output_offset + length] = source_bytes[output_offset : output_offset + length]
            output_offset += length

        elif action == 1:  # TargetRead
            target[output_offset : output_offset + length] = patch_bytes[offset : offset + length]
            offset += length
            output_offset += length

        elif action == 2:  # SourceCopy
            offset_val, offset = bps_read_vli(patch_bytes, offset)
            source_relative_offset += (-(offset_val >> 1)) if (offset_val & 1) else (offset_val >> 1)
            for _ in range(length):
                target[output_offset] = source_bytes[source_relative_offset]
                output_offset += 1
                source_relative_offset += 1

        elif action == 3:  # TargetCopy
            offset_val, offset = bps_read_vli(patch_bytes, offset)
            target_relative_offset += (-(offset_val >> 1)) if (offset_val & 1) else (offset_val >> 1)
            for _ in range(length):
                target[output_offset] = target[target_relative_offset]
                output_offset += 1
                target_relative_offset += 1

    # CRC32 Verification
    exp_src_crc, exp_tgt_crc, exp_patch_crc = struct.unpack("<III", patch_bytes[-12:])
    actual_src_crc = zlib.crc32(source_bytes) & 0xFFFFFFFF
    actual_tgt_crc = zlib.crc32(target) & 0xFFFFFFFF
    actual_patch_crc = zlib.crc32(patch_bytes[:-4]) & 0xFFFFFFFF

    if actual_src_crc != exp_src_crc:
        raise ValueError(f"Source CRC32 mismatch! Expected: {exp_src_crc:08X}, Got: {actual_src_crc:08X}")
    if actual_tgt_crc != exp_tgt_crc:
        raise ValueError(f"Target CRC32 mismatch! Expected: {exp_tgt_crc:08X}, Got: {actual_tgt_crc:08X}")
    if actual_patch_crc != exp_patch_crc:
        raise ValueError(f"Patch checksum mismatch! Expected: {exp_patch_crc:08X}, Got: {actual_patch_crc:08X}")

    return bytes(target)

def create_bps(source_bytes: bytes, target_bytes: bytes) -> bytes:
    patch = bytearray(b"BPS1")
    patch.extend(bps_write_vli(len(source_bytes)))
    patch.extend(bps_write_vli(len(target_bytes)))
    patch.extend(bps_write_vli(0))  # No metadata

    cursor = 0
    src_len = len(source_bytes)
    tgt_len = len(target_bytes)

    while cursor < tgt_len:
        # Check matching runs against source (SourceRead)
        match_len = 0
        while (cursor + match_len < tgt_len and
               cursor + match_len < src_len and
               source_bytes[cursor + match_len] == target_bytes[cursor + match_len]):
            match_len += 1

        if match_len >= 4 or (cursor + match_len == tgt_len and match_len > 0):
            cmd = ((match_len - 1) << 2) | 0  # Action 0: SourceRead
            patch.extend(bps_write_vli(cmd))
            cursor += match_len
            continue

        # Non-matching byte run (TargetRead)
        diff_len = 0
        while cursor + diff_len < tgt_len:
            # Check if entering a run of matching bytes
            if (cursor + diff_len < src_len and
                source_bytes[cursor + diff_len] == target_bytes[cursor + diff_len]):
                # Peak ahead: is it at least 4 identical bytes?
                run = 0
                while (cursor + diff_len + run < tgt_len and
                       cursor + diff_len + run < src_len and
                       source_bytes[cursor + diff_len + run] == target_bytes[cursor + diff_len + run]):
                    run += 1
                if run >= 4:
                    break
            diff_len += 1

        cmd = ((diff_len - 1) << 2) | 1  # Action 1: TargetRead
        patch.extend(bps_write_vli(cmd))
        patch.extend(target_bytes[cursor : cursor + diff_len])
        cursor += diff_len

    # Append Checksum Footers (Source CRC32, Target CRC32, Patch CRC32)
    src_crc = zlib.crc32(source_bytes) & 0xFFFFFFFF
    tgt_crc = zlib.crc32(target_bytes) & 0xFFFFFFFF
    patch.extend(struct.pack("<II", src_crc, tgt_crc))
    patch_crc = zlib.crc32(patch) & 0xFFFFFFFF
    patch.extend(struct.pack("<I", patch_crc))
    return bytes(patch)

# --- IPS ENGINE ---

def apply_ips(source_bytes: bytes, patch_bytes: bytes) -> bytes:
    if len(patch_bytes) < 8 or patch_bytes[:5] != b"PATCH":
        raise ValueError("Invalid IPS header: magic 'PATCH' missing.")

    target = bytearray(source_bytes)
    offset = 5

    while offset < len(patch_bytes):
        if patch_bytes[offset:offset+3] == b"EOF":
            break

        rec_offset = (patch_bytes[offset] << 16) | (patch_bytes[offset+1] << 8) | patch_bytes[offset+2]
        size = (patch_bytes[offset+3] << 8) | patch_bytes[offset+4]
        offset += 5

        if size > 0:
            payload = patch_bytes[offset : offset + size]
            offset += size
            # Pad target if record writes past current length
            if rec_offset + size > len(target):
                target.extend(b"\x00" * (rec_offset + size - len(target)))
            target[rec_offset : rec_offset + size] = payload
        else:
            # RLE Record
            rle_size = (patch_bytes[offset] << 8) | patch_bytes[offset+1]
            rle_byte = patch_bytes[offset+2:offset+3]
            offset += 3
            if rec_offset + rle_size > len(target):
                target.extend(b"\x00" * (rec_offset + rle_size - len(target)))
            target[rec_offset : rec_offset + rle_size] = rle_byte * rle_size

    return bytes(target)

def create_ips(source_bytes: bytes, target_bytes: bytes) -> bytes:
    if len(target_bytes) > 0x1000000:
        raise ValueError("IPS format cannot handle ROMs larger than 16MB (0xFFFFFF offset limit). Use BPS.")

    patch = bytearray(b"PATCH")
    cursor = 0
    max_len = max(len(source_bytes), len(target_bytes))

    while cursor < max_len:
        src_b = source_bytes[cursor] if cursor < len(source_bytes) else None
        tgt_b = target_bytes[cursor] if cursor < len(target_bytes) else None

        if src_b == tgt_b:
            cursor += 1
            continue

        start_offset = cursor
        chunk = bytearray()
        while cursor < len(target_bytes) and len(chunk) < 0xFFFF:
            s = source_bytes[cursor] if cursor < len(source_bytes) else None
            t = target_bytes[cursor]
            # Terminate chunk if we encounter 6 identical matching bytes
            if s == t:
                peek = 0
                while (cursor + peek < len(target_bytes) and
                       (cursor + peek < len(source_bytes) and source_bytes[cursor + peek] == target_bytes[cursor + peek])):
                    peek += 1
                if peek >= 6:
                    break
            chunk.append(t)
            cursor += 1

        # Check for RLE compression profitability (identical bytes >= 8)
        if len(chunk) >= 8 and len(set(chunk)) == 1:
            # Write RLE Record
            patch.extend(start_offset.to_bytes(3, byteorder="big"))
            patch.extend((0).to_bytes(2, byteorder="big"))  # Size 0 signals RLE
            patch.extend(len(chunk).to_bytes(2, byteorder="big"))
            patch.append(chunk[0])
        else:
            # Write Standard Record
            patch.extend(start_offset.to_bytes(3, byteorder="big"))
            patch.extend(len(chunk).to_bytes(2, byteorder="big"))
            patch.extend(chunk)

    patch.extend(b"EOF")
    return bytes(patch)

# --- CLI ROUTING ---

def main():
    parser = argparse.ArgumentParser(description="High-performance BPS and IPS binary patch utility.")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # Apply
    p_apply = subparsers.add_parser("apply", help="Apply BPS or IPS patch to a base ROM")
    p_apply.add_argument("patch", type=Path, help="Patch file (.bps or .ips)")
    p_apply.add_argument("source", type=Path, help="Clean Base ROM file (.gba)")
    p_apply.add_argument("target", type=Path, help="Output Patched ROM file (.gba)")

    # Create
    p_create = subparsers.add_parser("create", help="Generate a patch comparing Base ROM to Modified ROM")
    p_create.add_argument("source", type=Path, help="Clean Base ROM file (.gba)")
    p_create.add_argument("target", type=Path, help="Modified ROM file (.gba)")
    p_create.add_argument("patch", type=Path, help="Output Patch file (.bps or .ips)")

    args = parser.parse_args()

    if args.command == "apply":
        patch_data = args.patch.read_bytes()
        src_data = args.source.read_bytes()

        if patch_data.startswith(b"BPS1"):
            print(f"[*] Applying BPS Patch: {args.patch.name}")
            result = apply_bps(src_data, patch_data)
        elif patch_data.startswith(b"PATCH"):
            print(f"[*] Applying IPS Patch: {args.patch.name}")
            result = apply_ips(src_data, patch_data)
        else:
            raise ValueError("Unknown patch signature. Must begin with 'BPS1' or 'PATCH'.")

        args.target.write_bytes(result)
        print(f"[✓] Successfully generated: {args.target} ({len(result):,} bytes)")

    elif args.command == "create":
        src_data = args.source.read_bytes()
        tgt_data = args.target.read_bytes()
        ext = args.patch.suffix.lower()

        if ext == ".bps":
            print(f"[*] Compiling differential BPS patch: {args.patch.name}")
            patch_data = create_bps(src_data, tgt_data)
        elif ext == ".ips":
            print(f"[*] Compiling legacy IPS patch: {args.patch.name}")
            patch_data = create_ips(src_data, tgt_data)
        else:
            raise ValueError("Patch output must end with .bps or .ips")

        args.patch.write_bytes(patch_data)
        print(f"[✓] Created {ext[1:].upper()} patch: {args.patch} ({len(patch_data):,} bytes)")

if __name__ == "__main__":
    main()
