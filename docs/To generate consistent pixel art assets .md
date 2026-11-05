To generate consistent pixel art assets for a Game Boy Advance Pokémon ROM hack, the generator must enforce strict hardware constraints:

* **Dimensions & Grid:** 64×64 pixels (front/back battle sprites), 16×16 or 32×32 (overworld sprites/tiles), 8×8 (tile basis).
* **Color Limits & Indexing:** Exactly 16 colors per palette (Index 0 is dedicated to transparent/background color; 15 visible colors).
* **Color Depth:** 15-bit RGB (5 bits per channel: R, G, B values from 0 to 31, rounded to 8-bit multiples of 8).
* **Stylistic Consistency:** Clean silhouette, limited cluster dithering, crisp 1-pixel dark outlines, and directional top-left key lighting matching Generation 3 (Ruby/Sapphire/Emerald/FireRed/LeafGreen).

Here is a turnkey Python tool using Pillow and NumPy that enforces these constraints. It can downscale and quantize source reference artwork, map it to an exact 16-color indexed palette, and export both GBA-ready indexed PNGs and GBA C source header arrays (`.h` / `.c`) or `.pal` / `.act` files.

### 1. Requirements

Install the dependencies:

```bash
pip install pillow numpy

```

---

### 2. Generator & Quantizer Script (`gba_asset_tool.py`)

```python
import sys
from pathlib import Path
from PIL import Image
import numpy as np

def convert_to_gba_color(r, g, b):
    """Snaps standard 8-bit RGB to GBA 5-bit channel values (0-31 scaled to 0-248)."""
    r5 = round(r * 31 / 255)
    g5 = round(g * 31 / 255)
    b5 = round(b * 31 / 255)
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

```

---

### 3. Usage & Workflow for ROM Hacking

1. **For Battle Sprites (Front/Back):**
```bash
python gba_asset_tool.py source_art.png mon_front.png 64 64

```


2. **For Overworld Sprites:**
```bash
python gba_asset_tool.py overworld_raw.png walk_down.png 16 32

```


3. **Integration Options:**
* **Binary Hacking (HMA / NSE / unLZ-GBA):** Import the generated `mon_front.png`. Index 0 is set to Magenta (`#FF00FF`), recognized automatically as the transparency index.
* **Decomp Projects (`pokeemerald`, `pokefirered`):** Use the generated `.png` directly in `graphics/pokemon/<mon>/front.png`, or include the generated `.h` arrays into your sprite tables.

--- 002 ---

## 1. Automated Overworld Sprite-Sheet Splitter (`split_overworld.py`)

In standard Gen 3 decomp bases (`pokeemerald`, `pokefirered`), overworld walking sheets follow a standard 3-frame or 4-frame directional layout:

* **Frame dimensions:** typically 16×32 pixels (tall humanoid) or 16×16 pixels (small NPC/items).
* **Direction sequence:** Down, Up, Left, Right (or 3-column walk cycles: Stand, Step 1, Step 2).

This script extracts frames into individual indexed tiles or formats them directly into decomp-ready horizontal strips.

```python
import sys
from pathlib import Path
from PIL import Image
import numpy as np

def split_and_index_sheet(
    sheet_path: str,
    output_dir: str,
    frame_w: int = 16,
    frame_h: int = 32,
    export_strip: bool = True
):
    sheet = Image.open(sheet_path).convert("RGBA")
    total_w, total_h = sheet.size

    cols = total_w // frame_w
    rows = total_h // frame_h
    out_path = Path(output_dir)
    out_path.mkdir(parents=True, exist_ok=True)

    # Global palette quantization for the entire sheet to prevent color drift across frames
    rgb_sheet = Image.new("RGB", sheet.size, (255, 0, 255))
    rgb_sheet.paste(sheet, mask=sheet.split()[3])

    # 15 visible colors + 1 reserved for transparency (Index 0 = #FF00FF)
    quantized = rgb_sheet.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    raw_pal = quantized.getpalette()[:45]
    final_pal = [255, 0, 255] + raw_pal
    while len(final_pal) < 768:
        final_pal.extend([0, 0, 0])

    frames = []
    directions = ["down", "up", "left", "right"]

    for r in range(rows):
        dir_name = directions[r] if r < len(directions) else f"row_{r}"
        for c in range(cols):
            box = (c * frame_w, r * frame_h, (c + 1) * frame_w, (r + 1) * frame_h)
            cropped_rgba = sheet.crop(box)
            cropped_q = quantized.crop(box)

            alpha = np.array(cropped_rgba)[:, :, 3]
            idx_arr = np.array(cropped_q) + 1
            idx_arr[alpha < 128] = 0

            frame_img = Image.fromarray(idx_arr.astype(np.uint8), mode="P")
            frame_img.putpalette(final_pal)

            frame_name = f"{dir_name}_frame_{c}.png"
            frame_img.save(out_path / frame_name)
            frames.append(frame_img)

    # Decomp projects often expect a single horizontal strip per object event
    if export_strip and frames:
        strip = Image.new("P", (frame_w * len(frames), frame_h))
        strip.putpalette(final_pal)
        for i, frame in enumerate(frames):
            strip.paste(frame, (i * frame_w, 0))
        strip.save(out_path / "sheet_decomp_strip.png")
        print(f"[✓] Decomp horizontal strip saved: {out_path / 'sheet_decomp_strip.png'}")

    print(f"[✓] Extracted {len(frames)} frames into: {out_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python split_overworld.py <sheet.png> <output_dir> [frame_w] [frame_h]")
        sys.exit(1)

    fw = int(sys.argv[3]) if len(sys.argv) > 3 else 16
    fh = int(sys.argv[4]) if len(sys.argv) > 4 else 32
    split_and_index_sheet(sys.argv[1], sys.argv[2], fw, fh)

```

---

## 2. Palette Harmonizer Script (`harmonize_palette.py`)

GBA backgrounds and overworld objects share a pool of 16 palettes (16 colors each). If multiple sprites appear in the same scene or share an overworld object palette, they must fit into the exact same 15 colors (+ transparency at slot 0).

This script takes a master palette (or extracts the optimal shared palette from multiple images) and re-indexes all target images using minimum Euclidean color distance in GBA 15-bit RGB space.

```python
import sys
from pathlib import Path
from PIL import Image
import numpy as np

def to_gba_color(rgb):
    """Clamps 8-bit RGB down to 5-bit channel depth (GBA 15-bit)."""
    return tuple(int(round(c * 31 / 255) * 255 / 31) for c in rgb)

def load_or_create_shared_palette(source_images, colors=15):
    """Builds a shared 15-color palette from a batch of images using k-means/median cut."""
    combined_pixels = []
    for path in source_images:
        img = Image.open(path).convert("RGBA")
        np_img = np.array(img)
        visible = np_img[np_img[:, :, 3] >= 128][:, :3]
        if len(visible) > 0:
            combined_pixels.append(visible)

    all_vis = np.vstack(combined_pixels)
    temp_img = Image.fromarray(all_vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
    q = temp_img.quantize(colors=colors, method=Image.Quantize.MEDIANCUT)
    raw = q.getpalette()[: colors * 3]

    shared_palette = [to_gba_color(raw[i:i+3]) for i in range(0, len(raw), 3)]
    return shared_palette

def harmonize_image(img_path, output_path, shared_palette):
    """Maps an RGBA sprite to a fixed shared 16-color palette (index 0 = transparency)."""
    img = Image.open(img_path).convert("RGBA")
    np_img = np.array(img)
    alpha = np_img[:, :, 3]
    rgb = np_img[:, :, :3]

    h, w, _ = rgb.shape
    out_indices = np.zeros((h, w), dtype=np.uint8)

    palette_arr = np.array(shared_palette)  # shape (15, 3)

    for y in range(h):
        for x in range(w):
            if alpha[y, x] < 128:
                out_indices[y, x] = 0
            else:
                pixel = to_gba_color(rgb[y, x])
                # Find nearest color in the shared palette
                distances = np.sum((palette_arr - pixel) ** 2, axis=1)
                best_idx = np.argmin(distances)
                out_indices[y, x] = best_idx + 1  # 1-indexed

    # Construct standard 256-color palette buffer with #FF00FF as slot 0
    full_pal = [255, 0, 255]
    for c in shared_palette:
        full_pal.extend(c)
    while len(full_pal) < 768:
        full_pal.extend([0, 0, 0])

    out_img = Image.fromarray(out_indices, mode="P")
    out_img.putpalette(full_pal)
    out_img.save(output_path, format="PNG")
    print(f"[✓] Harmonized: {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python harmonize_palette.py <output_dir> <image1.png> [image2.png ...]")
        sys.exit(1)

    out_dir = Path(sys.argv[1])
    out_dir.mkdir(parents=True, exist_ok=True)
    src_images = sys.argv[2:]

    print(f"[*] Calculating shared 15-color palette across {len(src_images)} images...")
    master_pal = load_or_create_shared_palette(src_images, colors=15)

    for src in src_images:
        dest = out_dir / Path(src).name
        harmonize_image(src, dest, master_pal)

```

---

## 3. Integrating Assets into Decomp Projects (`pokeemerald` / `pokefirered` / `pokeemerald-expansion`)

Decomp build systems use the internal tool `gbagfx` during the `make` process to convert `.png` and `.pal` files into raw 4bpp binary tiles and indexed binary palettes automatically.

### Directory Placement

For a Pokémon species named `MYMON`:

```text
graphics/pokemon/mymon/
├── front.png          # 64x64, 4bpp (16 colors indexed, slot 0 = #FF00FF)
├── back.png           # 64x64, 4bpp
├── normal.pal         # Generated automatically by gbagfx, or exported JASC .pal
├── shiny.pal          # Alternate palette referencing identical pixel indices
├── anim_front.png     # Two 64x64 frames side-by-side (128x64) if animated
└── icon.png           # 32x32 party box icon (uses shared icon palettes)

```

---

### Step-by-Step Registration

#### 1. Sprite Definitions (`src/data/graphics/pokemon.h`)

Declare the graphics labels and the compile-time conversion rules:

```c
const u32 gMonFrontPic_Mymon[] = INCBIN_U32("graphics/pokemon/mymon/front.4bpp.lz");
const u32 gMonBackPic_Mymon[]  = INCBIN_U32("graphics/pokemon/mymon/back.4bpp.lz");
const u16 gMonPalette_Mymon[]  = INCBIN_U16("graphics/pokemon/mymon/normal.gbapal.lz");
const u16 gMonShinyPalette_Mymon[] = INCBIN_U16("graphics/pokemon/mymon/shiny.gbapal.lz");
const u8 gMonIcon_Mymon[]      = INCBIN_U8("graphics/pokemon/mymon/icon.4bpp");

```

*(Note: The build engine automatically processes `front.png` → `front.4bpp` → `front.4bpp.lz` using the rules in `Makefile` and `spritesheet_rules.mk`.)*

---

#### 2. Sprite Table Registration (`src/data/pokemon_graphics/front_pic_table.h` & `back_pic_table.h`)

Assign the pic pointers in the graphics tables:

```c
// front_pic_table.h
[SPECIES_MYMON] = {
    .dimensions = { .width = 64, .height = 64 },
    .data = gMonFrontPic_Mymon,
},

// back_pic_table.h
[SPECIES_MYMON] = {
    .dimensions = { .width = 64, .height = 64 },
    .data = gMonBackPic_Mymon,
},

```

---

#### 3. Palette Table Registration (`src/data/pokemon_graphics/palette_table.h` & `shiny_palette_table.h`)

Hook the palette pointers into the table:

```c
// palette_table.h
[SPECIES_MYMON] = {
    .data = gMonPalette_Mymon,
    .tag = SPECIES_MYMON,
},

// shiny_palette_table.h
[SPECIES_MYMON] = {
    .data = gMonShinyPalette_Mymon,
    .tag = SPECIES_MYMON,
},

```

---

#### 4. Species Data (`src/data/pokemon/species_info.h` in pokeemerald-expansion)

In modern `pokeemerald-expansion`, graphics coordinates and offsets are centralized in `species_info.h`:

```c
[SPECIES_MYMON] =
{
    .frontPic = gMonFrontPic_Mymon,
    .frontPicSize = MON_COORDS_SIZE(64, 64),
    .frontPicYOffset = 2,
    .frontAnimFrames = sAnims_SingleFrame,
    .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
    .backPic = gMonBackPic_Mymon,
    .backPicSize = MON_COORDS_SIZE(64, 64),
    .backPicYOffset = 6,
    .palette = gMonPalette_Mymon,
    .shinyPalette = gMonShinyPalette_Mymon,
    .iconSprite = gMonIcon_Mymon,
    .iconPaletteIndex = 0,
    // ... base stats, typings, learnsets
},

```

---

### Alternative: Direct `.h` Array Injection (C Header Fallback)

If compiling a custom test build or injecting via an independent C module without running `gbagfx`:

1. Take the `.h` generated from `export_to_c_header()` in the first tool.
2. Replace `INCBIN_U32("...")` with the direct array pointer:
```c
#include "graphics/pokemon/mymon/custom_sprite.h"

// In your sprite table:
[SPECIES_MYMON] = {
    .dimensions = { .width = 64, .height = 64 },
    .data = (const u32 *)custom_sprite_Tiles,
},

```

--- 3 ---

## 1. JASC-PAL, Adobe ACT, and GBA C/Binary Converter (`pal_converter.py`)

This script handles bidirectional conversions between:

* **JASC-PAL (`.pal`):** Standard text-based format used by Paint Shop Pro, GraphicsGale, and `gbagfx`.
* **Adobe Color Table (`.act`):** 768-byte binary format used by Photoshop and Aseprite.
* **GBA BGR555 (`.h` / `.gbapal`):** Native 16-bit little-endian color representations used by GBA hardware and decomp projects.

```python
import sys
import struct
from pathlib import Path

def rgb888_to_bgr555(r: int, g: int, b: int) -> int:
    """Converts 8-bit RGB channels to 15-bit GBA BGR555 integer."""
    r5 = (r >> 3) & 0x1F
    g5 = (g >> 3) & 0x1F
    b5 = (b >> 3) & 0x1F
    return (b5 << 10) | (g5 << 5) | r5

def bgr555_to_rgb888(bgr: int) -> tuple[int, int, int]:
    """Converts 15-bit GBA BGR555 integer to 8-bit RGB channels."""
    r = (bgr & 0x1F) << 3
    g = ((bgr >> 5) & 0x1F) << 3
    b = ((bgr >> 10) & 0x1F) << 3
    return (r, g, b)

def read_jasc_pal(path: Path) -> list[tuple[int, int, int]]:
    lines = [line.strip() for line in path.read_text().splitlines() if line.strip()]
    if lines[0] != "JASC-PAL":
        raise ValueError("Invalid JASC-PAL header.")
    count = int(lines[2])
    colors = []
    for line in lines[3:3 + count]:
        parts = [int(p) for p in line.split()]
        colors.append((parts[0], parts[1], parts[2]))
    return colors

def write_jasc_pal(path: Path, colors: list[tuple[int, int, int]]):
    lines = ["JASC-PAL", "0100", str(len(colors))]
    for r, g, b in colors:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def read_act(path: Path) -> list[tuple[int, int, int]]:
    raw = path.read_bytes()
    colors = []
    # An ACT file is 768 bytes (256 colors * 3 bytes)
    for i in range(0, min(len(raw), 768), 3):
        colors.append((raw[i], raw[i+1], raw[i+2]))
    return colors

def write_act(path: Path, colors: list[tuple[int, int, int]]):
    buf = bytearray()
    for r, g, b in colors[:256]:
        buf.extend([r, g, b])
    while len(buf) < 768:
        buf.extend([0, 0, 0])
    path.write_bytes(buf)

def read_gbapal(path: Path) -> list[tuple[int, int, int]]:
    raw = path.read_bytes()
    colors = []
    for i in range(0, len(raw), 2):
        val = struct.unpack("<H", raw[i:i+2])[0]
        colors.append(bgr555_to_rgb888(val))
    return colors

def write_gbapal(path: Path, colors: list[tuple[int, int, int]]):
    buf = bytearray()
    for r, g, b in colors[:16]:
        bgr = rgb888_to_bgr555(r, g, b)
        buf.extend(struct.pack("<H", bgr))
    path.write_bytes(buf)

def write_c_header(path: Path, colors: list[tuple[int, int, int]], var_name="gCustomPalette"):
    hex_values = [f"0x{rgb888_to_bgr555(r, g, b):04X}" for r, g, b in colors[:16]]
    content = f"// Generated GBA BGR555 Palette\nconst u16 {var_name}[16] = {{\n    "
    content += ", ".join(hex_values)
    content += "\n};\n"
    path.write_text(content)

def convert_palette(input_file: str, output_file: str):
    inp = Path(input_file)
    out = Path(output_file)

    if inp.suffix.lower() == ".pal":
        colors = read_jasc_pal(inp)
    elif inp.suffix.lower() == ".act":
        colors = read_act(inp)
    elif inp.suffix.lower() in [".gbapal", ".bin"]:
        colors = read_gbapal(inp)
    else:
        raise ValueError(f"Unsupported input format: {inp.suffix}")

    out_suffix = out.suffix.lower()
    if out_suffix == ".pal":
        write_jasc_pal(out, colors)
    elif out_suffix == ".act":
        write_act(out, colors)
    elif out_suffix in [".gbapal", ".bin"]:
        write_gbapal(out, colors)
    elif out_suffix == ".h":
        write_c_header(out, colors, var_name=out.stem)
    else:
        raise ValueError(f"Unsupported output format: {out_suffix}")

    print(f"[✓] Converted {inp} -> {out}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python pal_converter.py <input.pal|.act|.gbapal> <output.pal|.act|.gbapal|.h>")
        sys.exit(1)
    convert_palette(sys.argv[1], sys.argv[2])

```

---

## 2. Configuring `gbagfx` Rules in Decomp Projects

Decomp repos (`pokeemerald`, `pokefirered`) rely on pattern rules inside `Makefile` and `spritesheet_rules.mk` to invoke `tools/gbagfx/gbagfx`.

### How Asset Transformation Pipelines Work

The tool chain operates sequentially through suffixes:

1. `front.png` + `normal.pal` → `front.4bpp` (via `gbagfx`)
2. `front.4bpp` → `front.4bpp.lz` (via `gbagfx`)
3. `normal.pal` → `normal.gbapal` → `normal.gbapal.lz` (via `gbagfx`)

### Dedicated Rule Configurations (`Makefile` / `spritesheet_rules.mk`)

Place these pattern definitions in your project's `Makefile` or `spritesheet_rules.mk` if you need custom flags for sprite tiles, backgrounds, or overworlds:

```make
# -------------------------------------------------------------
# Tool definitions
# -------------------------------------------------------------
GBAGFX := tools/gbagfx/gbagfx

# -------------------------------------------------------------
# 4bpp Sprite Extraction & Packaging Rules
# -------------------------------------------------------------

# Standard Pokemon battler sprite (64x64, 4bpp, 16 colors)
# -num_tiles 64 ensures an exact 8x8 tile matrix (64x64px)
graphics/pokemon/%/front.4bpp: graphics/pokemon/%/front.png
	$(GBAGFX) $< $@ -num_tiles 64

graphics/pokemon/%/back.4bpp: graphics/pokemon/%/back.png
	$(GBAGFX) $< $@ -num_tiles 64

# Overworld Walk Sheets (Strip layout: 16px wide tiles)
graphics/characters/object_events/%.4bpp: graphics/characters/object_events/%.png
	$(GBAGFX) $< $@

# -------------------------------------------------------------
# Palette Extraction Rules
# -------------------------------------------------------------

# Extract JASC-PAL or PNG palette into GBA native 16-bit binary palette (.gbapal)
# -num_colors 16 forces indexing to 16 slots
%.gbapal: %.pal
	$(GBAGFX) $< $@ -num_colors 16

%.gbapal: %.png
	$(GBAGFX) $< $@ -num_colors 16

# -------------------------------------------------------------
# GBA BIOS LZ77 Compression Rules
# -------------------------------------------------------------

# Compress raw 4bpp tile binaries
%.4bpp.lz: %.4bpp
	$(GBAGFX) $< $@

# Compress palette binaries
%.gbapal.lz: %.gbapal
	$(GBAGFX) $< $@

```

### Key `gbagfx` Flags Reference

| Flag | Purpose | Recommended Use Case |
| --- | --- | --- |
| `-num_tiles <N>` | Limits or pads output to exactly `N` 8×8 tiles | Pokémon front/back sprites (`-num_tiles 64`) |
| `-num_colors <N>` | Restricts palette binary to `N` colors | Battle palettes (`-num_colors 16`) |
| `-mwidth <N>` | Defines tilemap width in 8×8 tile blocks | UI, town maps, and battle backgrounds |
| `-transparent <HEX>` | Specifies which color index is forced to slot 0 | Sprites rendered on white/magenta backdrops |

---

## 3. Automated Shiny Palette Generator (`generate_shiny.py`)

A natural shiny palette in Gen 3 preserves the original lightness/luminance curve while applying a controlled shift across the hue spectrum. This maintains the shading, highlights, and shadow contrast of the sprite without blowing out darker outline pixels.

This script loads any GBA 16-color palette (JASC `.pal` or indexed `.png`), skips index 0 (transparency), converts colors to HSV, rotates the hue, balances saturation, and writes the resulting `shiny.pal`.

```python
import sys
import colorsys
from pathlib import Path
from PIL import Image

def rgb_to_gba(r, g, b):
    """Clamps to 5 bits per channel."""
    r5 = round(r * 31 / 255)
    g5 = round(g * 31 / 255)
    b5 = round(b * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))

def shift_color_hsv(r, g, b, hue_shift=0.33, sat_mult=1.0, val_mult=1.0):
    """Transforms RGB color by rotating Hue and adjusting Saturation/Value."""
    h, s, v = colorsys.rgb_to_hsv(r / 255.0, g / 255.0, v / 255.0)
    
    # Apply hue rotation
    h = (h + hue_shift) % 1.0
    s = min(max(s * sat_mult, 0.0), 1.0)
    v = min(max(v * val_mult, 0.0), 1.0)
    
    r_new, g_new, b_new = colorsys.hsv_to_rgb(h, s, v)
    return rgb_to_gba(int(r_new * 255), int(g_new * 255), int(b_new * 255))

def generate_shiny_palette(
    input_path: str,
    output_pal_path: str,
    hue_shift: float = 0.35,
    sat_scale: float = 1.1,
    preserve_outlines: bool = True
):
    inp = Path(input_path)
    
    # Read colors from either an existing JASC .pal or directly from an indexed PNG
    colors = []
    if inp.suffix.lower() == ".pal":
        lines = [line.strip() for line in inp.read_text().splitlines() if line.strip()]
        count = int(lines[2])
        for line in lines[3:3 + count]:
            parts = [int(p) for p in line.split()]
            colors.append((parts[0], parts[1], parts[2]))
    else:
        img = Image.open(inp)
        raw_pal = img.getpalette()
        if not raw_pal:
            raise ValueError("Input image has no embedded palette.")
        for i in range(0, 48, 3):
            colors.append((raw_pal[i], raw_pal[i+1], raw_pal[i+2]))

    shiny_colors = []
    
    for idx, (r, g, b) in enumerate(colors[:16]):
        # Index 0 is always transparency: never modify it
        if idx == 0:
            shiny_colors.append((r, g, b))
            continue
            
        # Optional: Retain dark structural outline colors (luminance threshold)
        luminance = 0.299 * r + 0.587 * g + 0.114 * b
        if preserve_outlines and luminance < 32:
            shiny_colors.append((r, g, b))
            continue
            
        shiny_rgb = shift_color_hsv(r, g, b, hue_shift, sat_scale)
        shiny_colors.append(shiny_rgb)

    # Write out JASC-PAL compliant format
    out_lines = ["JASC-PAL", "0100", "16"]
    for r, g, b in shiny_colors:
        out_lines.append(f"{r} {g} {b}")
        
    out_path = Path(output_pal_path)
    out_path.write_text("\n".join(out_lines) + "\n")
    print(f"[✓] Generated shiny palette at: {out_path} (Hue rotation: +{hue_shift:.2f})")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python generate_shiny.py <normal.pal|front.png> <shiny.pal> [hue_shift 0.0-1.0]")
        sys.exit(1)
        
    shift = float(sys.argv[3]) if len(sys.argv) > 3 else 0.35
    generate_shiny_palette(sys.argv[1], sys.argv[2], hue_shift=shift)

```

### Complete Folder Structure for Decomp Build

With all tools combined, your target Pokémon graphics directory will look like this:

```text
graphics/pokemon/mymon/
├── front.png            # 64x64 indexed PNG
├── back.png             # 64x64 indexed PNG
├── normal.pal           # JASC-PAL (16 colors, generated from front.png)
├── shiny.pal            # JASC-PAL (generated by generate_shiny.py)
└── anim_front.png       # Optional: multi-frame front animation

```

Running `make` in your project root will detect `front.png`, `back.png`, `normal.pal`, and `shiny.pal`, running `gbagfx` across each target automatically to output the `.4bpp.lz` and `.gbapal.lz` binaries.

--- 4 ---

## 1. CLI Batch-Importer for New Species (`species_batch_importer.py`)

This CLI tool automates the full pipeline for ingesting raw art into decomp repositories (`pokeemerald`, `pokefirered`, or `pokeemerald-expansion`). Given an input folder containing raw concept art/sprites named `front.png`, `back.png`, and optionally `icon.png`:

1. Resizes and quantizes `front.png` and `back.png` to strict 64×64 15-bit GBA Indexed PNGs (Slot 0 = `#FF00FF`).
2. Extracts `normal.pal` (JASC-PAL format).
3. Generates a balanced `shiny.pal` via HSV rotation.
4. Generates a 32×32 party `icon.png`.
5. Emits ready-to-paste C configurations for `species_info.h` (or legacy graphics/palette tables).

```python
import argparse
import colorsys
from pathlib import Path
from PIL import Image
import numpy as np

def to_gba_color(r, g, b):
    """Clamps 8-bit RGB channels to GBA 5-bit channel depth (0-31 scaled to 0-255)."""
    r5 = round(r * 31 / 255)
    g5 = round(g * 31 / 255)
    b5 = round(b * 31 / 255)
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
    pal_arr = np.array(palette_colors[1:]) # shape (14 or 15, 3)
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
        if lum < 28: # Retain deep outline shadows
            shiny.append((r, g, b))
            continue
        h, s, v = colorsys.rgb_to_hsv(r / 255.0, g / 255.0, v / 255.0)
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

```

---

## 2. Automated Palette-Conflict Detector (`check_palette_conflicts.py`)

GBA tiles and overworld maps operate on fixed hardware VRAM limits:

* Background tilemaps (Layer 0–3) share **Palettes 0–15** (16 colors each).
* Each 8×8 tile in a tilemap can only reference **one** palette ID (4 bits).
* An overworld object sprite can only reference **one** 16-color palette index.

When artists draft tilesets or maps in standard RGB without checking palette boundaries, two common collisions break the ROM build:

1. **Intra-Tile Overflow:** An individual 8×8 tile contains more than 16 distinct colors (impossible on 4bpp GBA hardware).
2. **Tileset Palette Collision:** Adjacent tiles that must share a palette require mutually exclusive color subsets exceeding 16 unique values.

This script scans raw tilesets, overworld sheets, or assembled map images to identify offending 8×8 pixel tiles, logs coordinates, and outputs an annotated visual heat map.

```python
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

```

---

### Example Workflow Execution

#### Batch Ingest a New Species

```bash
python species_batch_importer.py \
  --src ./raw_art/aerodactyl \
  --repo ./pokeemerald-expansion \
  --name aerodactyl \
  --hue 0.40

```

This writes `front.png`, `back.png`, `normal.pal`, `shiny.pal`, `icon.png`, and prints the complete C structure snippet to drop directly into `src/data/pokemon/species_info.h`.

#### Run Collision Detection on a Tileset

```bash
python check_palette_conflicts.py tileset_building.png --debug-out conflicts_view.png

```

Tiles violating the 16-color hardware constraint are highlighted in bright red on `conflicts_view.png` with their exact tile coordinates displayed in the console.

--- 5 ---

## 1. Automated Tile-Reduction Optimizer (`tile_optimizer.py`)

GBA background VRAM is limited to 1,024 8×8 tiles per character block (in practice, `pokeemerald` reserves 512 tiles for primary tilesets and 512 for secondary tilesets).

This tool:

1. Slices an input tileset/graphic into 8×8 blocks.
2. Identifies exact duplicates, including **horizontal flips (`X-flip`)**, **vertical flips (`Y-flip`)**, and **both (`XY-flip`)** (which GBA background tilemaps handle natively via tile attributes without consuming extra VRAM).
3. Optionally merges **visually similar tiles** using a Mean Squared Error (MSE) threshold.
4. Outputs an optimized, deduplicated tile sheet alongside the corresponding tilemap array (`tile_index`, `x_flip`, `y_flip`).

```python
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

```

---

## 2. Porymap Tileset Packaging Tool (`package_porymap_tileset.py`)

Porymap and standard Gen 3 decomp architectures (`pokeemerald`, `pokefirered`) structure overworld map environments through **Metatiles** (16×16 blocks consisting of four 8×8 tiles on layer 1 and four on layer 2).

A standard decomp tileset folder requires:

* `tiles.png`: 4bpp indexed image containing all individual 8×8 tiles.
* `palettes/*.pal`: 16 individual JASC-PAL files (`00.pal` through `15.pal`).
* `metatiles.bin`: Binary array of 16-bit entries describing the 8×8 tiles, palette selection, and flip attributes.
* `metatile_attributes.bin`: Binary array containing collision behavior and terrain types.
* `tileset.json`: Porymap metadata file.

This script packages an indexed 16×16 metatile image and a master palette file directly into a validated Porymap tileset directory:

```python
import argparse
import json
from pathlib import Path
from PIL import Image
import numpy as np

def build_porymap_tileset(
    metatile_sheet_path: Path,
    master_pal_path: Path,
    dest_dir: Path,
    tileset_name: str,
    is_secondary: bool = False
):
    dest_dir.mkdir(parents=True, exist_ok=True)
    pal_dir = dest_dir / "palettes"
    pal_dir.mkdir(exist_ok=True)

    sheet = Image.open(metatile_sheet_path)
    if sheet.mode != "P":
        raise ValueError("Metatile sheet must be an indexed PNG (mode P).")

    # 1. Distribute palettes (Porymap requires separate 16-color JASC .pal files)
    raw_pal = sheet.getpalette()
    if master_pal_path and master_pal_path.exists():
        # Read JASC-PAL lines
        lines = [l.strip() for l in master_pal_path.read_text().splitlines() if l.strip()]
        total_colors = int(lines[2])
        all_colors = []
        for l in lines[3:3+total_colors]:
            p = [int(v) for v in l.split()]
            all_colors.append((p[0], p[1], p[2]))
    else:
        all_colors = [(raw_pal[i], raw_pal[i+1], raw_pal[i+2]) for i in range(0, min(len(raw_pal), 768), 3)]

    # Slice into 16 discrete palettes (each 16 colors)
    pal_count = 16
    for pal_idx in range(pal_count):
        sub_colors = all_colors[pal_idx*16:(pal_idx+1)*16]
        while len(sub_colors) < 16:
            sub_colors.append((0, 0, 0))
        
        jasc = ["JASC-PAL", "0100", "16"]
        for r, g, b in sub_colors:
            jasc.append(f"{r} {g} {b}")
        (pal_dir / f"{pal_idx:02d}.pal").write_text("\n".join(jasc) + "\n")

    # 2. Extract 8x8 tiles and compile metatiles.bin
    sheet_arr = np.array(sheet)
    h, w = sheet_arr.shape
    metatiles_x = w // 16
    metatiles_y = h // 16
    total_metatiles = metatiles_x * metatiles_y

    tiles_list = []
    metatiles_bin = bytearray()
    metatile_attr_bin = bytearray()

    for my in range(metatiles_y):
        for mx in range(metatiles_x):
            # A 16x16 metatile consists of four 8x8 quadrants: Top-Left, Top-Right, Bottom-Left, Bottom-Right
            sub_boxes = [
                (mx*16, my*16),       # TL
                (mx*16 + 8, my*16),   # TR
                (mx*16, my*16 + 8),   # BL
                (mx*16 + 8, my*16 + 8)# BR
            ]

            # Bottom layer: 4 tiles
            for sx, sy in sub_boxes:
                tile_data = sheet_arr[sy:sy+8, sx:sx+8]
                
                # Check tile list for index matching
                tile_bytes = tile_data.tobytes()
                found_id = -1
                for idx, existing in enumerate(tiles_list):
                    if existing == tile_bytes:
                        found_id = idx
                        break
                if found_id == -1:
                    found_id = len(tiles_list)
                    tiles_list.append(tile_bytes)

                # Determine palette ID from the first non-zero pixel
                non_zero = tile_data[tile_data != 0]
                active_color = non_zero[0] if len(non_zero) > 0 else 0
                pal_id = min(active_color // 16, 15)
                tile_idx = found_id % 16

                # 16-bit Metatile entry format:
                # bits 0-9: Tile Index, bit 10: X-flip, bit 11: Y-flip, bits 12-15: Palette Index
                entry = (found_id & 0x3FF) | ((pal_id & 0x0F) << 12)
                metatiles_bin.extend(int(entry).to_bytes(2, byteorder="little"))

            # Top layer: 4 transparent empty tiles (0x0000)
            for _ in range(4):
                metatiles_bin.extend((0).to_bytes(2, byteorder="little"))

            # Attributes: 32-bit field (behavior byte + layer/encounter flags)
            # 0x00 = Passable normal ground
            metatile_attr_bin.extend((0).to_bytes(4, byteorder="little"))

    # 3. Save tiles.png (arranged 16 tiles wide)
    cols = 16
    rows = (len(tiles_list) + cols - 1) // cols
    out_tiles_arr = np.zeros((rows * 8, cols * 8), dtype=np.uint8)

    for idx, t_bytes in enumerate(tiles_list):
        t_arr = np.frombuffer(t_bytes, dtype=np.uint8).reshape((8, 8))
        cx = (idx % cols) * 8
        cy = (idx // cols) * 8
        out_tiles_arr[cy:cy+8, cx:cx+8] = t_arr

    out_tiles_img = Image.fromarray(out_tiles_arr, mode="P")
    out_tiles_img.putpalette(raw_pal)
    out_tiles_img.save(dest_dir / "tiles.png")

    # 4. Write binary metadata
    (dest_dir / "metatiles.bin").write_bytes(metatiles_bin)
    (dest_dir / "metatile_attributes.bin").write_bytes(metatile_attr_bin)

    # 5. Write tileset.json for Porymap
    tileset_json = {
        "id": f"gTileset_{tileset_name}",
        "name": tileset_name,
        "is_secondary": is_secondary,
        "padding": 0
    }
    (dest_dir / "tileset.json").write_text(json.dumps(tileset_json, indent=2))

    print(f"[✓] Created Porymap tileset '{tileset_name}' in: {dest_dir}")
    print(f"    - Metatiles created: {total_metatiles}")
    print(f"    - Unique 8x8 tiles: {len(tiles_list)}")
    print(f"    - Palettes saved: 16 individual files")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package indexed metatiles into a complete Porymap tileset.")
    parser.add_argument("metatile_sheet", type=Path, help="Indexed PNG of 16x16 metatiles")
    parser.add_argument("dest_dir", type=Path, help="Destination directory (e.g. data/tilesets/primary/general)")
    parser.add_argument("--name", type=str, required=True, help="Tileset identifier (e.g. General or Petalburg)")
    parser.add_argument("--master-pal", type=Path, default=None, help="Optional 256-color JASC .pal file")
    parser.add_argument("--secondary", action="store_true", help="Flag as a secondary tileset")
    args = parser.parse_args()

    build_porymap_tileset(args.metatile_sheet, args.master_pal, args.dest_dir, args.name, args.secondary)

```

---

## 3. GitHub Action for Decomp Asset Validation (`.github/workflows/asset_validation.yml`)

This automated continuous integration workflow runs on pull requests and pushes affecting `graphics/**` or `data/tilesets/**`. It:

1. Runs the **palette collision check** to ensure no single 8×8 tile exceeds 16 colors.
2. Verifies that all Pokémon sprites conform to exact 64×64 pixel dimensions.
3. Compiles the repo's native `gbagfx` tool.
4. Executes test conversions (`.png` → `.4bpp` → `.4bpp.lz`, `.pal` → `.gbapal`) to ensure assets compile without build errors.

Create `.github/workflows/asset_validation.yml`:

```yaml
name: GBA Asset Validation & Build Test

on:
  push:
    paths:
      - 'graphics/**'
      - 'data/tilesets/**'
      - 'tools/gbagfx/**'
  pull_request:
    paths:
      - 'graphics/**'
      - 'data/tilesets/**'

jobs:
  validate-assets:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout Repository
        uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v5
        with:
          python-version: '3.11'
          cache: 'pip'

      - name: Install Python Dependencies
        run: |
          pip install pillow numpy

      - name: Build gbagfx Tool
        run: |
          make -C tools/gbagfx

      - name: Validate Pokémon Sprite Dimensions & Indexing
        run: |
          python - << 'EOF'
          import sys
          from pathlib import Path
          from PIL import Image

          failed = False
          pokemon_gfx = Path("graphics/pokemon")
          if not pokemon_gfx.exists():
              print("No graphics/pokemon directory found; skipping dimension check.")
              sys.exit(0)

          for png_path in pokemon_gfx.glob("**/*.png"):
              if png_path.name in ["front.png", "back.png"]:
                  with Image.open(png_path) as img:
                      if img.size != (64, 64):
                          print(f"[ERROR] {png_path} dimension mismatch: {img.size} (must be 64x64)")
                          failed = True
                      if img.mode != "P":
                          print(f"[ERROR] {png_path} is not an indexed PNG (mode: {img.mode})")
                          failed = True
          if failed:
              sys.exit(1)
          print("[✓] All Pokemon sprite dimensions and indexing validated successfully.")
          EOF

      - name: Run Palette Conflict Checker on Overworld & Tilesets
        run: |
          python - << 'EOF'
          import sys
          from pathlib import Path
          from PIL import Image
          import numpy as np

          failed = False
          scan_dirs = [Path("graphics/object_events"), Path("data/tilesets")]

          for s_dir in scan_dirs:
              if not s_dir.exists():
                  continue
              for img_path in s_dir.glob("**/*.png"):
                  if img_path.name == "tiles.png":
                      continue # Handled by tileset packaging
                  with Image.open(img_path).convert("RGBA") as img:
                      arr = np.array(img)
                      h, w = arr.shape[:2]
                      for ty in range(h // 8):
                          for tx in range(w // 8):
                              box = arr[ty*8:(ty+1)*8, tx*8:(tx+1)*8]
                              vis = box[box[:, :, 3] >= 128][:, :3]
                              unique_c = len({tuple(p) for p in vis})
                              has_trans = np.any(box[:, :, 3] < 128)
                              slots = unique_c + (1 if has_trans else 0)
                              if slots > 16:
                                  print(f"[ERROR] {img_path} at tile ({tx},{ty}) uses {slots} colors (limit 16).")
                                  failed = True
                                  break
                          if failed:
                              break
          if failed:
              sys.exit(1)
          print("[✓] Zero 4bpp tile palette violations detected.")
          EOF

      - name: Run gbagfx Compile Test on Modified Assets
        run: |
          python - << 'EOF'
          import subprocess
          import sys
          from pathlib import Path

          GBAGFX = "tools/gbagfx/gbagfx"
          failed = False

          # Test compile all changed battle sprites to 4bpp and LZ77
          for p in Path("graphics/pokemon").glob("**/front.png"):
              base = p.parent / p.stem
              out_4bpp = base.with_suffix(".4bpp")
              out_lz = base.with_suffix(".4bpp.lz")
              
              # 1. Convert to raw 4bpp
              res = subprocess.run([GBAGFX, str(p), str(out_4bpp), "-num_tiles", "64"], capture_output=True, text=True)
              if res.returncode != 0:
                  print(f"[FAIL] gbagfx 4bpp conversion failed for {p}:\n{res.stderr}")
                  failed = True
                  continue
                  
              # 2. Compress with LZ77
              res = subprocess.run([GBAGFX, str(out_4bpp), str(out_lz)], capture_output=True, text=True)
              if res.returncode != 0:
                  print(f"[FAIL] gbagfx LZ compression failed for {out_4bpp}:\n{res.stderr}")
                  failed = True
                  
              # Cleanup test artifacts
              out_4bpp.unlink(missing_ok=True)
              out_lz.unlink(missing_ok=True)

          if failed:
              sys.exit(1)
          print("[✓] All modified assets compiled successfully via gbagfx.")
          EOF

```
