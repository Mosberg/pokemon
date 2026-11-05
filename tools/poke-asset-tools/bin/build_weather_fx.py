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
build_weather_fx.py - GBA Environmental Weather & Fog Effect Generator.
Synthesizes 4bpp particle sheets, scrolling fog backgrounds, and BLDCNT blending arrays.
"""

import argparse
import math
from pathlib import Path

import numpy as np
from PIL import Image


def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def generate_weather_particles(output_dir: Path):
    """
    Synthesizes standard 16x16 / 8x8 particle frames for GBA weather:
    - Ash Flake (8x8)
    - Rain Drop & Splash (8x16)
    - Sandstorm Dust (8x8)
    - Deep Sea Bubble (8x8)
    """
    output_dir.mkdir(parents=True, exist_ok=True)

    # 1. Volcanic Ash Flake (8x8)
    ash_arr = np.zeros((8, 8), dtype=np.uint8)
    ash_arr[2:5, 3:6] = 2  # Core flake
    ash_arr[1, 3] = 1; ash_arr[3, 2] = 1; ash_arr[5, 4] = 1 # Soft edge

    # 2. Rain Drop (8x16)
    rain_arr = np.zeros((16, 8), dtype=np.uint8)
    for y in range(4, 14):
        x = 2 + (y // 4)
        rain_arr[y, min(x, 7)] = 2
        rain_arr[y, min(x + 1, 7)] = 1

    # 3. Deep Sea Bubble (8x8)
    bubble_arr = np.zeros((8, 8), dtype=np.uint8)
    circle = [
        (2, 1), (3, 1), (4, 1), (5, 1),
        (1, 2), (6, 2), (1, 3), (6, 3),
        (1, 4), (6, 4), (1, 5), (6, 5),
        (2, 6), (3, 6), (4, 6), (5, 6)
    ]
    for x, y in circle:
        bubble_arr[y, x] = 2
    bubble_arr[2, 3] = 3 # Specular highlight

    # Save Composite Weather Particle Sheet (64x16, 4bpp indexed)
    sheet = np.zeros((16, 64), dtype=np.uint8)
    sheet[0:8, 0:8] = ash_arr
    sheet[0:16, 8:16] = rain_arr
    sheet[0:8, 16:24] = bubble_arr

    # Unified Weather Palette (Slot 0 = #FF00FF Key)
    pal = [
        (255, 0, 255), (140, 140, 150), (220, 220, 230), (255, 255, 255),
        (80, 110, 160), (140, 180, 240), (210, 170, 110), (160, 120, 70)
    ]
    while len(pal) < 16:
        pal.append((0, 0, 0))

    write_jasc_pal(output_dir / "weather_particles.pal", pal)

    pal_buf = []
    for c in pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    p_img = Image.fromarray(sheet, mode="P")
    p_img.putpalette(pal_buf)
    p_img.save(output_dir / "weather_particles.png")
    print(f"[✓] Weather particles compiled: {output_dir / 'weather_particles.png'}")

def generate_seamless_fog(output_dir: Path, w: int = 240, h: int = 160):
    """Generates a tileable cloud/fog layer for GBA affine background scrolling."""
    output_dir.mkdir(parents=True, exist_ok=True)
    fog_arr = np.zeros((h, w), dtype=np.uint8)

    # Multi-octave sinusoidal Perlin-approximation for seamless loops
    for y in range(h):
        for x in range(w):
            v1 = math.sin((x / w) * 2 * math.pi * 2) * math.cos((y / h) * 2 * math.pi * 2)
            v2 = math.sin((x / w) * 2 * math.pi * 4 + 1.2) * math.sin((y / h) * 2 * math.pi * 3 + 0.8)
            norm = (v1 + 0.5 * v2 + 1.5) / 3.0
            fog_arr[y, x] = max(1, min(15, int(norm * 14) + 1))

    # Grayscale Fog Palette with soft alpha graduation
    fog_pal = [(255, 0, 255)] # Slot 0
    for i in range(1, 16):
        level = int((i / 15.0) * 240 + 15)
        fog_pal.append((level, level, min(255, level + 15)))

    write_jasc_pal(output_dir / "fog.pal", fog_pal)

    pal_buf = []
    for c in fog_pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    fog_img = Image.fromarray(fog_arr, mode="P")
    fog_img.putpalette(pal_buf)
    fog_img.save(output_dir / "fog_layer.png")

    # Generate C control registers and scrolling callbacks
    c_code = f"""
// Auto-generated GBA Weather Configuration: Fog & Alpha Blending
#include "global.h"
#include "field_weather.h"

// Blending Setup for Atmospheric Fog:
// BLDCNT: Target 1 = BG0 (Fog), Target 2 = BG1 | BG2 | BG3 | OBJ
// BLDALPHA: EVA = 8 (50% fog intensity), EVB = 10 (62% world background)
void InitAtmosphericFogBlend(void)
{{
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(8, 10));
}}

// Delta velocity vectors for continuous diagonal drift
void UpdateFogScroll(u16 *bg0_x, u16 *bg0_y, u32 frame_count)
{{
    *bg0_x = (frame_count * 1) % {w}; // Scroll X at 1 px/frame
    *bg0_y = (frame_count * 1) % {h}; // Scroll Y at 1 px/frame
}}
"""
    (output_dir / "weather_fx.c").write_text(c_code)
    print(f"[✓] Seamless fog layer and blend code generated: {output_dir / 'fog_layer.png'}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate GBA weather particle sheets and scrolling atmospheric fog.")
    parser.add_argument("dest", type=Path, help="Target graphics folder (e.g., graphics/weather/)")
    args = parser.parse_args()

    generate_weather_particles(args.dest)
    generate_seamless_fog(args.dest)
