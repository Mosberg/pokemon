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
from pathlib import Path
from PIL import Image
import numpy as np

def quantize_indexed(img: Image.Image, num_colors: int = 15) -> tuple[Image.Image, list]:
    """Quantizes an image to 15 visible colors with slot 0 as transparency key."""
    rgb_img = img.convert("RGB")
    q = rgb_img.quantize(colors=num_colors, method=Image.Quantize.MEDIANCUT)
    raw = q.getpalette()[: num_colors * 3]
    
    pal = [(255, 0, 255)] # Slot 0
    for i in range(0, len(raw), 3):
        pal.append((raw[i], raw[i+1], raw[i+2]))
    
    pal_buf = []
    for c in pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])
        
    out = Image.fromarray(np.array(q) + 1, mode="P")
    out.putpalette(pal_buf)
    return out, pal

def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def process_battle_background(scene_path: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    scene = Image.open(scene_path).convert("RGBA").resize((240, 160), Image.Resampling.LANCZOS)

    # 1. Extract Base Platforms
    # Player base occupies bottom-left: (x: 0-128, y: 112-160)
    # Opponent base occupies top-right: (x: 112-240, y: 48-96)
    player_base_raw = scene.crop((0, 112, 128, 160))
    opp_base_raw = scene.crop((112, 48, 240, 96))

    pb_img, pb_pal = quantize_indexed(player_base_raw, 15)
    pb_img.save(output_dir / "player_base.png")
    write_jasc_pal(output_dir / "player_base.pal", pb_pal)

    ob_img, ob_pal = quantize_indexed(opp_base_raw, 15)
    ob_img.save(output_dir / "opponent_base.png")
    write_jasc_pal(output_dir / "opponent_base.pal", ob_pal)

    # 2. Extract and Deduplicate Main Battle Background (240x160 -> 30x20 8x8 tiles)
    bg_raw = scene.crop((0, 0, 240, 160))
    bg_indexed, bg_pal = quantize_indexed(bg_raw, 15)
    bg_indexed.save(output_dir / "battle_bg_full.png")
    write_jasc_pal(output_dir / "battle_bg.pal", bg_pal)

    # Slicing into 8x8 tiles
    bg_arr = np.array(bg_indexed)
    tile_list = []
    tilemap = []

    for ty in range(20):
        for tx in range(30):
            tile = bg_arr[ty*8:(ty+1)*8, tx*8:(tx+1)*8].tobytes()
            if tile in tile_list:
                tilemap.append(tile_list.index(tile))
            else:
                tilemap.append(len(tile_list))
                tile_list.append(tile)

    # Assemble deduplicated tile sheet (16 tiles wide)
    cols = 16
    rows = (len(tile_list) + cols - 1) // cols
    tiles_sheet = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for i, t_bytes in enumerate(tile_list):
        t_arr = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (i % cols) * 8
        cy = (i // cols) * 8
        tiles_sheet[cy:cy+8, cx:cx+8] = t_arr

    dedup_img = Image.fromarray(tiles_sheet, mode="P")
    dedup_img.putpalette(bg_indexed.getpalette())
    dedup_img.save(output_dir / "battle_bg_tiles.png")

    # Export binary tilemap (30x20 u16 entries)
    map_bytes = bytearray()
    for t_id in tilemap:
        map_bytes.extend(int(t_id & 0x3FF).to_bytes(2, byteorder="little"))
    (output_dir / "battle_bg_tilemap.bin").write_bytes(map_bytes)

    print("=" * 60)
    print(f"[✓] Battle Arena Split Completed: {output_dir}")
    print(f"  - Player Base:    128x48 (saved to player_base.png)")
    print(f"  - Opponent Base:  128x48 (saved to opponent_base.png)")
    print(f"  - Unique BG Tiles: {len(tile_list)} / 600 total (saved to battle_bg_tiles.png)")
    print(f"  - Binary Tilemap: 30x20 entries (saved to battle_bg_tilemap.bin)")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Slice a 240x160 scene into GBA battle background, platforms, and tilemaps.")
    parser.add_argument("scene", type=Path, help="Input 240x160 arena mock image")
    parser.add_argument("output_dir", type=Path, help="Target folder inside graphics/battle_terrain/")
    args = parser.parse_args()

    process_battle_background(args.scene, args.output_dir)
