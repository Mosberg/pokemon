# COMPLETED FEATURES & MIGRATIONS

This document tracks all fully converted, integrated, and verified features in **Pokémon Confluence Version** (`pokeconfluence`). Features are verified via automated C unit tests (`pokeconfluence/scripts/test.sh`), ROM builds (`make -C pokeconfluence`), engine limit auditing (`check_limits.py`), and emulator test suites.

---

## 1. Confluence Multi-Region Architecture & Progression

- **24-Badge Level Cap Engine**: Soft level caps scale across all 24 badges (0 badges: 15, 8 badges: 48, 24 badges: 80, Apex Champion: 100). Implemented in [src/caps.c](src/caps.c) and [src/confluence.c](src/confluence.c).
- **Dynamic Boss Scaling**: Gym Leaders, Elite Four, and Champions dynamically scale upward so their strongest Pokémon matches the player's current badge level cap (never downscaled).
- **Meridian Transit System**: Fast travel connecting Slateport (Hoenn), Vermilion (Kanto), and Olivine (Johto) unlocking at 2 badges via Meridian Station (`MeridianStation_Johto`).
- **Resonance Weather Anomaly System**: Convergence crisis weather anomalies trigger across all three regions until Syndicate Enforcers and Chairman are defeated at 12 badges.
- **Regional Hall of Fame Continue Warps**: GameClear continue respawn dynamically routes the player to their native region's home town: New Bark Town (`HEAL_LOCATION_JOHTO_NEW_BARK_TOWN`) for Johto, Pallet Town (`HEAL_LOCATION_PALLET_TOWN`) for Kanto, and Littleroot Town (`HEAL_LOCATION_LITTLEROOT_TOWN_*`) for Hoenn. Implemented in [src/post_battle_event_funcs.c](src/post_battle_event_funcs.c).
- **Field Kit System**: Party menu action item (`ITEM_FIELD_KIT`) allowing Surf, Fly, Flash, Dig, Teleport, Dive, and Waterfall without occupying bag or party move slots, integrated in [src/party_menu.c](src/party_menu.c) and [src/confluence.c](src/confluence.c).

---

## 2. Trainer Card & Regional Badges

- **Multi-Region Trainer Card Display**:
  - Automatically loads the badge case corresponding to the player's active region upon opening (`GetCurrentRegion()`).
  - Interactive regional cycling: Pressing `DPAD_LEFT` / `L_BUTTON` or `DPAD_RIGHT` / `R_BUTTON` / `SELECT_BUTTON` cycles through Hoenn, Kanto, and Johto badge cases with audio feedback (`SE_DEX_PAGE`).
  - Active badge set state tracked via `TrainerCard_GetBadgeRegion()` in [src/trainer_card.c](src/trainer_card.c) and [include/trainer_card.h](include/trainer_card.h).
- **Authentic GBC Crystal Johto Badges**:
  - 8 authentic Crystal badge sprites (Zephyr, Hive, Plain, Fog, Storm, Mineral, Glacier, Rising) extracted and compiled into 128x16 4bpp GBA format with palette in [graphics/trainer_card/johto/badges.png](graphics/trainer_card/johto/badges.png).
- **Regional Badge Engine Mechanics**:
  - Johto and Kanto badges drive Pokémon battle obedience via `GetBadgeFlagForRegion(GetCurrentRegion(), badge)` in [src/battle_util.c](src/battle_util.c).
  - Field move badge requirements adapt to current region in [src/field_move.c](src/field_move.c).
  - Johto badge counter `VAR_BADGES` implemented via `JohtoCountBadges()` in [src/johto_scripts.c](src/johto_scripts.c).
  - Bounds-checked badge flag accessor `GetBadgeFlagForRegion()` in [src/regions.c](src/regions.c).

---

## 3. Pokégear, Communication & Phone Rematches

- **Pokégear Start Menu Entry**:
  - Dynamically replaces Pokénav with Pokégear when in Johto (`GetCurrentRegion() == REGION_JOHTO`) once `FLAG_JOHTO_ENGINE_POKEGEAR` is set.
  - Implemented in [src/start_menu.c](src/start_menu.c) and [src/strings.c](src/strings.c) (`gText_MenuPokegear`).
- **Pokégear Map Card & Phone Card UI**:
  - In Johto (`GetCurrentRegion() == REGION_JOHTO`), opening Town Map requires Map Card (`FLAG_JOHTO_ENGINE_MAP_CARD` / `Johto_HasMapCard()`). Without it, plays `SE_FAILURE` and displays `"The MAP CARD is not installed."`.
  - Match Call requires Phone Card (`FLAG_JOHTO_ENGINE_PHONE_CARD` / `Johto_HasPhoneCard()`). Without it, plays `SE_FAILURE` and displays `"The PHONE CARD is not installed."`.
  - Contextual help text displayed in Pokénav menu: `"Check the map of the JOHTO region."`, `"Call a registered contact."`, and `"Put away the POKéGEAR."`.
  - Implemented in [src/pokenav_menu_handler.c](src/pokenav_menu_handler.c) and [src/pokenav_menu_handler_gfx.c](src/pokenav_menu_handler_gfx.c).
- **Johto Phone Book & Overworld Rematches**:
  - Full registration system supporting all 37 Crystal phone trainers: `JohtoPhoneIsRegistered`, `JohtoPhoneRegister`, and flags in [include/constants/johto_flags.h](include/constants/johto_flags.h).
  - 5-tier rematch team scaling stored in `VAR_JOHTO_MEM_W*`.
  - Rematch arming (`FLAG_JOHTO_ENGINE_*_READY_FOR_REMATCH`) and item gifting for the 11 gift trainers.
- **Overworld Incoming Phone Calls Subsystem**:
  - Implemented authentic Crystal overworld phone calls while walking in Johto in [src/johto_phone.c](src/johto_phone.c) and [include/johto_phone.h](include/johto_phone.h).
  - Wired into `TryStartMatchCall()` in [src/match_call.c](src/match_call.c): counts steps outdoor (~60 steps with 25% trigger probability), selects a registered contact, rings phone with `SE_POKENAV_CALL`, freezes player avatar, and shows slide-down caller message with authentic Crystal dialogue.
  - Supports 30+ Crystal phone contacts, arms rematch flags (`FLAG_JOHTO_ENGINE_*_READY_FOR_REMATCH`) and item gifts (`FLAG_JOHTO_ENGINE_*_HAS_*`). Smooth unfreeze and control restore upon hangup.

---

## 4. Overworld Mechanics, Navigation & Field Moves

- **Party Menu / Field Kit Cut for Johto**:
  - Cut usable directly from party menu / field kit in front of Johto cut trees (which are background sign events rather than object events). Implemented via `GetFacingJohtoCutTreeScript()` and `FieldCallback_CutJohtoTree()` in [src/fldeff_cut.c](src/fldeff_cut.c).
  - Cutting tall grass blocks in Johto tilesets swaps metatiles to plain mowed ground via `SetCutGrassMetatile()`.
- **Johto Fly Destinations & Dedicated Town Map Layout**:
  - Regional heal locations wired for all 11 outdoor Johto town map sections in `sMapHealLocations` in [src/region_map.c](src/region_map.c).
  - Dedicated Johto Town Map layout (`REGION_MAP_JOHTO`, `sRegionMapSections_Johto[15][28]`) with 45 authentic Crystal map sections on a 28x15 grid in [src/data/region_map/region_map_layout_johto.h](src/data/region_map/region_map_layout_johto.h).
  - Configured section coordinates, dimensions, and names in [src/data/region_map/region_map_sections.json](src/data/region_map/region_map_sections.json).
  - All 12 Johto fly destinations mapped to `FLAG_JOHTO_ENGINE_FLYPOINT_*` in `sFlyLocations` in [src/region_map.c](src/region_map.c).
  - Dynamic regional map detection and routing via `GetRegionMapType()` and `GetMapSecIdAt()` for `REGION_JOHTO`.
  - Out-of-bounds array read guards added to `FilterFlyDestination()` and `SetFlyDestination()`.
- **Daily Fruit Tree Regrowth**:
  - Regrowth cycle runs in `DoDailyEvents()` via `JohtoDailyResetFruitTrees()` across all 30 Johto and Kanto berry trees.
- **Pokémon Center Nurse Enhancements**:
  - Time-of-day greetings (morning, day, evening) and Pokérus detection.

---

## 5. Event Scripts, Sidequests & Gifts

- **Route 34 Day Care & Odd Egg Gift**:
  - Johto Day Care couple connected to the core engine day care.
  - Authentic Day Care Man Odd Egg gift (`GiveOddEgg` / `JohtoGiveOddEgg`) granting baby Pokémon (Pichu, Cleffa, Igglybuff, Smoochum, Magby, Elekid, Tyrogue) with authentic 14% shiny rate and Dizzy Punch, setting `FLAG_JOHTO_GOT_ODD_EGG`.
- **Bug-Catching Contest Gate Entry**:
  - National Park gate entry script (`GiveParkBalls` awarding 20 Sport Balls, contestant randomization) and early return prompt (`buffernumberstring`).
- **Goldenrod Pokémon Center GS Ball Trigger**:
  - GS Ball quest trigger event (`EVENT_CAN_GIVE_GS_BALL_TO_KURT`) converting the Japanese Crystal Pokémon Center event.
- **Kanto Yellow Gift Starters**:
  - Bulbasaur in Cerulean City House 1 from Melanie (`FLAG_GOT_YELLOW_BULBASAUR`).
  - Charmander on Route 24 from Damian (`FLAG_GOT_YELLOW_CHARMANDER`).
  - Squirtle in Vermilion City from Officer Jenny (`FLAG_GOT_YELLOW_SQUIRTLE`).
  - Includes authentic dialogue, badge requirements, party/PC deposit, and nickname prompts.
- **High-Level Script Bytecode & Specials (Wave 2 & Wave 3)**:
  - Dynamic multichoice menus (`dynmultipush` + `dynmultistack`): Dragon Shrine quiz & ExtremeSpeed Dratini gift, Goldenrod & Celadon Game Corner prize counters, vending machines, Move Tutor, Earl's Academy blackboard.
  - Dept. Store elevators (Goldenrod & Celadon, including B1F warehouse cycling).
  - Password doors: Mahogany Team Rocket Base B2F & B3F password locks, Player's House 2F poster.
  - Goldenrod Radio Tower 1F Lucky Number Show (`CheckLuckyNumberShowFlag`, `PrintTodaysLuckyNumber`, `CheckForLuckyNumberWinners`) and 2F Buena's Password Show (`VAR_BLUECARDBALANCE`).
  - Lake of Rage Fishing Guru (`CheckMagikarpLength`).
  - Viridian Trainer House Cal battle (`TrainerHouse`).
  - Goldenrod Dept. Store 5F Mystery Gift (`UnlockMysteryGift`).
  - Ruins of Alph puzzle chambers (`UnownPuzzle`, `HoOhChamber`, `OmanyteChamber`, `skyfall_top`).
  - Apricorn crafting with Kurt (`JohtoSelectApricornForKurt`).
  - Celebi Shrine encounter (`CelebiShrineEvent`, `CheckCaughtCelebi`).
  - Vermilion Snorlax / Poké Flute (`SnorlaxAwake`).
  - Power Plant Machine Part quest (`MACHINE_PART` / `ITEM_DEVON_PARTS`).
  - Goldenrod <-> Saffron Magnet Train (`MagnetTrain`).
  - Mania's Shuckie quest (`GiveShuckle` / `ReturnShuckie`).
  - Route 35/31 Kenya Spearow mail delivery quest (`checkpokemail` / `givepokemail`).
  - Move Deletion & Relearner.
  - Lance Hall of Fame entry and Mt. Silver Red credits sequence.
  - Tin Tower Rainbow Wing & Ho-Oh verification (`BeastsCheck` / `MonCheck`).

---

## 6. Asset & Tooling Conversions

- **Crystal Overworld Sprites**: All 118 Crystal `SPRITE_*` constants mapped to validated `OBJ_EVENT_GFX_*` counterparts (Gym Leaders, Grunts, Oak, Red, Blue, Kurt, legendary beasts, etc.).
- **Crystal Audio**: All 48 Crystal `MUSIC_*` constants mapped to FRLG/Emerald `MUS_RG_*` and `MUS_*` tracks in `MAP_MUSIC`.
- **Item & TM/HM Mappings**: All Gen 2 TMs and HMs mapped to Gen 3 TM/HM constants in `CMD_ITEMS` (0 Nugget fallbacks remaining).
- **Map Loading & Smoke Testing**: All 383 Johto maps load cleanly in emulator smoke tests (0 crash failures, 0 out-of-bounds mapsec errors).
- **Limit Integrity**: 1,324 total maps checked; 0 exceed 64 object events limit.

---

## 7. Universal 386 Pokémon Mood & Stone Refusal System (Yellow Expansion)

- **Universal Mood System (Gen 1-3, 386 Species)**:
  - Expands Pokémon Yellow's Pikachu mood reactions into an engine-wide system supporting all 386 species across Generations 1, 2, and 3.
  - Implemented in [src/mood.c](src/mood.c) and [include/mood.h](include/mood.h).
  - Evaluates 11 distinct emotional states: `MOOD_ECSTATIC` (>= 220 friendship), `MOOD_HAPPY` (160..219 friendship), `MOOD_CONTENT` (100..159 friendship), `MOOD_NORMAL` (50..99 friendship), `MOOD_DISTANT` (< 50 friendship), `MOOD_TIRED` (HP <= 25%), `MOOD_SICK` (poison/burn), `MOOD_PARALYZED` (paralysis/freeze), `MOOD_SLEEPING`, `MOOD_ANGRY` (refused stone / defeated), and `MOOD_SURPRISED` (weather anomaly / legendary presence).
  - Maps to 12 PMD SpriteCollab 40x40 emotion portraits (`PORTRAIT_EMOTION_*` matching `assets/SpriteCollab/portrait/`) and overworld follower emote bubbles (`FOLLOWER_EMOTION_*`).
  - Tailored species flavor text for Pikachu family, starter trios (Bulbasaur/Charmander/Squirtle, Chikorita/Cyndaquil/Totodile, Treecko/Torchic/Mudkip), and all 386 species.
  - Interactive "CHECK MOOD" menu item added to party menu (`MENU_CHECK_MOOD`) in [src/party_menu.c](src/party_menu.c), playing the Pokémon's cry and displaying its reaction description.
- **Authentic Stone Refusal & Starter Loyalty**:
  - Faithful to Pokémon Yellow: Pikachu refuses `ITEM_THUNDER_STONE`, shakes its head vigorously with sound effect `SE_FAILURE`, message `gText_PokemonRefusedStone`, and enters an angry/stubborn overworld follower state.
  - Rejection logic also protects Everstone holders and loyal starters (`FLAG_STARTER_LOYALTY_REFUSAL`, `FLAG_POKEMON_REFUSED_STONE`), preventing accidental item consumption.
  - Interacting with an overworld follower after stone refusal displays the angry emote bubble and refusal reaction.
- **Automated Verification**:
  - Comprehensive unit test suite in [test/confluence.c](test/confluence.c) covering Pikachu Thunder Stone rejection, Everstone rejection, non-stone valid evolution allowance, friendship mood progression, and status condition overrides.
- **Kanto Progression, Meridian Ferry & Yellow Expansion Playtest Verification**:
  - Verified 2-badge Meridian Transit access in [src/confluence.c](src/confluence.c): Slateport (Hoenn) <-> Vermilion (Kanto) <-> Olivine (Johto). Requires 2 badges before boarding is granted.
  - Verified Kanto progression and gift starters (Bulbasaur in Cerulean, Charmander on Route 24, Squirtle in Vermilion) across Viridian Forest, Mt. Moon, Cerulean City, Vermilion City, and Route 24.
  - Verified legacy tooling compliance (`poke-patch-townmap`, `poke-scan`), confirming saveblock memory integrity, Kanto flag/var bands, and zero missing script flags.

---

## 8. Wild Encounter Tables & Mechanics

- **Time-of-day Wild Encounters (Morning, Day, Night)**:
  - Enabled `OW_TIME_OF_DAY_ENCOUNTERS TRUE` in [include/config/overworld.h](include/config/overworld.h).
  - Normalized time-of-day handling in `GetTimeOfDayForEncounters` in [src/wild_encounter.c](src/wild_encounter.c) so Gen 2 evening correctly maps to night.
  - Generated 447 multi-time encounter headers across all 151 Johto maps in [src/data/wild_encounters.h](src/data/wild_encounters.h) matching authentic GBC Crystal morning, day, and night distributions.
  - Authentic 10-species Bug-Catching Contest wild encounter table for `MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST` (Caterpie, Weedle, Metapod, Kakuna, Venonat, Paras, Butterfree, Beedrill, Scyther, Pinsir).
- **Authentic Headbutt Tree System**:
  - Implemented in [src/headbutt.c](src/headbutt.c) and [include/headbutt.h](include/headbutt.h).
  - Authentic GBC Crystal encounter sets (CANYON, TOWN, ROUTE, KANTO, LAKE, FOREST, ROCK) with 50% empty, 35% common, 15% rare rolls, diurnal/nocturnal sleeping status generation (`CheckSleepingTreeMon`), and map lookup table.
  - Overworld interaction script `Johto_EventScript_HeadbuttTree` in [data/scripts/johto_common.inc](data/scripts/johto_common.inc) with `special JohtoCheckHeadbuttUser` (supporting party moves and Field Kit fallback), screen shakes, and wild battle dispatch.
- **Daily Pokémon Swarms**:
  - Implemented in [src/johto_swarms.c](src/johto_swarms.c) and [include/johto_swarms.h](include/johto_swarms.h).
  - Authentic Crystal swarm table: Dunsparce (Dark Cave), Yanma (Route 35), Snubbull (Route 38), Marill (Mt. Mortar), Remoraid (Route 44), Qwilfish (Route 32).
  - Daily swarm rotation via `Johto_DailyResetSwarm()` in [src/clock.c](src/clock.c) hooked into daily RTC events, with 50% encounter override in `TryGenerateWildMon`.
- **Roaming Legendary Beasts**:
  - Expanded roamer capacity to 3 (`ROAMER_COUNT 3`) in [include/constants/global.h](include/constants/global.h).
  - Built authentic Johto route network adjacency table `sJohtoRoamerLocations` in [src/roamer.c](src/roamer.c) from Crystal `roammon_maps.asm`.
  - Added `InitJohtoRoamMons` initializing Raikou and Entei at level 40, triggered upon breaking the seal in Burned Tower B1F (`BurnedTowerB1F_Johto_ReleaseTheBeasts`).
  - Adapted `RoamerMove` and `RoamerMoveToOtherLocationSet` to navigate across Johto map groups and preserve Hoenn roamer separation.
- **Fleeing Wild Pokémon Tables & Fast Ball Synergy**:
  - Implemented in [src/flee_mons.c](src/flee_mons.c) and [include/flee_mons.h](include/flee_mons.h).
  - Authentic flee percentages: Sometimes (10%: Magnemite, Grimer, Tangela, Mr. Mime, Eevee, Porygon, Dratini, Dragonair, Unown), Often (50%: Abra, Cubone, Articuno, Zapdos, Moltres, Quagsire, Delibird, Phanpy, Teddiursa), Always (100%: Raikou, Entei, Suicune).
  - AI fleeing action hooked into `OpponentHandleChooseMove` in [src/battle_controller_opponent.c](src/battle_controller_opponent.c).
  - 4x catch rate multiplier for Fast Ball (`BALL_FAST`) wired in [src/battle_script_commands.c](src/battle_script_commands.c) against all fleeing species.
- **Ruins of Alph Unown Unlock Stages**:
  - Implemented in [src/unown.c](src/unown.c) and [include/unown.h](include/unown.h).
  - Progressive letter unlock evaluating puzzle completion flags (`FLAG_JOHTO_SOLVED_*_PUZZLE`): Kabuto (A-K), Omanyte (L-R), Aerodactyl (S-W), Ho-Oh (X-Z), All 4 (rare ? and ! unlocked).
  - Exact Unown letter generation hooked into `CreateWildMon` in [src/wild_encounter.c](src/wild_encounter.c) via `GetMonPersonality`.

---

## 9. Engine Integration & Audio-Visual Fidelity

- **Overworld Day/Night System (DNS) Palettes for Johto**:
  - Extracted authentic GBC Crystal nighttime palette values from `games/gbc/pokecrystal/gfx/tilesets/bg_tiles.pal` across morn, day, and nite.
  - Implemented and mapped nighttime palettes (slots 15, 00, 01, 02, 03, 04, 05) via `(day + 9) % 16` for secondary tilesets `crystal_johto` and `crystal_johto_modern`.
  - Configured `.swapPalettes = SWAP_PAL(6) | SWAP_PAL(7) | SWAP_PAL(8) | SWAP_PAL(9) | SWAP_PAL(10) | SWAP_PAL(11) | SWAP_PAL(12)` in [src/data/tilesets/headers.h](src/data/tilesets/headers.h).
  - Window lighting animation masks (`10.pla`) added to blend illuminated windows at night.
- **Johto Regional Pokédex Ordering**:
  - Defined 251 species in authentic Crystal New Pokédex order (`FOREACH_SPECIES_IN_JOHTO_DEX_ORDER(F)` from Chikorita #001 to Celebi #251) and `enum JohtoDexOrder` in [include/constants/pokedex.h](include/constants/pokedex.h).
  - Created `sJohtoToNationalOrder[JOHTO_REGIONAL_DEX_COUNT]` lookup table in [src/pokemon.c](src/pokemon.c).
  - Implemented `NationalToJohtoOrder()`, `SpeciesToJohtoPokedexNum()`, `JohtoToNationalOrder()`, and `GetRegionalDexCount()` in [src/pokemon.c](src/pokemon.c) and [include/pokemon.h](include/pokemon.h).
  - Implemented `GetJohtoPokedexCount()` and `HasAllJohtoMons()` in [src/pokedex.c](src/pokedex.c) and [include/pokedex.h](include/pokedex.h).
  - Dynamic regional routing in `SpeciesToRegionalPokedexNum`, `RegionalToNationalOrder`, `GetRegionalPokedexCount`, `HasAllRegionalMons`, and `CreatePokedexList` based on `GetCurrentRegion() == REGION_JOHTO`.
- **Authentic Trainer Class DVs & Battle Audio**:
  - Mapped all 67 Crystal trainer classes to Gen 3 IV bitfields in `GetTrainerClassDVs()` in [src/trainer_util.c](src/trainer_util.c), applied automatically to trainer Pokémon with default IVs.
  - Wired authentic GBC legendary beast battle BGM `MUS_C_VS_LEGEND_BEAST` in `GetBattleBGM()` in [src/pokemon.c](src/pokemon.c) for Suicune, Raikou, and Entei.
  - Contextual regional battle music dispatch for Johto wild and trainer battles (`MUS_RG_VS_WILD`, `MUS_RG_VS_TRAINER`).
- **GBC Visual Polish & Scroll Arrows**:
  - Replaced prompt down-arrow graphics with authentic GBC Crystal down-arrow glyphs in [graphics/fonts/down_arrow.png](graphics/fonts/down_arrow.png) and [graphics/fonts/down_arrow_alt.png](graphics/fonts/down_arrow_alt.png).



