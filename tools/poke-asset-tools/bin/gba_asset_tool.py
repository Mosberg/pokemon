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

import sys
from pathlib import Path
from PIL import Image
import numpy as np

def convert_to_gba_color(r, g, b):
    """Snaps standard 8-bit RGB to GBA 5-bit channel values (0-31 scaled to 0-248)."""
    r5 = round(int(r) * 31 / 255)
    g5 = round(int(g) * 31 / 255)
    b5 = round(int(b) * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))

def process_gba_sprite(input_image_path, output_png_path, target_size=(64, 64), transparent_hex="#000000"):
    """
    Processes an input image into a 16-color indexed PNG compliant with GBA ROM hack standards.
    Slot 0 of the palette is strictly reserved for the background/transparency key.
    """
    img = Image.open(input_image_path).convert("RGBA")
    
    # 1. Resize to target GBA sprite frame (e.g., 64x64) using nearest or box filter to preserve sharp pixels
    img_resized = img.resize(target_size, Image.Resampling.LANCZOS)
    
    # 2. Extract alpha mask
    np_img = np.array(img_resized)
    alpha = np_img[:, :, 3]
    rgb = np_img[:, :, :3]
    
    # Convert pixels to GBA 15-bit color space
    for y in range(target_size[1]):
        for x in range(target_size[0]):
            r, g, b = rgb[y, x]
            rgb[y, x] = convert_to_gba_color(r, g, b)
            
    visible_pixels = Image.fromarray(rgb, "RGB")
    
    # 3. Quantize visible regions to at most 15 colors (reserving 1 slot for transparent background)
    quantized_15 = visible_pixels.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    palette_raw = quantized_15.getpalette()[:45]  # 15 colors * 3 channels
    
    # Construct full 16-color palette: Index 0 = background key (e.g. magenta or black)
    # Magenta #FF00FF is standard for GBA ROM tooling (unLZ, NSE, Porymap)
    bg_color = [255, 0, 255]
    final_palette = bg_color + palette_raw
    
    # Pad to 256 colors as standard for indexed PNG
    while len(final_palette) < 768:
        final_palette.extend([0, 0, 0])
        
    # Remap indices: shift quantized values (0-14) up by 1 (to 1-15), set transparent areas to 0
    idx_array = np.array(quantized_15) + 1
    idx_array[alpha < 128] = 0
    
    # Build final indexed image
    out_img = Image.fromarray(idx_array.astype(np.uint8), mode="P")
    out_img.putpalette(final_palette)
    out_img.save(output_png_path, format="PNG")
    print(f"[✓] GBA Sprite saved: {output_png_path} ({target_size[0]}x{target_size[1]}, 16-color indexed)")

    # Also export standard JASC-PAL
    pal_dest = Path(output_png_path).with_suffix(".pal")
    jasc_lines = ["JASC-PAL", "0100", "16"]
    for i in range(0, 48, 3):
        jasc_lines.append(f"{final_palette[i]} {final_palette[i+1]} {final_palette[i+2]}")
    pal_dest.write_text("\n".join(jasc_lines) + "\n")
    print(f"[✓] JASC-PAL saved: {pal_dest}")

def export_to_c_header(indexed_png_path, header_path, var_name="custom_sprite"):
    """Exports indexed PNG pixel data and palette directly to C arrays for decomp (pokeemerald/pokefirered)."""
    img = Image.open(indexed_png_path)
    if img.mode != "P":
        raise ValueError("Image must be an indexed PNG.")
        
    palette = img.getpalette()[:48]  # First 16 colors (16 * 3)
    
    # Convert palette to GBA 16-bit BGR555 format
    gba_pal = []
    for i in range(0, 48, 3):
        r = palette[i] >> 3
        g = palette[i + 1] >> 3
        b = palette[i + 2] >> 3
        bgr555 = (b << 10) | (g << 5) | r
        gba_pal.append(f"0x{bgr555:04X}")
        
    pixels = np.array(img).flatten()
    
    with open(header_path, "w") as f:
        f.write(f"// Generated GBA Sprite Data: {var_name}\n\n")
        f.write(f"const u16 {var_name}_Pal[16] = {{\n    ")
        f.write(", ".join(gba_pal))
        f.write("\n};\n\n")
        f.write(f"const u8 {var_name}_Tiles[{len(pixels) // 2}] = {{\n")
        
        # Pack two 4-bit pixels into 1 byte (4bpp GBA tile format)
        packed_bytes = []
        for i in range(0, len(pixels), 2):
            p1 = pixels[i] & 0x0F
            p2 = pixels[i + 1] & 0x0F
            packed_bytes.append(f"0x{(p2 << 4) | p1:02X}")
            
        for i in range(0, len(packed_bytes), 16):
            f.write("    " + ", ".join(packed_bytes[i:i+16]) + ",\n")
        f.write("};\n")
    print(f"[✓] C header saved: {header_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python gba_asset_tool.py <input_img> <output_png> [width] [height]")
        sys.exit(1)
        
    w = int(sys.argv[3]) if len(sys.argv) > 3 else 64
    h = int(sys.argv[4]) if len(sys.argv) > 4 else 64
    
    process_gba_sprite(sys.argv[1], sys.argv[2], target_size=(w, h))
    export_to_c_header(sys.argv[2], Path(sys.argv[2]).with_suffix(".h"))
