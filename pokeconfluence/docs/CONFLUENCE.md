# Pokémon Confluence: design and status

Confluence is `pokemultiregion` (one ROM with Hoenn, Kanto and Johto, built on pokeemerald-expansion) plus a **Confluence layer**. Everything the layer adds is marked `POKE-CONFLUENCE` in the source; the base behaves as before.

Build target: `make -j$(nproc) confluence` → `pokeconfluence.gba` (title `POKECONFLUEN`, game code `BPEE`, map set `multiregion`).

## What the Confluence layer adds

| System | Where | Behaviour |
| --- | --- | --- |
| **24-badge circuit** | [src/confluence.c](../src/confluence.c) `Confluence_CountBadges` | Counts Hoenn (`FLAG_BADGE01..08`), Kanto (`FLAG_BADGE09..16`) and Johto badge flags through `GetBadgeFlagForRegion`. |
| **Badge-count level cap** | [src/caps.c](../src/caps.c), [include/config/caps.h](../include/config/caps.h) | `B_EXP_CAP_TYPE = EXP_CAP_SOFT`, new `B_LEVEL_CAP_TYPE = LEVEL_CAP_BADGE_COUNT`. Cap = table by badges held (15 with none, 48 with 8, 80 with 24), in any order and any region. Clearing the Apex Summit lifts it to 100. Over-cap Pokémon get reduced EXP. |
| **Meridian Transit** | [data/scripts/confluence.inc](../data/scripts/confluence.inc) | Conductors in Slateport Harbor (Hoenn), Vermilion City (Kanto, the old ferry sailor) and Olivine City (Johto, new NPC). With fewer than 2 badges the line is closed; otherwise the player picks either other region, or reads the *Circuit report* (badges, level cap, Resonances calmed). Replaces the old Hoenn↔Kanto-only ferry. |
| **Resonance Encounters (tracking)** | `Confluence_CountResonanceCalmed` | The 9 legends (Articuno, Zapdos, Moltres, Raikou, Entei, Suicune, Regirock, Regice, Registeel) count as calmed once registered as caught. |
| **Apex Summit** | warden NPC in Silver Cave Outside (Johto), trainers `TRAINER_APEX_*` in [src/data/trainers.party](../src/data/trainers.party) | Needs all 24 badges. Four fights in a row (Kanto, Johto and Hoenn Wardens, then the Summit Champion), party healed between rounds, progress kept in the trainer flags. Winning sets `FLAG_CONFLUENCE_APEX_CHAMPION`, gives a Master Ball and lifts the level cap. |
| **Reusable TMs** | [include/config/item.h](../include/config/item.h) | `I_REUSABLE_TMS = TRUE`. |

Constants: [include/constants/confluence.h](../include/constants/confluence.h). Flags `FLAG_CONFLUENCE_*` reuse `FLAG_UNUSED_0x020..0x022`. Trainer ids 855–858 use four of the nine trainer flags still free in the Hoenn band (do not add more than 5 further Hoenn-band trainers).

## Verified

- Headless tests: `scripts/test.sh` runs [test/confluence.c](../test/confluence.c) (badge counting across regions, level cap table and Apex lift, Meridian and Apex gates, Resonance counting, trainer id range). 7 of 7 pass.
- Played in the embedded emulator (`scripts/play.sh` + `mgba-agent`): new game, Olivine conductor dialogue with the 4-entry menu, circuit report (2 of 24 badges, cap 24), ride to Slateport Harbor, Slateport conductor, Apex warden refusal with 2 badges and the first Apex battle (Kestrel) with 24 badges.

## Not done yet (honest list)

- Gym/trainer **scaling**: opponents keep their original levels; only the player's level cap follows badges.
- **Resonance weather anomalies** and catastrophes; the legends are the stock static encounters (Johto's beasts are not roaming, see [MISSING.md](../MISSING.md)).
- The **Convergence Crisis story**: the syndicate, Rocket/Magma/Aqua alliance, Great Meridian lore scenes. No scripted storyline exists yet.
- A Meridian **train station map**/animation (the line is a warp today), HM field moves as key items, Hall of Fame and credits for the Apex Summit, the Mt. Silver summit arena (the fights run from the warden in front of the cave).
- Everything listed in [MISSING.md](../MISSING.md) for the Johto and Kanto conversions.

## Tooling

`scripts/setup.sh` (toolchain check, native tools, `.venv`, optional Node.js/Go), `scripts/build.sh`, `scripts/test.sh`, `scripts/play.sh`. The tools in the repository-level `tools/` folder (poke-migrator-pro, pokeemerald-ai-bridge, porymap, porytiles, poryscript, porypal, agbcc) are the ones the base hack was created with; `mgba-agent/` in this folder is retargeted at `pokeconfluence.gba` and `pokeconfluence.elf`.
