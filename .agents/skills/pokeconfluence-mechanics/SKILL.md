---
name: pokeconfluence-mechanics
description: Master guide for expanding pokeemerald-expansion mechanics: new Pokémon, moves, abilities, AI logic, follower NPCs, DNS, and overworld systems. Activates when adding or tuning game mechanics.
---

# Pokémon Confluence Mechanics Expansion Skill

This skill synthesizes all 32 specialized tutorials from `pokeconfluence/docs/tutorials/` for implementing and modifying modern mechanics in the pokeemerald-expansion engine.

## 1. Adding a New Pokémon
In pokeemerald-expansion v1.6.0+, adding a new species only requires modifying ~5 files:
1. `include/constants/species.h`: Define `SPECIES_<NAME>`.
2. `src/data/pokemon/species_info.h`: Add species base stats, types, abilities, catch rate, exp yield, gender ratio, egg groups, evolution methods, and body color.
3. `src/data/pokemon/level_up_learnsets.h`: Add level-up moves.
4. `src/data/pokemon/teachable_learnsets.h`: Add TM/HM/tutor moves.
5. `graphics/pokemon/<name>/`: Add front/back sprites (64x64 indexed 16 colors, color 0 transparent), shiny palette, icon, and footprints.

## 2. Adding a New Move
1. `include/constants/moves.h`: Define `MOVE_<NAME>`.
2. `src/data/moves_info.h`: Configure move power, accuracy, PP, type, split (`SPLIT_PHYSICAL`/`SPECIAL`/`STATUS`), effect, target, priority, flags (`FLAG_MAKES_CONTACT`, `FLAG_PROTECT_AFFECTED`, etc.).
3. `src/data/battle_scripts_1.s` / `src/battle_anim_moves.c`: Battle animations and custom effects.
4. `src/data/text/move_descriptions.h`: Move description strings (max 2 lines).

## 3. Custom AI Flags & Logic
- Located in `src/battle_ai_main.c` and `include/constants/battle_ai.h`.
- Custom AI flags (`AI_FLAG_CHECK_BAD_MOVE`, `AI_FLAG_SMART_SWITCHING`, `AI_FLAG_ACE_POKEMON`, `AI_FLAG_DOUBLE_BATTLE`).
- Dynamic AI functions evaluate party state, field terrain, weather, stat boosts, and hazard damage to score potential moves.

## 4. Follower NPCs
- Configured in [include/config/follower_npc.h](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/include/config/follower_npc.h).
- Trigger follower in scripts using `special SetFollowerNPC` with sprite ID and script pointer for interaction dialogue.
- Follower system handles ledge jumping, bike riding, surfing transitions, and indoor map warps automatically.

## 5. Day/Night System (DNS)
- Configured in [include/config/overworld.h](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/include/config/overworld.h).
- Automatically tints background and sprite palettes based on real-time clock (RTC) hours:
  - Morning (04:00 - 09:59)
  - Day (10:00 - 16:59)
  - Evening / Twilight (17:00 - 19:59)
  - Night (20:00 - 03:59)
- Time-of-day wild encounters: Configured per map in `src/data/wild_encounters.json` with morning/day/night tables.

## 6. Overworld Wild Encounters
- Overworld roaming sprites can trigger wild battles via `how_to_overworld_wild_encounters.md`.
- Uses custom object events with movement type `MOVEMENT_TYPE_WANDER_AROUND` linked to battle scripts calling `special StartOverworldWildBattle`.

