# MISSING FEATURES & WORK IN PROGRESS

This document tracks all features, scripts, and subsystems that are unfinished, in progress, or require live playtesting in **Pokémon Confluence Version**. All fully implemented and verified features have been migrated to [COMPLETED.md](COMPLETED.md).

For hard limits and engine constraints, refer to [LIMITS.md](LIMITS.md). Overall status: all 383 Johto maps load in emulator smoke tests (0 crash failures), with 0 stubs in single-player overworld/indoor/dungeon progression. Only 21 `@ TODO unsupported:` stubs remain across all 383 maps, confined exclusively to Link/Mobile rooms (16) and Crystal's Battle Tower (5).

---

## Progress Overview

| Feature / Subsystem | Status | Progress | Notes |
|:---|:---:|:---:|:---|
| **Audio, Sprites & Visual Polish** | WIP | `[█████░░░░░] 50%` | 118 sprites & 48 songs mapped; native GBC chiptunes & battle pics pending |
| **Engine Integration** | WIP | `[████░░░░░░] 40%` | Badges, caps, scaling, obedience done; DNS & Johto Dex pending |
| **Script Playtesting** | WIP | `[████░░░░░░] 40%` | Early game verified; mid/late game & static encounters unplayed |
| **Embedded Emulator & Tooling** | WIP | `[███░░░░░░░] 30%` | Headless runner & pytest done; RTC hardware sync missing |
| **Battle Tower & Mobile** | Backlog | `[██░░░░░░░░] 20%` | 21 link/tower stubs remain; single-player untouched |

*(Previously completed and fully verified subsystems: **Fly Points & Navigation (100%)**, **Phone & Rematches (100%)**, **Kanto / Yellow Content & 386 Mood System (100%)**, and **Wild Encounter Tables & Mechanics (100%)** have been migrated to [COMPLETED.md](COMPLETED.md).)*

---

## 1. Audio, Sprites & Visual Polish

- `[█████░░░░░] 50%` **GBC Audio & Visual Fidelity**
  - **Completed**: All 118 Crystal `SPRITE_*` constants mapped to validated FRLG/Emerald `OBJ_EVENT_GFX_*` counterparts. All 48 Crystal `MUSIC_*` constants mapped to `MUS_RG_*` / `MUS_*` tracks. Authentic GBC Johto badges integrated on the Trainer Card.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Real GBC Crystal synth chiptune playback / mid2agb conversions.
    - `[░░░░░░░░░░] 0%` Custom GBC overworld sprites and trainer battle front/back pictures.
    - `[░░░░░░░░░░] 0%` Crystal text font and authentic scroll-arrow tiles.

---

## 2. Engine Integration

- `[████░░░░░░] 40%` **Engine Mechanics**
  - **Completed**: 24-badge soft level caps, dynamic Gym Leader/Elite Four scaling, regional `GameClear` Hall of Fame continue warps, multi-region Trainer Card badge display with cycling, regional battle obedience in `battle_util.c`, field-move badges in `field_move.c`, `VAR_BADGES` counter, and party menu / field kit Cut for Johto background trees and tall grass.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Overworld Day/Night color palettes (DNS).
    - `[░░░░░░░░░░] 0%` Johto regional Pokédex ordering and area map pages.
    - `[░░░░░░░░░░] 0%` Per-class trainer DVs, per-class battle music, and Crystal held-item / learnset nuances.

---

## 3. Battle Tower, Mobile & Link Stubs

- `[██░░░░░░░░] 20%` **Crystal Link & Facility Stubs**
  - **Completed**: Bug-Catching Contest gate entry (`GiveParkBalls`) and Goldenrod Pokémon Center GS Ball trigger. 0 stubs in single-player overworld/indoor/dungeon progression.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Crystal Battle Tower actions (`BattleTowerAction` - 5 stubs).
    - `[░░░░░░░░░░] 0%` Link/Mobile room stubs (`Colosseum`, `TimeCapsule`, `TradeCenter`, `CableClubCheckWhichChris`, `AskMobileOrCable` - 16 stubs).

---

## 4. Overworld Scripts: Converted but Unplayed

- `[████░░░░░░] 40%` **Playtest Status**
  - **Verified in Play**: Mom's Pokegear scene, New Bark Town, Elm's lab, all three starter selections (Totodile, Cyndaquil, Chikorita rival variant), Elm's Aide, Route 29 wild encounter, Route 30 trainer, Johto save/continue round trip, Cherrygrove Pokémon Center / Mart / Guide Gent / rival scene, Mr. Pokémon (Mystery Egg), Violet Gym (Falkner), Togepi egg from Aide, cut trees (Ilex Forest, Route 29), Sprout Tower rival scene & Sage Li Flash battle, NPC trade (Emy), Violet nurse respawn & whiteout wakeup.
  - **Converted but Unplayed**:
    - `[░░░░░░░░░░] 0%` Static wild battles (`loadwildmon`).
    - `[░░░░░░░░░░] 0%` Dynamic block changes (`changeblock`).
    - `[░░░░░░░░░░] 0%` Hidden items across 60 maps.
    - `[░░░░░░░░░░] 0%` Strength boulders and Rock Smash breakable rocks in Johto dungeons.
    - `[░░░░░░░░░░] 0%` Elder Li's Flash gift follow-up sequence.
    - `[░░░░░░░░░░] 0%` Route 32 Slowpoke Tail scene, Union Cave, Azalea Town, Kurt, and Ilex Forest Farfetch'd chase.
    - `[░░░░░░░░░░] 0%` Togepi hatching and Elm's follow-up phone call / scene.
    - `[░░░░░░░░░░] 0%` Per-town respawn in towns other than Violet.
    - `[░░░░░░░░░░] 0%` Fishing encounter tables (Old, Good, Super Rod across 149 maps).

---

## 5. Embedded Emulator & Tooling

- `[███░░░░░░░] 30%` **Harness & Tooling**
  - **Completed**: Headless C integration test suite (`test.sh`), emulator smoke test runner (`test_units.py`), limit auditor (`check_limits.py`), Field Kit party menu row, and mGBA Python bridge protocol.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Real Cartridge RTC time sync (weekday and day-of-week behaviour in Johto scripts).
    - `[░░░░░░░░░░] 0%` Native-mGBA savestate import.
    - `[░░░░░░░░░░] 0%` VS Code extension views, dashboard, and debug adapter panels.
    - `[░░░░░░░░░░] 0%` Automated CI/CD script that rebuilds the ROM and replays the Johto opening.

- `[███░░░░░░░] 30%` **Harness & Tooling**
  - **Completed**: Headless C integration test suite (`test.sh`), emulator smoke test runner (`test_units.py`), limit auditor (`check_limits.py`), Field Kit party menu row, and mGBA Python bridge protocol.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Real Cartridge RTC time sync (weekday and day-of-week behaviour in Johto scripts).
    - `[░░░░░░░░░░] 0%` Native-mGBA savestate import.
    - `[░░░░░░░░░░] 0%` VS Code extension views, dashboard, and debug adapter panels.
    - `[░░░░░░░░░░] 0%` Automated CI/CD script that rebuilds the ROM and replays the Johto opening.
