# Pokémon GBA Asset Studio v1.1.0 (`poke-decomp-asset-studio`)

A professional, high-performance VSCode extension engineered specifically for Pokémon GBA decompilation projects (`pokeemerald`, `pokefirered`, `pokeruby`, `pokecrystal`, `pokeconfluence`).

Features an integrated **Asset Gallery**, **Pixel Inspector**, **16-Color Palette Studio**, **Sprite Animator**, **Planar 4bpp/8bpp Binary Engine**, and **GBA Hardware Engine Compliance Auditor**.

---

## What's New in v1.1.0

### 1. Expanded Drawing Tools & Transforms
- **Line Tool (`L`)**: Bresenham line algorithm with real-time preview overlay while dragging.
- **Rectangle Tool (`U`)**: Outlined or filled bounding boxes.
- **Circle Tool (`C`)**: Midpoint circle and ellipse tool.
- **Color Replace Tool (`R`)**: Click any pixel to replace all occurrences of that palette index across the entire sprite with the active index.
- **Brush Sizes**: 1px, 2px, and 4px square brushes.
- **Sprite Transforms**:
  - **Flip Horizontal (Mirror X)**
  - **Flip Vertical (Mirror Y)**
  - **Rotate 90° Clockwise**

### 2. GBA Binary Planar (.4bpp / .8bpp) Direct Support
- Open and view raw `.4bpp` and `.8bpp` tile binaries.
- Edit pixels directly in the canvas.
- Save directly back to `.4bpp` (32 bytes per 8x8 tile) and `.8bpp` (64 bytes per 8x8 tile) binaries with round-trip fidelity.
- Live VRAM tile counter badge showing exactly how many 8x8 VRAM tiles and bytes your asset consumes.

### 3. Palette Studio & Hardware Tools
- **Auto-Quantize to 16 Colors**: Intelligent median-cut color quantization that snaps arbitrary images to 16 GBA BGR555 colors while preserving Slot 0 as transparent.
- **Tweak Colors Modal**: Non-destructive Brightness (-60 to +60) and Contrast (-60 to +60) adjustment sliders with hardware BGR555 re-quantization.
- **Swap Slots Modal**: Swap any two palette indices across the entire image and palette with one click.
- **Copy C Code**: Copies the GBA C array (`const u16 gPalette_...[16]`) directly to your system clipboard.
- **Additional Palette Formats**: Support for GIMP Palette (`.gpl`) and Adobe Photoshop Color Table (`.act`).

### 4. Animation & Overworld Upgrades
- **1:1 Live Scale Actual Size Preview**: Docked actual GBA screen scale (1x) preview updating in real-time side-by-side as you paint at 800% or 1600%.
- **Onion Skinning**: Faint semi-transparent ghost of frame $N-1$ under the canvas for frame-by-frame walk cycle alignment.
- **Directional Overworld Walk Cycle Animator**: Quick buttons for ⬇️ Down, ⬆️ Up, ⬅️ Left, and ➡️ Right animations.
- **Framerate Slider**: Configurable 1 to 60 FPS playback.

### 5. Activity Bar Gallery & Navigation
- **Generation Filters**: Filter 1,028 species by **All**, **Gen 1 Kanto**, **Gen 2 Johto**, **Gen 3 Hoenn**, or **Gen 4+ / Custom**.
- **Interface & UI Category**: Browse battle interfaces, PokéNav graphics, town maps, title screens, and text window fonts.
- **Live Stats Bar**: Real-time counter of total species, trainers, items, and overworld characters.
- **Project Graphics Audit**: One-click command `pokeAssetStudio.auditAssets` to generate a comprehensive markdown health report of all workspace graphics.

---

## Configuration Settings

You can customize the extension via VSCode Settings (`Ctrl+,` -> search `Pokémon GBA Asset Studio`):

| Setting | Default | Description |
| :--- | :--- | :--- |
| `pokeAssetStudio.defaultZoom` | `8` (800%) | Default zoom factor when opening images (1x, 2x, 4x, 8x, 16x, 32x). |
| `pokeAssetStudio.defaultBackground` | `"checkerboard-dark"` | Default backdrop (`checkerboard-dark`, `checkerboard-light`, `magenta`, `black`, `white`). |
| `pokeAssetStudio.animationFps` | `15` | Default playback framerate for sprite animations (1–60 FPS). |
| `pokeAssetStudio.autoSavePalWithPng` | `true` | Automatically update matching sibling `.pal` when saving an indexed `.png`. |
| `pokeAssetStudio.strictBgr555` | `true` | Strictly enforce GBA 15-bit hardware color depth. |
| `pokeAssetStudio.slotZeroStrict` | `true` | Warn when opaque pixels are assigned to Slot 0 (transparent in GBA PPU). |

---

## Keyboard Shortcuts

| Shortcut | Tool / Action |
| :--- | :--- |
| `B` | Pencil Tool |
| `E` | Eraser Tool (Slot 0 transparent) |
| `L` | Straight Line Tool |
| `U` | Rectangle Box Tool |
| `C` | Circle Tool |
| `G` | Bucket Fill Tool |
| `R` | Replace Color Tool |
| `I` | Eyedropper / Color Picker |
| `H` or `Space` | Pan Tool |
| `Ctrl + Z` | Undo |
| `Ctrl + Y` or `Ctrl + Shift + Z` | Redo |
| `Ctrl + S` | Save Asset |
| `Mouse Wheel` | Nearest-neighbor zoom centered on cursor |
