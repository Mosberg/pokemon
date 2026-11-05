# MISSING

The Confluence layer (Meridian Transit, 24-badge level cap, Apex Summit) is tracked in [docs/CONFLUENCE.md](docs/CONFLUENCE.md). The lists below are inherited from `pokemultiregion`.

Everything known to be unfinished, unconverted or untested. Items are removed when done and verified, and appended when found.
Hard caps and approximations live in LIMITS.md. Status of the Johto conversion: all 383 maps load in the emulator smoke test (0 failures),
30 coverage items (33 `@ TODO unsupported:` stubs across all 383 maps, confined exclusively to Link/Mobile rooms, Crystal's Battle Tower, and the Bug-Catching Contest gate — 0 in single-player overworld/indoor/dungeon progression) remain (`poke-crystal-maps <crystal> <project> --scripts-only` prints the live list).

## Johto: scripts still not converted (largest groups first)

- **Phone book & rematches (converted for overworld interactions, no Pokegear call menu)**: `askforphonenumber`, `addcellnum`, `checkcellnum`, `loadvar VAR_CALLERID`, `readvar VAR_CALLERID`, `gettrainername`, `readmem`, `loadmem`, `writemem`, and `addval` are now converted across all 37 Johto phone trainers (`JohtoPhoneIsRegistered`, `JohtoPhoneRegister`, `VAR_JOHTO_MEM_W*`). Accepting a trainer's number registers `FLAG_JOHTO_PHONE_*_REGISTERED`, arms `FLAG_JOHTO_ENGINE_*_READY_FOR_REMATCH` (and gift flags for the 11 item-gifting trainers), and re-arms rematches on subsequent overworld visits; winning rematches increments `w<Trainer>FightCount` across all 5 tiers. Still missing: the Pokegear start-menu phone UI and incoming random overworld phone calls.
- **Day care**: the Johto day care man/lady run the engine's own day care (Route 117 scripts; the woman's offer dialogue verified in play), and the wandering yard mons (`DayCareMon1`, `DayCareMon2`) play cries. Not verified: handing over Pokemon, egg generation/hatching, the Crystal Odd Egg gift (`GiveOddEgg`).
- **Battle Tower** (`BattleTowerAction`), **Link/Trade/Mobile** (`Colosseum`, `TimeCapsule`, `TradeCenter`, `CableClubCheckWhichChris`, `AskMobileOrCable`), **Bug-Catching Contest** (`GiveParkBalls`, `getnum`).
- **Converted in Wave 2 & Wave 3**:
  - `loadmenu` / `verticalmenu` / `_2dmenu` (`dynmultipush` + `dynmultistack` with `maxBeforeScroll = min(len(opts), 6)`, unlocking the Dragon Shrine 8th-badge quiz and ExtremeSpeed Dratini gift, Goldenrod & Celadon Game Corner prize counters, Goldenrod & Celadon Dept. Store vending machines, Goldenrod Move Tutor, and Earl's Academy blackboard)
  - `elevator` (Goldenrod & Celadon Dept. Store elevators, including B1F warehouse box-layout cycling)
  - `BGEVENT_IFSET` / `BGEVENT_IFNOTSET` + `conditional_event` (Mahogany Team Rocket Base B2F & B3F password-locked doors to the transmitter room and Giovanni's office, verified in emulator play; Player's House 2F poster)
  - Goldenrod Radio Tower 1F Lucky Number Show (`CheckLuckyNumberShowFlag`, `PrintTodaysLuckyNumber`, `CheckForLuckyNumberWinners`) and 2F Buena's Password Show (`VAR_BLUECARDBALANCE`, `AskRememberPassword`, `BuenasPassword`, `BuenaPrize`)
  - Lake of Rage Fishing Guru (`CheckMagikarpLength`), Viridian Trainer House (`TrainerHouse` -> Trainer Cal battle), Goldenrod Dept. Store 5F (`UnlockMysteryGift`), Ruins of Alph (`UnownPuzzle`, `HoOhChamber`, `OmanyteChamber`, `skyfall_top`, `RuinsOfAlphResearchCenterScientist1Text_GotAllUnown`)
  - `checkcoins` / `givecoins` / `takecoins`, `SelectApricornForKurt` (`JohtoSelectApricornForKurt`), `CelebiShrineEvent` / `CheckCaughtCelebi`, `SnorlaxAwake` (Vermilion Snorlax), `MACHINE_PART` (`ITEM_DEVON_PARTS` in Cerulean Gym & Power Plant), `warpcheck` / `MagnetTrain` (Goldenrod <-> Saffron Magnet Train & Ruins of Alph chambers), `GiveShuckle` / `ReturnShuckie` (Mania's Shuckie), `checkpokemail` / `givepokemail` (Route 35/31 Kenya mail quest), `MoveDeletion` / `MoveTutor`, `halloffame` / `credits` / `warpfacing` (Lance -> Hall of Fame and Mt. Silver Red -> Credits), `BeastsCheck` / `MonCheck` (Tin Tower Rainbow Wing & Ho-Oh), `catchtutorial`, `describedecoration`, `readvar VAR_DEXCAUGHT` / `VAR_XCOORD` / `VAR_YCOORD`, and `{d:...}` price/coin string interpolation.
  - All Gen 2 TMs/HMs (`TM_PSYCHIC_M`, `TM_DRAGONBREATH`, `TM_DYNAMICPUNCH`, `TM_FURY_CUTTER`, `TM_ICY_WIND`, `TM_MUD_SLAP`, `TM_ZAP_CANNON`, `TM_THUNDERPUNCH`, `TM_FIRE_PUNCH`, `TM_ICE_PUNCH`, `TM_HEADBUTT`, `TM_ROCK_SMASH`, `HM_WHIRLPOOL`, etc.) mapped to Gen 3 TM/HM equivalents in `CMD_ITEMS` (0 Nugget fallbacks remaining).
  - All 118 Crystal `SPRITE_*` constants mapped to validated `OBJ_EVENT_GFX_*` entries in `SPRITE_MAP` (Team Rocket Grunts, all 16 Johto/Kanto Gym Leaders & Elite Four, Suicune/Raikou/Entei/Ho-Oh/Lugia, Snorlax, Sudowoodo, Berry Trees, Prof. Oak, Bill, Red, Blue, Lance, Kurt/Elder, Gym Guides, etc.) and all 48 Crystal `MUSIC_*` constants mapped to `MUS_RG_*` / `MUS_*` tracks in `MAP_MUSIC`.
- Nurse: time-of-day greetings, Pokecom/phone and Pokerus handling (plain heal), heal-machine animation
- Phone / Pokegear: no Pokegear start-menu entry, incoming overworld calls, or map card (overworld phone registration and rematches are converted)
- Fruit trees give their berry once (no daily regrowth)

## Johto: content not imported

- Time-of-day (morning/night) wild tables; Headbutt trees, swarms, roaming Pokemon, Bug-Catching Contest table, flee mons, Unown unlocks
- Real GBC Crystal synth songs/SFX (maps now use per-map FRLG/Emerald `MUS_RG_*` and `MUS_*` tracks via `MAP_MUSIC`)
- Custom GBC overworld sprites and trainer pictures (maps now use validated FRLG/Emerald `OBJ_EVENT_GFX_*` counterparts for all 118 Crystal sprites), Crystal text font and scroll-arrow tiles (the arrow shows as a heart)
- Johto Pokedex ordering and area map; Johto town map and Fly points (heal locations / respawn points exist for 22 towns)
- Per-class trainer DVs, per-class battle music, Crystal move/learnset differences, Crystal held-item effects
- Goldenrod Radio Tower, Underground, Bug Contest, Lake of Rage events (their scripts convert as far as the unsupported commands above allow, untested)
- Mobile Stadium, Link/Trade, Mobile features (not planned)

## Johto: engine integration

- Johto Elite Four / Champion progression and Hall of Fame; Johto badge case / trainer card display (badges are flags that drive obedience, field-move badges and `VAR_BADGES`)
- Johto town map, music sets, Pokedex area pages and trainer card still use Hoenn's
- Pokemon Center PC / Pokegear start-menu entry; day/night palettes
- Cut _grass_ blocks and "use Cut from the party menu" (cutting works by facing the tree and pressing A)

## Verified in play / still untested

Verified in the embedded emulator: Mom's Pokegear scene, New Bark Town, Elm's scene, all three starters (Totodile and Cyndaquil picked, Chikorita's rival variant run), Aide scene, Route 29 wild encounter,
Route 30 trainer, Johto save + continue round trip (position and party survive), Cherrygrove Pokemon Center / Mart / Guide Gent / rival scene (all three starter variants), Mr. Pokemon (Mystery Egg flag), Violet Gym (Falkner), Togepi egg from the Aide,
cut trees (Ilex Forest, Route 29), item balls (Sprout Tower 3F Potion), Sprout Tower rival scene and the Sage Li fight giving Flash, NPC trade (Emy), a trainer battle played to the end, the Violet nurse setting the respawn point and a whiteout waking the player in Violet's Pokemon Center (nurse cutscene), all 383 maps loading. `make test-johto` replays these.

Converted but **not played**: static wild battles (`loadwildmon`), `changeblock`, hidden items (60 maps), boulders and rocks, Johto badges driving obedience/HM, Elder Li's Flash gift (needs the rival scene first),
Route 32 Slowpoketail scene / Union Cave / Azalea / Kurt / Ilex Forest, Togepi hatching and Elm's follow-up, per-town respawn in towns other than Violet,
fishing encounter tables (Old/Good/Super Rod for 149 maps; the Old Rod is accepted on corrected water, species/levels unchecked), Surf, wild encounter species/levels against the table, what the rival says/uses per starter.

## Kanto / Yellow

- Yellow Pikachu mood, refusing Poke Balls/evolution stones, Pikachu happiness reactions; Yellow gift starters
- Route 22 Jolteon upgrade and Jessie & James fights are built but never played
- Play-testing Viridian Forest, Mt. Moon, Cerulean and the ferry back to Hoenn with a Kanto badge
- The older plugin scripts (`poke-patch*`, `poke-migrate-*`) do not reproduce the trainer-id / flag-band changes

## Embedded emulator

- Cartridge RTC (real time-of-day / weekday behaviour in Johto scripts), link cable, rewind, cheats, breakpoint / memory-viewer panels and a Debug Adapter (gba-kit has the packages, not wired in)
- Native-mGBA savestate import
- Live test of keyboard / gamepad and audio in the webview beyond the screen (verified: screen, toolbar, bridge protocol, Python tools, crash banner logic)

## Tooling and extension

- Field Kit party-menu row: verified in the emulator for Fly and Teleport (and the Surf message); Flash, Dig, Dive and Waterfall through the list are not yet run
- VS Code extension views, dashboard, chat participant and real model calls are untested (only the emulator screen and MCP server were run)
- Headless mGBA Python bindings and the RL stack are not set up
- No automated test that rebuilds the ROM and replays the Johto opening (the manual replay scripts live in the session scratchpad, not in the repo)

## How this file is maintained

Add a line whenever something is found missing, unimplemented or untested; delete it when it is done and verified.
