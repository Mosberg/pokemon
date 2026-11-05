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


def process_tile_layer(img: Image.Image, output_tiles: Path, output_map: Path, output_pal: Path):
    """Processes an image into a 16-color indexed tile sheet and tilemap."""
    arr = np.array(img.convert("RGBA"))
    h, w = arr.shape[:2]
    vis = arr[arr[:, :, 3] >= 128][:, :3]

    temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    pal = [(255, 0, 255)] + [to_gba_color(raw_pal[i:i+3]) for i in range(0, 45, 3)]
    write_jasc_pal(output_pal, pal)

    pal_buf = []
    for c in pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    # Re-index
    pal_arr = np.array(pal[1:])
    out_arr = np.zeros((h, w), dtype=np.uint8)
    for y in range(h):
        for x in range(w):
            if arr[y, x, 3] < 128:
                out_arr[y, x] = 0
            else:
                dist = np.sum((pal_arr - to_gba_color(arr[y, x, :3])) ** 2, axis=1)
                out_arr[y, x] = np.argmin(dist) + 1

    indexed_img = Image.fromarray(out_arr, mode="P")
    indexed_img.putpalette(pal_buf)

    # Tile slicing & deduplication
    tiles_x = w // 8
    tiles_y = h // 8
    tile_list = []
    tilemap = []

    for ty in range(tiles_y):
        for tx in range(tiles_x):
            tile = out_arr[ty*8:(ty+1)*8, tx*8:(tx+1)*8].tobytes()
            if tile in tile_list:
                tilemap.append(tile_list.index(tile))
            else:
                tilemap.append(len(tile_list))
                tile_list.append(tile)

    cols = 16
    rows = (len(tile_list) + cols - 1) // cols
    sheet = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for i, t_bytes in enumerate(tile_list):
        t = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        sheet[(i // cols) * 8 : (i // cols) * 8 + 8, (i % cols) * 8 : (i % cols) * 8 + 8] = t

    dedup = Image.fromarray(sheet, mode="P")
    dedup.putpalette(pal_buf)
    dedup.save(output_tiles)

    map_bin = bytearray()
    for t_id in tilemap:
        map_bin.extend(int(t_id & 0x3FF).to_bytes(2, byteorder="little"))
    output_map.write_bytes(map_bin)

    return len(tile_list), tiles_x * tiles_y

def package_title_screen(bg_img_path: Path, logo_img_path: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)

    bg = Image.open(bg_img_path).resize((240, 160), Image.Resampling.LANCZOS)
    logo = Image.open(logo_img_path)

    # 1. Background Layer (Layer BG2)
    bg_tiles, bg_total = process_tile_layer(
        bg,
        output_dir / "title_bg_tiles.png",
        output_dir / "title_bg_tilemap.bin",
        output_dir / "title_bg.pal"
    )

    # 2. Game Logo Layer (Layer BG1)
    logo_tiles, logo_total = process_tile_layer(
        logo,
        output_dir / "title_logo_tiles.png",
        output_dir / "title_logo_tilemap.bin",
        output_dir / "title_logo.pal"
    )

    # 3. Emit C Integration Definitions
    c_code = f"""
// --- Append to src/title_screen.c ---
static const u32 sTitleBgTiles[]    = INCBIN_U32("graphics/title_screen/title_bg_tiles.4bpp.lz");
static const u32 sTitleBgTilemap[]  = INCBIN_U32("graphics/title_screen/title_bg_tilemap.bin.lz");
static const u16 sTitleBgPalette[]  = INCBIN_U16("graphics/title_screen/title_bg.gbapal");

static const u32 sTitleLogoTiles[]   = INCBIN_U32("graphics/title_screen/title_logo_tiles.4bpp.lz");
static const u32 sTitleLogoTilemap[] = INCBIN_U32("graphics/title_screen/title_logo_tilemap.bin.lz");
static const u16 sTitleLogoPalette[] = INCBIN_U16("graphics/title_screen/title_logo.gbapal");

// Background Tile Metrics:
// BG Landscape: {bg_tiles} unique tiles (out of {bg_total})
// Logo:         {logo_tiles} unique tiles (out of {logo_total})
"""
    (output_dir / "title_screen_entries.txt").write_text(c_code)

    print("=" * 60)
    print(f"[✓] Title Screen Sequence Packaged: {output_dir}")
    print(f"  - BG Landscape: {bg_tiles} tiles -> title_bg_tiles.png")
    print(f"  - Logo Layer:   {logo_tiles} tiles -> title_logo_tiles.png")
    print("  - Palettes:     title_bg.pal & title_logo.pal (16 colors each)")
    print("  - Code Snippet: title_screen_entries.txt")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package multi-layer title screen and logo assets for GBA decomp.")
    parser.add_argument("bg", type=Path, help="240x160 background image")
    parser.add_argument("logo", type=Path, help="Logo artwork image")
    parser.add_argument("output_dir", type=Path, help="Target folder (e.g. graphics/title_screen/)")
    args = parser.parse_args()

    package_title_screen(args.bg, args.logo, args.output_dir)
