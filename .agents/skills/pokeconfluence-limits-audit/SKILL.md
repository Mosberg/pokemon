---
name: pokeconfluence-limits-audit
description: Audits Pokémon Confluence against critical GBA hardware, engine, and saveblock limits. Activates when adding maps, trainers, object events, or inspecting LIMITS.md.
---

# Pokémon Confluence Limits Audit Skill

This skill provides procedures and automated tooling to inspect the codebase against hardware and engine constraints described in [LIMITS.md](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/LIMITS.md).

## Running the Limit Auditor

```bash
python3 /home/mosberg/wsl_projects/pokemon/.agents/scripts/check_limits.py
```

## Key Engine Limits & Verification Procedures

### 1. Map Sections (`MAPSEC_*`)
- **Hard Limit**: 253 max usable (`0x00..0xFC`).
- **Reserved Constants**:
  - `METLOC_SPECIAL_EGG` = 0xFD (253)
  - `METLOC_IN_GAME_TRADE` = 0xFE (254)
  - `METLOC_FATEFUL_ENCOUNTER` = 0xFF (255)
- **Status**: 254 entries defined in [region_map_sections.json](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/data/region_map/region_map_sections.json).
- **Rule**: No new map sections may be added. Maps must inherit parent sections (`MAPSEC_JOHTO_GOLDENROD_CITY`, `MAPSEC_JOHTO_SILVER_CAVE`, etc.).

### 2. Map Group Map Numbers (`s8` Limit)
- **Hard Limit**: In `WarpData`, `mapNum` is an `s8`. Maps within any group must not exceed 127.
- **Organization**: Johto's 383 maps are distributed across:
  - `gMapGroup_Johto1` (maps 0..99)
  - `gMapGroup_Johto2` (maps 0..99)
  - `gMapGroup_Johto3` (maps 0..99)
  - `gMapGroup_Johto4` (maps 0..84)
- **Check**: Look at [include/constants/map_groups.h](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/include/constants/map_groups.h) to ensure no group has map numbers >= 128.

### 3. Object Events per Map
- **Hard Limit**: 64 objects max (`OBJECT_EVENT_TEMPLATES_COUNT`).
- **Audit**: `check_limits.py` parses all `data/maps/*/map.json` files and alerts if any map has > 64 object events. (Current peak: `Route111` with 46 objects).

### 4. Trainer IDs
- **Hoenn Band Limit**: 864+ begins partner trainers. Free IDs are 855..863.
- **Audit**: Verify `trainers.party` defines valid trainer IDs without colliding with partner trainer blocks.

### 5. Unsupported Script Stubs
- Any unconverted script stubs containing `@ TODO unsupported:` must be tracked and eliminated during migration passes.

