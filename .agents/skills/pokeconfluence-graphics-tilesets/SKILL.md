---
name: pokeconfluence-graphics-tilesets
description: Compiling, editing, and debugging GBA tilesets, metatiles, palettes, and sprites using porytiles, porypal, and gbagfx. Activates when editing tilesets or maps.
---

# Pokémon Confluence Graphics & Tilesets Skill

This skill guides creating, editing, and compiling tilesets and graphics using `porytiles`, `porypal`, `porymap`, and `gbagfx`.

## 1. Porytiles Compilation Workflow
Modern tilesets are compiled using `porytiles`:
```bash
# Compile dual-layer primary tileset
tools/porytiles-linux-amd64/porytiles compile-primary \
    -o pokeconfluence/data/tilesets/primary/general/ \
    pokeconfluence/data/tilesets/primary/general/source/

# Compile secondary tileset with primary pairing
tools/porytiles-linux-amd64/porytiles compile-secondary \
    -o pokeconfluence/data/tilesets/secondary/crystal_train_station/ \
    pokeconfluence/data/tilesets/secondary/crystal_train_station/source/ \
    pokeconfluence/data/tilesets/primary/general/
```

## 2. Palette Allocation Principles
- **Slots 0..5 (Primary)**: Standard outdoor elements (grass, water, common roofs, trees, paths).
- **Slots 6..12 (Secondary)**: Area-specific tiles (e.g. train tracks, neon lights, gym decorations, mountain peaks).
- **Slots 13..15**: Dialogue boxes, text palettes, system windows.
- Any secondary tileset requesting more than 7 palette slots will trigger a compilation error in `porytiles` or corrupt the text engine in-game.

## 3. Metatile Structure
Each 16x16 metatile consists of 8 entries:
- 4 bottom layer tiles (8x8 tile ID + palette slot + X-flip + Y-flip).
- 4 top layer tiles (8x8 tile ID + palette slot + X-flip + Y-flip).
- 1 behavior/collision byte (e.g., `MB_NORMAL`, `MB_TALL_GRASS`, `MB_WATER`, `MB_IMPASSABLE_WALL`).

## 4. Transparent Pixel 0 Rule
- Color 0 of every palette is strictly transparent on GBA hardware.
- If importing GBC sprites or tiles where color 0 was opaque white, run `poke-palette-shift` to shift all color indices up by 1 before converting to 4bpp.

