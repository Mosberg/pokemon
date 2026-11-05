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
import colorsys
from pathlib import Path

import numpy as np
from PIL import Image


def to_gba_color(r, g, b):
    """Clamps 8-bit RGB channels to GBA 5-bit channel depth (0-31 scaled to 0-255)."""
    r5 = round(int(r) * 31 / 255)
    g5 = round(int(g) * 31 / 255)
    b5 = round(int(b) * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))

def quantize_to_gba_sprite(image_path: Path, target_size=(64, 64), fixed_palette=None):
    """Resizes, crops, and quantizes an image to 16 colors (slot 0 = transparency)."""
    img = Image.open(image_path).convert("RGBA")
    img = img.resize(target_size, Image.Resampling.LANCZOS)

    alpha = np.array(img)[:, :, 3]
    rgb = np.array(img)[:, :, :3]

    # Snap channels to GBA 15-bit
    for y in range(target_size[1]):
        for x in range(target_size[0]):
            rgb[y, x] = to_gba_color(*rgb[y, x])

    rgb_img = Image.fromarray(rgb, "RGB")

    if fixed_palette is None:
        # Quantize to 15 visible colors
        quantized = rgb_img.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
        raw_pal = quantized.getpalette()[:45]
        palette_colors = [(255, 0, 255)] # Slot 0 key
        for i in range(0, 45, 3):
            palette_colors.append((raw_pal[i], raw_pal[i+1], raw_pal[i+2]))
    else:
        palette_colors = fixed_palette

    # Build 768-byte palette buffer
    pal_buffer = []
    for c in palette_colors:
        pal_buffer.extend(c)
    while len(pal_buffer) < 768:
        pal_buffer.extend([0, 0, 0])

    # Remap indices
    pal_arr = np.array(palette_colors[1:])  # shape (14 or 15, 3)
    out_idx = np.zeros(target_size, dtype=np.uint8)

    for y in range(target_size[1]):
        for x in range(target_size[0]):
            if alpha[y, x] < 128:
                out_idx[y, x] = 0
            else:
                dist = np.sum((pal_arr - rgb[y, x]) ** 2, axis=1)
                out_idx[y, x] = np.argmin(dist) + 1

    out_img = Image.fromarray(out_idx, mode="P")
    out_img.putpalette(pal_buffer)
    return out_img, palette_colors


def write_jasc_pal(filepath: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    filepath.write_text("\n".join(lines) + "\n")


def generate_shiny(normal_colors: list, hue_shift=0.35):
    shiny = []
    for idx, (r, g, b) in enumerate(normal_colors[:16]):
        if idx == 0:
            shiny.append((r, g, b))
            continue
        lum = 0.299 * r + 0.587 * g + 0.114 * b
        if lum < 28:  # Retain deep outline shadows
            shiny.append((r, g, b))
            continue
        h, s, v = colorsys.rgb_to_hsv(int(r) / 255.0, int(g) / 255.0, int(b) / 255.0)
        h = (h + hue_shift) % 1.0
        r_n, g_n, b_n = colorsys.hsv_to_rgb(h, s, v)
        shiny.append(to_gba_color(int(r_n * 255), int(g_n * 255), int(b_n * 255)))
    return shiny


def import_species(source_dir: Path, decomp_root: Path, species_name: str, hue_shift: float):
    species_tag = species_name.lower()
    species_const = f"SPECIES_{species_name.upper()}"
    dest_dir = decomp_root / "graphics" / "pokemon" / species_tag
    dest_dir.mkdir(parents=True, exist_ok=True)

    front_raw = source_dir / "front.png"
    back_raw = source_dir / "back.png"
    icon_raw = source_dir / "icon.png"

    if not front_raw.exists():
        raise FileNotFoundError(f"Missing {front_raw}. A front sprite is required.")

    print(f"[*] Processing {species_const}...")

    # 1. Front Sprite & Master Palette
    front_img, master_palette = quantize_to_gba_sprite(front_raw, (64, 64))
    front_img.save(dest_dir / "front.png")
    write_jasc_pal(dest_dir / "normal.pal", master_palette)

    # 2. Back Sprite (Harmonized to Front Master Palette)
    if back_raw.exists():
        back_img, _ = quantize_to_gba_sprite(back_raw, (64, 64), fixed_palette=master_palette)
        back_img.save(dest_dir / "back.png")
    else:
        # Fallback placeholder
        front_img.save(dest_dir / "back.png")
        print("  [!] Back sprite missing; duplicated front sprite as temporary placeholder.")

    # 3. Shiny Palette
    shiny_palette = generate_shiny(master_palette, hue_shift=hue_shift)
    write_jasc_pal(dest_dir / "shiny.pal", shiny_palette)

    # 4. Box/Party Icon (32x32)
    if icon_raw.exists():
        icon_img, _ = quantize_to_gba_sprite(icon_raw, (32, 32))
        icon_img.save(dest_dir / "icon.png")

    print(f"[✓] Graphics created at: {dest_dir}")

    # 5. Emit pokeemerald-expansion C Template
    c_snippet = f"""
// --- Paste into src/data/pokemon/species_info.h under [{species_const}] ---
    [{species_const}] =
    {{
        .speciesName = _("{species_name.capitalize()}"),
        .frontPic = gMonFrontPic_{species_name.capitalize()},
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFrame,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_{species_name.capitalize()},
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_{species_name.capitalize()},
        .shinyPalette = gMonShinyPalette_{species_name.capitalize()},
        .iconSprite = gMonIcon_{species_name.capitalize()},
        .iconPaletteIndex = 0,
        // Fill in typing, base stats, exp yield, abilities, etc.
    }},
"""
    snippet_path = dest_dir / "species_info_entry.txt"
    snippet_path.write_text(c_snippet)
    print(f"[✓] C registration template written to: {snippet_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Batch import new Pokemon species into a GBA decomp tree.")
    parser.add_argument("--src", required=True, type=Path, help="Folder containing front.png, back.png, icon.png")
    parser.add_argument("--repo", required=True, type=Path, help="Root path of pokeemerald / pokefirered repository")
    parser.add_argument("--name", required=True, type=str, help="Species identifier (e.g. Aerodactyl or mymon)")
    parser.add_argument("--hue", default=0.35, type=float, help="HSV Hue rotation for shiny variant (0.0 - 1.0)")
    args = parser.parse_args()

    import_species(args.src, args.repo, args.name, args.hue)
