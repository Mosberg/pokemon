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
- **Johto Phone Book & Overworld Rematches**:
  - Full registration system supporting all 37 Crystal phone trainers: `JohtoPhoneIsRegistered`, `JohtoPhoneRegister`, and flags in [include/constants/johto_flags.h](include/constants/johto_flags.h).
  - 5-tier rematch team scaling stored in `VAR_JOHTO_MEM_W*`.
  - Rematch arming (`FLAG_JOHTO_ENGINE_*_READY_FOR_REMATCH`) and item gifting for the 11 gift trainers.

---

## 4. Overworld Mechanics, Navigation & Field Moves

- **Party Menu / Field Kit Cut for Johto**:
  - Cut usable directly from party menu / field kit in front of Johto cut trees (which are background sign events rather than object events). Implemented via `GetFacingJohtoCutTreeScript()` and `FieldCallback_CutJohtoTree()` in [src/fldeff_cut.c](src/fldeff_cut.c).
  - Cutting tall grass blocks in Johto tilesets swaps metatiles to plain mowed ground via `SetCutGrassMetatile()`.
- **Johto Fly Destinations & OOB Guard**:
  - Regional heal locations wired for all 11 outdoor Johto town map sections in `sMapHealLocations` in [src/region_map.c](src/region_map.c).
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

