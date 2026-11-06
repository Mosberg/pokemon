# LIMITS & ENGINE CONSTRAINTS

Hard limits (engine, format, tooling, save space) tracked while building **Pokémon Confluence Version**. Each entry documents the limit, its source, current status, and resolution/workaround.

---

## 1. Engine Limits (pokeemerald-expansion)

| Limit | Value | Current Status & Workaround |
|:---|:---|:---|
| **Map sections (`MAPSEC_*`)** | `u8`, max 253 (`0x00..0xFC`). `0xFD..0xFF` reserved for met locations (`METLOC_SPECIAL_EGG`, `METLOC_IN_GAME_TRADE`, `METLOC_FATEFUL_ENCOUNTER`). | **Resolved / At Capacity (253/253)**. Reclaimed duplicate Johto underground path section into Kanto `MAPSEC_UNDERGROUND_PATH`. Zero collision risk with `METLOC_SPECIAL_EGG` (0xFD). |
| **Map number in a group** | `s8` in `WarpData` (<= 127, group IDs < 127). | **Resolved**. Johto maps are cleanly partitioned into 4 groups (`gMapGroup_Johto1..4`) of <100 maps each. Maps 83 and 84 in `gMapGroup_Johto4` are `MeridianStation_Johto` and `ApexSummit_Johto`. |
| **Object events per map** | 64 (`OBJECT_EVENT_TEMPLATES_COUNT`). | **Compliant**. Peak map is Route 111 with 46 objects. All 383 Johto maps strictly within the 64-object ceiling. |
| **Metatiles** | 512 primary + 512 secondary; secondary palette slots 6–12. | Crystal tilesets converted to 4x4-tile blocks -> 4 metatiles, remapped into secondary slots with transparent pixel 0 preserved. |
| **Tile pixel 0** | Strictly transparent on GBA hardware. | Shifted opaque index 0 pixels to 1–4 across all converted tilesets, sprites, and trainer pics. |
| **Coord events** | Requires explicit variable condition (`var`, `var_value`). | Scene triggers use per-map `VAR_JOHTO_SCENE_*`. |
| **Trainer sight battles** | Script must start with `trainerbattle` command. | Johto trainer scripts emit directly without outer `lockall` wrapper. |
| **ON_TRANSITION scripts** | Runs before map objects exist. | Callback scripts restricted strictly to flag clearing/setting to prevent black-screen hangs. |
| **Trainer IDs & Bands** | Hoenn band ends at 863; partner band starts at 864+. | Johto trainers (855–862) use free Hoenn slots; remaining 541 trainers use extended party indexes. |
| **Region detection** | `GetCurrentRegion()` checks map section for Hoenn/Kanto and map groups for Johto (`gMapGroup_Johto1..4`). | Multi-region context handles obedience, wild battle themes, trainer back pics, and PokéNav/PokéGear toggles dynamically. |
| **Time of Day & Lighting** | `OW_TIMES_OF_DAY`, `OW_ENABLE_DNS` in `include/config/overworld.h`. | Supports authentic Day/Night System (DNS) palette shading and time-of-day encounter fallback. |

---

## 2. Save-Data Limits

| Limit | Value | Allocation & Current Status |
|:---|:---|:---|
| **SaveBlock1** | 15,872 bytes (4 sectors). | **13.8 KB used** (~2 KB headroom remaining after `FREE_*` optimizations). |
| **SaveBlock2** | 3,968 bytes. | **3,884 bytes used** (84 bytes headroom). |
| **Event flags** | Hoenn 300 + Kanto 91 + Kanto trainers 624 + Johto 1472 + Johto trainers 560. | `FLAGS_COUNT` extended cleanly in `flags.h` and saved in 723-byte bit array. |
| **Johto event flags** | 1,472 flag band. | **1,294 allocated** (item balls, hidden items, cut trees, story events). 178 flags free. |
| **Johto scene vars** | 128 variables (`0x4140..0x41BF`). | One allocated per map with story scenes. |
| **Johto trainer flags** | 560 flag band. | **541 allocated**, 19 flags free. |
| **ROM Size** | 32 MB cart ceiling. | **19,276,004 bytes used (57.45%)**. Over **12.7 MB free space** remaining. |
| **EWRAM / IWRAM** | 256 KB EWRAM / 32 KB IWRAM. | EWRAM: 85.87% (225 KB) / IWRAM: 86.65% (28.4 KB). |

---

## 3. Crystal -> GBA Conversion Fidelity

| Feature | Status | Implementation Details |
|:---|:---:|:---|
| **Trainer Battle Pictures** | **Implemented** | 16 authentic GBC front pics (Gym Leaders Falkner, Bugsy, Whitney, Morty, Chuck, Jasmine, Pryce, Clair, Will, Karen, Champion Lance, Silver, Sage Li, Kimono Girl, Officer Jenny, Cal) converted to centered 64x64 4bpp with `.gbapal` palettes via `poke-crystal-graphics`. |
| **Player Back Pictures** | **Implemented** | Authentic Ethan (Chris) and Kris 48x48 back pics converted to 64x64 4bpp with palette, wired to `PlayerGetTrainerBackPicId()` in Johto. |
| **Overworld Sprites** | **Implemented** | 13 custom GBC overworld NPC sheets converted to 144x32 4bpp 9-frame sheets in `graphics/object_events/pics/people/`. |
| **Soundtrack & Audio** | **Implemented** | 25 authentic GBC chiptune tracks converted from ASM -> MIDI -> M4A via `poke-crystal-audio` with `mid2agb`, wired across 33 Johto map headers and wild/trainer encounter BGM. |
| **Prompt Glyphs & Badges** | **Implemented** | Authentic GBC down-arrow prompt glyph integrated in text engine; 8 authentic Crystal badges rendered on Trainer Card with L/R region cycling. |
| **Fishing Encounters** | **Implemented** | Old, Good, and Super Rod encounter tables generated across 149 Johto water maps. |
| **Link & Facility Stubs** | **Implemented** | 0 remaining stubs. Johto 2F Mystery Gift delivery officer, link waiting rooms, and Battle Tower challenge progression cleanly converted. |

---

## 4. Subsystems Targeted for Expansion

All 6 primary expansion subsystems have been fully implemented, integrated, and verified:

1. **Morning & Night Encounter Sets**: Discrete morning, day, and night encounter tables active for all Johto maps in `wild_encounters.json` & `.h` via `OW_TIME_OF_DAY_ENCOUNTERS`.
2. **Headbutt Tree Encounters**: Authentic GBC tree metatile interaction (`MB_HEADBUTT_TREE`), tree coordinate scoring formula, asleep wild mon logic, and 7 table types.
3. **Roaming Legendary Beasts**: Overworld roaming network across 16 Johto routes for Raikou and Entei with flee AI, persistent status, and authentic battle BGM.
4. **Day-of-Week Overworld Events**:
   - Friday Lapras in Union Cave B2F with weekly midnight respawn.
   - All 7 Weekday Siblings with type-enhancing held item rewards.
5. **Lake of Rage Red Gyarados Event**: Level 30 forced-shiny `SPECIES_GYARADOS` battle, Lance reveal, and Mr. Pokémon Red Scale trade for Exp. Share.
6. **Full Bug-Catching Contest Minigame**: 20-minute (500 steps) timer, 20 Park Balls, authentic species/level/IV/HP judging algorithm, and prize distribution.
7. **Ruins of Alph Secret Riddle Chambers**: Secret chambers open upon solving authentic puzzle riddles (Escape Rope, Flash/Field Kit, Water Stone, Ho-Oh).
