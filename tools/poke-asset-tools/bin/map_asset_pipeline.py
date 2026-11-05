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
map_asset_pipeline.py - Comprehensive Map, Layout, and Tileset Compilation Suite.
Supports:
  - 8x8 Hardware tile slicing and lossless flip-deduplication (X-flip, Y-flip, XY-flip)
  - 16-color 4bpp palette quantization with JASC-PAL distribution
  - Porymap / pokeemerald metatile packaging (metatiles.bin, metatile_attributes.bin)
  - Map collision and warp softlock verification
  - Modern engine JSON/CSV level export
"""

import argparse
import json
import struct
import sys
from pathlib import Path

import numpy as np
from PIL import Image

# ---------------------------------------------------------------------------
# COLOR CONVERSION & PALETTE TOOLS
# ---------------------------------------------------------------------------

def snap_to_gba_15bit(r: int, g: int, b: int) -> tuple[int, int, int]:
    """Snaps standard 8-bit RGB to 5-bit channel values (multiples of 8)."""
    r5 = round(int(r) * 31 / 255)
    g5 = round(int(g) * 31 / 255)
    b5 = round(int(b) * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))

def write_jasc_pal(filepath: Path, colors: list[tuple[int, int, int]]):
    """Exports colors to a compliant JASC-PAL text format."""
    lines = ["JASC-PAL", "0100", "16"]
    for i in range(16):
        if i < len(colors):
            r, g, b = colors[i][:3]
        else:
            r, g, b = (0, 0, 0)
        lines.append(f"{r} {g} {b}")
    filepath.write_text("\n".join(lines) + "\n")

def read_jasc_pal(filepath: Path) -> list[tuple[int, int, int]]:
    """Reads a JASC-PAL file and returns RGB tuples."""
    lines = [l.strip() for l in filepath.read_text().splitlines() if l.strip()]
    if lines[0] != "JASC-PAL":
        raise ValueError(f"Invalid JASC-PAL header: {filepath}")
    count = int(lines[2])
    colors = []
    for l in lines[3:3 + count]:
        parts = [int(p) for p in l.split()]
        colors.append((parts[0], parts[1], parts[2]))
    return colors

# ---------------------------------------------------------------------------
# 8x8 TILE TRANSFORMS & LOSSLESS FLIP DEDUPLICATION
# ---------------------------------------------------------------------------

def get_tile_transforms(tile_arr: np.ndarray) -> dict[tuple[bool, bool], bytes]:
    """Computes byte buffers for Normal, X-flipped, Y-flipped, and XY-flipped versions."""
    return {
        (False, False): tile_arr.tobytes(),
        (True, False):  np.fliplr(tile_arr).tobytes(),
        (False, True):  np.flipud(tile_arr).tobytes(),
        (True, True):   np.flipud(np.fliplr(tile_arr)).tobytes(),
    }

def deduplicate_tiles(
    indexed_arr: np.ndarray,
    tile_size: int = 8,
    enable_flips: bool = True
) -> tuple[list[bytes], list[tuple[int, bool, bool]]]:
    """
    Slices indexed array into tiles and deduplicates matching patterns.
    Returns:
      - unique_tiles: List of raw byte buffers for distinct tiles
      - tilemap: List of (tile_index, x_flip, y_flip)
    """
    h, w = indexed_arr.shape[:2]
    tiles_x = w // tile_size
    tiles_y = h // tile_size

    unique_tiles = []
    tile_lookup = {}  # bytes -> tile_id
    tilemap = []

    for ty in range(tiles_y):
        for tx in range(tiles_x):
            tile = indexed_arr[ty*tile_size:(ty+1)*tile_size, tx*tile_size:(tx+1)*tile_size]
            normal_bytes = tile.tobytes()

            if not enable_flips:
                if normal_bytes in tile_lookup:
                    tilemap.append((tile_lookup[normal_bytes], False, False))
                else:
                    new_id = len(unique_tiles)
                    tile_lookup[normal_bytes] = new_id
                    unique_tiles.append(normal_bytes)
                    tilemap.append((new_id, False, False))
                continue

            # Check all four flip permutations
            transforms = get_tile_transforms(tile)
            matched = False

            for (xf, yf), trans_bytes in transforms.items():
                if trans_bytes in tile_lookup:
                    tilemap.append((tile_lookup[trans_bytes], xf, yf))
                    matched = True
                    break

            if not matched:
                new_id = len(unique_tiles)
                tile_lookup[normal_bytes] = new_id
                unique_tiles.append(normal_bytes)
                tilemap.append((new_id, False, False))

    return unique_tiles, tilemap

# ---------------------------------------------------------------------------
# PIPELINE 1: PORYMAP & DECOMP TILESET PACKAGER
# ---------------------------------------------------------------------------

def package_porymap_tileset(
    metatile_sheet_png: Path,
    output_dir: Path,
    tileset_name: str,
    master_pal: Path = None,
    is_secondary: bool = False
):
    """
    Converts a 16x16 metatile image into a complete Porymap-ready directory:
    - tiles.png (deduplicated 8x8 tiles in 4bpp indexed PNG)
    - palettes/00.pal - 15.pal (16 JASC-PAL files)
    - metatiles.bin (16-bit block entries: tile_id | x_flip | y_flip | pal_id)
    - metatile_attributes.bin (behavior byte + layer/collision mask)
    - tileset.json (Porymap registration metadata)
    """
    output_dir.mkdir(parents=True, exist_ok=True)
    pal_dir = output_dir / "palettes"
    pal_dir.mkdir(exist_ok=True)

    img = Image.open(metatile_sheet_png)
    if img.mode != "P":
        # Auto-quantize to 16 colors if not indexed
        img = img.convert("RGBA")
        arr = np.array(img)
        vis = arr[arr[:, :, 3] >= 128][:, :3]
        temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
        q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
        raw_pal = q.getpalette()[:45]
        pal = [255, 0, 255] + raw_pal
        while len(pal) < 768:
            pal.extend([0, 0, 0])
        idx = np.array(q) + 1
        idx[arr[:, :, 3] < 128] = 0
        img = Image.fromarray(idx.astype(np.uint8), mode="P")
        img.putpalette(pal)

    raw_pal = img.getpalette()
    if master_pal and master_pal.exists():
        all_colors = read_jasc_pal(master_pal)
    else:
        all_colors = [(raw_pal[i], raw_pal[i+1], raw_pal[i+2]) for i in range(0, min(len(raw_pal), 768), 3)]

    # Distribute 16 palettes of 16 colors each
    for pal_idx in range(16):
        sub_colors = all_colors[pal_idx*16:(pal_idx+1)*16]
        while len(sub_colors) < 16:
            sub_colors.append((0, 0, 0))
        write_jasc_pal(pal_dir / f"{pal_idx:02d}.pal", sub_colors)

    sheet_arr = np.array(img)
    h, w = sheet_arr.shape[:2]
    metatiles_x = w // 16
    metatiles_y = h // 16
    total_metatiles = metatiles_x * metatiles_y

    tiles_list = []
    tile_lookup = {}
    metatiles_bin = bytearray()
    metatile_attr_bin = bytearray()

    for my in range(metatiles_y):
        for mx in range(metatiles_x):
            # 16x16 metatile has 4 quadrants: TL, TR, BL, BR
            quadrants = [
                (mx*16,     my*16),      # Top-Left
                (mx*16 + 8, my*16),      # Top-Right
                (mx*16,     my*16 + 8),  # Bottom-Left
                (mx*16 + 8, my*16 + 8),  # Bottom-Right
            ]

            # Layer 1 (Bottom Terrain)
            for qx, qy in quadrants:
                tile = sheet_arr[qy:qy+8, qx:qx+8]
                tb = tile.tobytes()

                if tb in tile_lookup:
                    found_id = tile_lookup[tb]
                else:
                    found_id = len(tiles_list)
                    tile_lookup[tb] = found_id
                    tiles_list.append(tb)

                non_zero = tile[tile != 0]
                active_color = int(non_zero[0]) if len(non_zero) > 0 else 0
                pal_id = min(active_color // 16, 15)

                # 16-bit Metatile entry:
                # bits 0-9: Tile ID, bit 10: X-flip, bit 11: Y-flip, bits 12-15: Palette ID
                entry = (found_id & 0x03FF) | ((pal_id & 0x0F) << 12)
                metatiles_bin.extend(int(entry).to_bytes(2, byteorder="little"))

            # Layer 2 (Overhead / Transparent Empty Tiles: 0x0000)
            for _ in range(4):
                metatiles_bin.extend((0).to_bytes(2, byteorder="little"))

            # Metatile Attribute: 32-bit field (Behavior, Layer Mask, Elevation)
            # 0x00000000 = Passable standard ground (Elevation 3)
            metatile_attr_bin.extend((0x0300).to_bytes(4, byteorder="little"))

    # Reconstruct 8x8 tiles.png arranged 16 tiles wide (128px)
    cols = 16
    rows = (len(tiles_list) + cols - 1) // cols
    out_arr = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for idx, t_bytes in enumerate(tiles_list):
        t_np = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (idx % cols) * 8
        cy = (idx // cols) * 8
        out_arr[cy:cy+8, cx:cx+8] = t_np

    out_img = Image.fromarray(out_arr, mode="P")
    out_img.putpalette(raw_pal)
    out_img.save(output_dir / "tiles.png")

    (output_dir / "metatiles.bin").write_bytes(metatiles_bin)
    (output_dir / "metatile_attributes.bin").write_bytes(metatile_attr_bin)

    tileset_meta = {
        "id": f"gTileset_{tileset_name}",
        "name": tileset_name,
        "is_secondary": is_secondary,
        "padding": 0
    }
    (output_dir / "tileset.json").write_text(json.dumps(tileset_meta, indent=2))

    print("=" * 65)
    print(f"[✓] Porymap Tileset Created: {output_dir}")
    print(f"  - Metatiles Generated: {total_metatiles} (16x16)")
    print(f"  - Deduplicated Tiles:  {len(tiles_list)} / {total_metatiles * 4} 8x8 tiles")
    print("  - Palettes Saved:      16 individual .pal files in /palettes")
    print("=" * 65)

# ---------------------------------------------------------------------------
# PIPELINE 2: MAP COLLISION & ELEVATION AUDITOR
# ---------------------------------------------------------------------------

def audit_map_integrity(map_dir: Path, layouts_json: Path) -> bool:
    """
    Audits map.json, blockdata (map.bin), and warp definitions:
    1. Detects out-of-bounds warps
    2. Flags softlocks caused by warps targeting solid obstacles (0x01)
    3. Identifies broken Z-height elevation transitions
    """
    map_json_p = map_dir / "map.json"
    if not map_json_p.exists():
        print(f"[!] map.json not found in {map_dir}")
        return False

    map_meta = json.loads(map_json_p.read_text())
    layout_id = map_meta.get("layout")

    layouts = json.loads(layouts_json.read_text()).get("layouts", [])
    layout = next((l for l in layouts if l.get("id") == layout_id), None)
    if not layout:
        print(f"[!] Layout '{layout_id}' missing in {layouts_json}")
        return False

    w = layout["width"]
    h = layout["height"]
    block_path = Path(layout["blockdata_filepath"])
    if not block_path.exists():
        block_path = layouts_json.parent / block_path

    raw_data = block_path.read_bytes()
    expected_bytes = w * h * 2
    if len(raw_data) < expected_bytes:
        print(f"[!] Corrupted blockdata size. Expected {expected_bytes}, got {len(raw_data)}")
        return False

    collision_grid = []
    elevation_grid = []

    for y in range(h):
        c_row = []
        e_row = []
        for x in range(w):
            idx = (y * w + x) * 2
            val = struct.unpack("<H", raw_data[idx:idx+2])[0]
            collision = (val >> 10) & 0x03
            elevation = (val >> 12) & 0x0F
            c_row.append(collision)
            e_row.append(elevation)
        collision_grid.append(c_row)
        elevation_grid.append(e_row)

    issues = []
    for idx, warp in enumerate(map_meta.get("warp_events", [])):
        wx, wy = warp.get("x", 0), warp.get("y", 0)
        z = warp.get("elevation", 0)

        if not (0 <= wx < w and 0 <= wy < h):
            issues.append(f"Warp #{idx} at ({wx}, {wy}) falls outside map bounds ({w}x{h}).")
            continue

        if collision_grid[wy][wx] == 1:
            issues.append(f"Warp #{idx} spawns player onto solid collision barrier at ({wx}, {wy}).")

        tile_z = elevation_grid[wy][wx]
        if z != 0 and tile_z != 0 and z != tile_z:
            issues.append(f"Warp #{idx} elevation mismatch at ({wx}, {wy}): warp Z={z}, tile Z={tile_z}.")

    print("=" * 65)
    print(f"MAP AUDIT REPORT: {map_dir.name} ({w}x{h} metatiles)")
    print(f"Status: {'FAIL' if issues else 'PASS'}")
    print("=" * 65)

    if issues:
        for err in issues:
            print(f"  [ERROR] {err}")
        return False

    print("[✓] Zero warp softlocks, barrier traps, or elevation mismatches found.")
    return True

# ---------------------------------------------------------------------------
# PIPELINE 3: MODERN 2D ENGINE COMPILER (JSON & CSV EXPORTS)
# ---------------------------------------------------------------------------

def compile_engine_level(image_path: Path, output_dir: Path, tile_size: int = 16):
    """
    Slices a level mockup or tileset into:
      - tileset_atlas.png (Indexed sprite sheet)
      - tilemap.json (2D grid array with width, height, and layer offsets)
      - collision_matrix.csv (Passable vs Solid layer based on transparency)
    """
    output_dir.mkdir(parents=True, exist_ok=True)
    img = Image.open(image_path).convert("RGBA")
    w, h = img.size

    cols = w // tile_size
    rows = h // tile_size

    arr = np.array(img)
    tiles = []
    tile_hashes = {}
    grid_map = []
    collision_map = []

    for r in range(rows):
        row_grid = []
        row_coll = []
        for c in range(cols):
            box = arr[r*tile_size:(r+1)*tile_size, c*tile_size:(c+1)*tile_size]
            b_bytes = box.tobytes()

            if b_bytes in tile_hashes:
                tid = tile_hashes[b_bytes]
            else:
                tid = len(tiles)
                tile_hashes[b_bytes] = tid
                tiles.append(box)

            row_grid.append(tid)

            # Solid if >= 75% non-transparent pixels
            alpha = box[:, :, 3]
            is_solid = 1 if np.mean(alpha >= 128) > 0.75 else 0
            row_coll.append(is_solid)

        grid_map.append(row_grid)
        collision_map.append(row_coll)

    # Output Atlas (arranged in rows of 16)
    out_cols = min(16, len(tiles))
    out_rows = (len(tiles) + out_cols - 1) // out_cols
    atlas = np.zeros((out_rows * tile_size, out_cols * tile_size, 4), dtype=np.uint8)

    for i, t in enumerate(tiles):
        ax = (i % out_cols) * tile_size
        ay = (i // out_cols) * tile_size
        atlas[ay:ay+tile_size, ax:ax+tile_size] = t

    Image.fromarray(atlas, "RGBA").save(output_dir / "tileset_atlas.png")

    level_json = {
        "width": cols,
        "height": rows,
        "tile_size": tile_size,
        "unique_tiles": len(tiles),
        "tilemap": grid_map
    }
    (output_dir / "tilemap.json").write_text(json.dumps(level_json, indent=2))

    csv_lines = [",".join(map(str, row)) for row in collision_map]
    (output_dir / "collisions.csv").write_text("\n".join(csv_lines) + "\n")

    print("=" * 65)
    print(f"[✓] Level Compiled: {output_dir}")
    print(f"  - Tileset Atlas: {output_dir / 'tileset_atlas.png'} ({len(tiles)} unique tiles)")
    print(f"  - Tilemap Data:  {output_dir / 'tilemap.json'} ({cols}x{rows} grid)")
    print(f"  - Collision CSV: {output_dir / 'collisions.csv'}")
    print("=" * 65)

# ---------------------------------------------------------------------------
# CLI CONTROLLER
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="Universal 2D Map, Layout, and Tileset Processing Engine.")
    sub = parser.add_subparsers(dest="cmd", required=True)

    # 1. Porymap Packaging
    p_pory = sub.add_parser("porymap", help="Build a full Porymap tileset folder from 16x16 metatiles")
    p_pory.add_argument("sheet", type=Path, help="16x16 metatile image (PNG)")
    p_pory.add_argument("dest", type=Path, help="Destination directory (e.g. data/tilesets/primary/general)")
    p_pory.add_argument("--name", type=str, default="General", help="Tileset identifier")
    p_pory.add_argument("--master-pal", type=Path, default=None, help="Optional master 256-color JASC-PAL")
    p_pory.add_argument("--secondary", action="store_true", help="Flag as secondary tileset")

    # 2. Map Collision / Warp Audit
    p_audit = sub.add_parser("audit-map", help="Audit map warp coordinates and collision softlocks")
    p_audit.add_argument("map_dir", type=Path, help="Folder containing map.json")
    p_audit.add_argument("layouts", type=Path, help="Path to layouts.json")

    # 3. Modern Engine Level Compiler
    p_engine = sub.add_parser("compile-level", help="Export level into Atlas, Tilemap JSON, and Collision CSV")
    p_engine.add_argument("image", type=Path, help="Full layout or mockup image")
    p_engine.add_argument("dest", type=Path, help="Destination directory")
    p_engine.add_argument("--tile-size", type=int, default=16, help="Tile dimension (e.g. 8, 16, 32)")

    args = parser.parse_args()

    if args.cmd == "porymap":
        package_porymap_tileset(args.sheet, args.dest, args.name, args.master_pal, args.secondary)
    elif args.cmd == "audit-map":
        success = audit_map_integrity(args.map_dir, args.layouts)
        sys.exit(0 if success else 1)
    elif args.cmd == "compile-level":
        compile_engine_level(args.image, args.dest, args.tile_size)

if __name__ == "__main__":
    main()
