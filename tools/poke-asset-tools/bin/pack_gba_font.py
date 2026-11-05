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
from pathlib import Path

import numpy as np
from PIL import Image


def pack_font_sheet(
    font_png: Path,
    output_dir: Path,
    cell_w: int = 8,
    cell_h: int = 16,
    bpp: int = 1,
    start_char: int = 32,  # ASCII 32 = Space
    tracking_padding: int = 1,
):
    output_dir.mkdir(parents=True, exist_ok=True)
    img = Image.open(font_png).convert("RGBA")
    w, h = img.size

    cols = w // cell_w
    rows = h // cell_h
    total_glyphs = cols * rows

    img_arr = np.array(img)
    alpha = img_arr[:, :, 3]
    rgb = img_arr[:, :, :3]

    glyph_bin = bytearray()
    glyph_widths = []

    for idx in range(total_glyphs):
        col = idx % cols
        row = idx // cols

        box = alpha[row * cell_h : (row + 1) * cell_h, col * cell_w : (col + 1) * cell_w]

        # Calculate visual glyph width
        active_cols = np.where(box >= 128)[1]
        if len(active_cols) == 0:
            # Space or blank character
            char_width = cell_w // 2 if (idx + start_char) == 32 else 0
        else:
            min_col = np.min(active_cols)
            max_col = np.max(active_cols)
            # Width is furthest ink pixel plus spacing
            char_width = min(cell_w, int(max_col + 1 + tracking_padding))

        glyph_widths.append(char_width)

        # Pack pixels into bitstreams (1bpp or 2bpp)
        if bpp == 1:
            for y in range(cell_h):
                row_bits = 0
                for x in range(cell_w):
                    is_ink = 1 if box[y, x] >= 128 else 0
                    row_bits |= is_ink << (7 - x)
                glyph_bin.append(row_bits)
        elif bpp == 2:
            # 2bpp allows 4 levels (anti-aliased font)
            lum = 0.299 * rgb[:, :, 0] + 0.587 * rgb[:, :, 1] + 0.114 * rgb[:, :, 2]
            cell_lum = lum[row * cell_h : (row + 1) * cell_h, col * cell_w : (col + 1) * cell_w]

            for y in range(cell_h):
                for x_pair in range(0, cell_w, 4):
                    byte_val = 0
                    for px in range(4):
                        x = x_pair + px
                        if box[y, x] < 128:
                            color_idx = 0
                        else:
                            # Map brightness to 1, 2, or 3
                            l = cell_lum[y, x]
                            color_idx = 1 if l < 85 else (2 if l < 170 else 3)
                        byte_val |= (color_idx << (px * 2))
                    glyph_bin.append(byte_val)

    # Save packed glyph binary
    bin_path = output_dir / f"font_{bpp}bpp.bin"
    bin_path.write_bytes(glyph_bin)

    # Write C widths array
    c_out = [
        "// Variable Width Font (VWF) Metrics",
        f"// Total Glyphs: {total_glyphs}, Bounding Cell: {cell_w}x{cell_h} px",
        f"const u8 gFontWidthTable_{cell_w}x{cell_h}[{total_glyphs}] = {{",
    ]
    for i in range(0, total_glyphs, 16):
        batch = [f"{w:2d}" for w in glyph_widths[i:i+16]]
        c_out.append("    " + ", ".join(batch) + ",")
    c_out.append("};\n")

    c_file = output_dir / f"font_widths_{cell_w}x{cell_h}.h"
    c_file.write_text("\n".join(c_out))

    print("=" * 60)
    print(f"[✓] Font Processed: {font_png.name}")
    print(f"  - Extracted:   {total_glyphs} glyphs ({cell_w}x{cell_h} cell, {bpp}bpp)")
    print(f"  - Glyph Data:  {bin_path} ({len(glyph_bin)} bytes)")
    print(f"  - Width Table: {c_file}")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Pack font bitmap into GBA 1bpp/2bpp binary and emit VWF width tables.")
    parser.add_argument("font_png", type=Path, help="Bitmap containing font grid")
    parser.add_argument("output_dir", type=Path, help="Destination directory (e.g., graphics/fonts/)")
    parser.add_argument("--width", type=int, default=8, help="Character cell width in pixels")
    parser.add_argument("--height", type=int, default=16, help="Character cell height in pixels")
    parser.add_argument("--bpp", type=int, choices=[1, 2], default=1, help="Bits per pixel (1 or 2)")
    args = parser.parse_args()

    pack_font_sheet(args.font_png, args.output_dir, args.width, args.height, args.bpp)
