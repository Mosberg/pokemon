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
pokedex_asset_tool.py - Pokédex Footprint & Height Scale Silhouette Builder
Converts raw line art into 16x16 1bpp footprints and builds height-comparison assets.
"""

import argparse
from pathlib import Path

import numpy as np
from PIL import Image


def generate_footprint(input_path: Path, output_png: Path):
    """Processes paw/foot line art into a 16x16 4bpp footprint image with slot 0 transparency."""
    img = Image.open(input_path).convert("RGBA").resize((16, 16), Image.Resampling.LANCZOS)
    arr = np.array(img)
    alpha = arr[:, :, 3]
    lum = 0.299 * arr[:, :, 0] + 0.587 * arr[:, :, 1] + 0.114 * arr[:, :, 2]

    # Footprints in Gen 3 use black/dark gray ink with transparent background
    out_arr = np.zeros((16, 16), dtype=np.uint8)
    for y in range(16):
        for x in range(16):
            if alpha[y, x] >= 128 and lum[y, x] < 180:
                out_arr[y, x] = 1  # Solid footprint ink
            else:
                out_arr[y, x] = 0  # Transparent

    pal = [255, 0, 255, 48, 48, 56]  # Slot 0 = Key, Slot 1 = Ink
    while len(pal) < 768:
        pal.extend([0, 0, 0])

    res = Image.fromarray(out_arr, mode="P")
    res.putpalette(pal)
    output_png.parent.mkdir(parents=True, exist_ok=True)
    res.save(output_png)

    # Also emit raw 1bpp packed binary (32 bytes total for 16x16)
    bin_bytes = bytearray()
    for y in range(16):
        row_val = 0
        for x in range(16):
            if out_arr[y, x] == 1:
                row_val |= 1 << (15 - x)
        bin_bytes.extend(int(row_val).to_bytes(2, byteorder="big"))

    (output_png.with_suffix(".1bpp")).write_bytes(bin_bytes)
    print(f"[✓] Footprint generated: {output_png} (and {output_png.with_suffix('.1bpp')})")


def build_height_comparison(mon_front: Path, output_png: Path, height_dm: int):
    """
    Builds a 136x80 Pokédex scale view.
    Human reference = 1.4m (14 dm) = 56 pixels tall on the screen.
    Ratio = 4.0 pixels per decimeter.
    """
    CANVAS_W, CANVAS_H = 136, 80
    GROUND_Y = 70
    canvas = Image.new("RGBA", (CANVAS_W, CANVAS_H), (0, 0, 0, 0))

    # 1. Render Human Reference Silhouette (1.4m = 56px)
    human_w, human_h = 24, 56
    human_sil = Image.new("RGBA", (human_w, human_h), (80, 112, 160, 255))
    canvas.paste(human_sil, (20, GROUND_Y - human_h))

    # 2. Render Scaled Pokémon Silhouette
    mon_img = Image.open(mon_front).convert("RGBA")
    target_px_h = int(round(height_dm * 4.0))
    target_px_h = max(8, min(target_px_h, 64))  # Clamped to GBA screen limits

    # Preserve aspect ratio
    aspect = mon_img.width / mon_img.height
    target_px_w = int(round(target_px_h * aspect))

    mon_scaled = mon_img.resize((target_px_w, target_px_h), Image.Resampling.LANCZOS)

    # Convert Pokémon into a solid amber Pokédex silhouette
    mon_arr = np.array(mon_scaled)
    mask = mon_arr[:, :, 3] >= 128
    sil_arr = np.zeros_like(mon_arr)
    sil_arr[mask] = [208, 120, 48, 255] # Pokédex Orange Silhouette
    mon_sil = Image.fromarray(sil_arr, "RGBA")

    canvas.paste(mon_sil, (64, GROUND_Y - target_px_h), mask=mon_sil)

    # 3. Draw baseline ground indicator
    c_arr = np.array(canvas)
    c_arr[GROUND_Y:GROUND_Y+2, :, :] = [160, 160, 160, 255]

    # Quantize to 16-color Pokédex palette
    res = Image.fromarray(c_arr, "RGBA").convert("RGB").quantize(colors=15)
    raw_pal = res.getpalette()[:45]
    pal = [255, 0, 255] + raw_pal
    while len(pal) < 768:
        pal.extend([0, 0, 0])

    out_p = Image.fromarray(np.array(res) + 1, mode="P")
    out_p.putpalette(pal)
    output_png.parent.mkdir(parents=True, exist_ok=True)
    out_p.save(output_png)

    print(f"[✓] Pokédex height scale comparison saved: {output_png} ({height_dm / 10.0}m)")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Build Pokédex footprints and scale comparison silhouettes.")
    subparsers = parser.add_subparsers(dest="mode", required=True)

    # Footprint mode
    p_foot = subparsers.add_parser("footprint", help="Generate 16x16 footprint")
    p_foot.add_argument("src", type=Path, help="Paw/Foot line art PNG")
    p_foot.add_argument("dest", type=Path, help="Target footprint.png destination")

    # Scale mode
    p_scale = subparsers.add_parser("scale", help="Generate 136x80 scale view")
    p_scale.add_argument("front", type=Path, help="Front sprite PNG")
    p_scale.add_argument("dest", type=Path, help="Target scale silhouette destination")
    p_scale.add_argument("--height-dm", type=int, required=True, help="Height in decimeters (e.g. 17 for 1.7m)")

    args = parser.parse_args()

    if args.mode == "footprint":
        generate_footprint(args.src, args.dest)
    elif args.mode == "scale":
        build_height_comparison(args.front, args.dest, args.height_dm)
