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
generate_parallax.py - GBA Multi-Layer Parallax Background & HBlank Engine.
Extracts depth bands, deduplicates 8x8 tiles, and computes scanline scroll LUTs.
"""

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


def compute_parallax_lut(bands: list[dict], total_lines: int = 160) -> list[int]:
    """
    Computes horizontal scroll factor per scanline in 8.8 fixed-point.
    Bands format: [{'start_y': 0, 'end_y': 60, 'speed': 0.25}, ...]
    """
    lut = [0] * total_lines
    for band in bands:
        start = band["start_y"]
        end = min(total_lines, band["end_y"])
        speed = band["speed"]  # Pixels per frame

        # Linear or perspective velocity gradient within band
        grad = band.get("gradient", False)
        for y in range(start, end):
            if grad and (end - start > 1):
                t = (y - start) / float(end - start - 1)
                curr_speed = speed * (1.0 + t)
            else:
                curr_speed = speed
            # Convert to 8.8 fixed point
            lut[y] = int(round(curr_speed * 256.0))
    return lut

def process_parallax_scenery(image_path: Path, output_dir: Path, bands_config: list[dict]):
    output_dir.mkdir(parents=True, exist_ok=True)
    img = Image.open(image_path).convert("RGBA").resize((240, 160), Image.Resampling.LANCZOS)
    arr = np.array(img)

    # 1. 16-color Quantization (Index 0 = #FF00FF Key)
    vis = arr[arr[:, :, 3] >= 128][:, :3]
    temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = q.getpalette()[:45]

    master_pal = [(255, 0, 255)] + [to_gba_color(raw_pal[i:i+3]) for i in range(0, 45, 3)]
    write_jasc_pal(output_dir / "parallax_bg.pal", master_pal)

    pal_buf = []
    for c in master_pal:
        pal_buf.extend(c)
    while len(pal_buf) < 768:
        pal_buf.extend([0, 0, 0])

    indexed_img = Image.fromarray(np.array(q) + 1, mode="P")
    indexed_img.putpalette(pal_buf)

    # 2. Tile Slicing & Deduplication
    idx_arr = np.array(indexed_img)
    tile_list = []
    tilemap = []

    for ty in range(20):
        for tx in range(30):
            tile = idx_arr[ty*8:(ty+1)*8, tx*8:(tx+1)*8].tobytes()
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

    dedup_img = Image.fromarray(tiles_sheet, mode="P")
    dedup_img.putpalette(pal_buf)
    dedup_img.save(output_dir / "parallax_tiles.png")

    # Export tilemap binary
    map_bin = bytearray()
    for t_id in tilemap:
        map_bin.extend(int(t_id & 0x3FF).to_bytes(2, byteorder="little"))
    (output_dir / "parallax_tilemap.bin").write_bytes(map_bin)

    # 3. Compute HBlank Scroll Table
    scroll_lut = compute_parallax_lut(bands_config, total_lines=160)

    # 4. Generate C HBlank Interrupt Handler
    c_code = [
        "// Auto-generated GBA Parallax HBlank Scroll Engine",
        "#include \"global.h\"",
        "#include \"scanline_effect.h\"",
        "",
        "// Fixed-point 8.8 velocity per scanline",
        "static const s16 sParallaxScanlineVelocities[160] = {"
    ]

    for i in range(0, 160, 8):
        chunk = [f"{v:6d}" for v in scroll_lut[i:i+8]]
        c_code.append("    " + ", ".join(chunk) + ",")
    c_code.extend([
        "};",
        "",
        "// Applied during HBlank to update BG0HOFS per raster line",
        "void Task_ApplyParallaxHBlank(u8 taskId)",
        "{",
        "    struct ScanlineEffectParams params;",
        "    static u32 sFrameCounter = 0;",
        "    sFrameCounter++;",
        "",
        "    for (int y = 0; y < 160; y++) {",
        "        // Calculate current horizontal shift: (velocity * frame) >> 8",
        "        gScanlineEffectRegBuffers[0][y] = (sParallaxScanlineVelocities[y] * sFrameCounter) >> 8;",
        "    }",
        "",
        "    params.dmaDest = (void *)REG_ADDR_BG0HOFS;",
        "    params.dmaControl = SCANLINE_EFFECT_DMACNT_16BIT;",
        "    params.initState = 1;",
        "    ScanlineEffect_SetParams(params);",
        "}",
    ])

    (output_dir / "parallax_hblank.c").write_text("\n".join(c_code) + "\n")

    print("=" * 60)
    print(f"[✓] GBA Parallax Scenery Engine Generated: {output_dir}")
    print(f"  - Tiles Deduped: {len(tile_list)} / 600 total (parallax_tiles.png)")
    print("  - Binary Map:    30x20 entries (parallax_tilemap.bin)")
    print("  - HBlank C Code: parallax_hblank.c")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate GBA Parallax scrolling backgrounds and HBlank interrupt tables.")
    parser.add_argument("image", type=Path, help="Input 240x160 scene image")
    parser.add_argument("out_dir", type=Path, help="Destination directory (e.g. graphics/battle_bg/)")
    args = parser.parse_args()

    # Default Depth Bands: Sky (static), Mountains (slow), Foreground Trees (fast)
    default_bands = [
        {"start_y": 0,  "end_y": 50,  "speed": 0.10, "gradient": False}, # Far Clouds/Sky
        {"start_y": 50, "end_y": 100, "speed": 0.40, "gradient": True},  # Distant Mountains
        {"start_y": 100,"end_y": 160, "speed": 1.25, "gradient": True}   # Foreground Ground
    ]

    process_parallax_scenery(args.image, args.out_dir, default_bands)
