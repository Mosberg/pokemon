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

def scan_for_palette_conflicts(image_path: Path, output_debug: Path = None, max_colors_per_tile=16):
    img = Image.open(image_path).convert("RGBA")
    w, h = img.size
    
    if w % 8 != 0 or h % 8 != 0:
        print(f"[!] Warning: Image dimensions ({w}x{h}) are not multiples of 8. Edge tiles will be padded.")
        
    np_img = np.array(img)
    
    tiles_x = w // 8
    tiles_y = h // 8
    
    violations = []
    
    # Create debug overlay image (RGBA)
    debug_overlay = np_img.copy()
    
    for ty in range(tiles_y):
        for tx in range(tiles_x):
            box = np_img[ty*8:(ty+1)*8, tx*8:(tx+1)*8]
            
            # Filter fully transparent pixels (alpha < 128)
            visible_pixels = box[box[:, :, 3] >= 128][:, :3]
            
            # Map visible pixels to unique RGB tuples
            unique_colors = {tuple(p) for p in visible_pixels}
            
            # Transparency counts as 1 slot (Slot 0)
            slot_count = len(unique_colors) + (1 if np.any(box[:, :, 3] < 128) else 0)
            
            if slot_count > max_colors_per_tile:
                pixel_x = tx * 8
                pixel_y = ty * 8
                violations.append({
                    "tile": (tx, ty),
                    "pos": (pixel_x, pixel_y),
                    "count": slot_count,
                    "overflow": slot_count - max_colors_per_tile
                })
                
                # Mark tile with a red highlight on debug map
                debug_overlay[ty*8:(ty+1)*8, tx*8:(tx+1)*8, 0] = 255
                debug_overlay[ty*8:(ty+1)*8, tx*8:(tx+1)*8, 1] = 0
                debug_overlay[ty*8:(ty+1)*8, tx*8:(tx+1)*8, 2] = 0
                debug_overlay[ty*8:(ty+1)*8, tx*8:(tx+1)*8, 3] = 200

    print("=" * 60)
    print(f"PALETTE CONFLICT REPORT: {image_path.name}")
    print(f"Scanned: {tiles_x * tiles_y} total 8x8 tiles ({w}x{h} px)")
    print(f"Status:  {'FAIL' if violations else 'PASS'}")
    print("=" * 60)
    
    if not violations:
        print("[✓] Zero intra-tile color collisions found! All tiles comply with 4bpp limits.")
        return True
        
    print(f"[✗] Found {len(violations)} tiles exceeding the {max_colors_per_tile}-color GBA hardware limit:\n")
    print(f"{'Tile (X, Y)':<15} | {'Pixel Origin':<15} | {'Colors Used':<12} | {'Overflow'}")
    print("-" * 55)
    for v in violations[:25]: # Show first 25 violations
        print(f"{str(v['tile']):<15} | {str(v['pos']):<15} | {v['count']:<12} | +{v['overflow']}")
        
    if len(violations) > 25:
        print(f"... and {len(violations) - 25} more violating tiles.")
        
    if output_debug:
        out_img = Image.fromarray(debug_overlay, "RGBA")
        out_img.save(output_debug)
        print(f"\n[✓] Visual conflict map saved to: {output_debug}")
        
    return False

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Analyze GBA tilesets/maps for 4bpp (16-color) tile overflows.")
    parser.add_argument("image", type=Path, help="Tileset, overworld sheet, or battle background to analyze")
    parser.add_argument("--debug-out", type=Path, default=None, help="Path to save the highlighted collision map (e.g. conflicts.png)")
    parser.add_argument("--max-colors", type=int, default=16, help="Maximum allowed colors per tile (Default: 16)")
    args = parser.parse_args()

    scan_for_palette_conflicts(args.image, args.debug_out, args.max_colors)
