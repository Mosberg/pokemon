# MISSING FEATURES & WORK IN PROGRESS

This document tracks upcoming gameplay expansions, secondary Crystal mechanics, and multi-region enhancements in **Pokémon Confluence Version**. All primary conversion milestones, engine stubs, audio chiptunes, and trainer graphics have been fully integrated and verified in [COMPLETED.md](COMPLETED.md).

For hard limits, engine constraints, and saveblock budgeting, refer to [LIMITS.md](LIMITS.md).

---

## Roadmap Overview

| Feature / Subsystem | Status | Progress | Notes |
|:---|:---:|:---:|:---|
| **1. Morning & Night Wild Encounter Tables** | Completed | `[██████████] 100%` | Verified all 61 Crystal grass/outdoor maps with discrete morning/day/night tables in wild_encounters.json & .h |
| **2. Headbutt Tree Encounter Mechanics** | Completed | `[██████████] 100%` | Authentic GBC tree metatile interaction, tree scoring algorithm, asleep wild mons, and 7 table types |
| **3. Roaming Legendary Beasts** | Completed | `[██████████] 100%` | Overworld roaming AI across Johto routes for Raikou and Entei with authentic starting routes, flee logic, and battle music |
| **4. Day-of-Week Overworld Events** | Completed | `[██████████] 100%` | Friday Lapras in Union Cave B2F with weekly respawn & all 7 Weekday Siblings item gifts |
| **5. Lake of Rage Shiny Red Gyarados** | Completed | `[██████████] 100%` | Authentic Level 30 forced-shiny Gyarados battle, overworld sprite clearance, Red Scale reward, and Mr. Pokémon Exp. Share trade |
| **6. Bug-Catching Contest Minigame** | Planned | `[░░░░░░░░░░] 0%` | 20-minute timer, 20 Park Balls, judging scoring algorithm, and Sun Stone prize distribution |

---

## 1. Morning & Night Wild Encounter Tables

- `[██████████] 100%` **Time-of-Day Route Encounters**
  - **Completed**:
    - Extracted and verified all 61 Crystal grass/outdoor encounter tables from `games/gbc/pokecrystal/data/wild/johto_grass.asm`.
    - Discrete `[TIME_MORNING]`, `[TIME_DAY]`, and `[TIME_NIGHT]` encounter tables configured for all 149 Johto maps in `src/data/wild_encounters.json` and compiled into `src/data/wild_encounters.h`.
    - Verified Crystal time-of-day species distribution across Johto routes (Route 29 Hoothoot/Sentret, Route 30/31 Ledyba/Pidgey/Spinarak, Route 34/35 Snubbull/Drowzee, Route 37 Ledyba/Pidgey/Spinarak/Stantler).
    - `OW_TIME_OF_DAY_ENCOUNTERS = TRUE` enabled with RTC sampling in `src/wild_encounter.c`.
    - Automated C integration test added to `test/confluence.c` (21/21 passed).
  - **Missing**:
    - None. All time-of-day wild encounter features are fully implemented and verified.

---

## 2. Headbutt Tree Encounter Mechanics

- `[██████████] 100%` **Headbutt Field Move & Tree Spawns**
  - **Completed**:
    - Metatile collision & behavior: Added `MB_HEADBUTT_TREE` to `include/constants/metatile_behaviors.h` and helper `MetatileBehavior_IsHeadbuttTree()`. Configured in `tools/poke-migrator-pro/bin/poke-crystal-tilesets` and compiled for secondary tilesets (`crystal_johto`, `crystal_johto_modern`, `crystal_forest`, `crystal_park`, `crystal_battle_tower_outside`).
    - Overworld interaction: Wired into `GetInteractedMetatileScript()` in `src/field_control_avatar.c` allowing direct interaction (`A_BUTTON`) to trigger `Johto_EventScript_HeadbuttTree`.
    - Field move support: Implemented `JohtoCheckHeadbuttUser()` supporting Pokémon knowing `MOVE_HEADBUTT` as well as the `ITEM_FIELD_KIT`.
    - Crystal Tree Scoring: Replicated GBC formula `((x + 1) * (y + 1) - 1) / 5 % 10` diffed against `playerTrainerId % 10` to categorize trees into Rare (80% encounter, Pineco/Heracross/Aipom), Good (50% encounter), and Bad (10% encounter).
    - Authentic Crystal Encounter Tables: Parsed and added all 7 tree types from `games/gbc/pokecrystal/data/wild/treemon_*.asm` (Route, Town, Canyon, Lake, Forest, Rock, Kanto).
    - Diurnal/Nocturnal Sleep Mechanic: Implemented `CheckSleepingTreeMon` applying sleep status depending on hour of day.
    - Automated Unit Tests: Added `TEST("Confluence: Authentic Johto Headbutt Tree mechanics and encounter tables")` to `test/confluence.c` (22/22 passed).
  - **Missing**:
    - None. All Headbutt tree mechanics are fully integrated and verified.

---

## 3. Roaming Legendary Beasts

- `[██████████] 100%` **Raikou & Entei Overworld Roaming**
  - **Completed**:
    - Authentic GBC Crystal starting routes: Raikou initialized to Route 42 (`MAP_JOHTO_ROUTE_42`) and Entei to Route 37 (`MAP_JOHTO_ROUTE_37`) at level 40 upon awakening in Burned Tower B1F (`InitJohtoRoamMons`).
    - Authentic 16-route Johto roaming network from pokecrystal `roammon_maps.asm` configured in `sJohtoRoamerLocations` (Routes 29-46).
    - Dynamic route movement and jumping on map transitions via `RoamerMove()` and `RoamerMoveToOtherLocationSet()`.
    - Authentic encounter rules: Wild battle interceptor checks current route match; water surfing suppression ensures land-only encounters for beasts.
    - Authentic fleeing AI (`AI_FLAG_ROAMING`) attempting flee on turn 1 unless trapped by Mean Look or Shadow Tag / Arena Trap.
    - Authentic Crystal Legendary Beast battle theme (`MUS_C_VS_LEGEND_BEAST`) wired in `GetBattleBGM()` for `BATTLE_TYPE_ROAMER`.
    - Persistent HP and status conditions saved in `SaveBlock1.roamer` across encounters; deactivation upon faint or capture.
    - Pokédex Area screen accurately pinpoints current roaming route across Johto map sections.
    - Automated integration test `TEST("Confluence: Authentic Johto Roaming Legendary Beasts (Raikou & Entei)")` in `test/confluence.c` (23/23 passed).
  - **Missing**:
    - None. All roaming beast mechanics are fully implemented and verified.

---

## 4. Day-of-Week Overworld Events

- `[██████████] 100%` **Weekly Calendar Events**
  - **Completed**:
    - Friday Lapras in `UnionCaveB2F_Johto`: Spawns on water exclusively on Friday (`WEEKDAY_FRI`) at level 20 with authentic cry and battle script.
    - Weekly respawn: Defeating or catching Lapras sets `FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS`; midnight reset in `DoDailyEvents()` in `src/clock.c` clears the flag, allowing Lapras to return every Friday.
    - All 7 Weekday Siblings fully implemented with authentic Crystal schedules, dialogue, and type-boosting held items:
      - Sunday: Sunny on Route 37 (`ITEM_MAGNET` / `FLAG_JOHTO_GOT_MAGNET_FROM_SUNNY`)
      - Monday: Monica on Route 40 (`ITEM_SHARP_BEAK` / `FLAG_JOHTO_GOT_SHARP_BEAK_FROM_MONICA`)
      - Tuesday: Tuscany on Route 29 (`ITEM_PINK_BOW` / `FLAG_JOHTO_GOT_PINK_BOW_FROM_TUSCANY`)
      - Wednesday: Wesley on Lake of Rage (`ITEM_BLACKBELT_I` / `FLAG_JOHTO_GOT_BLACKBELT_FROM_WESLEY`)
      - Thursday: Arthur on Route 36 (`ITEM_HARD_STONE` / `FLAG_JOHTO_GOT_HARD_STONE_FROM_ARTHUR`)
      - Friday: Frieda on Route 32 (`ITEM_POISON_BARB` / `FLAG_JOHTO_GOT_POISON_BARB_FROM_FRIEDA`)
      - Saturday: Santos on Blackthorn City (`ITEM_SPELL_TAG` / `FLAG_JOHTO_GOT_SPELL_TAG_FROM_SANTOS`)
    - Map transition callbacks (`OnTransition`) check `special JohtoGetWeekday` to show/hide siblings appropriately.
    - Automated integration test `TEST("Confluence: Authentic Johto Day-of-Week events and Weekday Siblings")` in `test/confluence.c` (24/24 passed).
  - **Missing**:
    - None. All day-of-week calendar events and siblings are fully integrated and verified.

---

## 5. Lake of Rage Shiny Red Gyarados

- `[██████████] 100%` **Lake of Rage Climax**
  - **Completed**:
    - Lake of Rage map, Lance intro encounter, and Team Rocket Base scripts converted.
    - Scripted water sprite interaction triggering level 30 forced-shiny `SPECIES_GYARADOS` battle via `special JohtoSetWildMonShiny`.
    - Handles battle outcomes: fleeing or losing preserves the encounter; catching or defeating sets `FLAG_JOHTO_LAKE_OF_RAGE_RED_GYARADOS`, clears `FLAG_JOHTO_LAKE_OF_RAGE_LANCE`, spawns Lance on the shore, and awards `ITEM_RED_SCALE`.
    - Mr. Pokémon dialogue and trade on Route 30 (`MrPokemonsHouse_Johto`) faithfully trades `ITEM_RED_SCALE` for `ITEM_EXP_SHARE`.
    - Unit test `TEST("Confluence: Authentic Lake of Rage Shiny Red Gyarados and Red Scale trade")` verified in `test/confluence.c` (25/25 passed).
  - **Missing**:
    - None. 100% faithful to Pokémon Crystal.

---

## 6. Bug-Catching Contest Minigame

- `[░░░░░░░░░░] 0%` **National Park Tuesday/Thursday/Saturday Contest**
  - **Completed**: Entry gate check and 20 Park Balls delivery (`GiveParkBalls`) in `NationalParkBugContestGate_Johto`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` 20-minute step/time counter during contest.
    - `[░░░░░░░░░░] 0%` Judging calculation based on caught mon's species rarity, remaining HP, level, and IV total.
    - `[░░░░░░░░░░] 0%` Awarding `ITEM_SUN_STONE` (1st prize), `ITEM_EVERSTONE` (2nd prize), and `ITEM_SITRUS_BERRY` (3rd prize).
