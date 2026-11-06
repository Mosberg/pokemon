# MISSING FEATURES & WORK IN PROGRESS

This document tracks upcoming gameplay expansions, secondary Crystal mechanics, and multi-region enhancements in **Pokémon Confluence Version**. All primary conversion milestones, engine stubs, audio chiptunes, and trainer graphics have been fully integrated and verified in [COMPLETED.md](COMPLETED.md).

For hard limits, engine constraints, and saveblock budgeting, refer to [LIMITS.md](LIMITS.md).

---

## Roadmap Overview

| Feature / Subsystem | Status | Progress | Notes |
|:---|:---:|:---:|:---|
| **1. Morning & Night Wild Encounter Tables** | Completed | `[██████████] 100%` | Verified all 61 Crystal grass/outdoor maps with discrete morning/day/night tables in wild_encounters.json & .h |
| **2. Headbutt Tree Encounter Mechanics** | Planned | `[░░░░░░░░░░] 0%` | Overworld Headbutt field move trigger on small trees with Pineco, Heracross, and Aipom encounters |
| **3. Roaming Legendary Beasts** | Planned | `[░░░░░░░░░░] 0%` | Overworld roaming AI across Johto routes for Raikou and Entei with flee logic |
| **4. Day-of-Week Overworld Events** | Planned | `[░░░░░░░░░░] 0%` | Friday Lapras encounter in Union Cave B2F & 7 Siblings of the Week item gifts |
| **5. Lake of Rage Shiny Red Gyarados** | Planned | `[░░░░░░░░░░] 0%` | Static Shiny Gyarados battle script, Red Scale drop, and Mr. Pokémon trade for Exp. Share |
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

- `[░░░░░░░░░░] 0%` **Headbutt Field Move & Tree Spawns**
  - **Completed**: Field Kit system provides overworld HM moves; Headbutt exists in learnsets.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Overworld interaction on headbutt-compatible tree metatiles.
    - `[░░░░░░░░░░] 0%` Headbutt table parser from `games/gbc/pokecrystal/data/wild/treemon_*.asm` providing Pineco, Heracross, Spearow, and Aipom encounter rates.

---

## 3. Roaming Legendary Beasts

- `[░░░░░░░░░░] 0%` **Raikou & Entei Overworld Roaming**
  - **Completed**: Suicune/Raikou/Entei Crystal battle theme (`MUS_C_VS_LEGEND_BEAST`) wired and verified. Burned Tower awakening sequence scripted.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Roamer state tracking across Johto routes via `sRoamerLocation` engine hooks.
    - `[░░░░░░░░░░] 0%` Wild battle encounter interceptor checking current route match.

---

## 4. Day-of-Week Overworld Events

- `[░░░░░░░░░░] 0%` **Weekly Calendar Events**
  - **Completed**: `RtcCalcLocalTime` and `GetDayOfWeek` accessible in engine.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Friday Lapras event in `UnionCaveB2F_Johto`: spawns on water every Friday, respawns weekly, level 20 battle.
    - `[░░░░░░░░░░] 0%` 7 Weekday Siblings scripts and schedules (Arthur on Route 36 on Thursday, Sunny on Route 37 on Sunday, etc.) awarding type-boost items (Hard Stone, Magnet, etc.).

---

## 5. Lake of Rage Shiny Red Gyarados

- `[░░░░░░░░░░] 0%` **Lake of Rage Climax**
  - **Completed**: Lake of Rage map, Lance intro encounter, and Team Rocket Base scripts converted.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Water sprite interaction triggering level 30 forced-shiny `SPECIES_GYARADOS` battle.
    - `[░░░░░░░░░░] 0%` Setting `ITEM_RED_SCALE` reward on capture or defeat, and dialogue script with Mr. Pokémon on Route 30 trading Red Scale for `ITEM_EXP_SHARE`.

---

## 6. Bug-Catching Contest Minigame

- `[░░░░░░░░░░] 0%` **National Park Tuesday/Thursday/Saturday Contest**
  - **Completed**: Entry gate check and 20 Park Balls delivery (`GiveParkBalls`) in `NationalParkBugContestGate_Johto`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` 20-minute step/time counter during contest.
    - `[░░░░░░░░░░] 0%` Judging calculation based on caught mon's species rarity, remaining HP, level, and IV total.
    - `[░░░░░░░░░░] 0%` Awarding `ITEM_SUN_STONE` (1st prize), `ITEM_EVERSTONE` (2nd prize), and `ITEM_SITRUS_BERRY` (3rd prize).
