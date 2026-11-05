# Multi-Region Architecture & Confluence Systems

## Overview
Pokémon Confluence unifies three classical regions (Hoenn, Kanto, and Johto) into a single Game Boy Advance ROM image using `pokeemerald-expansion` as the base engine. All bespoke game logic is demarcated with `// POKE-CONFLUENCE`.

## 1. Regional Partitioning & Identification
The game tracks the player's active region via `GetCurrentRegion()` in [src/confluence.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/confluence.c):
- `REGION_HOENN`: Base Emerald maps (`gMapGroup_TownsAndRoutes` etc.).
- `REGION_KANTO`: Converted FireRed/LeafGreen maps (`gMapGroup_Kanto*`).
- `REGION_JOHTO`: Converted Crystal maps split across 4 groups of 100 (`gMapGroup_Johto1..4`).
- Transit hub: Meridian Station is map 83 of `gMapGroup_Johto4`.
- Summit arena: Apex Summit is map 84 of `gMapGroup_Johto4`.

## 2. 24-Badge Circuit
`Confluence_CountBadges()` aggregates badges across all three regions:
- **Hoenn**: `FLAG_BADGE01_GET` through `FLAG_BADGE08_GET` (Stone, Knuckle, Dynamo, Heat, Balance, Feather, Mind, Rain).
- **Kanto**: `FLAG_BADGE09_GET` through `FLAG_BADGE16_GET` (Boulder, Cascade, Thunder, Rainbow, Soul, Marsh, Volcano, Earth).
- **Johto**: `FLAG_JOHTO_ENGINE_ZEPHYRBADGE` through `FLAG_JOHTO_ENGINE_RISINGBADGE` (Zephyr, Hive, Plain, Fog, Storm, Mineral, Glacier, Rising).

## 3. Dynamic Level Caps & Scaling
Configured in [src/caps.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/caps.c) and [include/config/caps.h](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/include/config/caps.h):
- `B_EXP_CAP_TYPE = EXP_CAP_SOFT`: Over-cap Pokémon receive drastically reduced experience.
- `B_LEVEL_CAP_TYPE = LEVEL_CAP_BADGE_COUNT`: Level cap follows the table:
  - 0 Badges: 15
  - 1-7 Badges: Scaled linearly (18, 22, 26, 30, 34, 38, 43)
  - 8 Badges: 48
  - 9-23 Badges: Scaled linearly (50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 75, 78)
  - 24 Badges: 80
  - Apex Summit Victory (`FLAG_CONFLUENCE_APEX_CHAMPION`): 100.
- **Gym Leader & Elite Four Scaling**:
  - `Confluence_GetTrainerLevelBoost()` calculates the difference between the trainer's ace Pokémon and the current badge level cap.
  - Every Pokémon in the trainer's party is increased by this boost so the battle is always challenging, regardless of the order in which gyms are tackled. Levels are never reduced.

## 4. Meridian Transit Network
- Conductors situated in Slateport Harbor (Hoenn), Vermilion City (Kanto), and Olivine City (Johto) offer transit to `MeridianStation_Johto`.
- Unlocks when the player acquires at least 2 gym badges.
- Features four boarding gates:
  - Gate 1: Vermilion City (Kanto)
  - Gate 2: Olivine City (Johto)
  - Gate 3: Slateport City (Hoenn)
  - Gate 4: Sealed until Convergence Crisis endgame

## 5. Resonance Weather Anomalies & Crisis
- After obtaining 2 badges, atmospheric anomalies trigger in outdoor overworld areas:
  - Kanto outdoor maps -> Violent thunderstorms
  - Johto outdoor maps -> Dense fog
  - Hoenn outdoor maps -> Torrential downpours
- Calming the 9 Resonance legends (Articuno, Zapdos, Moltres; Raikou, Entei, Suicune; Regirock, Regice, Registeel) or defeating the Convergence Crisis Chairman clears anomalies permanently (`FLAG_CONFLUENCE_CRISIS_RESOLVED`).

## 6. Apex Summit Championship
- Unlocked in Mt. Silver Cave Outside upon acquiring all 24 badges.
- The player enters `ApexSummit_Johto` to face a gauntlet of regional wardens:
  1. Kanto Warden (Blue)
  2. Johto Warden (Lance)
  3. Hoenn Warden (Steven)
  4. Summit Champion (Red)
- Progress is preserved between rounds; winning awards the Master Ball and unlocks the level 100 cap.

