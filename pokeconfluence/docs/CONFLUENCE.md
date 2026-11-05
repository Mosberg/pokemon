# Pokémon Confluence: design and status

Confluence is `pokemultiregion` (one ROM with Hoenn, Kanto and Johto, built on pokeemerald-expansion) plus a **Confluence layer**. Everything the layer adds is marked `POKE-CONFLUENCE` in the source; the base behaves as before.

Build target: `make -j$(nproc) confluence` → `pokeconfluence.gba` (title `POKECONFLUEN`, game code `BPEE`, map set `multiregion`).

## What the Confluence layer adds

| System | Where | Behaviour |
| --- | --- | --- |
| **24-badge circuit** | [src/confluence.c](../src/confluence.c) `Confluence_CountBadges` | Counts Hoenn (`FLAG_BADGE01..08`), Kanto (`FLAG_BADGE09..16`) and Johto badge flags through `GetBadgeFlagForRegion`. |
| **Badge-count level cap** | [src/caps.c](../src/caps.c), [include/config/caps.h](../include/config/caps.h) | `B_EXP_CAP_TYPE = EXP_CAP_SOFT`, new `B_LEVEL_CAP_TYPE = LEVEL_CAP_BADGE_COUNT`. Cap = table by badges held (15 with none, 48 with 8, 80 with 24), in any order and any region. Clearing the Apex Summit lifts it to 100. Over-cap Pokémon get reduced EXP. |
| **Meridian Transit** | [data/scripts/confluence.inc](../data/scripts/confluence.inc), map `MeridianStation_Johto` | Conductors in Slateport Harbor (Hoenn), Vermilion City (Kanto, the old ferry sailor) and Olivine City (Johto) offer *Board the line*, *Circuit report* and *Crisis briefing*; with fewer than 2 badges the line is closed. Boarding rides (fade, shake, sounds) to **Meridian Station**, a hall with a conductor and four gates: platform 1 Vermilion, 2 Olivine, 3 Slateport, 4 closed. Replaces the old Hoenn↔Kanto-only ferry. |
| **Resonance Encounters (tracking)** | `Confluence_CountResonanceCalmed` | The 9 legends (Articuno, Zapdos, Moltres, Raikou, Entei, Suicune, Regirock, Regice, Registeel) count as calmed once registered as caught. |
| **Apex Summit** | warden NPC in Silver Cave Outside (Johto), map `ApexSummit_Johto`, trainers `TRAINER_APEX_*` in [src/data/trainers.party](../src/data/trainers.party) | Needs all 24 badges. The warden sends the player into the Summit arena, where the Kanto, Johto and Hoenn Wardens and the Summit Champion stand in a column and fight in order (each refuses until the one before is beaten), party healed before each round, progress kept in the trainer flags. Winning sets `FLAG_CONFLUENCE_APEX_CHAMPION`, gives a Master Ball, lifts the level cap and warps to the Hall of Fame scene. |
| **Gym leader scaling** | `Confluence_GetTrainerLevelBoost` in [src/confluence.c](../src/confluence.c), [src/trainer_util.c](../src/trainer_util.c) | Trainers of class Leader, Elite Four and Champion (Hoenn and Kanto, which includes the Apex wardens and Summit Champion) get every party level raised so their strongest Pokémon matches the badge-count level cap. Never lowered. |
| **Resonance weather anomalies** | `Confluence_GetAnomalyWeather`, hooked in [src/field_weather_effect.c](../src/field_weather_effect.c) | After the 2nd badge, clear outdoor weather becomes storms (Kanto), fog (Johto) or downpours (Hoenn) until that region's three legends are caught or the Chairman is beaten. |
| **Convergence Crisis** | [data/scripts/confluence.inc](../data/scripts/confluence.inc), `TRAINER_SYNDICATE_*` | *Crisis briefing* on the conductor menu. A syndicate enforcer waits at each terminal (Rocket at Vermilion, Magma at Olivine, Aqua at Slateport; need 6 badges). With all three beaten and 12 badges the conductor connects the Chairman; beating him sets `FLAG_CONFLUENCE_CRISIS_RESOLVED` (weather clears) and gives 5 Rare Candies. |
| **Field Kit** | `ITEM_FIELD_KIT`, `Confluence_GetFieldKitMon` | Key item given by the conductors. The first non-egg party Pokémon can use Cut, Rock Smash, Strength, Surf, Waterfall, Dive and Rock Climb without the HM move (badges are still required). One item for all of them. |
| **Reusable TMs** | [include/config/item.h](../include/config/item.h) | `I_REUSABLE_TMS = TRUE`. |

The two new maps are appended to `gMapGroup_Johto4` (map numbers 83 and 84), so `GetCurrentRegion()` reports Johto there, and use `MAPSEC_JOHTO_MERIDIAN_STATION` / `MAPSEC_JOHTO_APEX_SUMMIT`.

Constants: [include/constants/confluence.h](../include/constants/confluence.h). Flags `FLAG_CONFLUENCE_*` reuse `FLAG_UNUSED_0x020..0x024`. Trainer ids 855–862 use eight of the nine trainer flags still free in the Hoenn band (only id 863 is left; more trainers need flag space made in `constants/flags.h`).

## Verified

- Headless tests: `scripts/test.sh` runs [test/confluence.c](../test/confluence.c): badge counting, level cap table and Apex lift, Meridian and Apex gates, Resonance counting, trainer ids, gym leader boost, weather anomalies, Field Kit. All pass.
- Played in the embedded emulator by [mgba-agent/confluence_smoke.py](../mgba-agent/confluence_smoke.py) (`scripts/play.sh 8911`, then `new_game_kanto.py`, then the script; each test starts from the saved new game): Field Kit hand-out, boarding the line to Meridian Station and leaving by a platform gate, enforcer refusing at 2 badges / fighting at 6 / defeat recorded, Chairman call, the Apex warden sending the player into the arena, the Summit Champion fight and the ending (champion flag, Hall of Fame). Earlier by hand: the Olivine menu, circuit report, ride to Slateport, the Apex warden refusal and the first Apex fight. The smoke test keeps the stat-block Pokémon's PP and HP topped up, so it checks the scripted flow, not balance.

## Not done yet (honest list)

- The Meridian Station and the Summit arena reuse existing layouts (Record Corner, Ever Grande Champion's room) and sprites; no new tiles, art or music, and no animated train.
- Per-HM key items (one Field Kit stands in for all of them); the Fly/Teleport/Dig family is not covered. The party menu now shows a **FIELD KIT** row for the Kit mon that opens a list (Surf, Fly, Flash, Dig, Teleport, Dive, Waterfall + Cancel; `CursorCb_FieldKit` in `src/party_menu.c`, `Confluence_GetFieldKitMoveByIndex`). Played in the embedded emulator ([mgba-agent/field_kit_menu.py](../mgba-agent/field_kit_menu.py), after `confluence_smoke.py --only kit`): the row appears on the Kit mon, the list draws with all seven moves plus Cancel, and picking a move without its badge shows the badge-locked message; actually performing each move was not tested; Cut, Strength, Rock Smash and Rock Climb stay on the facing-prompt path, and the row is hidden when the mon already knows 4 field moves (the 8-row action window is full).
- Syndicate and Chairman use existing sprites and trainer pictures; no new art, music or cutscene animations.
- Opponents other than Leaders, Elite Four and Champions (ordinary trainers, Syndicate) keep their original levels.
- Everything listed in [MISSING.md](../MISSING.md) for the Johto and Kanto conversions.

## Tooling

`scripts/setup.sh` (toolchain check, native tools, `.venv`, optional Node.js/Go), `scripts/build.sh`, `scripts/test.sh`, `scripts/play.sh`. The tools in the repository-level `tools/` folder (poke-migrator-pro, pokeemerald-ai-bridge, porymap, porytiles, poryscript, porypal, agbcc) are the ones the base hack was created with; `mgba-agent/` in this folder is retargeted at `pokeconfluence.gba` and `pokeconfluence.elf`.
