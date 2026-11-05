# What features are included?

## Table of Contents

- [What features are included?](#what-features-are-included)
	- [Table of Contents](#table-of-contents)
	- [Confluence layer](#confluence-layer)
	- [Configuration files](#configuration-files)
	- [Upgraded Battle Engine](#upgraded-battle-engine)
	- [Full Trainer customization](#full-trainer-customization)
	- [Pokémon data](#pokémon-data)
	- [Interface improvements](#interface-improvements)
	- [Engine improvements](#engine-improvements)
	- [Overworld improvements](#overworld-improvements)
	- [Developer tools](#developer-tools)

## Confluence layer

Added on top of the base hack (design and status: [docs/CONFLUENCE.md](docs/CONFLUENCE.md)):

- 24-badge circuit across Kanto, Johto and Hoenn, with a level cap that follows the badges held
- Meridian Transit: fast travel between the three regions once you hold two badges
- Gym Leaders, Elite Four and Champions scaled to the level cap (never lowered)
- Resonance weather anomalies until each region's three legends are caught
- Convergence Crisis: three Syndicate enforcers, then the Chairman
- Apex Summit: four rounds against the three Regional Wardens and the Summit Champion in a dedicated Summit arena
- Field Kit: the first party Pokémon can use Cut, Rock Smash, Strength, Surf, Waterfall, Dive and Rock Climb in the overworld without the HM move, plus a **FIELD KIT** submenu in the party menu for Surf, Fly, Flash, Dig, Teleport, Dive and Waterfall
- Johto Phone Book & Rematches: register all 37 Johto phone trainers and battle their 5-tier scaled rematch teams
- Reusable TMs

## Configuration files

A lot of features listed below can be turned off as desired. Check which ones in these files

- [AI config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/ai.h)
- [Battle config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/battle.h)
- [Caps config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/caps.h)
- [Debug config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/debug.h)
- [DexNav config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/dexnav.h)
- [General config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/general.h)
- [HGSS Pokédex config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/pokedex_plus_hgss.h)
- [Item config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/item.h)
- [NPC Follower config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/follower_npc.h)
- [Overworld config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/overworld.h)
- [Pokémon config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/pokemon.h)
- [Save config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/save.h)
- [Species enabled](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/species_enabled.h)
- [Summary screen config](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/include/config/summary_screen.h)

## Upgraded Battle Engine

- **_Battle gimmicks:_** Mega Evolution, Primal Reversion, Ultra Burst, Z-Moves, Dynamax, Gigantamax and Terastallization.
- **_Newer game battle types:_** Double Wild Battles, custom Multi Battles, Inverse Battles, 1v2/2v1 battles, Sky Battles.
- **_Updated battle mechanics:_** Critical capture, Frostbite support, Poké Ball quick menu, Move description menu, no badge boosts, Gen 4 Fog, obedience, Affection, Party swap upon catch, move effectiveness in battle, FRLG/Gen4+ whiteout money calculation, Gen 4-style shadows.
- **_Updated move data_**: Fairy/Stellar types, Physical/Special split, flags.
- **_Updated calculations:_** Damage, experience, mid-turn speed, end-battle stats and EVs, Level 100 EVs.
- **_Every item, ability and move effect up to Gen IX:_** Includes contest data up to SwSh ([source](https://pokemonurpg.com/info/contests/rse-move-list/)).
- **_Initial battle conditions:_** Stat stages, battle terrain, Wild AI flags.
- **_Faster battles:_** Simultaneous HP reduction, shortcut to "Run" option, faster battle intro, faster HP drain, faster AI calculations.
- **_Easier customization:_** Cleaner codebase to implement custom moves and effects.
- **_Improved AI:_** Faster and considers new effects added by Expansion.
- **_Popular features:_** Level/EV Caps, Sleep Clause, Type Indicators.

## Full Trainer customization

- **_Compatible with Pokémon Showdown's team syntax:_** Create your trainer teams in the [teambuilder](https://play.pokemonshowdown.com/teambuilder) and paste the results!
- **_Custom Pokémon data:_** Nicknames, EVs, IVs, Moves, Abilities, Poké Balls, Friendship, Nature, Gender, Shininess, Dynamax level, Gigantamax Factor and Tera Type.
  - **_"Ace Pokémon":_** Will save a specific Pokémon for last.
  - **_Trainer Pools:_** A trainer may get a pool of randomized Pokémon instead of set teams.
- **_Custom sliding trainer messages:_** First Turn, landing a super-effective hit, before Mega Evolution, etc.
- **_New AI Flag options:_** Customize the intelligence of your trainers.
- **_Trainer class Poké Balls:_** Divers use Dive Balls, Breeders use Nest Balls, etc.

## Pokémon data

- **_Improved Pokémon Data structure:_** Optimized space to allow fitting more information, such as Tera type, 12-character names, Hyper-trained stats, evolution conditions, saved HP/status effect.
- **_Updated breeding mechanics:_** Poké Ball/Egg Move/Ability/Nature inheritance, Level 1 eggs automatic incense babies.
- **_Updated species data:_** Stats, Types, Abilities, Hidden Abilities, Egg Groups, EV Yields, movesets, Battle Facility bans, guaranteed perfect IV counts, ORAS Dex numbers.
- **_Simpler species data manipulation:_**: Only requires to edit ~5 files instead of vanilla pokeemerald's 20+ to add a new Pokémon.
- **_Updated sprites:_** DS-style sprites with support for Emerald's 2-frame animations and gender difference.
- **_Species toggles:_** You can disable specific groups of Pokémon to save space, including families, cross-gen evolutions, Mega Evolutions, Regional forms, etc.
- **_Revamped Evolution System_**: Multiple Evolution conditions can be stacked in order to create complex methods without additional coding. Every condition except Affection and console gyroscope is supported.
- **_Form Change System._** Most form changes can be added without additional coding. This includes support for: Holding/using an item, HP thresholds being met, weather change in and/or out of battle, Fusions, and more.

## Interface improvements

- **_Pokémon Summary:_** Move relearner, EV/IV checks, Nature colors ([feature branch](https://github.com/DizzyEggg/pokeemerald/tree/nature_color) by @DizzyEggg).
- **_Party Menu:_** "Move Item" option.
- **_Pokémon Storage System:_** Move option as default, access from Box Link item.
- **_HGSS-style Pokédex_** ([original feature branch](https://github.com/TheXaman/pokeemerald/tree/tx_pokedexPlus_hgss) by @TheXaman): Detailed in-game information accessible to players.

## Engine improvements

- **_All base pokeemerald bugfixes implemented by default:_** Anything under the `BUGFIX` define.
- **_Improved sprite and palette compression:_** Assets use less space than vanilla compression.
- **_Modern compiler support:_** Detect potential errors in your code more easily.
- **_Dynamic Multichoice_** ([original branch](https://github.com/SBird1337/pokeemerald/tree/feature/dynmulti) by @SBird1337): Easier way to add multiple-choice menus for scripting.
- **_High-Quality RNG:_** No more broken vanilla RNG.

## Overworld improvements

- **_Modern Mechanics_**: Defog field move, B2W2+ Repel system, Running indoors, Removed field poison, Chain fishing, VS. Seeker, FRLG+ whiteout message.
- **_Overworld and Follower Pokémon_** ([feature branch](https://github.com/aarant/pokeemerald/tree/followers-expanded-id) by @aarant)
  - _Includes Dynamic overworld palettes (DOWP) and Overworld Expansion for event IDs beyond 255._
  - _Includes Pokémon sprites up to Generation IX._
- **_Day/Night System:_** ([feature branch](https://github.com/aarant/pokeemerald/tree/lighting-expanded-id) by @aarant)
  - _Includes support for non-real time clock_.
- **_NPC Followers_**: ([feature branch](https://github.com/ghoulslash/pokeemerald/tree/follow_me) by @ghoulslash)
- **_BW Map Pop-ups_** ([feature branch](https://github.com/ravepossum/pokeemerald/tree/bsbob_map_popups) by @BSBob)
- **_XY Berry Mechanics:_** Mutations, moisture, weeds, pests.
- **_Obtained Item descriptions_** (feature branch by @ghoulslash).

## Developer tools

- **_Integrated Testing:_** Pinpoint if your custom mechanics have broken something else in the game or not.
- **_Pokémon Sprite Visualizer:_** Test every Pokémon sprite and animation.
- **\*Overworld debug menu** ([original feature branch](https://github.com/TheXaman/pokeemerald/tree/tx_debug_system) by @TheXaman)\*: Support menu with an assortment of features to facilitate debugging, including warping, flag and var toggling, Pokémon and item generation and more.
- **_Battle Debug Menu:_** Modify data on the fly in the middle of a battle.
- **_Learnset Helper:_** Autogenerate movesets from your custom TM and Tutor data based on official compatibility data.
- **_Configurable script flags:_** Disabling Wild encounters, Disabling Trainer battles, Forcing/Disabling Shinies.
- **_Saveblock Cleansing_** ([feature branch](https://github.com/ghoulslash/pokeemerald/tree/saveblock) by @ghoulslash)
