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


def to_gba_color(rgb):
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb[:3])

def write_jasc_pal(path: Path, colors: list):
    lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in colors[:16]:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def package_battle_ui(ui_mockup_path: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    mock = Image.open(ui_mockup_path).convert("RGBA")
    w, h = mock.size

    # 1. Extract Master 16-color UI Palette
    # Slot 0 = Transparent Key (#FF00FF)
    arr = np.array(mock)
    vis = arr[arr[:, :, 3] >= 128][:, :3]
    temp_img = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp_img.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    master_pal = [(255, 0, 255)] + [to_gba_color(raw_pal[i:i+3]) for i in range(0, 45, 3)]
    write_jasc_pal(output_dir / "battle_ui.pal", master_pal)

    pal_buf = []
    for c in master_pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    pal_arr = np.array(master_pal[1:])

    def quantize_crop(crop_box):
        cropped = mock.crop(crop_box)
        c_arr = np.array(cropped)
        alpha = c_arr[:, :, 3]
        rgb = c_arr[:, :, :3]
        ch, cw = c_arr.shape[:2]
        out_idx = np.zeros((ch, cw), dtype=np.uint8)

        for y in range(ch):
            for x in range(cw):
                if alpha[y, x] < 128:
                    out_idx[y, x] = 0
                else:
                    px = to_gba_color(rgb[y, x])
                    dist = np.sum((pal_arr - px) ** 2, axis=1)
                    out_idx[y, x] = np.argmin(dist) + 1

        res = Image.fromarray(out_idx, mode="P")
        res.putpalette(pal_buf)
        return res

    # 2. Extract Battle Message Box (Bottom 240x48)
    msg_box = quantize_crop((0, max(0, h - 48), 240, h))
    msg_box.save(output_dir / "battle_message_box.png")

    # Slicing Message Box to Deduplicated 8x8 Tiles & 30x6 Tilemap
    mb_arr = np.array(msg_box)
    tile_list = []
    tilemap = []

    for ty in range(6):
        for tx in range(30):
            tile = mb_arr[ty*8:(ty+1)*8, tx*8:(tx+1)*8].tobytes()
            if tile in tile_list:
                tilemap.append(tile_list.index(tile))
            else:
                tilemap.append(len(tile_list))
                tile_list.append(tile)

    cols = 16
    rows = (len(tile_list) + cols - 1) // cols
    tiles_sheet = np.zeros((rows * 8, cols * 8), dtype=np.uint8)
    for i, t_bytes in enumerate(tile_list):
        t_arr = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (i % cols) * 8
        cy = (i // cols) * 8
        tiles_sheet[cy:cy+8, cx:cx+8] = t_arr

    dedup_msg = Image.fromarray(tiles_sheet, mode="P")
    dedup_msg.putpalette(pal_buf)
    dedup_msg.save(output_dir / "battle_message_box_tiles.png")

    map_bin = bytearray()
    for t_id in tilemap:
        map_bin.extend(int(t_id & 0x3FF).to_bytes(2, byteorder="little"))
    (output_dir / "battle_message_box_map.bin").write_bytes(map_bin)

    # 3. Extract Player & Opponent HP Boxes
    # Standard GBA coords: Opponent (x: 16-120, y: 16-48), Player (x: 128-232, y: 80-112)
    opp_hp = quantize_crop((16, 16, 120, 48))
    opp_hp.save(output_dir / "opponent_hp_box.png")

    player_hp = quantize_crop((128, 80, 232, 112))
    player_hp.save(output_dir / "player_hp_box.png")

    # 4. Generate 8-Step Dynamic HP Fill Bar Spritesheet (8 frames of 8x8 blocks)
    # Renders empty -> full fill steps across green, yellow, red states
    hp_fill_arr = np.zeros((8, 64), dtype=np.uint8)
    for step in range(8):
        fill_width = step + 1
        # Fill rows 2 to 5 with color index 1 (foreground HP bar color)
        hp_fill_arr[2:6, step * 8 : step * 8 + fill_width] = 1
        # Add highlight in row 2 with color index 2
        hp_fill_arr[2, step * 8 : step * 8 + fill_width] = 2

    hp_bar_img = Image.fromarray(hp_fill_arr, mode="P")
    hp_bar_img.putpalette(pal_buf)
    hp_bar_img.save(output_dir / "hp_bar_fill.png")

    print("=" * 60)
    print(f"[✓] Battle UI Packaged Successfully into: {output_dir}")
    print(f"  - Message Box:  240x48 (Tiles: {len(tile_list)} / 180 total)")
    print("  - Player Box:   104x32 -> player_hp_box.png")
    print("  - Opponent Box: 104x32 -> opponent_hp_box.png")
    print("  - HP Fill:      64x8 (8 steps) -> hp_bar_fill.png")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package complete GBA battle UI and HUD assets.")
    parser.add_argument("mockup", type=Path, help="Full 240x160 battle UI mockup PNG")
    parser.add_argument("output_dir", type=Path, help="Destination graphics/battle_ui/ folder")
    args = parser.parse_args()

    package_battle_ui(args.mockup, args.output_dir)
