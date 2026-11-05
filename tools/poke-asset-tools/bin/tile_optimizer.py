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

def get_tile_transforms(tile: np.ndarray):
    """Returns the normal tile and its 3 hardware-supported reflections."""
    normal = tile
    x_flip = np.fliplr(tile)
    y_flip = np.flipud(tile)
    xy_flip = np.flipud(np.fliplr(tile))
    return {
        (False, False): normal,
        (True, False): x_flip,
        (False, True): y_flip,
        (True, True): xy_flip
    }

def tile_diff(t1: np.ndarray, t2: np.ndarray) -> float:
    """Mean squared error difference between two tiles."""
    return float(np.mean((t1.astype(float) - t2.astype(float)) ** 2))

def optimize_tileset(image_path: Path, output_tileset: Path, output_map: Path = None, tolerance: float = 0.0):
    img = Image.open(image_path)
    is_indexed = (img.mode == "P")
    palette = img.getpalette() if is_indexed else None
    
    img_rgba = img.convert("RGBA") if not is_indexed else img
    arr = np.array(img_rgba)
    h, w = arr.shape[:2]

    tiles_x = w // 8
    tiles_y = h // 8

    unique_tiles = []       # List of canonical 8x8 ndarrays
    tilemap = []            # Records (tile_id, x_flip, y_flip) for each position

    for ty in range(tiles_y):
        for tx in range(tiles_x):
            current_tile = arr[ty*8:(ty+1)*8, tx*8:(tx+1)*8]
            matched = False

            # Check against existing unique tiles and their hardware flips
            for u_idx, u_tile in enumerate(unique_tiles):
                transforms = get_tile_transforms(u_tile)
                for (x_flip, y_flip), trans_tile in transforms.items():
                    diff = tile_diff(current_tile, trans_tile)
                    if diff <= tolerance:
                        tilemap.append((u_idx, x_flip, y_flip))
                        matched = True
                        break
                if matched:
                    break

            if not matched:
                new_idx = len(unique_tiles)
                unique_tiles.append(current_tile)
                tilemap.append((new_idx, False, False))

    orig_count = tiles_x * tiles_y
    opt_count = len(unique_tiles)
    savings = (1.0 - (opt_count / orig_count)) * 100

    print("=" * 60)
    print(f"TILESET REDUCTION REPORT: {image_path.name}")
    print(f"Original Tiles:  {orig_count}")
    print(f"Optimized Tiles: {opt_count}")
    print(f"VRAM Saved:      {savings:.2f}% ({orig_count - opt_count} tiles removed)")
    print("=" * 60)

    # Reconstruct optimized tileset image (organized in rows of 16 tiles = 128px wide)
    out_cols = 16
    out_rows = (opt_count + out_cols - 1) // out_cols
    out_w = out_cols * 8
    out_h = out_rows * 8

    if is_indexed:
        out_arr = np.zeros((out_h, out_w), dtype=np.uint8)
    else:
        out_arr = np.zeros((out_h, out_w, 4), dtype=np.uint8)

    for idx, t in enumerate(unique_tiles):
        cx = (idx % out_cols) * 8
        cy = (idx // out_cols) * 8
        out_arr[cy:cy+8, cx:cx+8] = t

    if is_indexed:
        out_img = Image.fromarray(out_arr, mode="P")
        out_img.putpalette(palette)
    else:
        out_img = Image.fromarray(out_arr, mode="RGBA")

    out_img.save(output_tileset)
    print(f"[✓] Saved deduplicated tileset to: {output_tileset}")

    if output_map:
        # Export binary tilemap entries: 16-bit per tile (bits 0-9: ID, bit 10: X-flip, bit 11: Y-flip)
        map_bytes = bytearray()
        for t_id, xf, yf in tilemap:
            val = (t_id & 0x3FF) | ((1 if xf else 0) << 10) | ((1 if yf else 0) << 11)
            map_bytes.extend(int(val).to_bytes(2, byteorder="little"))
        output_map.write_bytes(map_bytes)
        print(f"[✓] Saved reconstructed tilemap to: {output_map}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Deduplicate GBA tiles with flip detection and MSE tolerance.")
    parser.add_argument("image", type=Path, help="Input raw tileset or map image")
    parser.add_argument("out_tileset", type=Path, help="Path for optimized output PNG")
    parser.add_argument("--out-map", type=Path, default=None, help="Optional binary tilemap destination")
    parser.add_argument("--tolerance", type=float, default=0.0, help="MSE color difference allowed for lossy merging (0.0 = lossless)")
    args = parser.parse_args()

    optimize_tileset(args.image, args.out_tileset, args.out_map, args.tolerance)
