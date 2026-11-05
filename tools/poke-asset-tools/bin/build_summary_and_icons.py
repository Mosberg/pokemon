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

# Standard Gen 3 Pokémon Party Box Icon Palettes (15-bit BGR555 native values)
GEN3_ICON_PALETTES = [
    # Palette 0: Normal / Grass / Bug / Neutral
    [(255, 0, 255), (128, 128, 128), (248, 248, 248), (32, 32, 32),
     (80, 168, 72), (136, 216, 128), (200, 120, 88), (248, 192, 160),
     (168, 56, 56), (232, 120, 120), (120, 80, 56), (184, 144, 112),
     (80, 112, 168), (136, 168, 224), (224, 208, 72), (248, 240, 152)],
    # Palette 1: Fire / Fighting / Electric
    [(255, 0, 255), (128, 128, 128), (248, 248, 248), (32, 32, 32),
     (208, 64, 48), (248, 136, 120), (224, 136, 40), (248, 192, 112),
     (176, 40, 40), (240, 104, 88), (144, 88, 32), (216, 160, 88),
     (112, 80, 160), (168, 136, 216), (232, 200, 32), (248, 232, 120)],
    # Palette 2: Water / Ice / Psychic / Dark
    [(255, 0, 255), (128, 128, 128), (248, 248, 248), (32, 32, 32),
     (48, 104, 208), (120, 168, 248), (64, 168, 160), (144, 224, 216),
     (136, 48, 160), (200, 120, 224), (72, 72, 120), (128, 128, 184),
     (160, 56, 80), (224, 120, 144), (224, 192, 64), (248, 232, 144)]
]

def map_to_palette(img: Image.Image, pal_idx: int) -> Image.Image:
    """Maps RGBA image directly to a selected Gen 3 icon palette."""
    palette = GEN3_ICON_PALETTES[pal_idx]
    pal_arr = np.array(palette[1:])  # 15 colors
    
    arr = np.array(img.convert("RGBA"))
    h, w = arr.shape[:2]
    alpha = arr[:, :, 3]
    rgb = arr[:, :, :3]
    
    out_arr = np.zeros((h, w), dtype=np.uint8)
    for y in range(h):
        for x in range(w):
            if alpha[y, x] < 128:
                out_arr[y, x] = 0
            else:
                dist = np.sum((pal_arr - rgb[y, x]) ** 2, axis=1)
                out_arr[y, x] = np.argmin(dist) + 1

    pal_buf = []
    for c in palette:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    res = Image.fromarray(out_arr, mode="P")
    res.putpalette(pal_buf)
    return res

def build_party_icon_sheet(icon_path: Path, output_path: Path, pal_idx: int = 0):
    icon = Image.open(icon_path).convert("RGBA").resize((32, 32), Image.Resampling.LANCZOS)
    
    # Frame 0: Standard position
    f0 = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
    f0.paste(icon, (0, 0))

    # Frame 1: Jump bounce (shifted up 2 pixels and slightly compressed horizontally)
    f1 = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
    bounced = icon.crop((0, 2, 32, 32))  # Shift up
    f1.paste(bounced, (0, 0))

    # Assemble 64x32 horizontal strip
    strip = Image.new("RGBA", (64, 32), (0, 0, 0, 0))
    strip.paste(f0, (0, 0))
    strip.paste(f1, (32, 0))

    final_icon = map_to_palette(strip, pal_idx)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    final_icon.save(output_path)
    print(f"[✓] Party icon sheet saved: {output_path} (64x32 px, Palette {pal_idx})")

def process_summary_screen(screen_path: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    screen = Image.open(screen_path).convert("RGBA").resize((240, 160), Image.Resampling.LANCZOS)

    # 1. Quantize background to 16 colors (Slot 0 = #FF00FF)
    arr = np.array(screen)
    vis = arr[arr[:, :, 3] >= 128][:, :3]
    temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    pal = [255, 0, 255]
    for i in range(0, 45, 3):
        pal.extend([raw_pal[i], raw_pal[i+1], raw_pal[i+2]])
    while len(pal) < 768:
        pal.extend([0, 0, 0])

    indexed_bg = Image.fromarray(np.array(q) + 1, mode="P")
    indexed_bg.putpalette(pal)
    indexed_bg.save(output_dir / "summary_bg_full.png")

    # 2. Slicing into 8x8 Tiles & Binary Tilemap
    bg_arr = np.array(indexed_bg)
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

    cols = 16
    rows = (len(tile_list) + cols - 1) // cols
    tile_sheet = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for i, t_bytes in enumerate(tile_list):
        t_arr = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (i % cols) * 8
        cy = (i // cols) * 8
        tile_sheet[cy:cy+8, cx:cx+8] = t_arr

    dedup_img = Image.fromarray(tile_sheet, mode="P")
    dedup_img.putpalette(pal)
    dedup_img.save(output_dir / "summary_tiles.png")

    map_bin = bytearray()
    for t_id in tilemap:
        map_bin.extend(int(t_id & 0x3FF).to_bytes(2, byteorder="little"))
    (output_dir / "summary_tilemap.bin").write_bytes(map_bin)

    print("=" * 60)
    print(f"[✓] Summary Screen Processed into: {output_dir}")
    print(f"  - Tiles Deduped: {len(tile_list)} / 600 total (summary_tiles.png)")
    print(f"  - Binary Tilemap: 30x20 entries (summary_tilemap.bin)")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package summary screen backgrounds and party icon jump animations.")
    subparsers = parser.add_subparsers(dest="mode", required=True)

    # Subcommand: Icon
    parser_icon = subparsers.add_parser("icon", help="Generate jumping party box icon sheet")
    parser_icon.add_argument("src", type=Path, help="Single 32x32 party icon PNG")
    parser_icon.add_argument("out", type=Path, help="Output destination for 64x32 sheet")
    parser_icon.add_argument("--palette", type=int, choices=[0, 1, 2], default=0, help="Gen 3 Icon Palette ID (0=Grass/Norm, 1=Fire, 2=Water)")

    # Subcommand: Summary Screen
    parser_sum = subparsers.add_parser("summary", help="Slice 240x160 summary screen into tiles and tilemap")
    parser_sum.add_argument("src", type=Path, help="Full 240x160 summary screen PNG")
    parser_sum.add_argument("out_dir", type=Path, help="Output directory")

    args = parser.parse_args()

    if args.mode == "icon":
        build_party_icon_sheet(args.src, args.out, args.palette)
    elif args.mode == "summary":
        process_summary_screen(args.src, args.out_dir)
