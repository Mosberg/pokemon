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
from PIL import Image, ImageSequence
import numpy as np

def to_gba_color(rgb):
    """Clamps 8-bit RGB channels to GBA 15-bit (5-bit depth)."""
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb)

def assemble_animation(input_source: Path, output_png: Path, frame_duration: int = 4):
    frames = []

    # Handle GIF or folder of PNG frames
    if input_source.is_file() and input_source.suffix.lower() == ".gif":
        gif = Image.open(input_source)
        for frame in ImageSequence.Iterator(gif):
            frames.append(frame.convert("RGBA").resize((64, 64), Image.Resampling.LANCZOS))
    elif input_source.is_dir():
        pngs = sorted(input_source.glob("*.png"))
        if not pngs:
            raise FileNotFoundError(f"No PNG frames found in {input_source}")
        for p in pngs:
            frames.append(Image.open(p).convert("RGBA").resize((64, 64), Image.Resampling.LANCZOS))
    else:
        raise ValueError("input_source must be a .gif file or a directory containing .png frames")

    num_frames = len(frames)
    if num_frames == 0:
        raise ValueError("No frames extracted.")

    # 1. Build a unified 15-color palette across all frames
    all_vis_pixels = []
    for f in frames:
        arr = np.array(f)
        vis = arr[arr[:, :, 3] >= 128][:, :3]
        if len(vis) > 0:
            all_vis_pixels.append(vis)

    if not all_vis_pixels:
        raise ValueError("All animation frames are completely transparent.")

    stacked_vis = np.vstack(all_vis_pixels)
    temp_img = Image.fromarray(stacked_vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    quantized = temp_img.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = quantized.getpalette()[:45]

    # Master GBA palette: Index 0 is #FF00FF
    master_palette = [(255, 0, 255)] + [to_gba_color(raw_pal[i:i+3]) for i in range(0, 45, 3)]
    pal_buffer = []
    for c in master_palette:
        pal_buffer.extend(c)
    while len(pal_buffer) < 768:
        pal_buffer.extend([0, 0, 0])

    pal_arr = np.array(master_palette[1:])  # 15 colors, shape (15, 3)

    # 2. Assemble horizontal strip (64 * num_frames x 64)
    strip_w = 64 * num_frames
    strip_arr = np.zeros((64, strip_w), dtype=np.uint8)

    for i, frame in enumerate(frames):
        f_arr = np.array(frame)
        alpha = f_arr[:, :, 3]
        rgb = f_arr[:, :, :3]

        for y in range(64):
            for x in range(64):
                if alpha[y, x] < 128:
                    strip_arr[y, i * 64 + x] = 0
                else:
                    px = to_gba_color(rgb[y, x])
                    dist = np.sum((pal_arr - px) ** 2, axis=1)
                    strip_arr[y, i * 64 + x] = np.argmin(dist) + 1

    out_img = Image.fromarray(strip_arr, mode="P")
    out_img.putpalette(pal_buffer)
    output_png.parent.mkdir(parents=True, exist_ok=True)
    out_img.save(output_png)

    # 3. Generate animation scripts for pokeemerald
    c_anim = [
        "// Animation Frame Array",
        f"static const union AnimCmd sAnim_Front_{output_png.stem}[] = {{",
    ]
    for i in range(num_frames):
        c_anim.append(f"    ANIMCMD_FRAME({i}, {frame_duration}),")
    c_anim.extend([
        "    ANIMCMD_LOOP(0),",
        "};",
        "",
        "static const union AnimCmd *const sAnims_Front[] = {",
        "    sAnim_GeneralFrame0,",
        f"    sAnim_Front_{output_png.stem},",
        "};"
    ])

    c_file = output_png.with_suffix(".txt")
    c_file.write_text("\n".join(c_anim) + "\n")

    print(f"[✓] Created anim strip: {output_png} ({strip_w}x64 px, {num_frames} frames)")
    print(f"[✓] Created anim script: {c_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Assemble frames/GIF into a decomp anim_front.png and C animation script.")
    parser.add_argument("source", type=Path, help="Folder containing frame PNGs or single animated .gif")
    parser.add_argument("output", type=Path, help="Path to save anim_front.png")
    parser.add_argument("--delay", type=int, default=4, help="Frame delay in in-game ticks (default: 4)")
    args = parser.parse_args()

    assemble_animation(args.source, args.output, args.delay)
