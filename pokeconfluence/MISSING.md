# MISSING

The Confluence layer (Meridian Transit, 24-badge level cap, Apex Summit) is tracked in [docs/CONFLUENCE.md](docs/CONFLUENCE.md). The lists below are inherited from `pokemultiregion`.

Everything known to be unfinished, unconverted or untested. Items are removed when done and verified, and appended when found.
Hard caps and approximations live in LIMITS.md. Status of the Johto conversion: all 383 maps load in the emulator smoke test (0 failures),
290 script commands still end in "This JOHTO event has not been converted yet" (`poke-crystal-scripts <crystal> <project>` prints the live list).

## Johto: scripts still not converted (largest groups first)

- **Rematch counters** (`readmem`, 33 of them are `w<Trainer>FightCount`; the rest are Battle Tower / Underground switch memory): the rematch branches are only reachable once a trainer is registered in the phone book, which this port does not have, so they are dead code and stay stubs. Converting them needs the phone book first (a trainer-number list, calls, `ENGINE_*_READY_FOR_REMATCH` flags) - it also exposes ~100 `loadtrainer`/`startbattle` rematch fights that are not converted
- **Day care**: the Johto day care man/lady now run the engine's own day care (Route 117 scripts; the woman's offer dialogue verified in play). Not verified: handing over Pokemon, egg generation/hatching, the Crystal Odd Egg gift (`GiveOddEgg`), the wandering day care mon objects
- **Unown / Ruins of Alph** (`DisplayUnownWords`, `VAR_UNOWNCOUNT`, puzzle specials), **Pokegear radio/Mobile** (`MapRadio` is skipped, `CheckMobileAdapterStatusSpecial`), **Battle Tower** (`BattleTowerAction`), **Coin Case / Game Corner** (`PlaceMoneyTopRight`, `DisplayCoinCaseBalance`, Card Flip), **Link/Trade**, **Bill's PC**, **move tutor**, **name rater**, **Magnet Train**
- `verbosegiveitemvar` (7), `catchtutorial` (Route 29 dude), `describedecoration` and the decoration system, `warpcheck`, `SelectApricornForKurt`, `CelebiShrineEvent`
- Text macros that do not translate (`<...>`, `{d:...}`, `text_decimal`, `text_asm`) become "(text not converted)"
- Object/bg kinds: `BGEVENT_IFSET`, `conditional_event`, `SCENE_ANY` coord events, `OBJECTTYPE_COMMAND` other than `jumptext*`
- Goldenrod Dept. Store floor logic and vending machines; Mart types BITTER/BARGAIN/PHARMACY/ROOFTOP open as a standard shop with Emerald prices
- Nurse: time-of-day greetings, Pokecom/phone and Pokerus handling (plain heal), heal-machine animation
- Phone / Pokegear: no phone book (trainers always get refused, caller id reads 0, no calls, no rematches), Pokegear menu entry, map card
- Fruit trees give their berry once (no daily regrowth); TMs whose move is not a TM in the expansion (Mud-Slap, Headbutt, Fury Cutter, Sweet Scent, the punch TMs) give a Nugget / are skipped in marts

## Johto: content not imported

- Time-of-day (morning/night) wild tables; Headbutt trees, swarms, roaming Pokemon, Bug-Catching Contest table, flee mons, Unown unlocks
- Crystal map music assignments (generic songs), real Crystal songs/SFX
- Crystal overworld sprites and trainer pictures (borrowed Hoenn/Kanto ones), Crystal text font and scroll-arrow tiles (the arrow shows as a heart)
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

- Field Kit party-menu row: the menu opens and draws in the emulator (see `mgba-agent/field_kit_menu.py`); performing each listed move through it (Surf, Fly, Dig, Teleport, Dive, Waterfall) is not yet verified
- VS Code extension views, dashboard, chat participant and real model calls are untested (only the emulator screen and MCP server were run)
- Headless mGBA Python bindings and the RL stack are not set up
- No automated test that rebuilds the ROM and replays the Johto opening (the manual replay scripts live in the session scratchpad, not in the repo)

## How this file is maintained

Add a line whenever something is found missing, unimplemented or untested; delete it when it is done and verified.
