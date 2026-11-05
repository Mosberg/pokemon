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
dns_tint_engine.py - 24-Hour Day, Night & Season Palette Transformation Engine
Calculates RGB color curves and exports GBA BGR555 transition tables for pokeemerald.
"""

import argparse
from pathlib import Path

from PIL import Image


def clamp(val, low=0, high=31):
    return max(low, min(high, int(round(val))))


def rgb888_to_bgr555(r, g, b):
    r5 = (r >> 3) & 0x1F
    g5 = (g >> 3) & 0x1F
    b5 = (b >> 3) & 0x1F
    return (b5 << 10) | (g5 << 5) | r5


def bgr555_to_rgb888(bgr):
    r = (bgr & 0x1F) << 3
    g = ((bgr >> 5) & 0x1F) << 3
    b = ((bgr >> 10) & 0x1F) << 3
    return (r, g, b)


# 24-Hour Target Tint Curves (Hourly Multipliers: R_mult, G_mult, B_mult, Brightness_Offset)
HOURLY_PROFILES = [
    # 00:00 - 04:00: Deep Night
    (0.40, 0.45, 0.75, -4),
    (0.38, 0.42, 0.72, -5),
    (0.35, 0.40, 0.70, -5),
    (0.35, 0.40, 0.70, -5),
    (0.42, 0.45, 0.75, -4),
    # 05:00 - 07:00: Dawn / Sunrise Transition
    (0.60, 0.55, 0.80, -2),
    (0.95, 0.70, 0.65, 0),
    (1.10, 0.85, 0.65, 1),
    # 08:00 - 16:00: Neutral Midday
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 1.00, 1.00, 0),
    (1.00, 0.98, 0.95, 0),
    # 17:00 - 19:00: Sunset / Dusk
    (1.15, 0.82, 0.60, 1),
    (1.20, 0.70, 0.55, 0),
    (0.90, 0.55, 0.70, -2),
    # 20:00 - 23:00: Twilight to Night
    (0.65, 0.50, 0.75, -3),
    (0.50, 0.48, 0.75, -4),
    (0.45, 0.45, 0.75, -4),
    (0.40, 0.45, 0.75, -4),
]


def apply_tint(r5: int, g5: int, b5: int, hour: int) -> tuple[int, int, int]:
    """Transforms a 5-bit channel RGB pixel according to the hour profile."""
    r_mult, g_mult, b_mult, offset = HOURLY_PROFILES[hour]

    # Calculate luminance for saturation protection
    lum = 0.299 * r5 + 0.587 * g5 + 0.114 * b5

    new_r = clamp(r5 * r_mult + offset)
    new_g = clamp(g5 * g_mult + offset)
    new_b = clamp(b5 * b_mult + offset)
    return new_r, new_g, new_b

def export_dns_c_lut(output_path: Path):
    """Generates the complete 24-hour C lookup tables for pokeemerald day_night.c."""
    out = [
        "// Auto-generated Day/Night System (DNS) Lookup Table",
        "// Contains 24 hourly color matrices for 5-bit GBA channels (0-31)",
        "#include \"global.h\"",
        "",
        "const u16 gDNSTintTable[24][32] = {"
    ]

    for h in range(24):
        out.append(f"    // Hour {h:02d}:00")
        out.append("    {")
        # Precompute transformation for all 32 channel values (5-bit depth)
        entries = []
        for val in range(32):
            r, _, _ = apply_tint(val, val, val, h)
            entries.append(f"{r:2d}")
        out.append("        " + ", ".join(entries))
        out.append("    },")

    out.append("};\n")
    output_path.write_text("\n".join(out))
    print(f"[✓] Exported DNS C LUT: {output_path}")

def preview_palette_cycle(input_png: Path, output_dir: Path):
    """Renders 24 PNG previews showing how a sprite/tileset looks across every hour."""
    output_dir.mkdir(parents=True, exist_ok=True)
    img = Image.open(input_png).convert("P")
    raw_pal = img.getpalette()

    for hour in range(24):
        tinted_pal = []
        for i in range(0, min(len(raw_pal), 768), 3):
            # Skip slot 0 (transparency key)
            if i == 0:
                tinted_pal.extend(raw_pal[0:3])
                continue

            r5 = raw_pal[i] >> 3
            g5 = raw_pal[i+1] >> 3
            b5 = raw_pal[i+2] >> 3

            tr, tg, tb = apply_tint(r5, g5, b5, hour)
            tinted_pal.extend([tr << 3, tg << 3, tb << 3])

        hour_img = img.copy()
        hour_img.putpalette(tinted_pal)
        hour_img.save(output_dir / f"hour_{hour:02d}.png")

    print(f"[✓] Generated 24 hourly preview renders in: {output_dir}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="GBA Day/Night System (DNS) Palette Engine.")
    parser.add_argument("--export-lut", type=Path, help="Export C lookup array (e.g., day_night_lut.h)")
    parser.add_argument("--preview-img", type=Path, help="Indexed PNG to preview across 24 hours")
    parser.add_argument("--preview-out", type=Path, default=Path("dns_preview"), help="Preview output folder")
    args = parser.parse_args()

    if args.export_lut:
        export_dns_c_lut(args.export_lut)
    if args.preview_img:
        preview_palette_cycle(args.preview_img, args.preview_out)
