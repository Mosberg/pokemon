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

"""
build_battle_particles.py - GBA Move Animation Particle Builder
Generates 4bpp sprite sheets, OAM affine transformation tables,
and battle animation script commands for pokeemerald/pokefirered.
"""

import math
import argparse
from pathlib import Path
from PIL import Image
import numpy as np

def to_gba_color(rgb):
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb[:3])

def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def generate_affine_rotation_table(num_frames: int = 32, max_angle_deg: float = 360.0, zoom_factor: float = 1.0):
    """
    Computes GBA Affine matrix parameters (PA, PB, PC, PD).
    GBA uses 8.8 fixed point integers.
    PA =  sx * cos(theta)
    PB = -sx * sin(theta)
    PC =  sy * sin(theta)
    PD =  sy * cos(theta)
    """
    matrix_entries = []
    for f in range(num_frames):
        theta = math.radians((f / num_frames) * max_angle_deg)
        sx = 1.0 / zoom_factor
        sy = 1.0 / zoom_factor

        pa = int(round(sx * math.cos(theta) * 256.0))
        pb = int(round(-sx * math.sin(theta) * 256.0))
        pc = int(round(sy * math.sin(theta) * 256.0))
        pd = int(round(sy * math.cos(theta) * 256.0))

        matrix_entries.append((pa, pb, pc, pd))
    return matrix_entries

def build_particle_system(image_path: Path, output_dir: Path, anim_name: str, tile_size: int = 16):
    output_dir.mkdir(parents=True, exist_ok=True)
    img = Image.open(image_path).convert("RGBA")
    w, h = img.size

    cols = w // tile_size
    rows = h // tile_size
    num_particles = cols * rows

    # Quantize to unified 16-color palette (index 0 = transparency)
    arr = np.array(img)
    vis = arr[arr[:, :, 3] >= 128][:, :3]
    if len(vis) == 0:
        raise ValueError("Image has no non-transparent pixels.")

    temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    master_pal = [(255, 0, 255)] + [to_gba_color(raw_pal[i:i+3]) for i in range(0, 45, 3)]
    write_jasc_pal(output_dir / f"{anim_name}.pal", master_pal)

    pal_buf = []
    for c in master_pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    pal_arr = np.array(master_pal[1:])

    # Map particles to horizontal strip
    strip_arr = np.zeros((tile_size, tile_size * num_particles), dtype=np.uint8)

    for idx in range(num_particles):
        col = idx % cols
        row = idx // cols
        tile = arr[row*tile_size:(row+1)*tile_size, col*tile_size:(col+1)*tile_size]

        for y in range(tile_size):
            for x in range(tile_size):
                if tile[y, x, 3] < 128:
                    strip_arr[y, idx * tile_size + x] = 0
                else:
                    px = to_gba_color(tile[y, x, :3])
                    dist = np.sum((pal_arr - px) ** 2, axis=1)
                    strip_arr[y, idx * tile_size + x] = np.argmin(dist) + 1

    out_img = Image.fromarray(strip_arr, mode="P")
    out_img.putpalette(pal_buf)
    out_img.save(output_dir / f"{anim_name}.png")

    # Generate Affine Tables
    affine_table = generate_affine_rotation_table(num_frames=16, max_angle_deg=360.0)

    # Generate C and Decomp Battle Animation Script
    c_out = [
        f"// Auto-generated Battle Anim Particle: {anim_name}",
        f"#include \"global.h\"",
        f"#include \"battle_anim.h\"",
        "",
        f"const u32 gBattleAnimSprite_{anim_name}[] = INCBIN_U32(\"graphics/battle_anims/{anim_name}.4bpp.lz\");",
        f"const u16 gBattleAnimPalette_{anim_name}[] = INCBIN_U16(\"graphics/battle_anims/{anim_name}.gbapal.lz\");",
        "",
        f"static const struct OamData sOamData_{anim_name} = {{",
        f"    .affineMode = ST_OAM_AFFINE_DOUBLE,",
        f"    .objMode = ST_OAM_OBJ_NORMAL,",
        f"    .mosaic = FALSE,",
        f"    .bpp = ST_OAM_4BPP,",
        f"    .shape = SPRITE_SHAPE_SQUARE,",
        f"    .size = SPRITE_SIZE({tile_size}x{tile_size}),",
        f"}};",
        "",
        f"static const struct AffineAnimCmd sAffineAnim_{anim_name}[] = {{"
    ]

    for pa, pb, pc, pd in affine_table:
        c_out.append(f"    {{ .pa = {pa}, .pb = {pb}, .pc = {pc}, .pd = {pd} }},")

    c_out.extend([
        "    { .type = AFFINEANIMCMDTYPE_END }",
        "};",
        "",
        f"static const union AnimCmd sAnim_{anim_name}_Frames[] = {{",
    ])

    for i in range(num_particles):
        c_out.append(f"    ANIMCMD_FRAME({i * (tile_size // 8) * (tile_size // 8)}, 2),")

    c_out.extend([
        "    ANIMCMD_JUMP(0),",
        "};",
        "",
        f"const struct SpriteTemplate gBattleAnim_{anim_name}_Template = {{",
        f"    .tileTag = ANIM_TAG_{anim_name.upper()},",
        f"    .paletteTag = ANIM_TAG_{anim_name.upper()},",
        f"    .oam = &sOamData_{anim_name},",
        f"    .anims = (const union AnimCmd *const[]) {{ sAnim_{anim_name}_Frames }},",
        f"    .images = NULL,",
        f"    .affineAnims = (const union AffineAnimCmd *const[]) {{ sAffineAnim_{anim_name} }},",
        f"    .callback = AnimMoveParticleTask,",
        f"}};"
    ])

    (output_dir / f"{anim_name}_anim.c").write_text("\n".join(c_out) + "\n")

    print("=" * 60)
    print(f"[✓] Battle Animation Particle System Created:")
    print(f"  - Particle Sheet: {output_dir / f'{anim_name}.png'} ({tile_size}x{tile_size * num_particles} px)")
    print(f"  - Palette:        {output_dir / f'{anim_name}.pal'}")
    print(f"  - C Animation:    {output_dir / f'{anim_name}_anim.c'}")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compile particle sprites and affine transforms for battle animations.")
    parser.add_argument("image", type=Path, help="Particle sheet or sequence image")
    parser.add_argument("output_dir", type=Path, help="Target folder (e.g., graphics/battle_anims/)")
    parser.add_argument("--name", type=str, default="custom_particle", help="Animation tag identifier")
    parser.add_argument("--size", type=int, choices=[8, 16, 32, 64], default=16, help="Tile size (8, 16, 32, 64)")
    args = parser.parse_args()

    build_particle_system(args.image, args.output_dir, args.name, args.size)
