---
description: Graphics, tileset, and palette conversion rules for GBA hardware
globs: pokeconfluence/data/tilesets/**, pokeconfluence/graphics/**
---

# Graphics & Palette Conversion Standards

All graphical assets in `pokeconfluence/` must adhere to GBA hardware constraints:

## 1. Palette Slot Allocation
- **GBA Palettes**: 16 colors per palette (color 0 is always transparent).
- **Background Palettes (0..12)**:
  - Slots `0` to `5`: Primary tileset (shared across all maps using that primary tileset).
  - Slots `6` to `12`: Secondary tileset (map-specific or area-specific tiles).
  - Slots `13` to `15`: Reserved for text engine, dialogue boxes, and standard UI windows.
- **Sprite Palettes (16..31)**:
  - 16 sprite palette slots available for overworld NPCs, player sprites, and dynamic objects.

## 2. Metatile Limits
- GBA maps use 16x16 metatiles composed of four 8x8 tiles across two layers (bottom and top).
- **Primary Metatiles**: Maximum 512 metatiles per primary tileset.
- **Secondary Metatiles**: Maximum 512 metatiles per secondary tileset.
- **Total Metatiles**: 1024 max addressable per map layout.

## 3. GBC to GBA Color Remapping
- Crystal/Gen 2 used 4 colors per 8x8 tile:
  - Color 0 (often white/transparent)
  - Color 1 (light tone)
  - Color 2 (dark tone)
  - Color 3 (black)
- In GBA, pixel value 0 is **always transparent**.
- When importing GBC tiles, color 0 must be shifted to colors 1..4 so that white building walls and roads do not turn transparent in-game.

## 4. Asset Tooling
- Use `porytiles` for modern tileset compilation (`porytiles-linux-amd64`).
- Use `gbagfx` for sprite indexing, palette reduction, and LZ77 compression.
- Use `porypal` for verifying palette allocations across tilesets.

