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

import colorsys
import sys
from pathlib import Path

from PIL import Image


def rgb_to_gba(r, g, b):
    """Clamps to 5 bits per channel."""
    r5 = round(int(r) * 31 / 255)
    g5 = round(int(g) * 31 / 255)
    b5 = round(int(b) * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))


def shift_color_hsv(r, g, b, hue_shift=0.33, sat_mult=1.0, val_mult=1.0):
    """Transforms RGB color by rotating Hue and adjusting Saturation/Value."""
    h, s, v = colorsys.rgb_to_hsv(int(r) / 255.0, int(g) / 255.0, int(b) / 255.0)

    # Apply hue rotation
    h = (h + hue_shift) % 1.0
    s = min(max(s * sat_mult, 0.0), 1.0)
    v = min(max(v * val_mult, 0.0), 1.0)

    r_new, g_new, b_new = colorsys.hsv_to_rgb(h, s, v)
    return rgb_to_gba(int(r_new * 255), int(g_new * 255), int(b_new * 255))


def generate_shiny_palette(
    input_path: str,
    output_pal_path: str,
    hue_shift: float = 0.35,
    sat_scale: float = 1.1,
    preserve_outlines: bool = True,
):
    inp = Path(input_path)

    # Read colors from either an existing JASC .pal or directly from an indexed PNG
    colors = []
    if inp.suffix.lower() == ".pal":
        lines = [line.strip() for line in inp.read_text().splitlines() if line.strip()]
        count = int(lines[2])
        for line in lines[3 : 3 + count]:
            parts = [int(p) for p in line.split()]
            colors.append((parts[0], parts[1], parts[2]))
    else:
        img = Image.open(inp)
        raw_pal = img.getpalette()
        if not raw_pal:
            raise ValueError("Input image has no embedded palette.")
        for i in range(0, 48, 3):
            colors.append((raw_pal[i], raw_pal[i + 1], raw_pal[i + 2]))

    shiny_colors = []

    for idx, (r, g, b) in enumerate(colors[:16]):
        # Index 0 is always transparency: never modify it
        if idx == 0:
            shiny_colors.append((r, g, b))
            continue

        # Optional: Retain dark structural outline colors (luminance threshold)
        luminance = 0.299 * r + 0.587 * g + 0.114 * b
        if preserve_outlines and luminance < 32:
            shiny_colors.append((r, g, b))
            continue

        shiny_rgb = shift_color_hsv(r, g, b, hue_shift, sat_scale)
        shiny_colors.append(shiny_rgb)

    # Write out JASC-PAL compliant format
    out_lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in shiny_colors:
        out_lines.append(f"{r} {g} {b}")

    out_path = Path(output_pal_path)
    out_path.write_text("\n".join(out_lines) + "\n")
    print(f"[✓] Generated shiny palette at: {out_path} (Hue rotation: +{hue_shift:.2f})")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python generate_shiny.py <normal.pal|front.png> <shiny.pal> [hue_shift 0.0-1.0]")
        sys.exit(1)

    shift = float(sys.argv[3]) if len(sys.argv) > 3 else 0.35
    generate_shiny_palette(sys.argv[1], sys.argv[2], hue_shift=shift)
