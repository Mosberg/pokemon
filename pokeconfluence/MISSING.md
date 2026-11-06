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
| **9. Interactive Kurt's Apricorn Crafting**              | `pokecrystal`           | In Progress | `[██░░░░░░░░] 25%`  | Multichoice Apricorn selection menu, midnight RTC wait timer                                       |
| **10. Unown Pokédex Form Viewer (Unown Dex)**            | `pokecrystal`           | In Progress | `[██░░░░░░░░] 20%`  | Pokédex sub-screen cataloging caught A-Z, ?, ! forms & definitions                                 |
| **11. Goldenrod Game Corner Card Flip Minigame**         | `pokecrystal`           |   Backlog   |  `[░░░░░░░░░░] 0%`  | 4x6 grid betting minigame (`card_flip.asm`), coin payouts                                          |
| **12. Buena's Password Blue Card Point Exchange**        | `pokecrystal`           | In Progress | `[████░░░░░░] 40%`  | 2F Radio Tower point shop for 9 prizes, radio broadcast sync                                       |
| **13. Johto Battle Tower 7-Trainer Ladder**              | `pokecrystal`           | In Progress | `[████░░░░░░] 45%`  | Level 10-100 room brackets, 7 consecutive battles, vitamin rewards                                 |
| **14. Fame Checker Subsystem Restoration**               | `pokefirered`           | In Progress | `[██░░░░░░░░] 20%`  | Uncomment & restore `src/fame_checker.c`, 16 Kanto VIP profiles                                    |
| **15. Joyful Game Corner & Berry Crusher Vendor**        | `pokefirered`           | In Progress | `[██████░░░░] 60%`  | Overworld script linkage for Dodrio Berry-Picking & Powder Jar vendor                              |
| **16. Teachy TV & Contextual Help System**               | `pokefirered`           |   Backlog   |  `[░░░░░░░░░░] 0%`  | Dude's tutorial programs, battle basics, L/R help glossary                                         |
| **17. Surfing Pikachu Beach Minigame**                   | `pokeyellow`            |   Backlog   |  `[░░░░░░░░░░] 0%`  | Route 19 Beach House, surfing physics, Radness flips, high scores                                  |
| **18. Pikachu Voiced 8-bit PCM Audio Samples**           | `pokeyellow`            |   Backlog   |  `[░░░░░░░░░░] 0%`  | Ikue Otani battle entries, faints, mood reaction audio clips                                       |
| **19. Hoenn Gym Leader Match Call Rematches**            | `pokeemerald`           | In Progress | `[████░░░░░░] 40%`  | 4-tier rematch teams for Roxanne through Juan via Match Call                                       |
| **20. Trick House Puzzles 1-8 & Mirage Island**          | `pokeemerald`           | In Progress | `[██████░░░░] 60%`  | Route 110 maze rooms, badge unlocks, Route 130 Mirage Island seed                                  |
| **21. Contest Halls & Berry Blender Pokéblock Minigame** | `pokeemerald`           | In Progress | `[████████░░] 80%`  | Slateport/Verdanturf/Fallarbor/Lilycove halls & blender minigame                                   |
| **22. DexNav Search Levels & Encounter HUD**             | `pokeemerald-expansion` | In Progress | `[██████░░░░] 60%`  | Saveblock-safe search levels, hidden abilities, egg moves HUD                                      |
| **23. Modern Party EXP Share Key Item Toggle**           | `pokeemerald-expansion` | In Progress | `[██████░░░░] 60%`  | `I_EXP_SHARE_FLAG` option in `include/config/item.h`                                               |
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

- `[██░░░░░░░░] 25%` **Apricorn Selection UI & Overnight Crafting Timer**
  - **Reference**: `games/gbc/pokecrystal/engine/events/kurt.asm`, `data/items/apricorns.asm`
  - **Completed**:
    - Kurt event script in `KurtsHouse_Johto/scripts.inc` calls `special JohtoSelectApricornForKurt`.
    - All 7 Apricorn items (`ITEM_RED_APRICORN`, `ITEM_BLU_APRICORN`, `ITEM_YLW_APRICORN`, `ITEM_GRN_APRICORN`, `ITEM_WHT_APRICORN`, `ITEM_BLK_APRICORN`, `ITEM_PNK_APRICORN`) and balls (`ITEM_LEVEL_BALL`, `ITEM_LURE_BALL`, `ITEM_MOON_BALL`, `ITEM_FRIEND_BALL`, `ITEM_FAST_BALL`, `ITEM_HEAVY_BALL`, `ITEM_LOVE_BALL`) exist in the engine.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Interactive selection menu: replace the auto-first-item logic in `JohtoSelectApricornForKurt` ([src/johto_scripts.c](src/johto_scripts.c#L192)) with a dynamic multichoice list displaying only the Apricorns currently in the player's Bag.
    - `[░░░░░░░░░░] 0%` Overnight crafting timer: record `VAR_KURT_APRICORN_GIVEN` and date in `DoDailyEvents()` ([src/clock.c](src/clock.c)); Kurt tells the player "It will take a day to make a Ball. Come back tomorrow!" and only delivers the crafted ball after midnight RTC tick.
    - `[░░░░░░░░░░] 0%` Batch crafting option: allow giving multiple Apricorns of the same color at once (Gen 4 HGSS quality-of-life feature).

---

### 10. Unown Pokédex Form Viewer (`pokecrystal`)

- `[██░░░░░░░░] 20%` **Ruins of Alph Unown Dex Mode**
  - **Reference**: `games/gbc/pokecrystal/engine/pokedex/unown_dex.asm`
  - **Completed**:
    - Catching 3+ Unown triggers the scientist in `RuinsOfAlphResearchCenter_Johto` to award `FLAG_JOHTO_ENGINE_UNOWN_DEX`.
    - Letter unlocking based on solved puzzle chambers (Kabuto A-K, Omanyte L-R, Aerodactyl S-W, Ho-Oh X-Z, and secret chamber ?/!) is functional in `src/unown.c`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Dedicated Pokédex Form Viewer sub-screen: when viewing Unown in the Pokédex with `FLAG_JOHTO_ENGINE_UNOWN_DEX` set, pressing `SELECT` opens the Unown Dex mode.
    - `[░░░░░░░░░░] 0%` Visual grid rendering all 28 Unown forms in order caught, displaying their associated ancient word meanings (Anger, Bear, Chase, Direct, Engage, Find, Give, Help, Increase, Join, Keep, Laugh, Move, Nuzzle, Observe, Perform, Quicken, Reassure, Search, Tell, Undo, Vanish, Want, XXXXX, Yield, Zoom, ????, !!!!).

---

### 11. Goldenrod Game Corner Card Flip Minigame (`pokecrystal`)

- `[░░░░░░░░░░] 0%` **Card Guessing Minigame Engine**
  - **Reference**: `games/gbc/pokecrystal/engine/games/card_flip.asm`
  - **Completed**:
    - Sound effects `SE_RG_CARD_FLIP` and `SE_RG_CARD_FLIPPING` compiled and present in sound engine.
    - Goldenrod and Celadon Game Corner slot machines and prize redemption counters are functional.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Card Flip game engine: 4x6 grid (24 cards) featuring 4 Pokémon suits (Pikachu, Jigglypuff, Poliwag, Oddish) and 6 numeric ranks (1 to 6).
    - `[░░░░░░░░░░] 0%` Betting interface: allow betting 1 to 5 coins on single cards (24x payout), pairs (12x payout), columns (4x payout), or suits (3x payout).
    - `[░░░░░░░░░░] 0%` Deck shuffling and 12-round deal sequence with persistent coin tally.

---

### 12. Buena's Password Blue Card Point Exchange (`pokecrystal`)

- `[████░░░░░░] 40%` **Radio Show Quiz & Prize Redemption Counter**
  - **Reference**: `games/gbc/pokecrystal/engine/events/buena.asm`
  - **Completed**:
    - `ITEM_BLUE_CARD` and point variable `VAR_BLUECARDBALANCE` exist.
    - Buena NPC present in `RadioTower2F_Johto`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Daily password generation: generate 1 of 30 authentic passwords daily at midnight RTC tick.
    - `[░░░░░░░░░░] 0%` Evening dialogue quiz (18:00 to 23:59): Buena asks the player for today's password using a 3-choice menu; correct answer adds 1 point to `VAR_BLUECARDBALANCE` (max 30 points) with once-per-day lock flag.
    - `[░░░░░░░░░░] 0%` Prize exchange receptionist: exchange points for Ultra Ball (2 pts), Full Restore (5 pts), Nugget (10 pts), Rare Candy (15 pts), Protein (20 pts), Iron (20 pts), Carbos (20 pts), Calcium (20 pts), HP Up (20 pts).

---

### 13. Johto Battle Tower 7-Trainer Ladder (`pokecrystal`)

- `[████░░░░░░] 45%` **Tiered Challenge Rooms & Authentic Vitamin Rewards**
  - **Reference**: `games/gbc/pokecrystal/engine/events/battle_tower/battle_tower.asm`
  - **Completed**:
    - Battle Tower 1F lobby scene, receptionist dialogue, party eligibility check (`JohtoCheckBattleTowerEligibility`), elevator, and hallway sequence are fully functional without freezes.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Level bracket selection: multichoice menu offering Level 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 challenge brackets.
    - `[░░░░░░░░░░] 0%` 7-trainer battle gauntlet in `BattleTowerBattleRoom_Johto`: consecutive opponent generation with no EXP gain, heal between rounds, and streak tracking.
    - `[░░░░░░░░░░] 0%` Victory rewards: clearing all 7 trainers awards 5 random stat vitamins (HP Up, Protein, Iron, Carbos, Calcium).

---

### 14. Fame Checker Subsystem Restoration (`pokefirered`)

- `[██░░░░░░░░] 20%` **Restore `src/fame_checker.c` and Kanto VIP Lore Journal**
  - **Reference**: `games/gba/pokefirered/src/fame_checker.c`, `include/fame_checker.h`
  - **Completed**:
    - `ITEM_FAME_CHECKER` and item icons exist in Bag and graphics data.
    - Full source implementation exists in [src/fame_checker.c](src/fame_checker.c), but lines 20–1735 are currently commented out to avoid sprite tag conflicts during early migration.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Uncomment and update `src/fame_checker.c`: rebind sprite tags (`SPRITETAG_SELECTOR_CURSOR`, `SPRITETAG_OAK`, `SPRITETAG_DAISY`, `SPRITETAG_BILL`, `SPRITETAG_FUJI`) to safe Confluence sprite tag ranges.
    - `[░░░░░░░░░░] 0%` Link UI tilemaps (`graphics/fame_checker/tilemap1.bin`) and palette buffers.
    - `[░░░░░░░░░░] 0%` Verify all 16 Kanto person profiles: Prof. Oak, Daisy Oak, Brock, Misty, Lt. Surge, Erika, Koga, Sabrina, Blaine, Giovanni, Lorelei, Bruno, Agatha, Lance, Bill, Mr. Fuji.
    - `[░░░░░░░░░░] 0%` Overworld flavor text triggers across Kanto signposts, bookshelves, and NPCs that set the corresponding `FLAG_FAME_CHECKER_*` flags.

---

### 15. Joyful Game Corner Minigames & Berry Crusher Vendor (`pokefirered`)

- `[██████░░░░] 60%` **Wireless Minigame Overworld Linkage & Berry Powder Economy**
  - **Reference**: `games/gba/pokefirered/src/berry_crush.c`, `dodrio_berry_picking.c`, `pokemon_jump.c`
  - **Completed**:
    - C source engines for `berry_crush.c`, `dodrio_berry_picking.c`, and `pokemon_jump.c` are fully compiled and linked in the ROM.
    - `FREE_POKEMON_JUMP = FALSE` in `include/config/save.h` preserves save data.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Overworld interaction scripts in `TwoIsland_JoyfulGameCorner_Frlg`: link counter NPCs to launch `dodrio_berry_picking` and `pokemon_jump` minigame tasks directly (including solo/bot practice mode).
    - `[░░░░░░░░░░] 0%` Cerulean City Berry Powder Man: award `ITEM_POWDER_JAR` upon first visit, track total powder crushed via `IncrementGameStat(GAME_STAT_PLAYED_BERRY_CRUSH)`, and open powder exchange shop for Energypowder, Heal Powder, Energy Root, Revival Herb, Protein, Iron, Carbos, Calcium, Zinc, HP Up, and PP Up.

---

### 16. Teachy TV & Contextual Help System (`pokefirered`)

- `[░░░░░░░░░░] 0%` **Dude's Interactive Tutorial TV & Overworld Glossary**
  - **Reference**: `games/gba/pokefirered/src/teachy_tv.c`, `src/help_system.c`
  - **Completed**:
    - Item definition `ITEM_TEACHY_TV` exists in items table.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Port `teachy_tv.c` from `pokefirered`: interactive television program menu with Poke Dude hosting 5 episodes (How to Battle, Status Conditions, Type Matchups, Catching Pokémon, TM/HM Basics).
    - `[░░░░░░░░░░] 0%` Optional Contextual Help System: assess restoring FRLG's L/R button in-game glossary without conflicting with Trainer Card / Fly Map regional cycling.

---

### 17. Surfing Pikachu Beach Minigame (`pokeyellow`)

- `[░░░░░░░░░░] 0%` **Route 19 Beach House Wave Surfing Physics**
  - **Reference**: `games/gbc/pokeyellow/engine/games/surfing_pikachu.asm`
  - **Completed**:
    - FRLG Route 19 Beach House map layout and Summer Beach House NPCs exist in `data/maps/Route19_Frlg/`.
    - Universal mood system and Pikachu Thunder Stone refusal logic from Yellow are fully operational in `src/mood.c`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Check for Pikachu knowing `MOVE_SURF` in party upon interacting with Surfer Dude in Route 19 Beach House.
    - `[░░░░░░░░░░] 0%` 2D Surfing minigame task: ocean wave crest generation, speed calculation, jump trajectory, directional pad acrobatic flips ("Radness" scoring), and landing alignment physics.
    - `[░░░░░░░░░░] 0%` High score tracking sign / printer display inside the Beach House.

---

### 18. Pikachu Voiced 8-bit PCM Audio Samples (`pokeyellow`)

- `[░░░░░░░░░░] 0%` **Authentic Ikue Otani Digitized Voice Clips**
  - **Reference**: `games/gbc/pokeyellow/audio/pikachu_pcm.asm`, `audio/sfx_pikachu.asm`
  - **Completed**:
    - Standard GBA electronic cry `sound/direct_sound_samples/cries/pikachu.bin` compiles in `sound/cry_tables.inc`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Digitize authentic Ikue Otani Yellow voice samples into GBA 8-bit unsigned PCM: battle entrance ("Pikachu!"), faint ("Pikaaa..."), low HP moan, level-up celebration, and Thunder shock cry.
    - `[░░░░░░░░░░] 0%` Config toggle `VOICED_PIKACHU_CRIES` in `include/config/pokemon.h` allowing players to select between classic Yellow anime voice and Gen 3 synthetic cry.

---

### 19. Hoenn Gym Leader Match Call Rematches (`pokeemerald`)

- `[████░░░░░░] 40%` **4-Tier Scaled Rematch Teams for All 8 Hoenn Leaders**
  - **Reference**: `games/gba/pokeemerald/src/battle_setup.c`, `data/trainers.party`
  - **Completed**:
    - Match Call system in Hoenn (`pokenav_match_call.c`) supports trainer calls and rematch notifications.
    - All 37 Johto phone rematches are fully operational in `src/johto_phone.c`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Add 4-tier rematch rosters in `src/data/trainers.party` for Roxanne, Brawly, Wattson, Flannery, Norman, Winona, Tate & Liza, and Juan.
    - `[░░░░░░░░░░] 0%` Wire rematch flags (`FLAG_REMATCH_ROXANNE`, etc.) into `sRematchTable` with post-badge and post-champion qualification checks.

---

### 20. Trick House Puzzles 1–8 & Mirage Island Mechanics (`pokeemerald`)

- `[██████░░░░] 60%` **Route 110 Puzzle Rooms & Route 130 Mirage Seed Generation**
  - **Reference**: `games/gba/pokeemerald/src/mirage_island.c`, `data/maps/Route110_TrickHousePuzzle*/`
  - **Completed**:
    - All 8 Trick House puzzle map layouts exist in `data/maps/`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Verify door scroll passcodes (`"TRICK MASTER is smart"`, etc.) and badge gate sequence across all 8 Trick House puzzles.
    - `[░░░░░░░░░░] 0%` Mirage Island daily check in `src/clock.c`: generate random daily 16-bit seed, compare with party Pokémon personalities in `IsMirageIslandPresent()`, and toggle visibility of Route 130 Mirage Island (Liechi Berry tree and wild Wynaut).
    - `[░░░░░░░░░░] 0%` Route 111 Desert Mirage Tower crumbling sequence when retrieving Root or Claw Fossil.

---

### 21. Contest Halls & Berry Blender Pokéblock Minigame (`pokeemerald`)

- `[████████░░] 80%` **Contest Appeals & 4-Player Blender Engine**
  - **Reference**: `games/gba/pokeemerald/src/contest.c`, `src/berry_blender.c`
  - **Completed**:
    - Contest source files (`contest.c`, `contest_ai.c`, `berry_blender.c`) are linked.
    - Contest categories (Cool, Beauty, Cute, Smart, Tough) and ribbons supported.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Slateport, Verdanturf, Fallarbor, and Lilycove Contest Hall receptionists: verify seamless contest registration and appeal staging in multiregion save format.
    - `[░░░░░░░░░░] 0%` Solo NPC Berry Blender: ensure 1 to 3 NPC blenders function smoothly without link timeouts, awarding correct Pokéblock colors and feels based on berry metrics.

---

### 22. DexNav Search Levels & Encounter HUD Calibration (`pokeemerald-expansion`)

- `[██████░░░░] 60%` **Saveblock-Safe Search Levels & Overworld Target Tracking**
  - **Reference**: `games/roms/pokeemerald-expansion/src/dexnav.c`, `include/config/dexnav.h`
  - **Completed**:
    - `DEXNAV_ENABLED = TRUE` enabled in `include/config/dexnav.h`.
    - DexNav radar search, hidden abilities, egg moves, and chaining active in overworld.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Compact search level bitfield: `USE_DEXNAV_SEARCH_LEVELS` is currently `FALSE` because full 386-byte allocation risks SaveBlock1 overflow. Implement a packed 4-bit nibble table or 64-slot dynamic cache to allow persistent search level bonuses without exceeding save limits.
    - `[░░░░░░░░░░] 0%` DexNav wild species verification across Johto maps (ensuring daytime/nighttime species appear accurately on DexNav radar).

---

### 23. Modern Party EXP Share Key Item Toggle (`pokeemerald-expansion`)

- `[██████░░░░] 60%` **Key Item Exp. Share Configuration & Distribution**
  - **Reference**: `include/config/item.h`, `src/battle_main.c`
  - **Completed**:
    - Gen 2-5 held item Exp. Share (`ITEM_EXP_SHARE`) is fully functional.
    - Mr. Pokémon trade in Route 30 awards `ITEM_EXP_SHARE` for `ITEM_RED_SCALE`.
  - **Missing**:
    - `[░░░░░░░░░░] 0%` Add config option `I_EXP_SHARE_MODE` in `include/config/item.h` to choose between:
      1. `EXP_SHARE_HELD_ITEM` (Classic Gen 2–5 held item splitting EXP).
      2. `EXP_SHARE_KEY_ITEM` (Modern Gen 6+ party-wide toggleable Key Item).
    - `[░░░░░░░░░░] 0%` In battle exp calculation ([src/battle_main.c](src/battle_main.c)): if `EXP_SHARE_KEY_ITEM` is active and the Key Item flag is enabled, distribute 50% base EXP to non-participating party members.

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
