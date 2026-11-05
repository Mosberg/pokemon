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
render_dynamic_hp.py - Procedural GBA Dynamic Multi-Palette Health Bar Generator.
Outputs 4bpp-indexed HP fill sheets, multi-tier status palettes, and C math drivers.
"""

import argparse
from pathlib import Path

import numpy as np
from PIL import Image

BAR_WIDTH = 48
BAR_HEIGHT = 4

# GBA 15-bit RGB Color Sets (Highlight, Body, Shadow)
HP_PALETTES = {
    "green":  [(112, 248, 168), (0, 200, 80),   (0, 128, 48)],
    "yellow": [(248, 240, 128), (232, 168, 0),  (160, 112, 0)],
    "red":    [(248, 144, 120), (224, 64, 48),  (144, 24, 16)]
}

def to_gba_color(rgb):
    """Snaps standard RGB to GBA 5-bit depth."""
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb[:3])

def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def generate_hp_assets(output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)

    # 1. Generate Multi-Tier Palettes (Slot 0 = #FF00FF Key, Slot 1 = Highlight, Slot 2 = Body, Slot 3 = Shadow, Slot 4 = Empty Groove)
    pal_buffers = {}
    for state, colors in HP_PALETTES.items():
        master_pal = [
            (255, 0, 255),               # 0: Transparent
            to_gba_color(colors[0]),     # 1: Highlight
            to_gba_color(colors[1]),     # 2: Core Body
            to_gba_color(colors[2]),     # 3: Shadow
            (64, 64, 64)                 # 4: Empty Background Groove
        ]
        while len(master_pal) < 16:
            master_pal.append((0, 0, 0))

        write_jasc_pal(output_dir / f"hp_{state}.pal", master_pal)

        buf = []
        for c in master_pal:
            buf.extend(c)
        while len(buf) < 768:
            buf.extend([0, 0, 0])
        pal_buffers[state] = buf

    # 2. Build 49-state Horizontal Spritesheet (0 px filled to 48 px filled)
    # Total canvas: 48 pixels wide, (49 * 4) = 196 pixels high
    sheet_arr = np.zeros((49 * BAR_HEIGHT, BAR_WIDTH), dtype=np.uint8)

    for fill_pixels in range(49):
        y_start = fill_pixels * BAR_HEIGHT

        # Draw empty groove background across entire width
        sheet_arr[y_start : y_start + BAR_HEIGHT, :] = 4

        if fill_pixels > 0:
            # Row 0: Top Highlight
            sheet_arr[y_start, 0 : fill_pixels] = 1
            # Rows 1-2: Core Body
            sheet_arr[y_start + 1 : y_start + 3, 0 : fill_pixels] = 2
            # Row 3: Drop Shadow
            sheet_arr[y_start + 3, 0 : fill_pixels] = 3

    out_img = Image.fromarray(sheet_arr, mode="P")
    out_img.putpalette(pal_buffers["green"])
    out_img.save(output_dir / "hp_fill_sheet.png")

    # 3. Export C Healthbar Controller Logic
    c_logic = """
// Auto-generated GBA Dynamic Health Bar Driver
#include "global.h"
#include "battle.h"

#define HP_BAR_MAX_PIXELS 48

// Returns the pixel fill width (0 to 48) based on current/max HP
u8 CalculateHpBarPixels(s32 currentHp, s32 maxHp)
{
    if (currentHp <= 0)
        return 0;
    if (currentHp >= maxHp)
        return HP_BAR_MAX_PIXELS;

    // Fixed-point division with ceiling preservation
    u8 pixels = (currentHp * HP_BAR_MAX_PIXELS) / maxHp;
    if (pixels == 0 && currentHp > 0)
        pixels = 1; // Always show at least 1 pixel if alive
    return pixels;
}

// Returns the active palette ID based on health percentage
// 0 = Green (>50%), 1 = Yellow (20-50%), 2 = Red (<=20%)
u8 GetHpBarPaletteTag(s32 currentHp, s32 maxHp)
{
    s32 doubleHp = currentHp * 2;
    s32 fiveHp   = currentHp * 5;

    if (doubleHp > maxHp)
        return 0; // Green
    if (fiveHp > maxHp)
        return 1; // Yellow
    return 2;     // Red
}
"""
    (output_dir / "battle_hp_controls.c").write_text(c_logic)

    print("=" * 65)
    print(f"[✓] Dynamic Health Bar Assets Compiled: {output_dir}")
    print(f"  - Spritesheet: {output_dir / 'hp_fill_sheet.png'} (48x196 px, 49 states)")
    print("  - Palettes:    hp_green.pal, hp_yellow.pal, hp_red.pal")
    print(f"  - Driver Code: {output_dir / 'battle_hp_controls.c'}")
    print("=" * 65)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate GBA dynamic 4bpp battle HP bar assets and C drivers.")
    parser.add_argument("dest", type=Path, help="Target folder (e.g. graphics/battle_ui/hp_bar/)")
    args = parser.parse_args()

    generate_hp_assets(args.dest)
