---
description: Critical GBA hardware and pokeemerald-expansion engine limits
globs: pokeconfluence/**
---

# Pokémon Confluence Engine & Hardware Limits

Every modification to maps, scripts, graphics, or data must strictly obey these limits to prevent ROM corruptions, memory leaks, and runtime crashes.

## 1. Map Sections (`MAPSEC_*`)
- **Limit**: Maximum 253 usable section IDs (`0x00` through `0xFC`).
- **Reserved Values**:
  - `0xFD` (253): `METLOC_SPECIAL_EGG`
  - `0xFE` (254): `METLOC_IN_GAME_TRADE`
  - `0xFF` (255): `METLOC_FATEFUL_ENCOUNTER`
- **Current Allocation**: Hoenn + Kanto use 209; Johto uses 43; Meridian Station and Apex Summit use the final slots.
- **Action Rule**: DO NOT add new map sections. New indoor maps or sub-areas MUST reuse existing parent landmark sections (e.g. `MAPSEC_JOHTO_GOLDENROD_CITY`, `MAPSEC_JOHTO_SILVER_CAVE`).

## 2. Map Groups & Map Numbers
- **Limit**: In `WarpData`, `mapNum` is an 8-bit signed integer (`s8`), meaning map indices inside any map group MUST be `<= 127`.
- **Johto Grouping**: All 383+ Johto maps are grouped into chunks of 100:
  - `gMapGroup_Johto1` (maps 0..99)
  - `gMapGroup_Johto2` (maps 0..99)
  - `gMapGroup_Johto3` (maps 0..99)
  - `gMapGroup_Johto4` (maps 0..84)
- **Action Rule**: Any new map added to Johto must be placed in `gMapGroup_Johto4` (map index < 127) or a new group `gMapGroup_Johto5` must be created.

## 3. Object Events per Map
- **Limit**: Max 64 object events (`OBJECT_EVENT_TEMPLATES_COUNT`).
- **Enforcement**: Converted maps from GBC or Gen 1/2 must clamp their object list to <= 64. Map JSON files (`data/maps/*/map.json`) exceeding 64 will overflow the object event table in EWRAM.

## 4. Tilesets & Palettes
- **Metatiles**: Max 512 primary metatiles + max 512 secondary metatiles.
- **Palettes**: Secondary tileset palettes must fit into slots 6 to 12 (primary uses slots 0 to 5, slots 13-15 are reserved for sprites/UI).
- **Pixel 0**: In GBA hardware, palette color 0 in all 16 palettes is transparent. GBC tiles that used color 0 as opaque must be shifted to colors 1..4.

## 5. Trainer IDs & Flags
- **Hoenn Band**: Trainer IDs 855 to 862 are allocated for Apex Summit wardens and Syndicate bosses. ID 863 is the last free slot before the partner trainer band at 864+.
- **Action Rule**: If adding new trainers, use trainer pool flags or expand the flag space in `include/constants/flags.h`.

## 6. SaveBlock & EWRAM Budget
- The multi-region SaveBlock must not overflow the 4 sectors allocated for save data.
- Do not add massive arrays to `gSaveBlock1` or `gSaveBlock2` without auditing `sizeof(struct SaveBlock1)` and `sizeof(struct SaveBlock2)`.

