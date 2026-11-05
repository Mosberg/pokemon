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

def generate_shadow(size: str = "medium") -> Image.Image:
    """Generates standard GBA oval drop shadows (16x8 or 32x8)."""
    w, h = (32, 8) if size == "medium" else (16, 8)
    arr = np.zeros((h, w), dtype=np.uint8)

    cx, cy = (w - 1) / 2.0, (h - 1) / 2.0
    rx, ry = w / 2.0 - 1.0, h / 2.0 - 1.0

    for y in range(h):
        for x in range(w):
            norm_dist = ((x - cx) / rx) ** 2 + ((y - cy) / ry) ** 2
            if norm_dist <= 0.60:
                arr[y, x] = 2  # Solid inner shadow
            elif norm_dist <= 1.0:
                # Checkerboard dither on outer edge to simulate alpha on GBA hardware
                if (x + y) % 2 == 0:
                    arr[y, x] = 1  # Dither shadow
                else:
                    arr[y, x] = 0

    # Palette: 0=Key (Magenta), 1=Outer Dither, 2=Core Shadow
    pal = [255, 0, 255,  80, 80, 96,  32, 32, 48]
    while len(pal) < 768:
        pal.extend([0, 0, 0])

    img = Image.fromarray(arr, mode="P")
    img.putpalette(pal)
    return img

def build_reflection_sheet(sheet_path: Path, output_path: Path, frame_w=16, frame_h=32):
    src = Image.open(sheet_path).convert("RGBA")
    w, h = src.size

    cols = w // frame_w
    rows = h // frame_h

    # Canvas for water reflection (same width, half height per frame)
    ref_h = frame_h // 2
    out_img = Image.new("RGBA", (w, rows * ref_h), (0, 0, 0, 0))

    src_arr = np.array(src)

    for r in range(rows):
        for c in range(cols):
            # Crop lower half of the frame (legs/torso)
            box = (c * frame_w, r * frame_h + ref_h, (c + 1) * frame_w, (r + 1) * frame_h)
            frame_bottom = src.crop(box)

            # 1. Flip vertically
            flipped = frame_bottom.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            f_arr = np.array(flipped).astype(float)

            # 2. Apply underwater color matrix: Tint towards cyan/navy and soften opacity
            mask = f_arr[:, :, 3] >= 128
            f_arr[mask, 0] = f_arr[mask, 0] * 0.40          # Red attenuation
            f_arr[mask, 1] = f_arr[mask, 1] * 0.70 + 30.0   # Green tint
            f_arr[mask, 2] = f_arr[mask, 2] * 0.90 + 60.0   # Blue boost
            f_arr[mask, 3] = 160.0                          # Alpha blending baseline

            res_frame = Image.fromarray(np.clip(f_arr, 0, 255).astype(np.uint8), "RGBA")
            out_img.paste(res_frame, (c * frame_w, r * ref_h))

    # Quantize to 16 colors indexed for GBA OAM/tile insertion
    vis = np.array(out_img)[np.array(out_img)[:, :, 3] >= 128][:, :3]
    temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    pal = [255, 0, 255]
    for i in range(0, 45, 3):
        pal.extend([raw_pal[i], raw_pal[i+1], raw_pal[i+2]])
    while len(pal) < 768:
        pal.extend([0, 0, 0])

    # Build indexed result
    out_idx = np.array(q) + 1
    out_idx[np.array(out_img)[:, :, 3] < 128] = 0
    final_ref = Image.fromarray(out_idx.astype(np.uint8), mode="P")
    final_ref.putpalette(pal)
    final_ref.save(output_path)
    print(f"[✓] Reflection sheet saved to: {output_path} ({w}x{rows * ref_h} px)")

def process_ow_effects(sheet_path: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # 1. Reflections
    build_reflection_sheet(sheet_path, output_dir / "water_reflections.png")

    # 2. Shadow Sprites
    sh_sm = generate_shadow("small")
    sh_sm.save(output_dir / "shadow_small.png")
    sh_med = generate_shadow("medium")
    sh_med.save(output_dir / "shadow_medium.png")
    print(f"[✓] GBA Shadow assets generated: shadow_small.png (16x8), shadow_medium.png (32x8)")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate water reflection sheets and shadow sprites for GBA overworlds.")
    parser.add_argument("sheet", type=Path, help="Overworld walk cycle sprite sheet")
    parser.add_argument("output_dir", type=Path, help="Output directory for generated effects")
    args = parser.parse_args()

    process_ow_effects(args.sheet, args.output_dir)
