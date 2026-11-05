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

import argparse
import json
from pathlib import Path

import numpy as np
from PIL import Image


def to_gba_color(rgb):
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb[:3])

def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def package_region_map(map_image: Path, cursor_image: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    map_raw = Image.open(map_image).convert("RGBA").resize((240, 160), Image.Resampling.LANCZOS)

    # 1. Quantize Background to 16 Colors (Slot 0 = #FF00FF)
    arr = np.array(map_raw)
    vis = arr[arr[:, :, 3] >= 128][:, :3]
    temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    master_pal = [(255, 0, 255)] + [to_gba_color(raw_pal[i : i + 3]) for i in range(0, 45, 3)]
    write_jasc_pal(output_dir / "region_map.pal", master_pal)

    pal_buf = []
    for c in master_pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    indexed_map = Image.fromarray(np.array(q) + 1, mode="P")
    indexed_map.putpalette(pal_buf)

    # 2. Slice and Deduplicate 8x8 Tiles (30x20 tile grid)
    map_arr = np.array(indexed_map)
    tile_list = []
    tilemap = []

    for ty in range(20):
        for tx in range(30):
            tile = map_arr[ty * 8 : (ty + 1) * 8, tx * 8 : (tx + 1) * 8].tobytes()
            if tile in tile_list:
                tilemap.append(tile_list.index(tile))
            else:
                tilemap.append(len(tile_list))
                tile_list.append(tile)

    cols = 16
    rows = (len(tile_list) + cols - 1) // cols
    tile_sheet = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for i, t_bytes in enumerate(tile_list):
        t_arr = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (i % cols) * 8
        cy = (i // cols) * 8
        tile_sheet[cy : cy + 8, cx : cx + 8] = t_arr

    dedup_img = Image.fromarray(tile_sheet, mode="P")
    dedup_img.putpalette(pal_buf)
    dedup_img.save(output_dir / "region_map_tiles.png")

    # Save 30x20 tilemap (16-bit entries)
    map_bin = bytearray()
    for t_id in tilemap:
        map_bin.extend(int(t_id & 0x3FF).to_bytes(2, byteorder="little"))
    (output_dir / "region_map_tilemap.bin").write_bytes(map_bin)

    # 3. Process 16x16 Cursor / Player Head Sprite
    cursor_raw = Image.open(cursor_image).convert("RGBA").resize((16, 16), Image.Resampling.LANCZOS)
    c_arr = np.array(cursor_raw)
    c_alpha = c_arr[:, :, 3]
    c_rgb = c_arr[:, :, :3]

    pal_arr = np.array(master_pal[1:])
    c_idx = np.zeros((16, 16), dtype=np.uint8)

    for y in range(16):
        for x in range(16):
            if c_alpha[y, x] < 128:
                c_idx[y, x] = 0
            else:
                px = to_gba_color(c_rgb[y, x])
                dist = np.sum((pal_arr - px) ** 2, axis=1)
                c_idx[y, x] = np.argmin(dist) + 1

    cursor_img = Image.fromarray(c_idx, mode="P")
    cursor_img.putpalette(pal_buf)
    cursor_img.save(output_dir / "map_cursor.png")

    # 4. Generate Default Coordinates Definition Template
    coords_meta = {
        "map_dimensions": {"width_tiles": 30, "height_tiles": 20},
        "landmarks": [
            {"id": "MAPSEC_START_TOWN", "tile_x": 4, "tile_y": 14, "name": "Starting Town"},
            {"id": "MAPSEC_FIRST_CITY", "tile_x": 8, "tile_y": 10, "name": "First Gym City"},
            {"id": "MAPSEC_ROUTE_101",  "tile_x": 4, "tile_y": 12, "name": "Route 101"}
        ]
    }
    (output_dir / "region_map_coords.json").write_text(json.dumps(coords_meta, indent=2))

    print("=" * 60)
    print(f"[✓] Region Map Packaged: {output_dir}")
    print(f"  - Tiles Deduped: {len(tile_list)} / 600 total (region_map_tiles.png)")
    print("  - Tilemap:       30x20 binary (region_map_tilemap.bin)")
    print("  - Cursor:        16x16 sprite (map_cursor.png)")
    print("  - Config:        region_map_coords.json")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package Region Map artwork and cursors for GBA Pokénav / Town Map.")
    parser.add_argument("map_png", type=Path, help="Full 240x160 illustrated region map")
    parser.add_argument("cursor_png", type=Path, help="16x16 player head / cursor icon")
    parser.add_argument("output_dir", type=Path, help="Output destination folder")
    args = parser.parse_args()

    package_region_map(args.map_png, args.cursor_png, args.output_dir)
