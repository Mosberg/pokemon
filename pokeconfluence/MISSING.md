# MISSING FEATURES & WORK IN PROGRESS

This document tracks all features, scripts, and subsystems that are unfinished, in progress, or require live playtesting in **Pokémon Confluence Version**. All fully implemented and verified features have been migrated to [COMPLETED.md](COMPLETED.md).

For hard limits and engine constraints, refer to [LIMITS.md](LIMITS.md). Overall status: all 383 Johto maps load in emulator smoke tests (0 crash failures), with 0 stubs in single-player overworld/indoor/dungeon progression. Only 21 `@ TODO unsupported:` stubs remain across all 383 maps, confined exclusively to Link/Mobile rooms (16) and Crystal's Battle Tower (5).

---

## Progress Overview

| Feature / Subsystem | Status | Progress | Notes |
|:---|:---:|:---:|:---|
| **Audio, Sprites & Visual Polish** | WIP | `[███████░░░] 75%` | 118 sprites, 48 songs, down-arrows & beast battle BGM mapped; full chiptunes & trainer pics pending |
| **Battle Tower & Mobile** | Backlog | `[██░░░░░░░░] 20%` | 21 link/tower stubs remain; single-player untouched |

*(Previously completed and fully verified subsystems: **Embedded Emulator & Tooling (100%)**, **Johto Overworld Scripts & Playtesting (100%)**, **Engine Integration & Learnsets/Held Items (100%)**, **Fly Points & Multi-Region Navigation (100%)**, **Phone & Rematches (100%)**, **Kanto / Yellow Content & 386 Mood System (100%)**, and **Wild Encounter Tables & Mechanics (100%)** have been migrated to [COMPLETED.md](COMPLETED.md).)*

---

## 1. Audio, Sprites & Visual Polish

- `[███████░░░] 75%` **GBC Audio & Visual Fidelity**
  - **Completed**: All 118 Crystal `SPRITE_*` constants mapped to validated FRLG/Emerald `OBJ_EVENT_GFX_*` counterparts. All 48 Crystal `MUSIC_*` constants mapped to `MUS_RG_*` / `MUS_*` tracks. Authentic GBC Johto badges integrated on the Trainer Card. Authentic GBC Crystal prompt down-arrow glyphs integrated in text rendering. Suicune/Raikou/Entei Crystal legendary beast chiptune battle theme (`MUS_C_VS_LEGEND_BEAST`) wired.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Real GBC Crystal synth chiptune playback / mid2agb conversions for full overworld soundtrack.
    - `[░░░░░░░░░░] 0%` Custom GBC overworld sprites and trainer battle front/back pictures.

---

## 2. Battle Tower, Mobile & Link Stubs

- `[██░░░░░░░░] 20%` **Crystal Link & Facility Stubs**
  - **Completed**: Bug-Catching Contest gate entry (`GiveParkBalls`) and Goldenrod Pokémon Center GS Ball trigger. 0 stubs in single-player overworld/indoor/dungeon progression.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Crystal Battle Tower actions (`BattleTowerAction` - 5 stubs).
    - `[░░░░░░░░░░] 0%` Link/Mobile room stubs (`Colosseum`, `TimeCapsule`, `TradeCenter`, `CableClubCheckWhichChris`, `AskMobileOrCable` - 16 stubs).
