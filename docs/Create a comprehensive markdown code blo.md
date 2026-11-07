Create a comprehensive markdown code block overview of the Foundational Architecture, Core Mechanical, Subsystem Features, Engine Additions, etc that are already implemented and integrated in pokeemerald-expansion and pokeconfluence from all these other decomp games Pokemon Blue, Red, Yellow, Gold, Silver, Crystal, Ruby, Sapphire, Emerald, FireRed, LeafGreen, Emerald Expansion, pokemultiregion and pokeconfluence, ensuring a robust and cohesive framework for all gameplay and system functionalities.

## 1. Core Architecture (The "How")
#low_level_asm, #memory_offsets, #ram_mapping, #vram_management, #interrupt_handlers, #stack_frames, #pointer_tables, #binary_patching, #opcode_optimization, #registers

## 2. Game Logic & Systems (The "What")
#battle_engine, #turn_calculator, #damage_formula, #exp_logic, #type_chart, #status_effects, #move_pool, #ability_triggers, #stat_scaling, #catch_mechanics, #evolution_logic

## 3. World & Environment (The "Where")
#tile_maps, #collision_masks, #event_triggers, #warp_coordinates, #npc_ai_scripts, #flag_system, #global_variables, #field_effects, #coordinate_system

## 4. Data & Assets (The "Stuff")
#sprite_sheets, #palette_swaps, #midi_sequencing, #text_compression, #item_databases, #pokemon_stats_table, #move_data, #cry_assets, #font_rendering

## 5. Interface & UX (The "View")
#menu_navigation, #ui_overlays, #cursor_logic, #dialogue_boxes, #battle_hud, #inventory_screens, #animation_states, #screen_transitions

## 6. Configuration & Metadata (The "Rules")
#save_block_structure, #checksum_validation, #game_version_flags, #difficulty_settings, #global_config, #build_pipeline

The architecture and subsystem features implemented across **`pokeemerald-expansion`** and the **`pokeconfluence`** framework synthesize modern Game Boy Advance decompilation engineering, multi-region game design, and automated developer tooling [cite: 1, 32, 44, 46, 50]. 

---

### 1. Foundational Architecture & Memory Subsystems

* **32 MB ROM Address Space**:
  * Vanilla Pokémon Emerald compiles to a 16 MB boundary (`0x01000000`) [cite: 136, 147, 149].
  * To accommodate the combined maps, tilesets, audio soundfonts, and sprite banks for Kanto, Johto, and Hoenn, the linker script (`ld_script.ld`) and build rules are expanded to a **32 MB cartridge window (`0x02000000` bytes)**, opening address space from `0x08000000` to `0x09FFFFFF` [cite: 82, 136, 149].
* **Hardware RAM Boundaries**:
  * **IWRAM (32 KB at `0x03000000`)**: Reserved for time-critical interrupt service routines (VBlank/HBlank), DMA buffers, and runtime execution stacks [cite: 102, 120, 149].
  * **EWRAM (256 KB at `0x02000000`)**: Houses primary game states, dynamic entity pools, map memory, and battle controllers [cite: 82, 102, 120]. Static assertions prevent `.bss` and heap allocations from crossing the 256 KB limit [cite: 102, 120].
* **Flash 1M Dynamic SaveBlock Allocation**:
  * Vanilla games pack state data into two rotating 4 KB sectors (`SaveBlock1` and `SaveBlock2`) in cartridge Flash [cite: 82, 120, 147].
  * `pokeemerald-expansion` activates **`B_SAVE_EXPANSION`**, decoupling save serialization across unused 128 KB Flash sectors (Sectors 14–31) [cite: 84, 108]. This prevents save corruption while supporting 24 Gym badges, 120+ visited map sections (`regionMapSectionsVisited` bitfield), and expanded Pokédex caught flags [cite: 115, 149].

---

### 2. Multi-Region World & Traversal Infrastructure

* **Tri-Continental World Hierarchy**:
  * Maps are organized into dedicated arrays inside `data/maps/map_groups.json` [cite: 33, 84, 136]:
    * Groups for **Kanto & Sevii Islands** [cite: 84, 136]
    * Groups for **Johto & Mt. Silver** [cite: 136]
    * Groups for **Hoenn & Battle Frontier** [cite: 84, 136]
* **The Great Meridian Transit Line & Inter-Regional Travel**:
  * Connects Kanto, Johto, and Hoenn via a deep-sea tectonic transit network [cite: 46, 50, 135].
  * Narrative gateways allow non-linear regional travel (via the Meridian line, S.S. Tidal/Aqua ferries, Magnet Train, and Route 27/Tohjo Falls corridor) [cite: 33, 51, 88, 140, 144].
* **Multi-Region PokéNav & Fly Subsystem (`src/region_map.c`)**:
  * Replaces the hardcoded \\(28 \times 15\\) single-region grid with an active region state (`REGION_HOENN`, `REGION_KANTO`, `REGION_JOHTO`, `REGION_SEVII`) [cite: 84, 99, 131, 150].
  * Players cycle through regional maps using **L / R trigger buttons** [cite: 99, 108, 131, 150].
  * Regional viewports dynamically swap background tilemaps, cursor coordinate grids, and visited heal locations (`sMapHealLocations`) [cite: 99, 131, 132, 150].
* **Decoupled Badge Obedience & Field Moves**:
  * **Obedience (`src/battle_util.c`)**: Decoupled from vanilla Hoenn flags [cite: 84, 96, 115]. The engine evaluates badge obedience based on the active player region (Badges 1–8 for Hoenn, 9–16 for Kanto, 17–24 for Johto) [cite: 96, 115].
  * **HMs / Field Moves**: Badge requirements for Cut, Surf, Strength, and Waterfall are decoupled from Hoenn milestones, enabling native regional badges (or Key Items) to authorize field traversal without requiring HM slaves [cite: 52, 97, 104, 148].

---

### 3. Core Battle Engine & Modern Mechanics

* **Modern Combat Ruleset (Gen 4–9)**:
  * **Physical/Special/Status Split**: Moves are categorized individually rather than dictated by elemental type [cite: 16, 37, 52, 120].
  * **Fairy-Type Integration**: Type chart matrices, defensive resistances, and offensive multipliers fully integrated [cite: 31, 52, 120].
  * **Battle Gimmicks**: Native framework support for Mega Evolution, Primal Reversion, Ultra Burst, Z-Moves, Dynamax, and Terastallization [cite: 25, 120].
  * **Expanded Battle Assets**: Ability pop-up banners (Gen 5+ style), mid-turn trainer sliding dialogue, modern movepools, and updated ability triggers [cite: 27, 29, 30, 52].
* **Dynamic Scaling & Encounter Engine**:
  * Gym Leader parties, trainer teams, and wild encounter tables evaluate total collected badges (`FLAG_SYS_BADGE_COUNT`), dynamically scaling levels, IV/EV distributions, and AI viability [cite: 35, 51, 135, 140, 144].
  * **Competitive AI Decision Logic**: Upgrades basic vanilla AI to evaluate tactical viability (`AI_SCRIPT_CHECK_VIABILITY`), damage optimization (`AI_SCRIPT_TRY_TO_FAINT`), setup moves, and smart party switching [cite: 35, 97, 110, 128].
* **DexNav Subsystem**:
  * Integrated creeping encounter engine featuring search levels, hidden abilities, guaranteed egg moves, held items, and perfect IV generation rates [cite: 25].

---

### 4. Overworld, Graphics & Level Design Toolchain

* **Porytiles Asset Pipeline**:
  * Overworld tilesets are authored as 32-bit RGBA layers (`bottom.png`, `middle.png`, `top.png`) accompanied by `attributes.csv` [cite: 38, 121].
  * Compiling with `porytiles compile-secondary` locks palettes 0–5 against the primary base (`gTileset_General`), allocating local architectural graphics strictly into background palettes 6–12 without palette bleeding [cite: 38, 102, 121].
* **Palette Management & Sprite Architecture**:
  * Strict adherence to **15-bit BGR555** color depth and **4bpp indexing** (15 active colors + Slot 0 `#FF00FF` transparency) [cite: 121, 122].
  * Normal and shiny palettes (`normal.pal` / `shiny.pal`) maintain synchronized color index mappings to allow dynamic hardware palette swapping without silhouette corruption [cite: 122].
* **Day/Night Cycle (RTC & DNS)**:
  * Tracks hours and minutes via the cartridge Real-Time Clock (RTC) [cite: 35, 148].
  * Applies dynamic palette-tinting shaders over map tilesets for Morning, Day, Dusk, and Night, while adjusting encounter probabilities and nocturnal events [cite: 35, 39, 148].
* **Event Scripting via Poryscript**:
  * Replaces low-level assembly includes with structured C-like syntax (`if`, `else`, `switch`, `while`) compiled directly into native GBA `.inc` bytecode [cite: 34, 41, 121].
  * Features the `format(...)` typography engine, which calculates string breaks dynamically according to font glyph metric widths [cite: 102, 121].

---

### 5. Audio Subsystem

* **GBA "Music Player 2000" (m4a / MP2K) Sound Driver**:
  * Manages simultaneous hardware programmable sound generator (PSG) chiptune channels and DirectSound 8-bit PCM digital channels [cite: 128, 147].
* **Voicegroup Isolation & Sample Stitching**:
  * Prevents instrument clipping and sample collision by isolating regional voice tables (`voicegroup_frlg`, custom GSC soundfonts, and native Hoenn sets) [cite: 82, 108, 109, 136].
  * Sequences arranged in MIDI format are compiled into GBA-native assembly sound tracks (`sound/songs/*.s`) via `mid2agb` [cite: 38, 117, 147].

---

### 6. Automated Tooling, Verification & Telemetry

* **Static Analysis & Build Verification Oracles**:
  * Automated tools audit project health prior to compilation [cite: 100, 102, 108]:
    * **Warp Oracle (`poke_audit_warps.py`)**: Detects orphaned destination maps, out-of-bounds warp IDs, and missing return warps [cite: 100, 108].
    * **RAM Oracle (`tools/ram_check`)**: Asserts that compiled binaries strictly honor the 256 KB EWRAM and 32 KB IWRAM hardware bounds [cite: 102, 108, 111].
* **mGBA AI Bridge & Telemetry Integration**:
  * Headless emulation interfaces (via PyBoy, PyGBA, and mGBA socket/Lua hooks) parse raw memory buses to extract structured JSON data for player inventories, party statistics, and collision walkability grids [cite: 2, 11, 58, 78].
  * Real-time events stream over WebSockets to dashboards (such as the "Field Log" UI) to monitor milestones, battle statuses, and AI decision loops [cite: 2, 12, 58, 59].
* **Continuous Documentation Synchronization**:
  * Repository Markdown files are parsed and transformed into Confluence Storage Format XHTML [cite: 3, 9, 75].
  * Automated GitHub Actions workflows update Atlassian Confluence wiki pages via REST API v2 on PR merge events, keeping live game documentation and technical specifications synchronized without manual drift [cite: 3, 9, 13, 74, 75].
