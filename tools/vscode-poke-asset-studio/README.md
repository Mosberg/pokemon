# Pokémon GBA Asset Studio v1.2.0 (`poke-decomp-asset-studio`)

A professional, high-performance VSCode extension engineered specifically for Pokémon GBA decompilation projects (`pokeemerald`, `pokefirered`, `pokeruby`, `pokecrystal`, `pokeconfluence`).

Features an integrated **Asset Gallery**, **Pixel Inspector**, **16-Color Palette Studio**, **Sprite Animator**, **Planar 4bpp/8bpp Binary Engine**, **GBA Forge Magic Tools**, **GBA Battle Scene Simulator**, and the embedded **Pokémon GBA Forge Studio**.

---

## What's New in v1.2.0 (GBA Forge Integration)

### 1. Embedded Pokémon GBA Forge Studio
- **Launch via Command / Icon**: Run `Pokémon GBA Forge: Open Sprite Generator Studio` (`pokeAssetStudio.openForge`) or click the sparkle `$(sparkle)` icon in the editor title bar.
- **Hardware-Accurate Gen 3 AI Generator**: Generate authentic Ruby/Sapphire/Emerald & FireRed/LeafGreen sprites from text prompts.
- **⚡ Save to pokeconfluence Button**: One-click direct export of generated species straight into `pokeconfluence/graphics/pokemon/<name>/`:
  - `front.png` (64x64)
  - `back.png` (64x64)
  - `anim_front.png` (128x64 authentic 2-frame idle bounce)
  - `icon.png` (64x32 2-frame party menu icon)
  - `footprint.png` (16x16 1-bit Pokédex silhouette)
  - `normal.pal` (JASC-PAL 16 colors)
  - `shiny.pal` (JASC-PAL index-matched shiny swap)

### 2. GBA Forge Magic Tools (In Custom Editor)
Available in the side inspector of any open sprite:
- `✂️ Remove BG`: Flood-fill corner/edge background isolator that strips sketch backgrounds with clean alpha.
- `⚓ Ground Feet`: Official Game Freak battle sprite alignment (centers horizontally, grounds feet 2px from bottom).
- `🎨 Outlines`: Replaces harsh black edges with deep saturated body tones (navy, crimson, dark brown) of matching hue.
- `🎬 Gen Anim`: Synthesizes the authentic Emerald 2-frame front bounce (`anim_front.png`, 128x64) with 2px nudge and 1px squash.
- `⭐ Gen Icon`: Downscales front sprite into a 2-frame party menu icon (`icon.png`, 64x32) with a 2px vertical bob.
- `🐾 Gen Foot`: Stamps a 16x16 1-bit black/white footprint silhouette for the Pokédex (`footprint.png`).
- `🚶 Gen Overworld`: Generates a full 3x4 overworld walking spritesheet (`ow_sheet.png`) across Down, Up, Left, Right.
- `📦 Export Pack`: One-click save of all 6 standard species files directly into the current folder.

### 3. GBA Battle Scene Simulator ($240\times 160$)
- Real-time in-game battle screen mockup right inside the side inspector.
- **Biome Switcher**: Test your sprite across Grass/Field, Ocean/Water, Dark Cave, and Desert/Sand environments.
- **Terrain Platforms**: Renders standard GBA battle ellipses for opponent (`190, 88`) and player (`54, 134`).
- **✨ Toggle Shiny Foe**: Instant preview of normal vs shiny battle presentation.
- **GBA Dialogue Box & Healthbars**: Verifies in-game framing and visibility before compiling.

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
