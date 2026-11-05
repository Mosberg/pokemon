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

import sys
from pathlib import Path
from PIL import Image
import numpy as np

def to_gba_color(rgb):
    """Clamps 8-bit RGB down to 5-bit channel depth (GBA 15-bit)."""
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb)

def load_or_create_shared_palette(source_images, colors=15):
    """Builds a shared 15-color palette from a batch of images using k-means/median cut."""
    combined_pixels = []
    for path in source_images:
        img = Image.open(path).convert("RGBA")
        np_img = np.array(img)
        visible = np_img[np_img[:, :, 3] >= 128][:, :3]
        if len(visible) > 0:
            combined_pixels.append(visible)

    all_vis = np.vstack(combined_pixels)
    temp_img = Image.fromarray(all_vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp_img.quantize(colors=colors, method=Image.Quantize.MEDIANCUT)
    raw = q.getpalette()[: colors * 3]

    shared_palette = [to_gba_color(raw[i:i+3]) for i in range(0, len(raw), 3)]
    return shared_palette

def harmonize_image(img_path, output_path, shared_palette):
    """Maps an RGBA sprite to a fixed shared 16-color palette (index 0 = transparency)."""
    img = Image.open(img_path).convert("RGBA")
    np_img = np.array(img)
    alpha = np_img[:, :, 3]
    rgb = np_img[:, :, :3]

    h, w, _ = rgb.shape
    out_indices = np.zeros((h, w), dtype=np.uint8)

    palette_arr = np.array(shared_palette)  # shape (15, 3)

    for y in range(h):
        for x in range(w):
            if alpha[y, x] < 128:
                out_indices[y, x] = 0
            else:
                pixel = to_gba_color(rgb[y, x])
                # Find nearest color in the shared palette
                distances = np.sum((palette_arr - pixel) ** 2, axis=1)
                best_idx = np.argmin(distances)
                out_indices[y, x] = best_idx + 1  # 1-indexed

    # Construct standard 256-color palette buffer with #FF00FF as slot 0
    full_pal = [255, 0, 255]
    for c in shared_palette:
        full_pal.extend(c)
    while len(full_pal) < 768:
        full_pal.extend([0, 0, 0])

    out_img = Image.fromarray(out_indices, mode="P")
    out_img.putpalette(full_pal)
    out_img.save(output_path, format="PNG")
    print(f"[✓] Harmonized: {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python harmonize_palette.py <output_dir> <image1.png> [image2.png ...]")
        sys.exit(1)

    out_dir = Path(sys.argv[1])
    out_dir.mkdir(parents=True, exist_ok=True)
    src_images = sys.argv[2:]

    print(f"[*] Calculating shared 15-color palette across {len(src_images)} images...")
    master_pal = load_or_create_shared_palette(src_images, colors=15)

    for src in src_images:
        dest = out_dir / Path(src).name
        harmonize_image(src, dest, master_pal)
