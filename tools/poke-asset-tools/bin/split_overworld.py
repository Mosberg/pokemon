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

import sys
from pathlib import Path

import numpy as np
from PIL import Image


def split_and_index_sheet(
    sheet_path: str,
    output_dir: str,
    frame_w: int = 16,
    frame_h: int = 32,
    export_strip: bool = True
):
    sheet = Image.open(sheet_path).convert("RGBA")
    total_w, total_h = sheet.size

    cols = total_w // frame_w
    rows = total_h // frame_h
    out_path = Path(output_dir)
    out_path.mkdir(parents=True, exist_ok=True)

    # Global palette quantization for the entire sheet to prevent color drift across frames
    rgb_sheet = Image.new("RGB", sheet.size, (255, 0, 255))
    rgb_sheet.paste(sheet, mask=sheet.split()[3])

    # 15 visible colors + 1 reserved for transparency (Index 0 = #FF00FF)
    quantized = rgb_sheet.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = quantized.getpalette()[:45]
    final_pal = [255, 0, 255] + raw_pal
    while len(final_pal) < 768:
        final_pal.extend([0, 0, 0])

    frames = []
    directions = ["down", "up", "left", "right"]

    for r in range(rows):
        dir_name = directions[r] if r < len(directions) else f"row_{r}"
        for c in range(cols):
            box = (c * frame_w, r * frame_h, (c + 1) * frame_w, (r + 1) * frame_h)
            cropped_rgba = sheet.crop(box)
            cropped_q = quantized.crop(box)

            alpha = np.array(cropped_rgba)[:, :, 3]
            idx_arr = np.array(cropped_q) + 1
            idx_arr[alpha < 128] = 0

            frame_img = Image.fromarray(idx_arr.astype(np.uint8), mode="P")
            frame_img.putpalette(final_pal)

            frame_name = f"{dir_name}_frame_{c}.png"
            frame_img.save(out_path / frame_name)
            frames.append(frame_img)

    # Decomp projects often expect a single horizontal strip per object event
    if export_strip and frames:
        strip = Image.new("P", (frame_w * len(frames), frame_h))
        strip.putpalette(final_pal)
        for i, frame in enumerate(frames):
            strip.paste(frame, (i * frame_w, 0))
        strip.save(out_path / "sheet_decomp_strip.png")
        print(f"[✓] Decomp horizontal strip saved: {out_path / 'sheet_decomp_strip.png'}")

    print(f"[✓] Extracted {len(frames)} frames into: {out_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python split_overworld.py <sheet.png> <output_dir> [frame_w] [frame_h]")
        sys.exit(1)

    fw = int(sys.argv[3]) if len(sys.argv) > 3 else 16
    fh = int(sys.argv[4]) if len(sys.argv) > 4 else 32
    split_and_index_sheet(sys.argv[1], sys.argv[2], fw, fh)
