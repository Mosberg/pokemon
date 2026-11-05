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
verify_map_matrix.py - Porymap / pokeemerald Map Layout & Elevation Verifier.
Validates metatile collisions, Z-height elevation boundaries, and warp coordinates.
"""

import json
import struct
import argparse
from pathlib import Path

# Standard Gen 3 Metatile Collision & Behavior Flags
COLLISION_PASSABLE = 0x00
COLLISION_SOLID    = 0x01

# Standard Gen 3 Overworld Elevation Levels
ELEVATION_ANY      = 0  # Ignores height checks (e.g. ladders)
ELEVATION_SURF     = 1  # Water body
ELEVATION_GROUND   = 3  # Standard walking layer
ELEVATION_BRIDGE   = 4  # Overhead walkable bridge

def verify_map_layout(
    map_dir: Path,
    layouts_json: Path,
    all_maps_dir: Path = None,
    strict_elevation: bool = True
):
    map_json_path = map_dir / "map.json"
    if not map_json_path.exists():
        raise FileNotFoundError(f"Missing map.json in: {map_dir}")

    map_meta = json.loads(map_json_path.read_text())
    layout_id = map_meta.get("layout")
    
    # Locate layout metrics in layouts.json
    all_layouts = json.loads(layouts_json.read_text()).get("layouts", [])
    layout_data = next((l for l in all_layouts if l.get("id") == layout_id), None)
    if not layout_data:
        raise ValueError(f"Layout ID '{layout_id}' not found in {layouts_json}")

    width = layout_data["width"]
    height = layout_data["height"]
    blockdata_path = Path(layout_data["blockdata_filepath"])
    
    # Resolve relative path if needed
    if not blockdata_path.exists():
        blockdata_path = layouts_json.parent / blockdata_path

    raw_blocks = blockdata_path.read_bytes()
    expected_size = width * height * 2
    if len(raw_blocks) < expected_size:
        raise ValueError(f"Corrupted blockdata: expected {expected_size} bytes, found {len(raw_blocks)}")

    # Unpack 16-bit metatile entries: bits 0-9: Metatile ID, bits 10-11: Collision, bits 12-15: Elevation
    metatile_grid = []
    collision_grid = []
    elevation_grid = []

    for y in range(height):
        row_meta = []
        row_coll = []
        row_elev = []
        for x in range(width):
            idx = (y * width + x) * 2
            val = struct.unpack("<H", raw_blocks[idx:idx+2])[0]
            tile_id = val & 0x03FF
            collision = (val >> 10) & 0x03
            elevation = (val >> 12) & 0x0F

            row_meta.append(tile_id)
            row_coll.append(collision)
            row_elev.append(elevation)
        metatile_grid.append(row_meta)
        collision_grid.append(row_coll)
        elevation_grid.append(row_elev)

    issues = []

    # 1. Audit Warp Targets and Spawns
    warps = map_meta.get("warp_events", [])
    for w_idx, w in enumerate(warps):
        wx, wy = w.get("x", 0), w.get("y", 0)
        elev = w.get("elevation", 0)
        dest_map = w.get("dest_map", "NONE")
        dest_warp = w.get("dest_warp_id", 0)

        # Check bounds
        if not (0 <= wx < width and 0 <= wy < height):
            issues.append(f"[WARP #{w_idx}] Coordinate ({wx}, {wy}) falls outside map bounds ({width}x{height}).")
            continue

        tile_coll = collision_grid[wy][wx]
        tile_elev = elevation_grid[wy][wx]

        # Check solid spawn softlock
        if tile_coll == COLLISION_SOLID:
            issues.append(f"[WARP #{w_idx}] Softlock Risk: Warp placed on solid barrier at ({wx}, {wy}).")

        # Check elevation mismatch
        if elev != 0 and tile_elev != 0 and elev != tile_elev:
            issues.append(f"[WARP #{w_idx}] Elevation Mismatch at ({wx}, {wy}): Warp specifies Z={elev}, metatile has Z={tile_elev}.")

    # 2. Audit Adjacency Elevation Transitions
    if strict_elevation:
        for y in range(height):
            for x in range(width):
                c_now = collision_grid[y][x]
                e_now = elevation_grid[y][x]

                if c_now == COLLISION_SOLID or e_now == ELEVATION_ANY:
                    continue

                # Check horizontal and vertical neighbors
                for dx, dy in [(1, 0), (0, 1)]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < width and 0 <= ny < height:
                        c_next = collision_grid[ny][nx]
                        e_next = elevation_grid[ny][nx]

                        if c_next == COLLISION_SOLID or e_next == ELEVATION_ANY:
                            continue

                        # Disjoint elevation stepping (e.g. stepping between Ground [3] and Bridge [4] without ramp [0])
                        if abs(e_now - e_next) > 0 and e_now != 0 and e_next != 0:
                            if not ((e_now == 3 and e_next == 1) or (e_now == 1 and e_next == 3)): # Surf boundary exception
                                issues.append(
                                    f"[ELEVATION DISCONTINUITY] Tile ({x}, {y}) [Z={e_now}] connects to ({nx}, {ny}) [Z={e_next}] without transition buffer."
                                )

    # Output Validation Report
    print("=" * 70)
    print(f"MAP COLLISION & MATRIX AUDIT: {map_dir.name} (Layout: {layout_id})")
    print(f"Dimensions: {width}x{height} metatiles | Warps: {len(warps)}")
    print(f"Status:     {'FAILED' if issues else 'PASSED'}")
    print("=" * 70)

    if issues:
        print(f"[!] Discovered {len(issues)} structural issues:")
        for iss in issues:
            print(f"  - {iss}")
        return False

    print("[✓] Zero warp softlocks, boundary overflows, or elevation anomalies found.")
    return True

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Audit Porymap map layouts for collision and elevation softlocks.")
    parser.add_argument("map_dir", type=Path, help="Target map directory (containing map.json)")
    parser.add_argument("layouts_json", type=Path, help="Path to layouts.json")
    parser.add_argument("--lax-elevation", action="store_true", help="Suppress elevation step warnings")
    args = parser.parse_args()

    success = verify_map_layout(args.map_dir, args.layouts_json, strict_elevation=not args.lax_elevation)
    sys.exit(0 if success else 1)
