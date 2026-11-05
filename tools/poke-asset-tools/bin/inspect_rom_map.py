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
inspect_rom_map.py - Linker Map and GBA Memory Space Inspector.
Parses pokeemerald.map to report memory section occupancy, largest symbols,
and calculate free space headroom.
"""

import argparse
import json
import re
from pathlib import Path

# Hardware Memory Boundaries
GBA_MEMORY_REGIONS = {
    "EWRAM": {"origin": 0x02000000, "length": 256 * 1024, "name": "External Work RAM (256 KB)"},
    "IWRAM": {"origin": 0x03000000, "length": 32 * 1024, "name": "Internal Work RAM (32 KB)"},
    "ROM": {"origin": 0x08000000, "length": 32 * 1024 * 1024, "name": "Game Pak ROM (32 MB)"},
}


def parse_linker_map(map_path: Path):
    content = map_path.read_text(errors="replace")

    # 1. Parse memory configuration table
    # Example format:
    # ewram            0x02000000      0x40000
    # iwram            0x03000000       0x8000
    # rom              0x08000000    0x2000000
    sections = {}

    # Track current section placements
    # Regex matches symbol definitions: address size file object symbol
    # 0x08001234  0x120  src/battle.o  BattleMain
    sym_regex = re.compile(r"^\s+(0x[0-9a-fA-F]{8})\s+(0x[0-9a-fA-F]+)\s+(.+?)(?:\s+([a-zA-Z0-9_]+))?$", re.MULTILINE)

    symbols = []
    for match in sym_regex.finditer(content):
        addr_str, size_str, obj_file, sym_name = match.groups()
        addr = int(addr_str, 16)
        size = int(size_str, 16)
        if size > 0 and sym_name:
            symbols.append({"name": sym_name, "address": addr, "size": size, "object": obj_file.strip()})

    # Determine region consumption by scanning .text, .data, .bss, .rodata
    region_usage = {}
    for r_name, r_info in GBA_MEMORY_REGIONS.items():
        r_start = r_info["origin"]
        r_end = r_start + r_info["length"]

        region_syms = [s for s in symbols if r_start <= s["address"] < r_end]
        allocated = sum(s["size"] for s in region_syms)

        # Calculate max address reached
        max_addr = max([s["address"] + s["size"] for s in region_syms], default=r_start)
        actual_used = max_addr - r_start
        free_space = r_info["length"] - actual_used

        region_usage[r_name] = {
            "name": r_info["name"],
            "total_bytes": r_info["length"],
            "used_bytes": actual_used,
            "free_bytes": free_space,
            "percent_used": (actual_used / r_info["length"]) * 100.0,
            "symbols_count": len(region_syms),
        }

    return region_usage, symbols


def generate_report(map_path: Path, top_n: int = 15, export_json: Path = None):
    region_usage, symbols = parse_linker_map(map_path)

    print("=" * 75)
    print(f"GBA LINKER MEMORY MAP INSPECTOR: {map_path.name}")
    print("=" * 75)
    print(f"{'Memory Region':<28} | {'Used':<10} | {'Total':<10} | {'Free':<10} | {'Usage'}")
    print("-" * 75)

    for r_name, stats in region_usage.items():
        used_k = (
            f"{stats['used_bytes'] / 1024:.1f} KB"
            if stats["used_bytes"] < 1024 * 1024
            else f"{stats['used_bytes'] / (1024 * 1024):.2f} MB"
        )
        total_k = (
            f"{stats['total_bytes'] / 1024:.0f} KB"
            if stats["total_bytes"] < 1024 * 1024
            else f"{stats['total_bytes'] / (1024 * 1024):.0f} MB"
        )
        free_k = (
            f"{stats['free_bytes'] / 1024:.1f} KB"
            if stats["free_bytes"] < 1024 * 1024
            else f"{stats['free_bytes'] / (1024 * 1024):.2f} MB"
        )

        flag = " [!] CRITICAL" if stats["percent_used"] > 95.0 else ""
        print(
            f"{stats['name']:<28} | {used_k:<10} | {total_k:<10} | {free_k:<10} | {stats['percent_used']:6.2f}%{flag}"
        )

    print("-" * 75)

    # Top largest symbols
    print(f"\nTop {top_n} Largest Symbols in ROM:")
    print(f"{'Symbol Name':<35} | {'Address':<10} | {'Size (Bytes)':<12} | {'Object File'}")
    print("-" * 75)

    sorted_syms = sorted(symbols, key=lambda s: s["size"], reverse=True)
    for sym in sorted_syms[:top_n]:
        print(f"{sym['name'][:34]:<35} | 0x{sym['address']:08X} | {sym['size']:<12} | {sym['object']}")

    print("=" * 75)

    if export_json:
        export_data = {
            "regions": region_usage,
            "top_symbols": sorted_syms[:100]
        }
        export_json.write_text(json.dumps(export_data, indent=2))
        print(f"[✓] Exported map diagnostics to: {export_json}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Parse GBA decomp linker map files and audit memory allocation.")
    parser.add_argument("map_file", type=Path, help="Path to pokeemerald.map")
    parser.add_argument("--top", type=int, default=15, help="Number of largest symbols to display")
    parser.add_argument("--json", type=Path, default=None, help="Export metrics to JSON file")
    args = parser.parse_args()

    generate_report(args.map_file, args.top, args.json)
