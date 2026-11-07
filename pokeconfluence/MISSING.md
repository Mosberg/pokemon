# MISSING FEATURES & WORK IN PROGRESS

This document tracks upcoming gameplay expansions, secondary mechanics, missing features, functions, methods, logics, assets, media, options, settings, and configs in **Pokémon Confluence Version** across its six foundational codebases:
1. `games/gbc/pokeyellow` (Gen 1 Yellow-exclusive mechanics and media)
2. `games/gbc/pokecrystal` (Gen 2 Crystal mechanics, minigames, audio, and facilities)
3. `games/gba/pokefirered` (Gen 3 FRLG subsystems, Kanto/Sevii mechanics, and tools)
4. `games/gba/pokeemerald` (Gen 3 Emerald Battle Frontier, rematches, and world events)
5. `games/roms/pokeemerald-expansion` (Modern engine toggles, DexNav, battle options, and configs)
6. `games/roms/pokemultiregion` (Multi-region transit, dex switching, map cycling, and save budgeting)

For verified completions, see [COMPLETED.md](COMPLETED.md). For hard limits, engine constraints, and saveblock budgeting, refer to [LIMITS.md](LIMITS.md).

---

## Roadmap Overview

| Feature / Subsystem                                      | Source Origin           |   Status    |      Progress       | Key Target Files & Scope                                                                           |
| :------------------------------------------------------- | :---------------------- | :---------: | :-----------------: | :------------------------------------------------------------------------------------------------- |
| **1. Morning & Night Wild Encounter Tables**             | `pokecrystal`           |  Verified   | `[██████████] 100%` | Verified all 61 Crystal outdoor maps in `wild_encounters.json`                                     |
| **2. Headbutt Tree Encounter Mechanics**                 | `pokecrystal`           |  Verified   | `[██████████] 100%` | `MB_HEADBUTT_TREE`, coordinate scoring algorithm, asleep wild mons                                 |
| **3. Roaming Legendary Beasts**                          | `pokecrystal`           |  Verified   | `[██████████] 100%` | Raikou & Entei 16-route network, flee AI, persistent status                                        |
| **4. Day-of-Week Overworld Events**                      | `pokecrystal`           |  Verified   | `[██████████] 100%` | Friday Lapras, midnight reset, and all 7 Weekday Siblings                                          |
| **5. Lake of Rage Shiny Red Gyarados**                   | `pokecrystal`           |  Verified   | `[██████████] 100%` | Lv. 30 forced-shiny battle, Red Scale, Mr. Pokémon Exp. Share                                      |
| **6. Bug-Catching Contest Minigame**                     | `pokecrystal`           |  Verified   | `[██████████] 100%` | 20-min countdown, judging formula, 10 AI contestants, tiered prizes                                |
| **7. Ruins of Alph Secret Riddle Chambers**              | `pokecrystal`           |  Verified   | `[██████████] 100%` | Riddle triggers for Escape Rope, Flash, Water Stone, and Ho-Oh                                     |
| **8. Pokégear Radio Card & Audio Broadcasts**            | `pokecrystal`           |  Verified   | `[██████████] 100%` | Interactive station selection, Pokémon Talk swarms, March/Lullaby encounter mods, Buena's Password |
| **9. Interactive Kurt's Apricorn Crafting**              | `pokecrystal`           |  Verified   | `[██████████] 100%` | Dynamic Bag Apricorn selection, batch ball crafting, midnight RTC wait timer                        |
| **10. Unown Pokédex Form Viewer (Unown Dex)**            | `pokecrystal`           |  Verified   | `[██████████] 100%` | Pokédex sub-screen cataloging caught A-Z, ?, ! forms, ancient words & Ruins of Alph unlocks         |
| **11. Goldenrod Game Corner Card Flip Minigame**         | `pokecrystal`           |  Verified   | `[██████████] 100%` | 24-card deck, 5 betting modes, authentic Crystal payouts, 12-round deal loop & reshuffling          |
| **12. Buena's Password Blue Card Point Exchange**        | `pokecrystal`           |  Verified   | `[██████████] 100%` | 2F Radio Tower point shop for 9 prizes, radio broadcast sync                                       |
| **13. Johto Battle Tower 7-Trainer Ladder**              | `pokecrystal`           |  Verified   | `[██████████] 100%` | Level 10-100 room brackets, 7 consecutive battles, vitamin rewards                                 |
| **14. Fame Checker Subsystem Restoration**               | `pokefirered`           |  Verified   | `[██████████] 100%` | Restored `src/fame_checker.c`, all 16 Kanto VIP profiles, clues & field use                        |
| **15. Joyful Game Corner & Berry Crusher Vendor**        | `pokefirered`           |  Verified   | `[██████████] 100%` | Overworld script linkage for Dodrio Berry-Picking, Pokemon Jump & Powder Jar vendor                |
| **16. Teachy TV & Contextual Help System**               | `pokefirered`           |  Verified   | `[██████████] 100%` | Dude's tutorial programs, battle basics, L/R preserved for multi-region cycling                   |
| **17. Surfing Pikachu Beach Minigame**                   | `pokeyellow`            |  Verified   | `[██████████] 100%` | Route 19 Beach House, surfing physics, Radness flips, high scores                                  |
| **18. Pikachu Voiced 8-bit PCM Audio Samples**           | `pokeyellow`            |  Verified   | `[██████████] 100%` | Ikue Otani battle entries, faints, mood reaction audio clips                                       |
| **19. Hoenn Gym Leader Match Call Rematches**            | `pokeemerald`           |  Verified   | `[██████████] 100%` | 4-tier rematch teams for Roxanne through Juan via Match Call                                       |
| **20. Trick House Puzzles 1-8 & Mirage Island**          | `pokeemerald`           |  Verified   | `[██████████] 100%` | Route 110 maze rooms, badge unlocks, Route 130 Mirage Island seed                                  |
| **21. Contest Halls & Berry Blender Pokéblock Minigame** | `pokeemerald`           |  Verified   | `[██████████] 100%` | Slateport/Verdanturf/Fallarbor/Lilycove halls & blender minigame                                   |
| **22. DexNav Search Levels & Encounter HUD**             | `pokeemerald-expansion` |  Verified   | `[██████████] 100%` | Saveblock-safe 256-slot search level cache, dynamic chain, HUD calibration                         |
| **23. Modern Party EXP Share Key Item Toggle**           | `pokeemerald-expansion` |  Verified   | `[██████████] 100%` | `I_EXP_SHARE_MODE` (HELD vs KEY), `FLAG_EXP_SHARE_ENABLED`, 50% party Exp                          |
| **24. Unified Multi-Region Pokédex Selection**           | `pokemultiregion`       | In Progress | `[█████░░░░░] 50%`  | Pokédex menu UI toggle: Hoenn (202), Kanto (151), Johto (251)                                      |
| **25. Unified Bag Town Map Regional Cycling**            | `pokemultiregion`       | In Progress | `[███████░░░] 70%`  | L/R button region cycling for Bag Town Map & Pokégear Map Card                                     |
| **26. S.S. Aqua Weekly Sailing Schedule**                | `pokemultiregion`       | In Progress | `[███████░░░] 75%`  | Mon/Fri Olivine, Wed/Sun Vermilion, cabin battles & Granddaughter                                  |
| **27. Magnet Train Goldenrod-Saffron Pass Quest**        | `pokemultiregion`       | In Progress | `[██████░░░░] 60%`  | Copycat lost Clefairy doll quest, Magnet Train pass & transit cutscene                             |
| **28. Apex Summit 24-Leader Boss Gauntlet**              | `pokemultiregion`       | In Progress | `[████░░░░░░] 40%`  | Post-game Lv. 100 tournament challenging all 24 Gym Leaders                                        |

---

## Verified Subsystems (Sections 1–7)

### 1. Morning & Night Wild Encounter Tables (`pokecrystal`)
- `[██████████] 100%` **Time-of-Day Route Encounters**
  - **Completed**: Discrete `[TIME_MORNING]`, `[TIME_DAY]`, and `[TIME_NIGHT]` encounter tables configured for all 149 Johto maps in `src/data/wild_encounters.json` and compiled into `src/data/wild_encounters.h`. Tested in `test/confluence.c`.

### 2. Headbutt Tree Encounter Mechanics (`pokecrystal`)
- `[██████████] 100%` **Headbutt Field Move & Tree Spawns**
  - **Completed**: Metatile behavior `MB_HEADBUTT_TREE`, coordinate scoring algorithm `((x + 1) * (y + 1) - 1) / 5 % 10`, 7 treemon tables in `src/headbutt.c`, diurnal/nocturnal sleep status, and Field Kit integration.

### 3. Roaming Legendary Beasts (`pokecrystal`)
- `[██████████] 100%` **Raikou & Entei Overworld Roaming**
  - **Completed**: Starting routes (Raikou Route 42, Entei Route 37), 16-route network in `sJohtoRoamerLocations`, water surfing suppression, flee AI (`AI_FLAG_ROAMING`), `MUS_C_VS_LEGEND_BEAST` battle theme, and persistent HP/status tracking in `SaveBlock1.roamer`.

### 4. Day-of-Week Overworld Events (`pokecrystal`)
- `[██████████] 100%` **Weekly Calendar Events & Weekday Siblings**
  - **Completed**: Friday Lapras in `UnionCaveB2F_Johto` with weekly midnight respawn; all 7 Weekday Siblings (Sunny, Monica, Tuscany, Wesley, Arthur, Frieda, Santos) awarding type-boosting held items.

### 5. Lake of Rage Shiny Red Gyarados (`pokecrystal`)
- `[██████████] 100%` **Lake of Rage Climax**
  - **Completed**: Scripted water sprite interaction triggering level 30 forced-shiny `SPECIES_GYARADOS` battle, overworld sprite clearance, `ITEM_RED_SCALE` reward, and Mr. Pokémon `ITEM_EXP_SHARE` trade on Route 30.

### 6. Bug-Catching Contest Minigame (`pokecrystal`)
- `[██████████] 100%` **National Park Tuesday/Thursday/Saturday Contest**
  - **Completed**: 20 Park Balls, 20-minute (500 steps) countdown timer with `SE_DING_DONG` warning, authentic species/level/IV/HP judging algorithm against 10 AI contestants, and tiered Sun Stone / Everstone / Sitrus Berry / Oran Berry prize distribution.

### 7. Ruins of Alph Secret Riddle Chambers (`pokecrystal`)
- `[██████████] 100%` **Authentic Puzzle Riddle Triggers**
  - **Completed**: Escape Rope (Kabuto), Flash / Field Kit (Aerodactyl), Water Stone (Omanyte), and Ho-Oh in party (Ho-Oh) opening back wall chambers and uncovering hidden items and lore plaques.

### 8. Pokégear Radio Card & Audio Broadcasts (`pokecrystal`)
- `[██████████] 100%` **Interactive Radio Tuner UI & Overworld Station Effects**
  - **Reference**: `games/gbc/pokecrystal/engine/pokegear/radio.asm`, `engine/pokegear/pokegear.asm`
  - **Completed**:
    - Radio Card integration in Pokégear (`src/pokenav_menu_handler.c`, `src/pokenav_menu_handler_gfx.c`, `src/pokenav.c`): Condition slot dynamically maps to Radio Card in Johto with contextual description and automatic overworld transition to radio menu.
    - Station 4.5 (*Prof. Oak's Pokémon Talk & Mary*): dynamically queries active daily swarm (`Johto_GetActiveSwarm()`) and announces the swarming species and location with `MUS_RG_OAK`.
    - Station 7.5 (*Pokémon Music Channel*): Ben & Fern broadcast Pokémon March (`MUS_C_ROUTE29`) on Sun/Tue/Thu/Sat boosting wild encounter rates by 50% in `src/wild_encounter.c`, and Pokémon Lullaby (`MUS_RG_POKE_FLUTE`) on Mon/Wed/Fri reducing wild encounter rates by 50%.
    - Station 10.5 (*Buena's Password Show*): generates authentic daily password from all 11 Crystal categories with `MUS_C_GOLDENROD` and sets password knowledge flag.
    - Station 13.5 (*Ruins of Alph Signal*): detects `MAPSEC_JOHTO_RUINS_OF_ALPH` and broadcasts authentic eerie Unown signal (`MUS_C_RUINS_OF_ALPH`).
    - Station 20.0 (*Poké Flute Channel*): unlocked in Kanto with EXPN Card (`FLAG_JOHTO_ENGINE_EXPN_CARD`), playing `MUS_RG_POKE_FLUTE` to wake sleeping Snorlax.
    - Team Rocket Takeover Crisis: overrides all stations with Team Rocket manifesto loop (`MUS_RG_ENCOUNTER_ROCKET`) when `FLAG_JOHTO_ENGINE_ROCKETS_IN_RADIO_TOWER` is set.
    - Full overworld script and special interface (`Johto_EventScript_RadioMenu`, `data/specials.inc`) with dynamic multichoice menu (`dynmultipush` / `dynmultistack`).
    - Turn off radio restores initial map BGM and clears music encounter modifiers.
    - Automated unit test verified in `test/confluence.c` (29/29 tests pass).
  - **Missing**:
    - None. All Pokégear Radio Card stations and broadcast effects are fully implemented and verified.

---

## Detailed Missing Subsystems & Feature Backlog

---

### 9. Interactive Kurt's Apricorn Crafting (`pokecrystal`)

- `[██████████] 100%` **Apricorn Selection UI & Overnight Crafting Timer**
  - **Reference**: `games/gbc/pokecrystal/engine/events/kurt.asm`, `data/items/apricorns.asm`
  - **Completed**:
    - Kurt event script in `KurtsHouse_Johto/scripts.inc` features dynamic multichoice menu filtered to player's Bag inventory (`JohtoSelectApricornForKurt`).
    - Batch crafting option: allows crafting 1 or all held Apricorns of the selected color at once (`JohtoGetApricornQuantity`, `JohtoGiveKurtApricorns`).
    - Overnight wait condition: sets `FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS` and `VAR_JOHTO_KURT_APRICORN_COUNT`. Cleared daily at midnight RTC in `DoDailyEvents()`. Kurt delivers batch balls with fanfare and dialogue (`JohtoDeliverKurtBalls`).
    - All 7 Apricorn items (`ITEM_RED_APRICORN` through `ITEM_PNK_APRICORN`) and custom balls (`ITEM_LEVEL_BALL`, `ITEM_LURE_BALL`, `ITEM_MOON_BALL`, `ITEM_FRIEND_BALL`, `ITEM_FAST_BALL`, `ITEM_HEAVY_BALL`, `ITEM_LOVE_BALL`) verified.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 10. Unown Pokédex Form Viewer (`pokecrystal`)

- `[██████████] 100%` **Ruins of Alph Unown Dex Mode**
  - **Reference**: `games/gbc/pokecrystal/engine/pokedex/unown_dex.asm`, `data/pokemon/unown_words.asm`
  - **Completed**:
    - Catching 3+ Unown triggers the scientist in `RuinsOfAlphOutside_Johto` to award `FLAG_JOHTO_ENGINE_UNOWN_DEX` via `special JohtoGetUnownCaughtCount`.
    - Letter unlocking based on solved puzzle chambers (Kabuto A-K, Omanyte L-R, Aerodactyl S-W, Ho-Oh X-Z, and secret chamber ?/!) functional in `src/unown.c`.
    - Dedicated Pokédex Form Viewer sub-screen: when viewing Unown in the Pokédex with `FLAG_JOHTO_ENGINE_UNOWN_DEX` set and at least 1 Unown caught, pressing `SELECT` opens the interactive Unown Dex mode with D-pad Left/Right navigation, sprite loading, and return keybindings (`Task_HandleUnownDexInput`, `Pokedex_DrawUnownDexScreen`).
    - Bitfield tracking for all 28 forms (`VAR_JOHTO_UNOWN_CAUGHT_LOWER`, `VAR_JOHTO_UNOWN_CAUGHT_UPPER`), caught count popup, and all 28 authentic GBC Crystal ancient words (ANGRY, BEAR, CHASE, DIRECT, ENGAGE, FIND, GIVE, HELP, INCREASE, JOIN, KEEP, LAUGH, MAKE, NUZZLE, OBSERVE, PERFORM, QUICKEN, REASSURE, SEARCH, TELL, UNDO, VANISH, WANT, XXXXX, YIELD, ZOOM, !!!!, ????).
    - Unlocked dialogue for Ruins of Alph scientists, computer, and printer when catching 26+ Unown forms.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 11. Goldenrod Game Corner Card Flip Minigame (`pokecrystal`)

- `[██████████] 100%` **Card Guessing Minigame Engine**
  - **Reference**: `games/gbc/pokecrystal/engine/games/card_flip.asm`
  - **Completed**:
    - Card Flip game engine in `src/card_flip.c` and `include/card_flip.h`: authentic 24-card deck (4 Pokémon suits: Pikachu, Jigglypuff, Poliwag, Oddish; 6 numeric ranks: 1 through 6).
    - 5 authentic Crystal betting modes and multipliers: Single Card (24x, 72 coins), Single Rank (6x, 18 coins), Single Suit (4x, 12 coins), Rank Pair (3x, 9 coins), and Suit Pair (2x, 6 coins).
    - Authentic 12-round deal loop (2 cards dealt face down per round), Card 1 vs Card 2 choice, discard pile tracking, and automatic reshuffling once all 24 cards are played.
    - Full overworld script integration for Goldenrod Game Corner and Celadon Game Corner tables with interactive dynamic multichoice menus, coin case checks, live coin display window, and authentic Crystal sound effects (`SE_RG_CARD_FLIP`, `SE_RG_CARD_FLIPPING`, `SE_RG_CARD_OPEN`, `SE_SHOP`, `SE_BOO`).
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 12. Buena's Password Blue Card Point Exchange (`pokecrystal`)

- `[██████████] 100%` **Radio Show Quiz & Prize Redemption Counter**
  - **Reference**: `games/gbc/pokecrystal/engine/events/buena.asm`, `games/gbc/pokecrystal/data/items/buena_prizes.asm`
  - **Completed**:
    - Daily password generation across 10 categories (30 authentic passwords) generated dynamically or synchronized with Pokégear radio broadcast station 10.5 MHz.
    - Blue Card acquisition (`ITEM_BLUE_CARD`) and balance tracking up to 30 points (`VAR_JOHTO_BLUE_CARD_BALANCE`).
    - Evening dialogue quiz (18:00 to 23:59 verified via `special JohtoCheckBuenaTime` and RTC engine) with 3-choice dynamic multichoice menu (`JohtoGetBuenaPasswordChoices` and `dynmultipush` / `dynmultistack`). Correct answer adds 1 point to `VAR_JOHTO_BLUE_CARD_BALANCE` (capped at 30) with daily lock flag `FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY` resetting at midnight.
    - Authentic Crystal prize exchange counter with all 9 prizes (Ultra Ball [2 pts], Full Restore [2 pts], Nugget [3 pts], Rare Candy [3 pts], Protein [5 pts], Iron [5 pts], Carbos [5 pts], Calcium [5 pts], HP Up [5 pts]) via `special JohtoRedeemBuenaPrize`.
    - Goldenrod Radio Tower studio lobby desk script wired and verified.
    - Automated C unit test suite in `test/confluence.c` verifying balance, evening validation, correct/incorrect answer grading, point cap, and prize redemption.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 13. Johto Battle Tower 7-Trainer Ladder (`pokecrystal`)

- `[██████████] 100%` **Tiered Challenge Rooms & Authentic Vitamin Rewards**
  - **Reference**: `games/gbc/pokecrystal/engine/events/battle_tower/battle_tower.asm`
  - **Completed**:
    - Battle Tower 1F lobby scene, receptionist dialogue, party eligibility check (`JohtoCheckBattleTowerEligibility`), elevator, and hallway sequence are fully functional without freezes.
    - Level bracket selection: dynamic multichoice menu offering Level 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 challenge brackets (`VAR_JOHTO_BATTLE_TOWER_LEVEL`).
    - 7-trainer battle gauntlet in `BattleTowerBattleRoom_Johto`: consecutive opponent generation with no EXP gain, heal between rounds, streak tracking, and authentic Crystal trainer pool.
    - Victory rewards: clearing all 7 trainers awards 5 random stat vitamins (HP Up, Protein, Iron, Carbos, Calcium).
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 14. Fame Checker Subsystem Restoration (`pokefirered`)

- `[██████████] 100%` **Restore `src/fame_checker.c` and Kanto VIP Lore Journal**
  - **Reference**: `games/gba/pokefirered/src/fame_checker.c`, `include/fame_checker.h`
  - **Completed**:
    - `ITEM_FAME_CHECKER` and item icons exist in Bag and graphics data.
    - Full source implementation restored in [src/fame_checker.c](src/fame_checker.c) with conflict-free sprite tag allocation in `0xD500` range and full graphics pipeline in `graphics/fame_checker/`.
    - Saved state integrated into `SaveBlock1`: `struct FameCheckerSaveData fameChecker[NUM_FAMECHECKER_PERSONS]` (32 bytes budgeted in free sector space).
    - Verified all 16 Kanto person profiles: Prof. Oak, Daisy Oak, Brock, Misty, Lt. Surge, Erika, Koga, Sabrina, Blaine, Giovanni, Lorelei, Bruno, Agatha, Lance, Bill, Mr. Fuji.
    - Overworld flavor text triggers across Kanto signposts, bookshelves, and NPCs wired via `famechecker` script macro.
    - Bag & field usage: `ITEM_FAME_CHECKER` wired with `ItemUseOutOfBattle_FameChecker` supporting in-bag invocation and registered SELECT button quick usage.
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 15. Joyful Game Corner Minigames & Berry Crusher Vendor (`pokefirered`)

- `[██████████] 100%` **Wireless Minigame Overworld Linkage & Berry Powder Economy**
  - **Reference**: `games/gba/pokefirered/src/berry_crush.c`, `dodrio_berry_picking.c`, `pokemon_jump.c`
  - **Completed**:
    - C source engines for `berry_crush.c`, `dodrio_berry_picking.c`, and `pokemon_jump.c` are fully compiled and linked in the ROM.
    - `FREE_POKEMON_JUMP = FALSE` in `include/config/save.h` preserves save data.
    - Overworld interaction scripts in `TwoIsland_JoyfulGameCorner_Frlg` and `data/scripts/cable_club_frlg.inc`: link counter attendant supports standard wireless link play as well as solo practice mode for both Pokémon Jump and Dodrio Berry-Picking (`StartPokemonJumpPracticeSpecial`, `StartDodrioBerryPickingPracticeSpecial`), party species eligibility checks (`IsPokemonJumpSpeciesInParty`, `IsDodrioInParty`), and record displays.
    - Cerulean City Berry Powder Man (`CeruleanCity_House5_Frlg/scripts.inc`): awards `ITEM_POWDER_JAR` upon checking at least 1 berry in Bag (`specialvar VAR_RESULT, HasAtLeastOneBerry`), tracks total powder crushed via `IncrementGameStat(GAME_STAT_PLAYED_BERRY_CRUSH)`, and opens powder exchange shop for all 11 authentic items: Energypowder (50), Heal Powder (50), Energy Root (80), Revival Herb (300), Protein (1000), Iron (1000), Carbos (1000), Calcium (1000), Zinc (1000), HP Up (1000), and PP Up (3000).
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 16. Teachy TV & Contextual Help System (`pokefirered`)

- `[██████████] 100%` **Dude's Interactive Tutorial TV & Overworld Multi-Region Cycling**
  - **Reference**: `games/gba/pokefirered/src/teachy_tv.c`, `src/help_system.c`
  - **Completed**:
    - Ported `teachy_tv.c` and `include/teachy_tv.h` from `pokefirered` with Poke Dude hosting all 6 lessons (Battle Basics, Status Conditions, Type Matchups, Catching Pokémon, TMs, Key Item Registration) and CANCEL.
    - Integrated authentic Route 1 TV set backdrop with BG dynamic tile decompression and tall grass rustle sprites (`TeachyTvGrassAnimationMain`).
    - Wired `ITEM_TEACHY_TV` out-of-battle handler `ItemUseOutOfBattle_TeachyTv` in `src/item_use.c` and registered Key Item usage from field and bag menu.
    - Preserved L/R shoulder buttons for multi-region badge card and world map cycling without glossary interception.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 17. Surfing Pikachu Beach Minigame (`pokeyellow`)

- `[██████████] 100%` **Route 19 Beach House Wave Surfing Physics**
  - **Reference**: `games/gbc/pokeyellow/engine/minigame/surfing_pikachu.asm`
  - **Completed**:
    - Connected Route 19 Beach House (`Route19_UnusedHouse_Frlg`) in `gMapGroup_IndoorFuchsia_Frlg` with overworld beach entrance warp at (5, 9).
    - Added Surfin' Dude NPC, Surfing Pikachu, surf tip posters, and High Score printer BG event.
    - Added party scan special `CheckSurfingPikachuInParty` verifying `SPECIES_PIKACHU` knowing `MOVE_SURF`.
    - Implemented full 2D surfing simulation in `src/surfing_pikachu.c`: 24-section ocean course, sinusoidal wave crests and troughs, jump trajectories, D-Pad rotation tricks, Radness combo scaling (+100 * flips), Clean (+500 pts, boost), Rough (+100 pts), Hard, and Wipeout landing detection.
    - Integrated results calculation with time bonus (`hp * 5`) + Radness points, updating `VAR_SURFING_PIKACHU_HIGH_SCORE`, `VAR_SURFING_PIKACHU_RADNESS`, and `GAME_STAT_SURFING_PIKACHU_HIGH_SCORE`.
    - Added printer script reading saved high scores via `GetSurfingPikachuScores`.
    - Automated unit test suite verified: party qualification, move checking, score variables, and flag manipulation.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 18. Pikachu Voiced 8-bit PCM Audio Samples (`pokeyellow`)

- `[██████████] 100%` **Authentic Ikue Otani Digitized Voice Clips**
  - **Reference**: `games/gbc/pokeyellow/audio/pikachu_pcm.asm`, `audio/sfx_pikachu.asm`
  - **Completed**:
    - Converted and compiled authentic Ikue Otani voice samples into GBA 8-bit DPCM samples in `sound/direct_sound_samples/pikachu_voice/`: battle entrance (`cry_37.bin`), faint (`cry_4.bin`), low HP moan (`cry_17.bin`), level-up celebration (`cry_28.bin`), Thunder shock cry (`cry_2.bin`), joyful cheer (`cry_5.bin`), and sad/weary (`cry_31.bin`).
    - Config toggle `VOICED_PIKACHU_CRIES = TRUE` added to `include/config/pokemon.h` with instant fallback to standard Gen 3 electronic cries when disabled.
    - Linked `gPikachuVoiceTable` and `gPikachuVoiceTable_Reverse` in `sound/cry_tables.inc` and `sound/direct_sound_data.inc`.
    - Integrated direct dispatch functions `PlayPikachuVoice` and `PlayPikachuCelebrationCry` in `src/sound.c` and declared in `include/sound.h`.
    - Wired cry interception into `PlayCryInternal` automatically directing battle entrance, faints, low HP, thunder attacks, and overworld cries to authentic anime samples for all Pikachu forms (Cosplay, Rock Star, Belle, Pop Star, PhD, Libre, Partner, Starter, Gmax).
    - Integrated mood-reactive playback into `Special_ShowLeadPokemonMood` in `src/mood.c`.
    - Automated unit test suite verified: configuration, constants, table structures, reverse tables, Pikachu forms, and headless-safe execution.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 19. Hoenn Gym Leader Match Call Rematches (`pokeemerald`)

- `[██████████] 100%` **4-Tier Scaled Rematch Teams for All 8 Hoenn Leaders**
  - **Reference**: `games/gba/pokeemerald/src/battle_setup.c`, `data/trainers.party`, `src/gym_leader_rematch.c`
  - **Completed**:
    - Match Call system in Hoenn (`pokenav_match_call.c`, `pokenav_match_call_data.c`) supports trainer calls, caller registration, and rematch notifications.
    - All 5 trainer rosters (base + 4 rematch tiers) for all 8 Hoenn leaders (`TRAINER_ROXANNE_1..5`, `TRAINER_BRAWLY_1..5`, `TRAINER_WATTSON_1..5`, `TRAINER_FLANNERY_1..5`, `TRAINER_NORMAN_1..5`, `TRAINER_WINONA_1..5`, `TRAINER_TATE_AND_LIZA_1..5`, `TRAINER_JUAN_1..5`) linked in `gRematchTable`.
    - Gym leader rematch scripts across all 8 gyms support `trainerbattle_rematch_double` and dynamic rematch qualification.
    - Multi-region qualification in `src/gym_leader_rematch.c` and `src/pokenav_match_call_data.c`: rematches qualify upon `FLAG_SYS_GAME_CLEAR`, `FLAG_CONFLUENCE_APEX_CHAMPION`, or achieving 8+ badges (`Confluence_CountBadges() >= 8`).
    - Fixed `GetCurrentGymLeaderRematchLevel()` calculation and leader index bounds (`REMATCH_ROXANNE` to `< REMATCH_ELITE_FOUR_ENTRIES`).
    - Automated unit test suite verified: rematch tables, roster tier scaling, `CountBattledRematchTeams`, `ShouldTryRematchBattleForTrainerId`, and multi-region qualification.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 20. Trick House Puzzles 1–8 & Mirage Island Mechanics (`pokeemerald`)

- `[██████████] 100%` **Route 110 Puzzle Rooms & Route 130 Mirage Seed Generation**
  - **Reference**: `games/gba/pokeemerald/src/time_events.c`, `src/clock.c`, `data/maps/Route110_TrickHousePuzzle*/`
  - **Completed**:
    - All 8 Trick House puzzle map layouts, hidden Trick Master locations, scroll signs, locked doors, and reward delivery scripts verified.
    - Door scroll passcodes and door unlock triggers across all 8 rooms (`VAR_TRICK_HOUSE_PUZZLE_1_STATE` through `VAR_TRICK_HOUSE_PUZZLE_8_STATE`) verified.
    - Multi-region badge qualification in `Route110_TrickHouseEntrance/scripts.inc`: puzzles 2–8 evaluate regional Gym Badges (`FLAG_BADGE03_GET` through `FLAG_BADGE08_GET`, `FLAG_SYS_GAME_CLEAR`, `FLAG_CONFLUENCE_APEX_CHAMPION`) or total multi-region badge counts via `ConfluenceCountBadges`.
    - Mirage Island mechanics in `src/time_events.c`, `src/clock.c`, and `src/overworld.c`: daily 16-bit pseudorandom seed generation (`UpdateMirageRnd`), personality comparison (`IsMirageIslandPresent`), Pacifidlog Town Mirage Watcher script, and dynamic Route 130 layout switching (`LAYOUT_ROUTE130_MIRAGE_ISLAND`) revealing wild Wynaut and the Liechi Berry tree.
    - Desert Mirage Tower crumbling sequence on Route 111 upon retrieving Root Fossil or Claw Fossil (`special StartMirageTowerShake`, `special StartPlayerDescendMirageTower`, `special StartMirageTowerDisintegration`, and Desert Underpass access).
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 21. Contest Halls & Berry Blender Pokéblock Minigame (`pokeemerald`)

- `[██████████] 100%` **Contest Appeals & 4-Player Blender Engine**
  - **Reference**: `games/gba/pokeemerald/src/contest.c`, `src/berry_blender.c`, `src/pokeblock.c`
  - **Completed**:
    - Centralized Emerald Contest Lobby in Lilycove City (`LilycoveCity_ContestLobby`) supporting all four competition ranks: Normal, Super, Hyper, and Master, and all five categories: Cool, Beauty, Cute, Smart, and Tough.
    - Verified Emerald Battle Tents in Slateport, Verdanturf, and Fallarbor with dedicated rental, palace, and arena style tournament challenges.
    - Contest Receptionist script delivers `ITEM_POKEBLOCK_CASE`, checks entry qualifications and ribbons, and stages the 2-round contest appeals seamlessly in `data/scripts/contest_hall.inc` and `data/maps/ContestHall/`.
    - Solo NPC Berry Blenders in Lilycove Contest Lobby: 2-player (1 NPC Mister), 3-player (2 NPCs Laddie & Lassie), 4-player (3 NPCs Dude, Lassie, Miss), and PokéNews Blend Master tables fully functional without link timeouts (`DoBerryBlending`).
    - Pokéblock crafting algorithm: authentic calculation of colors, flavor levels, feel, max RPM, sheen, and nature-based flavor affinity (`PokeblockGetGain`) across all 40 Case slots.
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 22. DexNav Search Levels & Encounter HUD Calibration (`pokeemerald-expansion`)

- `[██████████] 100%` **Saveblock-Safe Search Levels & Overworld Target Tracking**
  - **Reference**: `games/roms/pokeemerald-expansion/src/dexnav.c`, `include/config/dexnav.h`
  - **Completed**:
    - Enabled `DEXNAV_ENABLED = TRUE` and `USE_DEXNAV_SEARCH_LEVELS = TRUE` in `include/config/dexnav.h`.
    - Solved SaveBlock3 overflow constraints (preventing 1698-byte overrun on 1624-byte SaveBlock3) by designing a 256-slot dynamic search level cache `struct DexNavSearchLevelEntry { u16 species; u8 searchLevel; }` inside `SaveBlock3` (~1072 bytes total).
    - Implemented `DexNav_GetSearchLevel(species)` and least-used cache entry recycling in `TryIncrementSpeciesSearchLevel()` in `src/dexnav.c`.
    - DexNav radar search, hidden abilities, egg moves, and chaining active across Johto, Kanto, and Hoenn maps with accurate time-of-day encounter synchronization.
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 23. Modern Party EXP Share Key Item Toggle (`pokeemerald-expansion`)

- `[██████████] 100%` **Key Item Exp. Share Configuration & Distribution**
  - **Reference**: `include/config/item.h`, `src/battle_main.c`, `src/battle_script_commands.c`, `src/battle_util.c`
  - **Completed**:
    - Added config options `EXP_SHARE_HELD_ITEM` (Gen 2-5) and `EXP_SHARE_KEY_ITEM` (Gen 6+) with `I_EXP_SHARE_MODE` selector in `include/config/item.h`.
    - Allocated persistent toggle flag `FLAG_EXP_SHARE_ENABLED` (0x264) in `include/constants/flags.h`.
    - Set `ITEM_EXP_SHARE` as a Key Item (`POCKET_KEY_ITEMS`, importance 1) when in `EXP_SHARE_KEY_ITEM` mode, supporting field/bag usage toggling on/off with sound effects `SE_EXP_MAX` / `SE_PC_OFF` and notifications.
    - Enhanced `IsGen6ExpShareEnabled()` in `src/battle_util.c` to require possessing `ITEM_EXP_SHARE` in the Bag before granting party Exp.
    - Verified battle exp distribution: participating Pokémon gain 100% calculated Exp while benched team members receive 50% base Exp when Key Item Exp. Share is active, plus team Exp message (`STRINGID_TEAMGAINEDEXP`).
    - Wired automatic activation on item receipt in Mr. Pokémon's House (`MrPokemonsHouse_Johto`), Devon Corp (`RustboroCity_DevonCorp_3F`), and Route 15 Gate (`Route15_WestEntrance_2F_Frlg`).
    - Verified by automated C unit test suite in `test/confluence.c`.
  - **Missing**:
    - None. Fully completed, integrated, and verified by automated C unit test suite.

---

### 24. Unified Multi-Region Pokédex Selection Menu (`pokemultiregion`)

- `[█████░░░░░] 50%` **In-Game Regional Pokédex Switching (Hoenn, Kanto, Johto, National)**
  - **Reference**: `games/roms/pokemultiregion/src/pokedex.c`, `include/constants/pokedex.h`
  - **Completed**:
    - Full Johto Regional Dex ordering defined in `FOREACH_SPECIES_IN_JOHTO_DEX_ORDER(F)` (Chikorita #001 to Celebi #251) in `include/constants/pokedex.h`.
    - Lookup table `sJohtoToNationalOrder[251]` and conversion functions (`SpeciesToJohtoPokedexNum()`, `GetJohtoPokedexCount()`, `HasAllJohtoMons()`) implemented in `src/pokemon.c` and `src/pokedex.c`.
    - Automatic regional dex loading based on `GetCurrentRegion() == REGION_JOHTO`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Interactive Pokédex Mode Selection Menu: upon opening the Pokédex, allow pressing `SELECT` or choosing from a submenu:
      - Hoenn Pokédex (202 species)
      - Kanto Pokédex (151 species)
      - Johto Pokédex (251 species)
      - National Pokédex (386 species)
    - `[░░░░░░░░░░] 0%` Dedicated diploma scripts for completing each of the three regional Pokédexes (Game Designer in Cove Lily Motel for Hoenn, Celadon Hotel for Kanto, and Goldenrod for Johto).

---

### 25. Unified Bag Town Map Regional Cycling (`pokemultiregion`)

- `[███████░░░] 70%` **L/R Region Cycling for Bag Town Map & Pokégear Map Card**
  - **Reference**: `src/region_map.c`, `src/pokenav_menu_handler.c`
  - **Completed**:
    - Fly Map supports seamless `L_BUTTON` and `R_BUTTON` cycling across Hoenn (`REGION_MAP_HOENN`), Kanto (`REGION_MAP_KANTO`), and Johto (`REGION_MAP_JOHTO`) with correct tilemaps and fly points.
    - Dedicated Johto Town Map layout (`sRegionMapSections_Johto[15][28]`) with 45 authentic Crystal map sections is fully rendered in `src/data/region_map/region_map_layout_johto.h`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Enable L/R regional cycling when viewing the Town Map from the Bag (`ITEM_TOWN_MAP`) or via the Pokégear Map Card, matching the Fly Map implementation.
    - `[░░░░░░░░░░] 0%` Position the player marker accurately on the native region's map and hide it when browsing other regions.

---

### 26. S.S. Aqua Weekly Sailing Schedule & Cabin Event Progression (`pokemultiregion`)

- `[███████░░░] 75%` **Weekday Ferry Timetable & Lost Granddaughter Questline**
  - **Reference**: `data/maps/FastShip1F_Johto/scripts.inc`, `FastShipCabins_*/scripts.inc`
  - **Completed**:
    - All 5 Fast Ship maps (`FastShip1F_Johto`, `FastShipCabins_NNW_NNE_NE_Johto`, `FastShipCabins_SW_SSW_NW_Johto`, `FastShipCabins_SE_SSE_CaptainsCabin_Johto`, `FastShipB1F_Johto`) and Vermilion/Olivine ports exist.
    - Boarding guard checks `ITEM_S_S_TICKET`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Enforce authentic Crystal weekly sailing timetable:
      - Departs **Olivine Port**: Monday & Friday.
      - Departs **Vermilion Port**: Wednesday & Sunday.
    - `[░░░░░░░░░░] 0%` First trip sequence: cabin sailor announces arrival only after player finds the lost little girl in the Captain's Cabin and brings her back to her worried grandfather on 1F, receiving `ITEM_METAL_COAT`.
    - `[░░░░░░░░░░] 0%` Directional passenger rotation: westbound vs eastbound passengers appear in different cabins on alternate sailing days.

---

### 27. Magnet Train Goldenrod–Saffron Pass Questline (`pokemultiregion`)

- `[██████░░░░] 60%` **Copycat Clefairy Doll Quest & High-Speed Transit Animation**
  - **Reference**: `data/maps/GoldenrodMagnetTrainStation_Johto/scripts.inc`, `SaffronCity_CopycatsHouse_2F_Frlg/`
  - **Completed**:
    - Magnet Train stations in Goldenrod and Saffron exist and connect to `MagnetTrain` special.
    - Power Plant Machine Part quest restores electricity to the Kanto grid (`FLAG_JOHTO_RESTORED_POWER_TO_KANTO`).
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Copycat lost Clefairy doll quest: talking to Copycat in Saffron City after power is restored reveals her Lost Item was left at the Pokémon Fan Club in Vermilion City.
    - `[░░░░░░░░░░] 0%` Returning `ITEM_LOST_ITEM` to Copycat awards the `ITEM_PASS` (`FLAG_JOHTO_GOT_PASS_FROM_COPYCAT`).
    - `[░░░░░░░░░░] 0%` Authentic high-speed Magnet Train transition cutscene playing `MUS_MAGNET_TRAIN` sound effects and scrolling landscape sprites.

---

### 28. Apex Summit 24-Leader Boss Gauntlet (`pokemultiregion`)

- `[████░░░░░░] 40%` **Level 100 Post-Game Multi-Region Tournament**
  - **Reference**: `data/maps/ApexSummit_Johto/`, `src/confluence.c`
  - **Completed**:
    - `ApexSummit_Johto` map exists as Map 84 in `gMapGroup_Johto4`.
    - 24-badge tracking via `Confluence_CountBadges()` and level cap lifting to 100 upon earning `FLAG_CONFLUENCE_APEX_CHAMPION`.
    - Dynamic boss scaling engine in `src/caps.c`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Apex Tournament registration receptionist and bracket generator: randomly pairs the player against 5 rounds of Gym Leaders, Elite Four, or Champions from Hoenn, Kanto, and Johto, all scaled to Level 100 with competitive held items, EVs, and modern movesets.
    - `[░░░░░░░░░░] 0%` Apex Champion Trophy and custom Trainer Card star / ribbon for conquering the 24-Leader Gauntlet.
