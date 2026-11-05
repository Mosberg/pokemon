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

import argparse
import json
from pathlib import Path
from PIL import Image
import numpy as np

def build_porymap_tileset(
    metatile_sheet_path: Path,
    master_pal_path: Path,
    dest_dir: Path,
    tileset_name: str,
    is_secondary: bool = False
):
    dest_dir.mkdir(parents=True, exist_ok=True)
    pal_dir = dest_dir / "palettes"
    pal_dir.mkdir(exist_ok=True)

    sheet = Image.open(metatile_sheet_path)
    if sheet.mode != "P":
        raise ValueError("Metatile sheet must be an indexed PNG (mode P).")

    # 1. Distribute palettes (Porymap requires separate 16-color JASC .pal files)
    raw_pal = sheet.getpalette()
    if master_pal_path and master_pal_path.exists():
        # Read JASC-PAL lines
        lines = [l.strip() for l in master_pal_path.read_text().splitlines() if l.strip()]
        total_colors = int(lines[2])
        all_colors = []
        for l in lines[3:3+total_colors]:
            p = [int(v) for v in l.split()]
            all_colors.append((p[0], p[1], p[2]))
    else:
        all_colors = [(raw_pal[i], raw_pal[i+1], raw_pal[i+2]) for i in range(0, min(len(raw_pal), 768), 3)]

    # Slice into 16 discrete palettes (each 16 colors)
    pal_count = 16
    for pal_idx in range(pal_count):
        sub_colors = all_colors[pal_idx*16:(pal_idx+1)*16]
        while len(sub_colors) < 16:
            sub_colors.append((0, 0, 0))
        
        jasc = ["JASC-PAL", "0100", "16"]
        for r, g, b in sub_colors:
            jasc.append(f"{r} {g} {b}")
        (pal_dir / f"{pal_idx:02d}.pal").write_text("\n".join(jasc) + "\n")

    # 2. Extract 8x8 tiles and compile metatiles.bin
    sheet_arr = np.array(sheet)
    h, w = sheet_arr.shape
    metatiles_x = w // 16
    metatiles_y = h // 16
    total_metatiles = metatiles_x * metatiles_y

    tiles_list = []
    metatiles_bin = bytearray()
    metatile_attr_bin = bytearray()

    for my in range(metatiles_y):
        for mx in range(metatiles_x):
            # A 16x16 metatile consists of four 8x8 quadrants: Top-Left, Top-Right, Bottom-Left, Bottom-Right
            sub_boxes = [
                (mx*16, my*16),       # TL
                (mx*16 + 8, my*16),   # TR
                (mx*16, my*16 + 8),   # BL
                (mx*16 + 8, my*16 + 8)# BR
            ]

            # Bottom layer: 4 tiles
            for sx, sy in sub_boxes:
                tile_data = sheet_arr[sy:sy+8, sx:sx+8]
                
                # Check tile list for index matching
                tile_bytes = tile_data.tobytes()
                found_id = -1
                for idx, existing in enumerate(tiles_list):
                    if existing == tile_bytes:
                        found_id = idx
                        break
                if found_id == -1:
                    found_id = len(tiles_list)
                    tiles_list.append(tile_bytes)

                # Determine palette ID from the first non-zero pixel
                non_zero = tile_data[tile_data != 0]
                active_color = non_zero[0] if len(non_zero) > 0 else 0
                pal_id = min(active_color // 16, 15)
                tile_idx = found_id % 16

                # 16-bit Metatile entry format:
                # bits 0-9: Tile Index, bit 10: X-flip, bit 11: Y-flip, bits 12-15: Palette Index
                entry = (found_id & 0x3FF) | ((pal_id & 0x0F) << 12)
                metatiles_bin.extend(int(entry).to_bytes(2, byteorder="little"))

            # Top layer: 4 transparent empty tiles (0x0000)
            for _ in range(4):
                metatiles_bin.extend((0).to_bytes(2, byteorder="little"))

            # Attributes: 32-bit field (behavior byte + layer/encounter flags)
            # 0x00 = Passable normal ground
            metatile_attr_bin.extend((0).to_bytes(4, byteorder="little"))

    # 3. Save tiles.png (arranged 16 tiles wide)
    cols = 16
    rows = (len(tiles_list) + cols - 1) // cols
    out_tiles_arr = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for idx, t_bytes in enumerate(tiles_list):
        t_arr = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (idx % cols) * 8
        cy = (idx // cols) * 8
        out_tiles_arr[cy:cy+8, cx:cx+8] = t_arr

    out_tiles_img = Image.fromarray(out_tiles_arr, mode="P")
    out_tiles_img.putpalette(raw_pal)
    out_tiles_img.save(dest_dir / "tiles.png")

    # 4. Write binary metadata
    (dest_dir / "metatiles.bin").write_bytes(metatiles_bin)
    (dest_dir / "metatile_attributes.bin").write_bytes(metatile_attr_bin)

    # 5. Write tileset.json for Porymap
    tileset_json = {
        "id": f"gTileset_{tileset_name}",
        "name": tileset_name,
        "is_secondary": is_secondary,
        "padding": 0
    }
    (dest_dir / "tileset.json").write_text(json.dumps(tileset_json, indent=2))

    print(f"[✓] Created Porymap tileset '{tileset_name}' in: {dest_dir}")
    print(f"    - Metatiles created: {total_metatiles}")
    print(f"    - Unique 8x8 tiles: {len(tiles_list)}")
    print(f"    - Palettes saved: 16 individual files")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package indexed metatiles into a complete Porymap tileset.")
    parser.add_argument("metatile_sheet", type=Path, help="Indexed PNG of 16x16 metatiles")
    parser.add_argument("dest_dir", type=Path, help="Destination directory (e.g. data/tilesets/primary/general)")
    parser.add_argument("--name", type=str, required=True, help="Tileset identifier (e.g. General or Petalburg)")
    parser.add_argument("--master-pal", type=Path, default=None, help="Optional 256-color JASC .pal file")
    parser.add_argument("--secondary", action="store_true", help="Flag as a secondary tileset")
    args = parser.parse_args()

    build_porymap_tileset(args.metatile_sheet, args.master_pal, args.dest_dir, args.name, args.secondary)
