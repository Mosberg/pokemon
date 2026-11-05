# Engine Limits, Hardware Constraints & Gotchas

This document serves as the master reference for all architectural constraints detailed in [LIMITS.md](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/LIMITS.md) and discovered during multi-region development.

## 1. Map Section ID (`MAPSEC_*`) Hard Ceiling
- **Definition**: Map sections identify the player's landmark location for Pokedex caught locations, fly map landmarks, and map popups.
- **Hardware/Data Type**: `u8` field in `PokemonSubstruct3` (`metLocation`).
- **Maximum Addressable**: 255 values (`0x00..0xFF`).
- **Reserved Engine Constants**:
  - `0xFD` (253): `METLOC_SPECIAL_EGG`
  - `0xFE` (254): `METLOC_IN_GAME_TRADE`
  - `0xFF` (255): `METLOC_FATEFUL_ENCOUNTER`
- **Usable Limit**: 253 map sections (indices `0` to `252`).
- **Current Allocation**: Hoenn + Kanto use 209; Johto uses 43; Meridian Station uses slot 252.
- **Pitfall**: Adding new map sections beyond 252 risks collisions with `METLOC_SPECIAL_EGG` in the summary screen. New sub-maps MUST share existing landmark mapsecs.

## 2. Warp Data Signed 8-bit Map Number Limit
- **Data Structure**:
  ```c
  struct WarpData {
      s8 mapGroup;
      s8 mapNum;
      s8 warpId;
      s16 x, y;
  };
  ```
- **Constraint**: `mapNum` is signed 8-bit (`s8`), meaning map index values must strictly satisfy `-128 <= mapNum <= 127`.
- **Johto Solution**: Johto comprises 383 converted maps. A single map group would overflow at map index 128. Maps are partitioned into groups of 100:
  - `gMapGroup_Johto1` (maps 0..99)
  - `gMapGroup_Johto2` (maps 0..99)
  - `gMapGroup_Johto3` (maps 0..99)
  - `gMapGroup_Johto4` (maps 0..84)

## 3. Object Events per Map
- **Limit**: Max 64 object event templates per map layout (`OBJECT_EVENT_TEMPLATES_COUNT`).
- **Effect**: If a map JSON specifies > 64 object events, the excess objects corrupt the EWRAM object event heap on map load, leading to visual corruption or instant crashes.
- **Auditing**: Always run `.agents/scripts/check_limits.py` to ensure all maps remain <= 64.

## 4. Tileset Metatile & Palette Allocations
- **Metatiles**:
  - Primary tileset: Max 512 metatiles (IDs 0..511).
  - Secondary tileset: Max 512 metatiles (IDs 512..1023).
- **Palette Slots**:
  - Slots 0..5: Primary tileset (shared overworld features).
  - Slots 6..12: Secondary tileset (7 palette slots max).
  - Slots 13..15: System UI, text window, dialogue boxes.
- **Transparent Pixel 0**:
  - On GBA, color 0 of every palette is transparent.
  - GBC tiles using index 0 as opaque white must be shifted via `poke-palette-shift` to avoid "see-through" buildings and scenery.

## 5. Map Transition Callbacks (`ON_TRANSITION`)
- `ON_TRANSITION` map callbacks execute synchronously while the screen is black before objects and tasks are initialized.
- **Strictly Prohibited**:
  - `msgbox` / `message` / `waitmessage`
  - `removeobject` / `addobject`
  - Any interactive waits or prompts
- **Permitted**:
  - `setflag` / `clearflag` (toggling hide flags for object spawning)
  - `setweather`
  - `changeblock` (modifying metatiles before rendering)

## 6. Trainer ID Banding
- Hoenn trainer IDs span 0..863.
- Partner trainers begin at ID 864+.
- IDs 855..862 are allocated to Confluence Apex and Syndicate trainers.
- Exactly 1 free ID (863) remains in the Hoenn band. Any new trainers must be assigned dynamically or use expanded flag tables.

