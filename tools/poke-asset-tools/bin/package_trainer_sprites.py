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

def to_gba_color(r, g, b):
    r5 = round(int(r) * 31 / 255)
    g5 = round(int(g) * 31 / 255)
    b5 = round(int(b) * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))

def quantize_trainer_frame(img: Image.Image, fixed_pal=None):
    img = img.convert("RGBA").resize((64, 64), Image.Resampling.LANCZOS)
    arr = np.array(img)
    alpha = arr[:, :, 3]
    rgb = arr[:, :, :3]

    if fixed_pal is None:
        vis = arr[alpha >= 128][:, :3]
        temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
        q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
        raw = q.getpalette()[:45]
        palette = [(255, 0, 255)] + [to_gba_color(raw[i], raw[i+1], raw[i+2]) for i in range(0, 45, 3)]
    else:
        palette = fixed_pal

    pal_arr = np.array(palette[1:])
    out_idx = np.zeros((64, 64), dtype=np.uint8)

    for y in range(64):
        for x in range(64):
            if alpha[y, x] < 128:
                out_idx[y, x] = 0
            else:
                px = to_gba_color(*rgb[y, x])
                dist = np.sum((pal_arr - px) ** 2, axis=1)
                out_idx[y, x] = np.argmin(dist) + 1

    pal_buf = []
    for c in palette:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    res = Image.fromarray(out_idx, mode="P")
    res.putpalette(pal_buf)
    return res, palette

def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def package_trainer(front_path: Path, back_paths: list[Path], dest_dir: Path, trainer_tag: str):
    dest_dir.mkdir(parents=True, exist_ok=True)
    t_id = trainer_tag.upper()

    # 1. Front Sprite & Master Palette
    front_raw = Image.open(front_path)
    front_img, master_pal = quantize_trainer_frame(front_raw)
    front_img.save(dest_dir / "front.png")
    write_jasc_pal(dest_dir / "normal.pal", master_pal)

    # 2. Back Sprite (Mugshot / Throw Animation)
    if len(back_paths) == 1:
        back_raw = Image.open(back_paths[0])
        back_img, _ = quantize_trainer_frame(back_raw, fixed_pal=master_pal)
        back_img.save(dest_dir / "back.png")
    else:
        # Multi-frame throw animation (e.g. 64x128 or 64x256 horizontal/vertical strip)
        # Pokeemerald uses horizontal strips of 64x64 tiles for animated backpics
        num_frames = len(back_paths)
        strip_arr = np.zeros((64, 64 * num_frames), dtype=np.uint8)
        for i, bp in enumerate(back_paths):
            f_img, _ = quantize_trainer_frame(Image.open(bp), fixed_pal=master_pal)
            strip_arr[:, i*64:(i+1)*64] = np.array(f_img)
        
        back_img = Image.fromarray(strip_arr, mode="P")
        back_img.putpalette(front_img.getpalette())
        back_img.save(dest_dir / "back.png")

    # 3. Emit C registration headers
    c_decl = f"""
// --- Append to src/data/graphics/trainers.h ---
const u32 gTrainerFrontPic_{t_id}[] = INCBIN_U32("graphics/trainers/front_pics/{trainer_tag.lower()}_front.4bpp.lz");
const u16 gTrainerPalette_{t_id}[]  = INCBIN_U16("graphics/trainers/front_pics/{trainer_tag.lower()}.gbapal.lz");
const u32 gTrainerBackPic_{t_id}[]  = INCBIN_U32("graphics/trainers/back_pics/{trainer_tag.lower()}_back.4bpp.lz");

// --- Entry in gTrainerFrontPicTable ---
[TRAINER_PIC_{t_id}] = {{
    .data = gTrainerFrontPic_{t_id},
    .size = MON_COORDS_SIZE(64, 64),
    .y_offset = 1,
}},

// --- Entry in gTrainerFrontPicPaletteTable ---
[TRAINER_PIC_{t_id}] = {{
    .data = gTrainerPalette_{t_id},
    .tag = TRAINER_PIC_{t_id},
}},
"""
    (dest_dir / "trainer_entries.txt").write_text(c_decl)
    print(f"[✓] Packaged Trainer {t_id} into {dest_dir}")
    print(f"    - front.png: 64x64 (4bpp, 16 colors)")
    print(f"    - back.png:  {64 * max(len(back_paths), 1)}x64 (aligned to master palette)")
    print(f"    - normal.pal: JASC-PAL")
    print(f"    - trainer_entries.txt: C declarations")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package trainer front and back mugshots for decomp projects.")
    parser.add_argument("--front", required=True, type=Path, help="Raw front sprite image")
    parser.add_argument("--backs", required=True, nargs="+", type=Path, help="1 or more raw back mugshot frames")
    parser.add_argument("--dest", required=True, type=Path, help="Destination directory in graphics/trainers/")
    parser.add_argument("--name", required=True, type=str, help="Trainer identifier (e.g. Leader_Roxanne or Rival)")
    args = parser.parse_args()

    package_trainer(args.front, args.backs, args.dest, args.name)
