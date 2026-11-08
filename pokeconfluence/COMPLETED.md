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
- **Headbutt Tree Encounter Mechanics**:
  - Overworld interaction on headbutt tree metatiles (`MB_HEADBUTT_TREE`) via `GetInteractedMetatileScript()` in [src/field_control_avatar.c](src/field_control_avatar.c) triggering `Johto_EventScript_HeadbuttTree`.
  - Replicated authentic GBC Crystal coordinate tree scoring formula `((x + 1) * (y + 1) - 1) / 5 % 10` diffed against `playerTrainerId % 10` into Rare (80% encounter, rare table with Pineco/Heracross), Good (50% encounter), and Bad (10% encounter) tree tiers.
  - Parsed and integrated all 7 distinct Crystal Treemon tables in [src/headbutt.c](src/headbutt.c) (Route, Town, Canyon, Lake, Forest, Rock, Kanto).
  - Diurnal and nocturnal sleep mechanics: wild Pokémon encountered during their sleep cycle spawn with the `STATUS1_SLEEP` condition.
  - Fully compatible with both Pokémon knowing `MOVE_HEADBUTT` and the Confluence `ITEM_FIELD_KIT`.
  - Automated integration test `TEST("Confluence: Authentic Johto Headbutt Tree mechanics and encounter tables")` in [test/confluence.c](test/confluence.c).
- **Roaming Legendary Beasts (Raikou & Entei)**:
  - Authentic awakening in Burned Tower B1F (`InitJohtoRoamMons`): Raikou starting on Route 42 (`MAP_JOHTO_ROUTE_42`) and Entei starting on Route 37 (`MAP_JOHTO_ROUTE_37`) at level 40.
  - Authentic 16-route network from pokecrystal `roammon_maps.asm` configured in `sJohtoRoamerLocations` spanning Routes 29 through 46 in [src/roamer.c](src/roamer.c).
  - Dynamic route movement and jumping on map transitions via `RoamerMove()` and `RoamerMoveToOtherLocationSet()`.
  - Encounter integration in [src/wild_encounter.c](src/wild_encounter.c) with land-only condition (suppressed while surfing).
  - Immediate turn 1 fleeing AI (`AI_FLAG_ROAMING`) unless trapped by Mean Look or trapping abilities.
  - Authentic GBC Crystal Legendary Beast battle theme (`MUS_C_VS_LEGEND_BEAST`) wired in `GetBattleBGM()` for `BATTLE_TYPE_ROAMER` in [src/pokemon.c](src/pokemon.c).
  - Persistent HP and status condition tracking across encounters in `SaveBlock1.roamer` with deactivation upon faint or capture.
  - Pokédex Area screen accurately pinpoints current roaming route across Johto map sections in [src/pokedex_area_screen.c](src/pokedex_area_screen.c).
  - Automated integration test `TEST("Confluence: Authentic Johto Roaming Legendary Beasts (Raikou & Entei)")` in [test/confluence.c](test/confluence.c).
- **Friday Lapras & Day-of-Week Overworld Events**:
  - Friday Lapras spawns in `UnionCaveB2F_Johto` on water every Friday at level 20.
  - Weekly respawn mechanics: defeating or catching Lapras sets `FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS`; daily midnight reset in `DoDailyEvents()` in [src/clock.c](src/clock.c) clears the flag for the next Friday.
  - Complete 7 Weekday Siblings scheduling and scripts awarding type-boost held items:
    - Sunday: Sunny on Route 37 (`ITEM_MAGNET` / `FLAG_JOHTO_GOT_MAGNET_FROM_SUNNY`)
    - Monday: Monica on Route 40 (`ITEM_SHARP_BEAK` / `FLAG_JOHTO_GOT_SHARP_BEAK_FROM_MONICA`)
    - Tuesday: Tuscany on Route 29 (`ITEM_PINK_BOW` / `FLAG_JOHTO_GOT_PINK_BOW_FROM_TUSCANY`)
    - Wednesday: Wesley on Lake of Rage (`ITEM_BLACKBELT_I` / `FLAG_JOHTO_GOT_BLACKBELT_FROM_WESLEY`)
    - Thursday: Arthur on Route 36 (`ITEM_HARD_STONE` / `FLAG_JOHTO_GOT_HARD_STONE_FROM_ARTHUR`)
    - Friday: Frieda on Route 32 (`ITEM_POISON_BARB` / `FLAG_JOHTO_GOT_POISON_BARB_FROM_FRIEDA`)
    - Saturday: Santos on Blackthorn City (`ITEM_SPELL_TAG` / `FLAG_JOHTO_GOT_SPELL_TAG_FROM_SANTOS`)
  - Automated integration test `TEST("Confluence: Authentic Johto Day-of-Week events and Weekday Siblings")` in [test/confluence.c](test/confluence.c).
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

---

## 10. Multi-Region Fly Navigation & Pokédex Area Screen

- **Multi-Region Fly Navigation (`src/region_map.c`)**:
  - Full three-region navigation across Hoenn, Kanto, and Johto (`REGION_MAP_HOENN`, `REGION_MAP_KANTO`, `REGION_MAP_JOHTO`) using `L_BUTTON` and `R_BUTTON` when in Fly Map mode.
  - Dynamic decompression and loading of regional graphics, tilemaps, and 3-palette color banks into BG2 on VRAM during region cycling.
  - Parameterized destination icons via `CreateFlyDestIcons(regionMapType)` and dynamic sprite clearing via `ClearFlyDestIcons()`, only displaying visited fly points for the active region.
  - Interactive player avatar icon management: visible and positioned at the player's real coordinates when viewing their current region; hidden gracefully when viewing other regions.
  - Center cursor defaults upon entering a new region (Hoenn: 14, 13; Kanto: 5, 11; Johto: 22, 9).
  - Added `HEAL_LOCATION_JOHTO_LAKE_OF_RAGE` and completed all 12 Johto fly destination definitions in `GetMapsecType` (`FLAG_JOHTO_ENGINE_FLYPOINT_*`).
  - Cross-region fast travel execution cleanly verified via `SetFlyDestination` -> `sMapHealLocations`.
- **Johto Pokédex Area Screen Wild Encounters (`src/pokedex_area_screen.c`)**:
  - Wired Johto map groups (`gMapGroup_Johto1..4`) into `FindMapsWithMon` by detecting `GetRegionForSectionId(headerSectionId) == REGION_JOHTO`.
  - Dispatches outdoor routes, towns, and cities to `SetAreaHasMon` and caves/special landmarks (Mt. Mortar, Dark Cave, Whirl Islands, Silver Cave, etc.) to `SetSpecialMapHasMon`.
  - Seamlessly renders active glowing area tiles and flashing special markers on Johto layout `sRegionMapSections_Johto`.

---

## 11. Authentic Johto Held Items, Fermentation & Learnset Nuances

- **Authentic Johto Crystal Wild Held Items (`src/pokemon.c`)**:
  - Implemented lookup table `sJohtoWildMonHeldItems` across 61 authentic Crystal species: Chansey and Blissey (Lucky Egg), Grimer and Muk (Nugget), Misdreavus (Spell Tag), Sneasel (Quick Claw), Farfetch'd (Leek), Cubone and Marowak (Thick Club), Ho-Oh (Sacred Ash), Cleffa/Clefairy/Clefable (Leppa Berry / Moon Stone), Shuckle (Oran Berry), Shellder and Cloyster (Pearl / Big Pearl), Slowpoke family (King's Rock), Magnemite family and Steelix (Metal Coat), Dragonair/Dragonite/Dratini/Horsea/Seadra/Kingdra (Dragon Scale), Snorlax (Leftovers), Staryu/Starmie (Stardust / Star Piece), etc.
  - Hooked into `SetWildMonHeldItem()`: dynamically overrides wild held items when `GetCurrentRegion() == REGION_JOHTO` while retaining vanilla/expansion items in Hoenn and Kanto.
- **Authentic Shuckle Berry Juice Fermentation (`src/confluence.c`, `src/battle_setup.c`)**:
  - Implemented post-battle fermentation routine `Johto_ConvertShuckleBerryJuice()`.
  - Faithful to Pokémon Crystal: requires reaching Goldenrod City (`FLAG_JOHTO_ENGINE_REACHED_GOLDENROD`).
  - Evaluates after wild and scripted wild battles (`CB2_EndWildBattle` and `CB2_EndScriptedWildBattle`). If the player party contains a Shuckle holding an Oran Berry, it has a 1-in-16 (6.25%) chance per battle to ferment the berry into `ITEM_BERRY_JUICE`.
- **Authentic Dragon Shrine ExtremeSpeed Dratini Gift (`data/maps/DragonShrine_Johto/scripts.inc`)**:
  - In the Dragon's Den Dragon Shrine, after completing Clair's badge test, the Elder quizzes the player on their philosophy regarding Pokémon.
  - If the player answers all questions with honor and compassionate devotion (checked via `FLAG_JOHTO_ANSWERED_DRAGON_MASTER_QUIZ_WRONG` not being set), the gift Dratini is awarded with the authentic Crystal event moveset: `MOVE_WRAP`, `MOVE_THUNDER_WAVE`, `MOVE_TWISTER`, and the exclusive `MOVE_EXTREME_SPEED`.

---

## 12. Johto Overworld Scripts, Playtests & Flow Verification

- **Static Wild Battles (`loadwildmon`)**:
  - All 17 authentic Crystal static wild encounters verified: Route 36 Sudowoodo (Lv. 20), Lake of Rage Red Gyarados (Lv. 30), Union Cave B2F Lapras (Lv. 20), Ilex Forest Celebi (Lv. 30), Tin Tower Suicune (Lv. 40), Tin Tower Roof Ho-Oh (Lv. 60), Whirl Islands Lugia (Lv. 60), Vermilion City Snorlax (Lv. 50), and Team Rocket Base B2F generator Electrodes (3x Lv. 23).
  - All static battles execute valid `setwildbattle` macros, level bounds, and encounter flags.
- **Dynamic Block Changes (`changeblock` / `setmetatile`)**:
  - All 812 metatile modifications across 45 maps verified.
  - Every script modifying metatiles properly executes `special DrawWholeMapView` to redraw the VRAM tilemap buffer. Covers Ruins of Alph secret chambers (Flash, Escape Rope, Water Stone, Ho-Oh), Mahogany Team Rocket Base electric barriers and trap statues, and Ice Path boulder traps.
- **Hidden Items Across 61 Maps**:
  - All 85 hidden items verified across 61 Johto maps matching authentic Crystal positions.
  - All item constants mapped to valid Gen 3 items, all flags mapped to defined flags in [include/constants/johto_flags.h](include/constants/johto_flags.h), and all coordinates verified within map layout dimensions.
- **Strength Boulders & Rock Smash Breakable Rocks**:
  - All 24 Strength boulders (`OBJ_EVENT_GFX_PUSHABLE_BOULDER`, `EventScript_StrengthBoulder`) and 16 Rock Smash rocks (`OBJ_EVENT_GFX_BREAKABLE_ROCK`, `EventScript_RockSmash`) verified across Johto dungeons and routes.
  - Fully integrated with Field Kit and badge obedience (Plain Badge for Strength, Zephyr Badge for Rock Smash in Johto).
- **Elder Li's Flash Gift Sequence**:
  - Sprout Tower 3F Sage Li battle, defeat logic, `ITEM_HM_FLASH` award, `FLAG_JOHTO_GOT_HM05_FLASH`, and post-battle dialogue advance verified.
- **Route 32, Slowpoke Well, Kurt & Ilex Forest Farfetch'd**:
  - Route 32 Slowpoke Tail salesman refusal sequence.
  - Slowpoke Well Team Rocket defeat and Kurt's Lure Ball reward (`FLAG_JOHTO_KURT_GAVE_YOU_LURE_BALL`).
  - Ilex Forest charcoal apprentice Farfetch'd chase (positions 1-4), herding completion (`FLAG_JOHTO_HERDED_FARFETCHD`), and Cut HM reward (`FLAG_JOHTO_GOT_HM01_CUT`).
- **Togepi Hatching & Elm's Pokégear Call**:
  - Integrated Togepi egg hatching in [src/egg_hatch.c](src/egg_hatch.c) setting `FLAG_JOHTO_TOGEPI_HATCHED`.
  - Wired Elm's priority incoming Pokégear call in [src/johto_phone.c](src/johto_phone.c) (`sText_ElmTogepiHatchedCall`, `FLAG_JOHTO_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE`).
  - Elm in New Bark Town lab inspects Togepi and awards the Everstone (`FLAG_JOHTO_GOT_EVERSTONE_FROM_ELM`).
- **Per-Town Respawn in Johto Pokémon Centers**:
  - Verified all 11 Johto towns (New Bark, Cherrygrove, Violet, Azalea, Goldenrod, Ecruteak, Olivine, Cianwood, Mahogany, Blackthorn, Lake of Rage) have dedicated heal locations in [src/data/heal_locations.json](src/data/heal_locations.json) and are wired into `sMapHealLocations` in [src/region_map.c](src/region_map.c).
  - All 22 Johto Pokémon Center nurse scripts set `setrespawn HEAL_LOCATION_JOHTO_*`. Whiteout wakeup properly recovers in the respective center.
- **Fishing Encounter Tables Across 149 Maps**:
  - All 149 Johto fishing headers verified in [src/data/wild_encounters.h](src/data/wild_encounters.h), ensuring 50% encounter rates, authentic species distributions (Old Rod Magikarp/Krabby/Poliwag; Good Rod Corsola/Qwilfish/Remoraid; Super Rod Kingler/Gyarados/Dratini), and zero invalid `SPECIES_NONE` slots.
- **Automated Verification Harnesses**:
  - [scripts/audit_johto_scripts.py](scripts/audit_johto_scripts.py): 18/18 static integrity checks passed.
  - [mgba-agent/tests/test_johto_overworld_flows.py](mgba-agent/tests/test_johto_overworld_flows.py): 9 comprehensive automated playtest flow suites (17/17 tests passed).

---

## 13. Embedded Emulator, Tooling & Debug Adapter

- **Real Cartridge RTC Time Sync & Weekday Setting**:
  - Implemented `JohtoSyncRtcTime` and `JohtoSetWeekday` in [src/johto_scripts.c](src/johto_scripts.c) and registered them in [data/specials.inc](data/specials.inc).
  - Authentic Mom Pokégear sequence in [data/maps/PlayersHouse1F_Johto/scripts.inc](data/maps/PlayersHouse1F_Johto/scripts.inc): detects cartridge RTC hardware via `RtcGetErrorStatus()`. If healthy RTC is present (mGBA or RTC-capable flash cartridge), clock automatically syncs; if RTC is uncalibrated or dry, dynamically displays Sunday-Saturday multichoice menu (`dynmultipush` / `dynmultistack`) and adjusts `localTimeOffset` days so that `GetDayOfWeek()` accurately yields the selected day.
  - Bridges with all 36 weekday-dependent scripts across Johto (Bug-Catching Contest, Friday Lapras, day-of-the-week siblings Arthur/Tuscany/Santos, S.S. Aqua sailing days, Mt. Moon Clefairy dance).
- **Native-mGBA Savestate Importer**:
  - Developed [tools/poke-migrator-pro/bin/poke-import-mgba-state](../tools/poke-migrator-pro/bin/poke-import-mgba-state): automatically parses native mGBA PNG savestates (`.ss0`..`.ss9`, `.ssA`..`.ssZ`), extracts and decompresses the `gbAs` zlib memory chunk (0x61000 bytes: R0-R15/CPSR registers, Palette RAM, VRAM, OAM, IWRAM, EWRAM), and either generates gba-kit compatible `.ss1` savestates or injects memory live into the TCP bridge.
  - Transparently integrated PNG savestate decompression into `loadState()` in [tools/pokeemerald-ai-bridge/src/emu/session.ts](../tools/pokeemerald-ai-bridge/src/emu/session.ts).
- **VS Code Extension Views, Dashboard & Debug Adapter**:
  - Contributed debugger configuration `"pokeemerald-debug"` to [tools/pokeemerald-ai-bridge/package.json](../tools/pokeemerald-ai-bridge/package.json) with launch and attach configurations for ROM debugging and bridge connectivity.
  - Registered `PokeemeraldDebugAdapterFactory` (`vscode.DebugAdapterServer`) in [tools/pokeemerald-ai-bridge/src/extension.ts](../tools/pokeemerald-ai-bridge/src/extension.ts).
  - Verified Game, Party, Battle, Opponent AI trees, and Dashboard webview panels with full node test suite pass (11/11 tests).
- **Automated CI/CD Pipeline & Regression Replay**:
  - Built comprehensive automation script [scripts/ci_rebuild_and_replay.sh](scripts/ci_rebuild_and_replay.sh) running the full verification pipeline:
    1. Multi-threaded ROM compilation (`make -C pokeconfluence -j$(nproc)`).
    2. Headless C unit tests ([scripts/test.sh](scripts/test.sh)).
    3. Structural script auditor ([scripts/audit_johto_scripts.py](scripts/audit_johto_scripts.py)).
    4. Limits & saveblock auditor ([.agents/scripts/check_limits.py](../../.agents/scripts/check_limits.py)).
    5. Headless emulator pytest test suite (`mgba-agent/tests`).
    6. Automated opening flow replay with headless agent (`mgba-agent/johto_regression.py`).
  - Added continuous integration workflow [.github/workflows/confluence_ci.yml](../../.github/workflows/confluence_ci.yml).

---

## 14. Battle Tower, Mobile & Link Stubs

- **All 21 Crystal Link, Mobile & Battle Tower Stubs Resolved**:
  - Replaced all legacy `@ TODO unsupported:` stubs across all 383 Johto maps, achieving 0 remaining stubs across the entire repository.
- **Johto Pokémon Center 2F Link Facility**:
  - `JohtoCheckMysteryGift` and `JohtoGetMysteryGiftItem`: Cleanly implemented in [src/johto_scripts.c](src/johto_scripts.c) and registered in [data/specials.inc](data/specials.inc). The Delivery Officer NPC in [Pokecenter2F_Johto](data/maps/Pokecenter2F_Johto/scripts.inc) awards event items with bag overflow checks.
  - Link Record Display Sign: Wired directly to native GBA `ShowLinkBattleRecords` and `RemoveRecordsWindow` specials.
  - Cable Trade, Battle, and Time Capsule Receptionists: Removed unsupported GBC Mobile Adapter GB calls, handling offline Link Cable connection checks and prompt messages (`Pokecenter2F_Johto_Text_FriendNotReady`).
- **Waiting Rooms (Colosseum, Trade Center, Time Capsule)**:
  - Console sign events in [data/maps/Colosseum_Johto/scripts.inc](data/maps/Colosseum_Johto/scripts.inc), [data/maps/TradeCenter_Johto/scripts.inc](data/maps/TradeCenter_Johto/scripts.inc), and [data/maps/TimeCapsule_Johto/scripts.inc](data/maps/TimeCapsule_Johto/scripts.inc) cleanly inform the player if a Game Link cable is not connected.
  - Callbacks properly hide offline opponent sprites (`FLAG_TEMP_11`, `FLAG_TEMP_12`) and support friend interactions.
- **Johto Battle Tower Progression**:
  - Lobby scene check in [data/maps/BattleTower1F_Johto/scripts.inc](data/maps/BattleTower1F_Johto/scripts.inc) properly arms and steps without freezing.
  - Authentic Receptionist interaction with `MULTI_CHALLENGEINFO` multichoice menu (Challenge, Info, Exit).
  - `JohtoCheckBattleTowerEligibility`: Verifies at least 3 eligible non-egg battle-ready Pokémon in the player's active party.
  - Elevator sequence in [data/maps/BattleTowerElevator_Johto/scripts.inc](data/maps/BattleTowerElevator_Johto/scripts.inc) with authentic elevator audio (`SE_ELEVATOR`) and warp transitions.
  - Hallway navigation in [data/maps/BattleTowerHallway_Johto/scripts.inc](data/maps/BattleTowerHallway_Johto/scripts.inc) guiding the player to the Battle Room doors.
  - Battle Room entrance sequence in [data/maps/BattleTowerBattleRoom_Johto/scripts.inc](data/maps/BattleTowerBattleRoom_Johto/scripts.inc) with receptionist welcoming and return warp.
- **Verification**:
  - [scripts/audit_johto_scripts.py](scripts/audit_johto_scripts.py): Verified 0 stubs remaining across all maps (18/18 checks pass).
  - [.agents/scripts/check_limits.py](../../.agents/scripts/check_limits.py): Verified 0 remaining stubs.

---

## 15. Configuration Studio GUI (`poke-config-gui`)

- **Interactive Configuration Editor for All 23 Headers in `include/config/`**:
  - Full support for `ai.h`, `battle.h`, `caps.h`, `contest.h`, `debug.h`, `dexnav.h`, `fishing.h`, `follower_npc.h`, `general.h`, `item.h`, `map_preview_screen.h`, `name_box.h`, `overworld.h`, `pokedex_plus_hgss.h`, `pokemon.h`, `pokerus.h`, `quickstart.h`, `save.h`, `species_enabled.h`, `summary_screen.h`, `test.h`, `text.h`, and `wild_encounter.h` (2,040+ game options).
- **Embedded Web GUI & Desktop GUI**:
  - **Modern Web Application**: Single-page dark mode UI on zero-dependency Python server with live instant search, category filters, type filters (Booleans, Generations, Enums, Numbers, Notices), and real-time pending change tracking.
  - **Native Desktop GUI**: Tkinter GUI (`poke-config-gui --desktop`) for native X11/Wayland window workflows.
  - **CLI Launcher**: `poke-config-gui` symlinked in `~/.local/bin/poke-config-gui` and `tools/poke-migrator-pro/bin/poke-config-gui`.
- **Comprehensive Setting Explanations & Context**:
  - Extracted descriptions for every single option detailing *what everything does and how it works*.
  - Historical notes on generational differences (`In Gen 4+...`, `In Gen 6+...`, `In Gen 9+...`).
  - Warning badges for `SAVE-BREAKING`, `WIP / Experimental`, and `Confluence Custom` options.
- **Safety, Non-Destructive Editing & Build Integration**:
  - **Live Unified Diff**: Review side-by-side / unified diff before writing changes to disk.
  - **Automated Snapshots**: Creates timestamped backups in `include/config/.backups/` on every save, with one-click snapshot restore.
  - **Precise C Formatter**: Preserves C indentation, spacing, comments, `#ifndef` guards, and `// POKE-CONFLUENCE` tags.
  - **Direct ROM Compilation**: Integrated `make -C pokeconfluence -j$(nproc)` button with streaming terminal build logs.

---

## 16. Authentic GBC Crystal Audio, Sprites & Visual Polish

- **Authentic GBC Crystal Overworld & Battle Soundtrack (`poke-crystal-audio`)**:
  - Implemented end-to-end Python conversion pipeline `tools/poke-migrator-pro/bin/poke-crystal-audio` that parses authentic GBC Pokécrystal sound bytecode (`tempo`, `volume`, `note_type`, `octave`, `note`, `rest`, `drum_note`, `sound_call`, `sound_ret`, `sound_loop`, `sound_jump`).
  - Converts GBC tracks to Standard Format 1 MIDI (division 48 ticks/quarter) with Square 1 (Ch 1), Square 2 (Ch 2), Wave Bass (Ch 3), and Noise Percussion (Ch 10).
  - Compiles all 25 tracks with `mid2agb` into native M4A sound engine sequences in [sound/songs/midi/](sound/songs/midi/).
  - Registered in [sound/songs/midi/midi.cfg](sound/songs/midi/midi.cfg), [sound/song_table.inc](sound/song_table.inc), and [include/constants/songs.h](include/constants/songs.h) (IDs 610..634).
  - 33 Johto map headers bound to authentic GBC audio tracks:
    - New Bark Town: `MUS_C_NEW_BARK`
    - Cherrygrove City: `MUS_C_CHERRYGROVE`
    - Violet City: `MUS_C_VIOLET`
    - Azalea Town: `MUS_C_AZALEA`
    - Goldenrod City: `MUS_C_GOLDENROD`
    - Ecruteak City: `MUS_C_ECRUTEAK`
    - Route 29: `MUS_C_ROUTE29`
    - Routes 30, 31, 32, 33: `MUS_C_ROUTE30`
    - Routes 34, 35, 36: `MUS_C_ROUTE36`
    - Routes 37, 38, 39: `MUS_C_ROUTE37`
    - Prof. Elm's Lab: `MUS_C_ELM_LAB`
    - Sprout Tower: `MUS_C_SPROUT_TOWER`
    - Dark Cave: `MUS_C_DARK_CAVE`
    - Union Cave: `MUS_C_UNION_CAVE`
    - Lake of Rage: `MUS_C_LAKE_OF_RAGE`
    - National Park: `MUS_C_NATIONAL_PARK`
    - Dragon's Den: `MUS_C_DRAGONS_DEN`
    - Burned Tower: `MUS_C_BURNED_TOWER`
    - Tin Tower: `MUS_C_TIN_TOWER`
    - Ruins of Alph: `MUS_C_RUINS_OF_ALPH`
  - Dynamic Region Battle BGM: In [src/pokemon.c](src/pokemon.c), Johto encounters automatically play authentic GBC battle themes:
    - Wild encounters: `MUS_C_VS_WILD_JOHTO`
    - Trainer encounters: `MUS_C_VS_TRAINER_JOHTO`
    - Gym Leaders & Elite Four: `MUS_C_VS_GYM_JOHTO`
    - Champion Lance: `MUS_C_VS_CHAMPION_LANCE`
    - Rival Silver: `MUS_C_VS_RIVAL_SILVER`
    - Legendary Beasts (Suicune / Raikou / Entei): `MUS_C_VS_LEGEND_BEAST`
- **Authentic GBC Crystal Trainer Battle Pictures (`poke-crystal-graphics`)**:
  - Implemented automated graphics conversion pipeline `tools/poke-migrator-pro/bin/poke-crystal-graphics`.
  - Converted 16 authentic Crystal front pictures into centered 64x64 4bpp indexed PNGs with flood-filled transparent background (pixel 0) and compiled `.gbapal` in [graphics/trainers/front_pics/](graphics/trainers/front_pics/):
    - Falkner, Bugsy, Whitney, Morty, Chuck, Jasmine, Pryce, Clair, Will, Karen, Champion Lance, Silver, Sage Li, Kimono Girl, Officer Jenny, Cal.
  - Registered in [include/constants/trainers.h](include/constants/trainers.h), [src/data/graphics/trainers.h](src/data/graphics/trainers.h), and [src/data/trainer_graphics.h](src/data/trainer_graphics.h).
  - Assigned authentic pics in [src/data/trainers_johto.party](src/data/trainers_johto.party) and compiled via `trainerproc` into [src/data/trainers_johto.h](src/data/trainers_johto.h).
- **Authentic Player Back Pictures (Chris & Kris)**:
  - Extracted authentic 48x48 back pictures for Chris (Ethan) and Kris from Pokécrystal.
  - Converted into 64x64 4bpp indexed PNGs with authentic palettes in [graphics/trainers/back_pics/](graphics/trainers/back_pics/) (`chris.png`, `kris.png`, `.gbapal`).
  - Registered `TRAINER_PIC_CHRIS` and `TRAINER_PIC_KRIS` in [src/data/graphics/trainers.h](src/data/graphics/trainers.h).
  - Dynamically selected in [src/battle_controller_player.c](src/battle_controller_player.c) (`PlayerGetTrainerBackPicId`) whenever `GetCurrentRegion() == REGION_JOHTO`.
- **Authentic GBC Overworld Sprites**:
  - Converted 13 custom GBC overworld sprites (`c_falkner.png`, `c_bugsy.png`, `c_whitney.png`, `c_morty.png`, `c_chuck.png`, `c_jasmine.png`, `c_pryce.png`, `c_clair.png`, `c_elder_li.png`, `c_kimono_girl.png`, `c_officer.png`, `c_kurt.png`, `c_prof_elm.png`) into standard GBA 144x32 4bpp 9-frame sprite sheets in [graphics/object_events/pics/people/](graphics/object_events/pics/people/).
- **Verification**:
  - Headless C test runner: 21/21 tests passed (`bash pokeconfluence/scripts/test.sh`).
  - Script & overworld auditor: 18/18 checks passed (`python3 pokeconfluence/scripts/audit_johto_scripts.py`).
  - Engine limit auditor: 0 stubs, 0 map overflow (`python3 .agents/scripts/check_limits.py`).
  - Complete ROM compilation: Clean build with 0 errors (`make -C pokeconfluence -j$(nproc)`).

---

## 8. Authentic Johto Time-of-Day Wild Encounter System

- **Crystal-Accurate Morning, Day, and Night Encounters**:
  - Extracted and verified all 61 grass and outdoor encounter tables from `games/gbc/pokecrystal/data/wild/johto_grass.asm`.
  - Configured discrete `[TIME_MORNING]`, `[TIME_DAY]`, and `[TIME_NIGHT]` wild encounter tables across all 149 Johto maps in [src/data/wild_encounters.json](src/data/wild_encounters.json) and compiled into [src/data/wild_encounters.h](src/data/wild_encounters.h).
  - Authentic species distribution verified across time of day:
    - Route 29: Hoothoot and Rattata appear at Night; Pidgey, Sentret, and Hoppip appear in Morning and Day.
    - Route 30 & 31: Morning features Ledyba and Caterpie; Day features Pidgey and Caterpie; Night features Spinarak, Hoothoot, and Poliwag.
    - Route 34: Morning/Day features Snubbull and Rattata; Night features Drowzee and Rattata.
    - Route 35: Morning/Day features Snubbull and Pidgey; Night features Drowzee and Hoothoot.
    - Route 36 & 37: Morning features Ledyba and Growlithe; Day features Pidgey and Growlithe; Night features Spinarak and Stantler.
- **Engine RTC Time Integration**:
  - `OW_TIME_OF_DAY_ENCOUNTERS = TRUE` enabled in [include/config/overworld.h](include/config/overworld.h).
  - `GetTimeOfDayForEncounters()` in [src/wild_encounter.c](src/wild_encounter.c) dynamically samples RTC time and indexes the corresponding time-of-day encounter block with fallback support (`OW_TIME_OF_DAY_DISABLE_FALLBACK = FALSE`).
- **Automated Verification**:
  - Added dedicated C unit test in [test/confluence.c](test/confluence.c) (`"Confluence: Johto authentic morning, day, and night wild encounter tables"`).
  - All 21/21 headless C unit tests pass (`bash pokeconfluence/scripts/test.sh`).
  - All 18/18 script integrity audits pass (`python3 pokeconfluence/scripts/audit_johto_scripts.py`).
  - Limits check clean at 253/253 `MAPSEC_*` (`python3 .agents/scripts/check_limits.py`).
  - Full ROM compilation clean (`make -C pokeconfluence -j$(nproc)`).

---

## 17. Authentic Johto Secondary Mechanics & Encounters

- **Headbutt Tree Overworld Mechanics**:
  - Implemented authentic GBC Crystal tree coordinate scoring algorithm in `src/johto_scripts.c`:
    - Coordinates combined with Trainer ID compute high/low encounter tree status.
    - Low-encounter trees produce 50% nothing, 35% tier 1, 15% tier 2 encounters.
    - High-encounter trees produce 10% nothing, 50% tier 1, 15% tier 2, 25% tier 3 rare encounters (Pineco, Heracross, Aipom).
  - All 7 authentic Crystal Headbutt encounter tables ported (`TREE_CANYON`, `TREE_CITY`, `TREE_FOREST`, `TREE_ILEX`, `TREE_LAKE`, `TREE_MOUNTAIN`, `TREE_ROUTE`).
  - Diurnal/nocturnal sleep status logic: wild Pokémon caught napping fall asleep at the start of battle based on their sleep cycle.
  - Overworld field interaction hooked seamlessly into tree metatiles via `MB_HEADBUTT_TREE` in `src/field_control_avatar.c` and Field Kit integration.

- **Roaming Legendary Beasts (Raikou & Entei)**:
  - 16-route authentic Johto roaming route network defined in `sJohtoRoamerLocations` in `src/roamer.c`.
  - Canonical Crystal starting routes configured: Raikou on Route 42, Entei on Route 37 upon awakening in Burned Tower.
  - Overworld battle interceptor checks player's current route and land encounter status (water roam encounters suppressed).
  - Authentic roamer battle AI (`AI_FLAG_ROAMING`) causes legendary beasts to attempt to flee immediately on turn 1.
  - Authentic battle theme `MUS_C_VS_LEGEND_BEAST` wired into `GetBattleBGM` in `src/pokemon.c`.
  - Persistent tracking: remaining HP, status conditions, and Pokédex area location map tracking.

- **Day-of-Week Overworld Events & Weekday Siblings**:
  - Friday Lapras in `UnionCaveB2F_Johto`: spawns on water every Friday at level 20, weekly respawn via `FLAG_JOHTO_ENGINE_UNION_CAVE_LAPRAS` reset at midnight in `DoDailyEvents()`.
  - All 7 Weekday Siblings fully implemented with authentic Crystal schedules, dialogue, and type-boosting held items:
    - Sunday: Sunny on Route 37 (`ITEM_MAGNET`)
    - Monday: Monica on Route 40 (`ITEM_SHARP_BEAK`)
    - Tuesday: Tuscany on Route 29 (`ITEM_PINK_BOW`)
    - Wednesday: Wesley on Lake of Rage (`ITEM_BLACKBELT_I`)
    - Thursday: Arthur on Route 36 (`ITEM_HARD_STONE`)
    - Friday: Frieda on Route 32 (`ITEM_POISON_BARB`)
    - Saturday: Santos on Blackthorn City (`ITEM_SPELL_TAG`)
  - Map transition callbacks dynamically evaluate RTC weekday via `special JohtoGetWeekday`.

- **Lake of Rage Shiny Red Gyarados Climax**:
  - Authentic water sprite interaction triggers scripted level 30 forced-shiny `SPECIES_GYARADOS` encounter using `special JohtoSetWildMonShiny`.
  - Battle outcomes preserve encounter if ran/lost; catching or defeating Gyarados permanently clears water sprite, awards `ITEM_RED_SCALE`, and reveals Lance on the shore.
  - Authentic Route 30 trade with Mr. Pokémon exchanges `ITEM_RED_SCALE` for `ITEM_EXP_SHARE`.
  - C unit test `TEST("Confluence: Authentic Lake of Rage Shiny Red Gyarados and Red Scale trade")` verified in `test/confluence.c` (25/25 passed).

- **National Park Bug-Catching Contest Minigame**:
  - Gate entries at Route 35 and Route 36 checking calendar weekday (Tuesday, Thursday, Saturday) and single-mon party rules.
  - 20 Park Balls (`ITEM_SPORT_BALL`) delivered and 5 random AI contestants randomized to appear in the park and gate lobby.
  - 20-minute (500 steps) countdown timer tracked across `field_control_avatar.c` via `JohtoBugContestTakeStep()` with authentic audio cue (`SE_DING_DONG`) on out-of-balls and time's up.
  - Officer dialogue dynamically converts steps to minutes remaining via `JohtoGetBugContestRemainingMinutes()`.
  - Authentic Crystal judging algorithm in `JohtoCalculateContestScore()` and `JohtoBugContestJudge()` evaluating Species base stats (Scyther/Pinsir vs Caterpie/Weedle), remaining HP / 8, Max HP * 4, and IV totals against 10 authentic AI contestants (Don, Ed, Nick, William, Benny, Barry, Cindy, Josh, Samuel, Kipp).
  - Awarding 1st Prize (`ITEM_SUN_STONE`), 2nd Prize (`ITEM_EVERSTONE`), 3rd Prize (`ITEM_SITRUS_BERRY`), and consolation prize (`ITEM_ORAN_BERRY`), with full-bag item holding logic by the gate officer.
  - Full cleanup (`JohtoBugContestCleanup()`): retrieves remaining Park Balls, returns held party Pokémon, sets `FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST`, and resets daily at midnight.
  - C unit test `TEST("Confluence: Authentic National Park Bug-Catching Contest Minigame")` verified in `test/confluence.c` (26/26 passed).

- **Ruins of Alph Secret Riddle Chambers**:
  - Implemented authentic Crystal puzzle riddle wall checks across all four chambers:
    - Kabuto Chamber (`RuinsOfAlphKabutoChamber_Johto`): checks for `ITEM_ESCAPE_ROPE` in bag to open the back wall (`FLAG_JOHTO_WALL_OPENED_IN_KABUTO_CHAMBER`).
    - Aerodactyl Chamber (`RuinsOfAlphAerodactylChamber_Johto`): checks for `ITEM_FIELD_KIT`, `ITEM_HM05`, or a party member knowing `FIELD_MOVE_FLASH` to open the back wall (`FLAG_JOHTO_WALL_OPENED_IN_AERODACTYL_CHAMBER`).
    - Omanyte Chamber (`RuinsOfAlphOmanyteChamber_Johto`): checks for `ITEM_WATER_STONE` in bag to open the back wall (`FLAG_JOHTO_WALL_OPENED_IN_OMANYTE_CHAMBER`).
    - Ho-Oh Chamber (`RuinsOfAlphHoOhChamber_Johto`): checks for `SPECIES_HO_OH` in player's party to open the back wall (`FLAG_JOHTO_WALL_OPENED_IN_HO_OH_CHAMBER`).
  - C unit test `TEST("Confluence: Ruins of Alph secret chambers open with proper riddle triggers")` verified in `test/confluence.c` (27/27 passed).

- **Pokégear Radio Card & Audio Broadcasts**:
  - Interactive radio station selection sub-menu in `src/johto_radio.c` and `data/scripts/johto_common.inc`.
  - Tuner supports 6 stations: Pokémon Talk (Prof. Oak & Mary with daily Route swarms), Pokémon Music (Pokémon March encounter boost and Pokémon Lullaby encounter reduction), Buena's Password evening broadcast, Ruins of Alph Unown radio signal (boosting Unown capture rate), Pokédex Show, and Pokéflute broadcast waking Snorlax.
  - C unit test `TEST("Confluence: Pokégear Radio Card broadcasts, encounter modifiers, and Buena's Password generation")` verified in `test/confluence.c` (28/28 passed).

- **Interactive Kurt's Apricorn Crafting**:
  - Kurt event script in `KurtsHouse_Johto/scripts.inc` features dynamic multichoice menu filtered to player's Bag inventory (`JohtoSelectApricornForKurt`).
  - Batch crafting: allows crafting 1 or all held Apricorns of the chosen color at once (`JohtoGetApricornQuantity`, `JohtoGiveKurtApricorns`).
  - Overnight wait condition: sets `FLAG_JOHTO_ENGINE_KURT_MAKING_BALLS` and `VAR_JOHTO_KURT_APRICORN_COUNT`. Cleared daily at midnight RTC in `DoDailyEvents()`. Kurt delivers batch balls with fanfare and dialogue (`JohtoDeliverKurtBalls`).
  - Supports all 7 Apricorn items (`ITEM_RED_APRICORN` through `ITEM_PNK_APRICORN`) and custom balls (`ITEM_LEVEL_BALL`, `ITEM_LURE_BALL`, `ITEM_MOON_BALL`, `ITEM_FRIEND_BALL`, `ITEM_FAST_BALL`, `ITEM_HEAVY_BALL`, `ITEM_LOVE_BALL`).
  - C unit test `TEST("Confluence: Authentic Johto Kurt Apricorn Crafting and Batch Ball Delivery")` verified in `test/confluence.c` (30/30 passed).

- **Unown Pokédex Form Viewer (Unown Dex)**:
  - Ruins of Alph scientist event script checks caught Unown form count via `special JohtoGetUnownCaughtCount` and unlocks `FLAG_JOHTO_ENGINE_UNOWN_DEX` upon catching 3+ forms.
  - Dedicated Pokédex Form Viewer sub-screen: when viewing Unown in the Pokédex with `FLAG_JOHTO_ENGINE_UNOWN_DEX` set and at least 1 Unown caught, pressing `SELECT` toggles the interactive Unown Dex mode with D-pad Left/Right navigation, sprite loading, and return keybindings (`Task_HandleUnownDexInput`, `Pokedex_DrawUnownDexScreen`).
  - Full bitfield tracking across all 28 forms (`VAR_JOHTO_UNOWN_CAUGHT_LOWER`, `VAR_JOHTO_UNOWN_CAUGHT_UPPER`), caught count popup, and all 28 authentic GBC Crystal ancient words (ANGRY, BEAR, CHASE, DIRECT, ENGAGE, FIND, GIVE, HELP, INCREASE, JOIN, KEEP, LAUGH, MAKE, NUZZLE, OBSERVE, PERFORM, QUICKEN, REASSURE, SEARCH, TELL, UNDO, VANISH, WANT, XXXXX, YIELD, ZOOM, !!!!, ????).
  - Unlocked dialogue for Ruins of Alph scientists, computer, and printer when catching 26+ Unown forms.
  - C unit test `TEST("Confluence: Authentic Johto Unown Pokédex Form Viewer and Word Catalog")` verified in `test/confluence.c` (31/31 passed).

- **Goldenrod Game Corner Card Flip Minigame**:
  - Implemented authentic Card Flip minigame engine in `src/card_flip.c` and `include/card_flip.h` faithfully recreating GBC Crystal's `card_flip.asm`.
  - 24-card deck comprising 4 Pokémon suits (Pikachu, Jigglypuff, Poliwag, Oddish) and 6 numeric ranks (1 to 6).
  - 5 authentic betting options and payout ratios: Single Card (24x, 72 coins), Single Rank (6x, 18 coins), Single Suit (4x, 12 coins), Rank Pair (3x, 9 coins), and Suit Pair (2x, 6 coins).
  - Authentic 12-round deal loop dealing 2 face-down cards per deal, Card 1 vs Card 2 choice, discard pile tracking, and automatic reshuffling once the 24 cards are exhausted.
  - Interactive table scripts for Goldenrod Game Corner and Celadon Game Corner with live coin box, dynamic multichoice menus, and authentic Crystal sound effects (`SE_RG_CARD_FLIP`, `SE_RG_CARD_FLIPPING`, `SE_RG_CARD_OPEN`, `SE_SHOP`, `SE_BOO`).
  - C unit test `TEST("Confluence: Authentic Goldenrod Game Corner Card Flip Minigame and Betting Engine")` verified in `test/confluence.c` (32/32 passed).

- **Buena's Password & Blue Card Point Exchange**:
  - Implemented authentic Buena's Password quiz and Blue Card point counter in `src/johto_radio.c` and `include/johto_radio.h` faithfully recreating GBC Crystal's `buena.asm` and `data/items/buena_prizes.asm`.
  - Evening broadcast hours check (18:00 to 23:59) synchronized with local RTC time via `special JohtoCheckBuenaTime`.
  - Daily password quiz featuring 3 dynamic choices via `special JohtoGetBuenaPasswordChoices` and `special JohtoCheckBuenaAnswer`, awarding 1 point to `VAR_JOHTO_BLUE_CARD_BALANCE` (capped at 30 points) and locking with `FLAG_JOHTO_ENGINE_BUENA_POINT_TODAY` which automatically resets at midnight RTC in `DoDailyEvents()`.
  - Goldenrod Radio Tower studio lobby kiosk script with live Blue Card delivery (`ITEM_BLUE_CARD`), password quiz, directory, and authentic prize exchange receptionist.
  - Full redemption menu supporting all 9 authentic Crystal prizes: Ultra Ball (2 pts), Full Restore (2 pts), Nugget (3 pts), Rare Candy (3 pts), Protein (5 pts), Iron (5 pts), Carbos (5 pts), Calcium (5 pts), and HP Up (5 pts) via `special JohtoRedeemBuenaPrize`.
  - C unit test `TEST("Confluence: Authentic Johto Buena's Password and Blue Card Point Exchange")` verified in `test/confluence.c` (33/33 passed).

- **Johto Battle Tower 7-Trainer Ladder & Level Brackets**:
  - Implemented authentic Crystal Battle Tower ladder subsystem in `src/johto_battle_tower.c` and `include/johto_battle_tower.h` faithfully recreating GBC Crystal's `battle_tower.asm` and `data/battle_tower/`.
  - Level bracket selection: dynamic multichoice menu (`dynmultipush` / `dynmultistack`) offering Level 10, 20, 30, 40, 50, 60, 70, 80, 90, and 100 challenge rooms (`VAR_JOHTO_BATTLE_TOWER_LEVEL`).
  - Full party eligibility verification: enforces 3 battle-ready Pokémon, Level restriction (no mon > room level), Species Clause (no duplicate species), Item Clause (no duplicate held items), and Egg restriction with informative error messages.
  - 7-trainer battle gauntlet in `BattleTowerBattleRoom_Johto`: authentic Crystal trainer generation with dynamic overworld sprite switching (`VAR_OBJ_GFX_ID_0`).
  - Scaled 3-Pokémon enemy teams generated from authentic Crystal species pool at exact room level, scaled IVs by round (12, 18, 24, 31), authentic held items, full stat calculation, and zero EXP gain (`BATTLE_TYPE_BATTLE_TOWER`).
  - Inter-round party healing, continue/cancel prompts, defeat and cancel escape handling returning safely to 1F lobby.
  - Victory rewards: defeating all 7 consecutive opponents awards 5 random stat vitamins (HP Up, Protein, Iron, Carbos, Calcium) with fanfare, win counter increment (`VAR_JOHTO_BATTLE_TOWER_WINS`), and challenge flag reset.
  - C unit test `TEST("Confluence: Authentic Johto Battle Tower 7-Trainer Ladder and Level Brackets")` verified in `test/confluence.c` (34/34 passed).

- **Fame Checker Subsystem Restoration & Kanto VIP Lore Journal**:
  - Restored and updated [src/fame_checker.c](src/fame_checker.c) with conflict-free sprite tag allocation (`0xD500` range) and full graphics pipeline in `graphics/fame_checker/` (background tilemaps 1/2/3, cursor, question mark, spinning pokeball, Oak, Daisy, Bill, Mr. Fuji, and silhouette palettes).
  - Saved state integrated into `SaveBlock1`: `struct FameCheckerSaveData fameChecker[NUM_FAMECHECKER_PERSONS]` (32 bytes budgeted in free sector memory).
  - Authentic person profiles, quotes, and flavor text pointers for all 16 Kanto personalities: Prof. Oak, Daisy Oak, Brock, Misty, Lt. Surge, Erika, Koga, Sabrina, Blaine, Lorelei, Bruno, Agatha, Lance, Bill, Mr. Fuji, and Giovanni.
  - Overworld script integration: `special SetFlavorTextFlagFromSpecialVars` and `special UpdatePickStateFromSpecialVar8005` wired to the `famechecker` script macro across Kanto dialogue and Pokemon Journal signposts/bookshelves (`data/scripts/fame_checker_frlg.inc`).
  - Bag & field usage: `ITEM_FAME_CHECKER` wired with `ItemUseOutOfBattle_FameChecker` supporting in-bag invocation and registered SELECT button quick usage.
  - C unit test `TEST("Confluence: Authentic FireRed Fame Checker Lore Journal Subsystem")` verified in `test/confluence.c` (35/35 passed).

- **Joyful Game Corner Minigames & Berry Crusher Vendor**:
  - Restored overworld minigame interaction scripts in [data/maps/TwoIsland_JoyfulGameCorner_Frlg/scripts.inc](data/maps/TwoIsland_JoyfulGameCorner_Frlg/scripts.inc) and [data/scripts/cable_club_frlg.inc](data/scripts/cable_club_frlg.inc).
  - Added solo practice mode support for both Pokémon Jump (`StartPokemonJumpPracticeSpecial`) and Dodrio Berry-Picking (`StartDodrioBerryPickingPracticeSpecial`), allowing single-player minigame engagement without physical GBA wireless adapters.
  - Authentic party eligibility validation: `special IsPokemonJumpSpeciesInParty` (verifies eligible jumping Pokémon under 2'04") and `special IsDodrioInParty` (verifies Dodrio in party).
  - Dedicated record displays for Pokémon Jump (`special ShowPokemonJumpRecords`) and Dodrio Berry-Picking (`special ShowDodrioBerryPickingRecords`).
  - Cerulean City Berry Powder Man in [data/maps/CeruleanCity_House5_Frlg/scripts.inc](data/maps/CeruleanCity_House5_Frlg/scripts.inc): awards `ITEM_POWDER_JAR` upon verifying at least 1 berry in Bag (`specialvar VAR_RESULT, HasAtLeastOneBerry`), tracks total powder crushed via `IncrementGameStat(GAME_STAT_PLAYED_BERRY_CRUSH)`, and opens the authentic powder exchange shop with dynamic powder display for all 11 medicine items: Energypowder (50), Heal Powder (50), Energy Root (80), Revival Herb (300), Protein (1000), Iron (1000), Carbos (1000), Calcium (1000), Zinc (1000), HP Up (1000), and PP Up (3000).
  - C unit test `TEST("Confluence: Authentic FireRed Joyful Game Corner Minigames and Berry Powder Economy")` verified in [test/confluence.c](test/confluence.c) (36/36 passed).

- **Teachy TV Subsystem (`pokefirered`)**:
  - Implemented authentic Teachy TV subsystem in [src/teachy_tv.c](src/teachy_tv.c) and [include/teachy_tv.h](include/teachy_tv.h) with Poke Dude hosting all 6 lessons (Battle Basics, Status Conditions, Type Matchups, Catching Pokémon, TMs, Key Item Registration) and CANCEL.
  - Linked authentic background UI assets in `graphics/teachy_tv/` (`tiles.png`, `palettes.pal`, `screen.bin`, `title.bin`) in `src/graphics.c` and declared in `include/graphics.h`.
  - Dynamic Route 1 set rendering on BG3 with tall grass rustle sprites (`TeachyTvGrassAnimationMain`), animated static TV noise on BG2 (`TeachyTvBg2AnimController`), Poke Dude host animations (`OBJ_EVENT_GFX_TEACHY_TV_HOST`), and audio themes (`MUS_RG_TEACHY_TV_MENU` and `MUS_RG_TEACHY_TV_SHOW`).
  - Wired `ITEM_TEACHY_TV` out-of-battle item handler `ItemUseOutOfBattle_TeachyTv` in `src/item_use.c` and `include/item_use.h`, configured `fieldUseFunc` and `.type = ITEM_USE_BAG_MENU` in `src/data/items.h`.
  - Viridian City Old Man gift event verified in `ViridianCity_Frlg/scripts.inc` (awards Teachy TV after catching demonstration).
  - Preserved multi-region L/R cycling for Trainer Card and Fly Map without collision.
  - C unit test `TEST("Confluence: Authentic FireRed Teachy TV Subsystem")` verified in [test/confluence.c](test/confluence.c) (37/37 passed).

- **Surfing Pikachu Beach Minigame (`pokeyellow`)**:
  - Connected Route 19 Beach House (`Route19_UnusedHouse_Frlg`) to Fuchsia City indoor group (`gMapGroup_IndoorFuchsia_Frlg`) with authentic warp at Route 19 beach coordinate (5, 9).
  - Populated Summer Beach House with Surfin' Dude NPC (`OBJ_EVENT_GFX_FISHERMAN`), Surfing Pikachu NPC (`OBJ_EVENT_GFX_PIKACHU`), surf tip posters, and High Score printer BG event.
  - Implemented authentic party qualification special `CheckSurfingPikachuInParty` checking for `SPECIES_PIKACHU` knowing `MOVE_SURF`.
  - Implemented full 2D surfing simulation in [src/surfing_pikachu.c](src/surfing_pikachu.c) and [include/surfing_pikachu.h](include/surfing_pikachu.h) with 24-section ocean course, sinusoidal wave crests and troughs, jump trajectories, D-Pad rotation tricks, Radness combo scaling (+100 * flips), Clean (+500 pts, boost), Rough (+100 pts), Hard, and Wipeout landing detection.
  - Results calculation with time bonus (`hp * 5`) + Radness points, updating `VAR_SURFING_PIKACHU_HIGH_SCORE`, `VAR_SURFING_PIKACHU_RADNESS`, and `GAME_STAT_SURFING_PIKACHU_HIGH_SCORE`.
  - Connected Beach House printer reading saved high scores via `GetSurfingPikachuScores`.
  - C unit test `TEST("Confluence: Authentic Yellow Surfing Pikachu Beach Minigame Subsystem")` verified in [test/confluence.c](test/confluence.c) (38/38 passed).

- **Pikachu Voiced 8-bit PCM Audio Samples (`pokeyellow`)**:
  - Digitized and compiled authentic Ikue Otani Pokémon Yellow voice clips into GBA 8-bit DPCM samples in `sound/direct_sound_samples/pikachu_voice/`: battle entrance (`cry_37.bin`), faint (`cry_4.bin`), low HP moan (`cry_17.bin`), level-up celebration (`cry_28.bin`), Thunder shock cry (`cry_2.bin`), joyful cheer (`cry_5.bin`), and sad/weary (`cry_31.bin`).
  - Added configurable toggle `VOICED_PIKACHU_CRIES = TRUE` in `include/config/pokemon.h` allowing seamless selection between authentic anime voice clips and Gen 3 synthetic cries.
  - Linked `gPikachuVoiceTable` and `gPikachuVoiceTable_Reverse` in `sound/cry_tables.inc` and sample data in `sound/direct_sound_data.inc`.
  - Added dedicated dispatch functions `PlayPikachuVoice(voiceId, pan)` and `PlayPikachuCelebrationCry()` in `src/sound.c` and declared in `include/sound.h`.
  - Wired automated cry interception in `PlayCryInternal` mapping battle entrance, fainting, low HP, and thunder attack moves to voiced samples for all Pikachu forms (Cosplay, Rock Star, Belle, Pop Star, PhD, Libre, Partner, Starter, Gmax).
  - Integrated mood-reactive vocalizations in `Special_ShowLeadPokemonMood` in `src/mood.c` (joyful for ecstatic/happy, melancholic for distant/angry, low HP moan for tired/sick/paralyzed).
  - C unit test `TEST("Confluence: Authentic Yellow Pikachu Voiced 8-bit PCM Audio Subsystem")` verified in [test/confluence.c](test/confluence.c) (39/39 passed).

- **Hoenn Gym Leader Match Call Rematches (`pokeemerald`)**:
  - All 5 trainer rosters (base + 4 rematch tiers) for all 8 Hoenn Gym Leaders (`TRAINER_ROXANNE_1..5`, `TRAINER_BRAWLY_1..5`, `TRAINER_WATTSON_1..5`, `TRAINER_FLANNERY_1..5`, `TRAINER_NORMAN_1..5`, `TRAINER_WINONA_1..5`, `TRAINER_TATE_AND_LIZA_1..5`, `TRAINER_JUAN_1..5`) integrated in `src/data/trainers.party` and mapped into `gRematchTable` in [src/battle_setup.c](src/battle_setup.c).
  - Overworld double-battle rematch scripts in all 8 Hoenn Gyms (`RustboroCity_Gym`, `DewfordTown_Gym`, `MauvilleCity_Gym`, `LavaridgeTown_Gym_1F`, `PetalburgCity_Gym`, `FortreeCity_Gym`, `MossdeepCity_Gym`, `SootopolisCity_Gym_1F`) configured with `trainerbattle_rematch_double`, party checks, and post-battle dialogue routing.
  - Multi-region rematch qualification in [src/gym_leader_rematch.c](src/gym_leader_rematch.c) and [src/pokenav_match_call_data.c](src/pokenav_match_call_data.c): leaders become eligible for rematches upon achieving `FLAG_SYS_GAME_CLEAR`, `FLAG_CONFLUENCE_APEX_CHAMPION`, or earning 8+ badges (`Confluence_CountBadges() >= 8`).
  - Fixed Gym Leader rematch tier calculation bug and bounds (`REMATCH_ROXANNE` to `< REMATCH_ELITE_FOUR_ENTRIES`) in `GetCurrentGymLeaderRematchLevel()`.
  - Match Call UI integration displaying rematch indicator icon and contextual telephone dialogue in Pokénav.
  - C unit test `TEST("Confluence: Authentic Emerald Hoenn Gym Leader Rematches Subsystem")` verified in [test/confluence.c](test/confluence.c) (40/40 passed).

- **Trick House Puzzles 1–8 & Mirage Island Mechanics (`pokeemerald`)**:
  - Verified all 8 Trick House puzzle map layouts, hidden Trick Master furniture hiding spots, scroll signs, locked doors, and reward distribution (Rare Candy, Timer Ball, Hard Stone, Smoke Ball, TM12 Taunt, Magnet, PP Max, Red/Blue Tent) in `data/maps/Route110_TrickHouse*`.
  - Door scroll passcodes and door unlock states (`VAR_TRICK_HOUSE_PUZZLE_1_STATE` through `VAR_TRICK_HOUSE_PUZZLE_8_STATE`) verified.
  - Multi-region badge qualification in `Route110_TrickHouseEntrance/scripts.inc`: puzzles 2–8 evaluate regional Gym Badges (`FLAG_BADGE03_GET` through `FLAG_BADGE08_GET`, `FLAG_SYS_GAME_CLEAR`, `FLAG_CONFLUENCE_APEX_CHAMPION`) or total multi-region badge counts via `ConfluenceCountBadges`.
  - Mirage Island daily mechanics in [src/time_events.c](src/time_events.c), [src/clock.c](src/clock.c), and [src/overworld.c](src/overworld.c): daily 16-bit pseudorandom seed advancement (`UpdateMirageRnd`), party personality match algorithm (`IsMirageIslandPresent`), Pacifidlog Town old man observer script, and Route 130 layout switching (`LAYOUT_ROUTE130_MIRAGE_ISLAND`) revealing wild Wynaut and the Liechi Berry tree.
  - Desert Mirage Tower crumbling and disintegration cutscene on Route 111 upon retrieving Root Fossil or Claw Fossil (`special StartMirageTowerShake`, `special StartPlayerDescendMirageTower`, `special StartMirageTowerDisintegration`, and Desert Underpass access).
  - C unit test `TEST("Confluence: Authentic Emerald Trick House Puzzles and Mirage Island Mechanics")` verified in [test/confluence.c](test/confluence.c) (41/41 passed).

- **Contest Halls & Berry Blender Pokéblock Minigame (`pokeemerald`)**:
  - Centralized Emerald Contest Lobby in Lilycove City (`LilycoveCity_ContestLobby`) supporting all four competition ranks: Normal, Super, Hyper, and Master, and all five categories: Cool, Beauty, Cute, Smart, and Tough.
  - Verified Emerald Battle Tents in Slateport, Verdanturf, and Fallarbor with dedicated rental, palace, and arena style tournament challenges.
  - Contest Receptionist script delivers `ITEM_POKEBLOCK_CASE`, checks entry qualifications and ribbons, and stages the 2-round contest appeals seamlessly in `data/scripts/contest_hall.inc` and `data/maps/ContestHall/`.
  - Solo NPC Berry Blenders in Lilycove Contest Lobby: 2-player (1 NPC Mister), 3-player (2 NPCs Laddie & Lassie), 4-player (3 NPCs Dude, Lassie, Miss), and PokéNews Blend Master tables fully functional without link timeouts (`DoBerryBlending`).
  - Pokéblock crafting algorithm in [src/berry_blender.c](src/berry_blender.c) and [src/pokeblock.c](src/pokeblock.c): authentic calculation of colors, flavor levels, feel, max RPM, sheen, and nature-based flavor affinity (`PokeblockGetGain`) across all 40 Case slots.
  - C unit test `TEST("Confluence: Authentic Emerald Contest Halls and Berry Blender Pokéblock Subsystem")` verified in [test/confluence.c](test/confluence.c) (42/42 passed).

- **DexNav Search Levels & Encounter HUD Calibration (`pokeemerald-expansion`)**:
  - Enabled `DEXNAV_ENABLED = TRUE` and `USE_DEXNAV_SEARCH_LEVELS = TRUE` in [include/config/dexnav.h](include/config/dexnav.h).
  - Designed and implemented a compact 256-slot search level cache in `struct SaveBlock3`: `struct DexNavSearchLevelEntry { u16 species; u8 searchLevel; } dexNavSearchLevels[256]` (1024 bytes) in [include/global.h](include/global.h), guaranteeing `sizeof(struct SaveBlock3) <= 1624` bytes.
  - Implemented `DexNav_GetSearchLevel(species)` and dynamic cache entry replacement in `TryIncrementSpeciesSearchLevel()` in [src/dexnav.c](src/dexnav.c).
  - Verified overworld chaining, shiny roll boosts, and accurate encounter detection across morning, day, and night wild tables in Johto, Kanto, and Hoenn.
  - C unit test `TEST("Confluence: DexNav Saveblock-Safe Search Levels and HUD Calibration")` verified in [test/confluence.c](test/confluence.c) (43/43 passed).

- **Modern Party EXP Share Key Item Toggle (`pokeemerald-expansion`)**:
  - Configured `EXP_SHARE_HELD_ITEM` (Gen 2-5) and `EXP_SHARE_KEY_ITEM` (Gen 6+) mode architecture with `I_EXP_SHARE_MODE` selector in [include/config/item.h](include/config/item.h).
  - Allocated persistent toggle flag `FLAG_EXP_SHARE_ENABLED` (`0x264`) in [include/constants/flags.h](include/constants/flags.h).
  - Classified `ITEM_EXP_SHARE` as a Key Item (`POCKET_KEY_ITEMS`, importance 1) when in `EXP_SHARE_KEY_ITEM` mode, supporting field and bag menu on/off toggling with sound effects `SE_EXP_MAX` / `SE_PC_OFF` and notifications.
  - Updated `IsGen6ExpShareEnabled()` in [src/battle_util.c](src/battle_util.c) to verify `CheckBagHasItem(ITEM_EXP_SHARE, 1)`, ensuring party Exp is granted only when the player possesses the item.
  - Verified battle exp distribution in [src/battle_script_commands.c](src/battle_script_commands.c): active Pokémon gain 100% calculated Exp while non-participating benched Pokémon receive 50% base Exp when the Key Item is active, accompanied by team Exp notifications.
  - Automatically enabled upon obtaining `ITEM_EXP_SHARE` from Mr. Pokémon on Route 30 (`MrPokemonsHouse_Johto`), Mr. Stone at Devon Corp (`RustboroCity_DevonCorp_3F`), and Oak's Aide on Route 15 (`Route15_WestEntrance_2F_Frlg`).
  - C unit test `TEST("Confluence: Modern Party EXP Share Key Item Toggle Subsystem")` verified in [test/confluence.c](test/confluence.c) (44/44 passed).

- **Unified Multi-Region Pokédex Selection Menu (`pokemultiregion`)**:
  - Implemented regional and national Pokédex modes (`DEX_MODE_HOENN`, `DEX_MODE_KANTO`, `DEX_MODE_JOHTO`, `DEX_MODE_NATIONAL`) in [include/constants/pokedex.h](include/constants/pokedex.h) and [src/pokedex.c](src/pokedex.c).
  - Added multi-region auto-selection via `GetDefaultPokedexMode()` and mode validation via `SanitizePokedexMode()`.
  - Added real-time L/R shoulder button regional Pokédex cycling in the main Pokédex list view.
  - Fully integrated Pokédex MODE row into the Search and Shift parameter menus, allowing players to filter and browse Pokédex listings for Hoenn (202), Kanto (151+), Johto (251), and National dexes.
  - Implemented dedicated regional diplomas for Hoenn, Kanto, Johto, and National Dex completions in [src/diploma.c](src/diploma.c) with Game Freak game designers in Lilycove, Celadon Mansion, and Goldenrod City.
  - Full compatibility with HGSS Pokédex UI in [src/pokedex_plus_hgss.c](src/pokedex_plus_hgss.c).
  - C unit test `TEST("Confluence: Unified Multi-Region Pokédex Selection Menu Subsystem")` verified in [test/confluence.c](test/confluence.c) (45/45 passed).

- **Unified Bag Town Map Regional Cycling (`pokemultiregion`)**:
  - Integrated `selectedRegionMapType` into `struct RegionMap` in [include/region_map.h](include/region_map.h), guaranteeing the 0x884 byte struct size invariant.
  - Implemented unified `SwitchRegionMapType()` and `GetNextRegionMapType()` with forward and reverse cycling across Hoenn (`REGION_MAP_HOENN`), Kanto (`REGION_MAP_KANTO`), and Johto (`REGION_MAP_JOHTO`) in [src/region_map.c](src/region_map.c).
  - Integrated L/R button regional cycling across Town Map from Bag (`ITEM_TOWN_MAP`) and PC wall maps in [src/field_region_map.c](src/field_region_map.c), and Pokégear Map Card (`POKENAV_REGION_MAP`) in [src/pokenav_region_map.c](src/pokenav_region_map.c).
  - Player icon accurately anchored to native coordinates (`playerIconSpritePosX`, `playerIconSpritePosY`) and automatically hidden with `HideRegionMapPlayerIcon()` when viewing other regions, defaulting the cursor to Iconic towns (Pallet Town, New Bark Town, Littleroot/Slateport).
  - Dynamic region title bar headers (`HOENN`, `KANTO`, `JOHTO`, and `{R_BUTTON} FLY`) with `gText_Johto` in [src/strings.c](src/strings.c).
  - C unit test `TEST("Confluence: Unified Bag Town Map Regional Cycling Subsystem")` verified in [test/confluence.c](test/confluence.c) (46/46 passed).

- **S.S. Aqua Weekly Sailing Schedule & Cabin Event Progression (`pokemultiregion`)**:
  - Implemented authentic Crystal weekly sailing timetable via RTC `special JohtoGetWeekday`:
    - Olivine Port departs on Mondays (`WEEKDAY_MON`) and Fridays (`WEEKDAY_FRI`). On all other days, informs the player of the next departure day.
    - Vermilion Port departs on Wednesdays (`WEEKDAY_WED`) and Sundays (`WEEKDAY_SUN`). On all other days, informs the player of the next departure day.
  - Complete First Trip sequence restoration:
    - B1F access blocked by on-duty sailor until the player discovers and defeats the lazy sailor in cabin NNW_NNE_NE (`TRAINER_JOHTO_SAILOR_STANLY`).
    - Fixed Granddaughter rescue quest in Captain's Cabin: girl returned to worried grandfather on 1F, persistent hide flags set, awarding `ITEM_METAL_COAT` and arrival docking sound (`SE_DING_DONG`).
    - Cabin bed accurately heals party, only triggering arrival announcements when eligible.
  - Directional passenger rotation:
    - Eastbound passengers (`FLAG_JOHTO_FAST_SHIP_PASSENGERS_EASTBOUND`) appear and reset battle flags on Johto -> Kanto voyages.
    - Westbound passengers (`FLAG_JOHTO_FAST_SHIP_PASSENGERS_WESTBOUND`) appear and reset battle flags on Kanto -> Johto voyages.
    - Maiden voyage passengers (`FLAG_JOHTO_FAST_SHIP_PASSENGERS_FIRST_TRIP`) appear exclusively during the initial maiden voyage.
  - C unit test `TEST("Confluence: S.S. Aqua Weekly Sailing Schedule & Cabin Progression Subsystem")` verified in [test/confluence.c](test/confluence.c) (47/47 passed).

- **Magnet Train Goldenrod–Saffron Pass Questline & High-Speed Transit (`pokemultiregion`)**:
  - Full-screen high-speed parallax Magnet Train transit cutscene engine in [src/magnet_train.c](src/magnet_train.c) (`MagnetTrain` and `MagnetTrainWarp`) with Eastbound/Westbound landscape scrolling, authentic chimes (`SE_WARP_IN`, `SE_TRUCK_MOVE`, `SE_DING_DONG`), and station arrivals.
  - Goldenrod and Saffron Magnet Train station scripts wired with power restoration check (`FLAG_JOHTO_RESTORED_POWER_TO_KANTO`) and Pass check (`ITEM_PASS`).
  - Restored Copycat lost Clefairy doll questline:
    - Saffron City Copycat House 2F: speaking with Copycat after power restoration sets `FLAG_JOHTO_MET_COPYCAT_FOUND_OUT_ABOUT_LOST_ITEM`.
    - Vermilion City Pokémon Fan Club: Clefairy Guy hands over `ITEM_LOST_ITEM` and sets `FLAG_JOHTO_VERMILION_FAN_CLUB_DOLL`.
    - Returning to Copycat trades `ITEM_LOST_ITEM` for `ITEM_PASS` (`FLAG_JOHTO_GOT_PASS_FROM_COPYCAT`) and dynamically renders the Clefairy doll sprite on her desk.
  - C unit test `TEST("Confluence: Magnet Train Goldenrod-Saffron Pass Questline Subsystem")` verified in [test/confluence.c](test/confluence.c) (48/48 passed).

- **Apex Summit 24-Leader Boss Gauntlet (`pokemultiregion`)**:
  - Implemented authentic post-game multi-region tournament in [src/apex_summit.c](src/apex_summit.c) and [include/apex_summit.h](include/apex_summit.h) staged at Mt. Silver's apex summit (`ApexSummit_Johto`, Map 84 in `gMapGroup_Johto4`).
  - Master database of 40 contenders across 3 tiers: 24 Gym Leaders across Hoenn, Kanto, and Johto; 11 Elite Four members; and 5 Champions/Legends (Lance, Steven, Wallace, Red, Summit Red) with authentic intro quotes and defeat quotes.
  - Bracket generator (`ApexSummit_GenerateBracket`): dynamically draws 5 escalating challenge rounds into persistent variables `VAR_APEX_OPPONENT_0` through `VAR_APEX_OPPONENT_4` (Rounds 1-2: Gym Leaders; Round 3: Elite Four; Round 4: Elite Four/Champion; Round 5: Apex Legend).
  - Scaled all contenders to Level 100 in `src/confluence.c` (`Confluence_GetTrainerLevelBoost`) with full competitive calibration in `src/trainer_util.c`: 31 IVs across all stats, optimal 252/252/4 EV spreads, and competitive battle items (Life Orb, Leftovers, Sitrus Berry).
  - Multi-round tournament loop: smooth transitions between rounds, automatic party heal (`HealPlayerParty`), streak tracking (`VAR_APEX_STREAK`), and defeat handling in `src/battle_setup.c` preventing whiteout.
  - Apex Champion honors: lifts player level cap to 100 (`FLAG_CONFLUENCE_APEX_CHAMPION`), bestows `MON_DATA_VICTORY_RIBBON` upon all party Pokémon, awards `ITEM_RELIC_CROWN`, presents the Gold Apex Trophy (`DECOR_GOLD_SHIELD`), awards the 5th Trainer Card star (`CountPlayerTrainerStars`), and registers the victory in the Hall of Fame.
  - C unit test `TEST("Confluence: Apex Summit 24-Leader Boss Gauntlet Subsystem")` verified in [test/confluence.c](test/confluence.c) (49/49 passed).

- **Daily Johto & Kanto Timed Events, Grooming & Viridian Trainer House (`pokecrystal`)**:
  - Implemented the midnight daily reset subsystem in [src/clock.c](src/clock.c) (`DoDailyEvents`) clearing 9 critical daily flags: `FLAG_JOHTO_ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY`, `FLAG_JOHTO_ENGINE_MT_MOON_SQUARE_CLEFAIRY`, `FLAG_JOHTO_ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT`, `FLAG_JOHTO_ENGINE_DAISYS_GROOMING`, `FLAG_JOHTO_ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN`, `FLAG_JOHTO_ENGINE_DAILY_MOVE_TUTOR`, `FLAG_JOHTO_ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT`, `FLAG_JOHTO_ENGINE_DAILY_BUG_CONTEST`, and `FLAG_JOHTO_ENGINE_GOLDENROD_UNDERGROUND_MERCHANT_CLOSED`.
  - Viridian City Trainer House Daily Gauntlet in [data/maps/TrainerHouseB1F_Johto/scripts.inc](data/maps/TrainerHouseB1F_Johto/scripts.inc): authentic progression-based Cal scaling via `special JohtoTrainerHouseGetOpponent` (< 8 badges: Cal 1 Lv. 10 starter trio; 8-15 badges: Cal 2 Lv. 30 mid evos; 16+ badges: Cal 3 Lv. 50 final evos), 1 challenge per day enforcement, and daily victory prize `ITEM_PP_UP`.
  - Authentic Haircut & Grooming Engine in [src/johto_scripts.c](src/johto_scripts.c): interactive party selection via `special ChoosePartyMon` with Egg rejection, nickname buffering to `gStringVar1`, species buffering to `VAR_0x8004` for species cries, and authentic probability tables: Older Brother (`JohtoOlderHaircut`, 500 yen, Tue/Thu/Sat), Younger Brother (`JohtoYoungerHaircut`, 300 yen, Sun/Wed/Fri), and Daisy Oak (`JohtoDaisyGrooming`, Pallet Town, daily 3 PM - 4 PM).
  - Mt. Moon Square Clefairy Dance in [data/maps/MountMoonSquare_Johto/scripts.inc](data/maps/MountMoonSquare_Johto/scripts.inc): Monday night (8 PM to 11:59 PM) choreographed Clefairy dance around the boulder, scattering upon approach, leaving behind breakable rock and hidden `ITEM_MOON_STONE` at (7, 7).
  - Sunday Goldenrod Dept. Store 5F woman evaluates lead mon friendship via `JohtoGetFirstMonHappiness`: awards TM27 Return if friendship >= 150 or TM21 Frustration if <= 50.
  - Safe bounds-checking and party count validation added to `JohtoGetFirstMonHappiness` in [src/regions.c](src/regions.c).
  - C unit test `TEST("Confluence: Daily Johto & Kanto Timed Events, Grooming & Viridian Trainer House")` verified in [test/confluence.c](test/confluence.c) (50/50 passed).





