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
gba_save_analyzer.py - GBA Pokemon Save & RTC State Inspection/Validation Engine
Validates CRC checksums, extracts active slot, inspects save counters,
and decodes in-game RTC timer structures.
"""

import argparse
import struct
import sys
from pathlib import Path

SAVE_MAGIC = 0x08012025
SECTOR_SIZE = 4096
SECTORS_PER_SLOT = 14
SLOT_SIZE = SECTOR_SIZE * SECTORS_PER_SLOT  # 57,344 bytes (0xE000)

SECTOR_NAMES = {
    0: "Trainer Info",
    1: "Team / Items",
    2: "Game State / Flags",
    3: "Misc Data",
    4: "Rival Info",
    5: "PC Buffer A",
    6: "PC Buffer B",
    7: "PC Buffer C",
    8: "PC Buffer D",
    9: "PC Buffer E",
    10: "PC Buffer F",
    11: "PC Buffer G",
    12: "PC Buffer H",
    13: "PC Buffer I"
}

def calculate_sector_checksum(data: bytes, sector_id: int) -> int:
    """Computes the 16-bit additive checksum of a 4KB save sector."""
    # Data length depends on sector ID
    data_length = 3968 if sector_id != 13 else 2000
    words = struct.unpack(f"<{data_length // 4}I", data[:data_length])
    checksum = sum(words)
    # Fold 32-bit sum into 16 bits: upper 16 + lower 16
    checksum = (checksum >> 16) + (checksum & 0xFFFF)
    return (checksum >> 16) + (checksum & 0xFFFF) & 0xFFFF

def parse_slot(data: bytes, offset: int, slot_name: str):
    sectors = {}
    valid_sectors = 0
    save_counter = 0

    for i in range(SECTORS_PER_SLOT):
        sec_offset = offset + (i * SECTOR_SIZE)
        sec_bytes = data[sec_offset:sec_offset + SECTOR_SIZE]

        # Read footer (last 12 bytes)
        sec_id, stored_csum, magic, counter = struct.unpack("<HHII", sec_bytes[0x0FF4:0x1000])

        if magic != SAVE_MAGIC:
            continue

        calc_csum = calculate_sector_checksum(sec_bytes, sec_id)
        is_valid = (calc_csum == stored_csum)

        if is_valid:
            valid_sectors += 1
            save_counter = max(save_counter, counter)

        sectors[sec_id] = {
            "index": i,
            "valid": is_valid,
            "calc_csum": calc_csum,
            "stored_csum": stored_csum,
            "counter": counter,
            "data": sec_bytes,
        }

    return {
        "name": slot_name,
        "offset": hex(offset),
        "valid_sectors": valid_sectors,
        "save_counter": save_counter,
        "sectors": sectors,
    }


def decode_trainer_info(sec0_data: bytes):
    """Decodes Player Name, Trainer ID, Secret ID, and Playtime from Sector 0."""
    raw_name = sec0_data[0x0000:0x0007]
    # Simple ASCII / Gen 3 Char map translation
    name = "".join([chr(b) if 32 <= b <= 126 else "?" for b in raw_name])
    gender = "Female" if sec0_data[0x0008] == 1 else "Male"
    trainer_id, secret_id = struct.unpack("<HH", sec0_data[0x000A:0x000E])

    # Playtime: Hours (2 bytes), Minutes (1 byte), Seconds (1 byte), VBlanks (1 byte)
    hours, minutes, seconds, vblanks = struct.unpack("<HBBB", sec0_data[0x000E:0x0013])

    return {
        "player_name": name.strip(),
        "gender": gender,
        "trainer_id": trainer_id,
        "secret_id": secret_id,
        "playtime": f"{hours:02d}:{minutes:02d}:{seconds:02d} (VBlanks: {vblanks})",
    }


def decode_rtc(sec0_data: bytes, sec2_data: bytes):
    """Decodes RTC calibration and elapsed time tracking."""
    # Sector 0 contains RTC initial time and offsets in Emerald/Ruby/Sapphire
    # LocalTime offset at 0x0098 in Emerald Sector 0
    days, hours, minutes, seconds = struct.unpack("<HHHH", sec0_data[0x0098:0x00A0])

    return {
        "rtc_days": days,
        "rtc_time": f"{hours:02d}:{minutes:02d}:{seconds:02d}",
        "raw_hex": sec0_data[0x0098:0x00A0].hex()
    }

def analyze_save(filepath: Path):
    raw = filepath.read_bytes()
    if len(raw) not in (131072, 65536):
        raise ValueError(f"Invalid file size ({len(raw)} bytes). Expected 128KB (Flash 1Mbit) or 64KB.")

    slot_a = parse_slot(raw, 0x00000, "Slot A")
    slot_b = parse_slot(raw, 0x0E000, "Slot B")

    active_slot = slot_a if slot_a["save_counter"] >= slot_b["save_counter"] else slot_b
    if active_slot["valid_sectors"] < 14:
        # Fallback to the other slot if the higher one is corrupt
        fallback = slot_b if active_slot == slot_a else slot_a
        if fallback["valid_sectors"] > active_slot["valid_sectors"]:
            active_slot = fallback

    print("=" * 65)
    print(f"GBA POKEMON SAVE ANALYSIS: {filepath.name}")
    print("=" * 65)
    print(f"Slot A Save Counter: {slot_a['save_counter']:<10} (Valid Sectors: {slot_a['valid_sectors']}/14)")
    print(f"Slot B Save Counter: {slot_b['save_counter']:<10} (Valid Sectors: {slot_b['valid_sectors']}/14)")
    print(f"Active Selected:     {active_slot['name']} @ {active_slot['offset']}")
    print("-" * 65)

    if 0 in active_slot["sectors"] and active_slot["sectors"][0]["valid"]:
        sec0 = active_slot["sectors"][0]["data"]
        trainer = decode_trainer_info(sec0)
        print(f"Trainer Name:        {trainer['player_name']}")
        print(f"Gender:              {trainer['gender']}")
        print(f"Trainer ID (TID):    {trainer['trainer_id']:05d} (Secret ID: {trainer['secret_id']:05d})")
        print(f"In-Game Playtime:    {trainer['playtime']}")

        sec2 = active_slot["sectors"].get(2, {}).get("data", b"")
        rtc = decode_rtc(sec0, sec2)
        print(f"RTC Elapsed Days:    {rtc['rtc_days']}")
        print(f"RTC Clock Time:      {rtc['rtc_time']}")
    else:
        print("[!] Sector 0 is corrupted or invalid in active slot.")

    print("\nSector Health Matrix:")
    print(f"{'ID':<3} | {'Name':<18} | {'Calc CSUM':<10} | {'Stored CSUM':<11} | {'Status'}")
    print("-" * 65)
    for s_id in range(14):
        s_name = SECTOR_NAMES.get(s_id, "Unknown")
        if s_id in active_slot["sectors"]:
            sec = active_slot["sectors"][s_id]
            stat = "PASS" if sec["valid"] else "FAIL (CORRUPT)"
            print(f"{s_id:<3} | {s_name:<18} | 0x{sec['calc_csum']:04X}     | 0x{sec['stored_csum']:04X}      | {stat}")
        else:
            print(f"{s_id:<3} | {s_name:<18} | {'MISSING':<10} | {'MISSING':<11} | FAIL")
    print("=" * 65)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Analyze, validate checksums, and extract RTC data from GBA .sav files.")
    parser.add_argument("save_file", type=Path, help="Path to 128KB Flash save file")
    args = parser.parse_args()
    analyze_save(args.save_file)
