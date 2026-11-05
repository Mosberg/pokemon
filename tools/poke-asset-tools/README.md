# GBA Retro Asset Pipeline & Compilation Suite (`poke-asset-tools`)

A production-grade collection of 38 CLI tools and shared libraries for GBA ROM hacking, pixel art processing, audio compiling, map auditing, and engine integration for **Pokémon Confluence** and `pokeemerald-expansion`.

## Master Orchestrator

Run all commands through the unified master CLI:
```bash
python3 tools/poke-asset-tools/bin/gba_romhack_toolkit.py <command> [args...]
# Or via symlink in tools/poke-migrator-pro/bin:
poke-toolkit <command> [args...]
```

## Tool Categories & Catalog

### 1. Sprites & Shinies
- **`gba_asset_tool.py` (`poke-asset-tool`, `toolkit sprite`)**: 15-bit color snapping, 15-color quantization (+ transparency at slot 0), outputs indexed PNG, JASC-PAL, and 4bpp C header.
- **`split_overworld.py` (`poke-split-ow`, `toolkit split-ow`)**: Splits overworld sprite sheets into directional frames or horizontal decomp strips.
- **`harmonize_palette.py` (`poke-harmonize-palette`, `toolkit harmonize`)**: Harmonizes multiple sprites into a single shared 15-color palette using Euclidean distance in GBA 15-bit color space.
- **`pal_converter.py` (`poke-pal-converter`, `toolkit pal-convert`)**: Lossless palette format converter between JASC-PAL, Adobe ACT, GBA binary `.gbapal`, and C headers (`.h`).
- **`generate_shiny.py` (`poke-generate-shiny`, `toolkit shiny`)**: Procedural shiny palette generator with HSV rotation, contrast retention, and shadow lock.
- **`species_batch_importer.py` (`poke-species-importer`, `toolkit species-import`)**: Complete batch importer for new Pokémon species (front, back, shiny, icons, footprints, and C registration).
- **`assemble_anim_sprite.py` (`poke-assemble-anim-sprite`, `toolkit anim-sprite`)**: Compiles animated multi-frame Pokémon front sprites with frame delays.
- **`package_trainer_sprites.py` (`poke-package-trainer-sprites`, `toolkit trainer-sprites`)**: Packages 64x64 trainer front and back sprites.
- **`pokedex_asset_tool.py` (`poke-pokedex-asset-tool`, `toolkit pokedex`)**: Generates 16x16 1bpp footprint tiles and height silhouette scale comparisons.

### 2. Tilesets, Metatiles & Maps
- **`map_asset_pipeline.py` (`poke-map-asset-pipeline`, `toolkit map-pipeline`)**: Automated map, layout, metatile compilation, and collision auditor suite.
- **`tile_optimizer.py` (`poke-tile-optimizer`, `toolkit tile-opt`)**: Lossless 8x8 tile deduplicator with hardware X, Y, and XY flip matching.
- **`package_porymap_tileset.py` (`poke-package-porymap-tileset`, `toolkit porymap-tileset`)**: Slices 16x16 metatiles, packages `tiles.png`, `metatiles.bin`, and 16 JASC-PAL files.
- **`check_palette_conflicts.py` (`poke-check-palette-conflicts`, `toolkit check-conflicts`)**: Scans metatiles and tiles for >16 colors, outputting conflict coordinates and debug heatmaps.
- **`verify_map_matrix.py` (`poke-verify-map-matrix`, `toolkit verify-map`)**: Audits map layouts for warp softlocks, elevation boundary violations, and collision traps.
- **`generate_parallax.py` (`poke-generate-parallax`, `toolkit parallax`)**: Slices multi-layer parallax battle backgrounds and generates HBlank interrupt C code.

### 3. Battle & UI
- **`slice_battle_bg.py` (`poke-slice-battle-bg`, `toolkit battle-bg`)**: Slices battle backgrounds into entry bars, player bases, and enemy platforms.
- **`package_battle_ui.py` (`poke-package-battle-ui`, `toolkit battle-ui`)**: Compiles HP boxes, battle text windows, and action selector menus.
- **`build_battle_particles.py` (`poke-build-battle-particles`, `toolkit particle`)**: Compiles move animation particles and 16-step affine rotation tables.
- **`build_summary_and_icons.py` (`poke-build-summary-icons`, `toolkit summary-icons`)**: Compiles 32x32 party menu icons and summary screen layout mockups.
- **`pack_gba_font.py` (`poke-pack-gba-font`, `toolkit font`)**: Packs variable-width or fixed-width font sheets into 1bpp/2bpp binary tables.
- **`package_region_map.py` (`poke-package-region-map`, `toolkit region-map`)**: Packages 240x160 PokéNav/Town Map tiles, metatiles, and player cursor icons.
- **`package_title_screen.py` (`poke-package-title-screen`, `toolkit title-screen`)**: Packages 240x160 title screen backgrounds and logo sprites.
- **`build_ow_effects.py` (`poke-build-ow-effects`, `toolkit ow-effects`)**: Generates water reflections and shadow sprites for overworld NPCs.
- **`render_dynamic_hp.py` (`poke-render-dynamic-hp`, `toolkit hp-bar`)**: Procedural 48px multi-palette battle HUD healthbar renderer and fixed-point C math driver.

### 4. Audio & Sound
- **`gba_audio_pipeline.py` (`poke-gba-audio-pipeline`, `toolkit audio`)**: DirectSound resampler and MIDI soundfont voicegroup compiler.
- **`convert_cry.py` (`poke-convert-cry`, `toolkit cry`)**: Batch Pokémon cry resampler and 8-bit signed PCM formatter.

### 5. Environmental & Shaders
- **`dns_tint_engine.py` (`poke-dns-tint-engine`, `toolkit dns`)**: 24-hour day/night/dusk/dawn and seasonal palette transformation LUT engine.
- **`build_weather_fx.py` (`poke-build-weather-fx`, `toolkit weather`)**: Dynamic multi-weather particle and fog generator.

### 6. Engine, Scripting & Saves
- **`gba_save_analyzer.py` (`poke-gba-save-analyzer`, `toolkit save`)**: GBA save file, saveblock, checksum, and RTC state inspector.
- **`pory_compiler.py` (`poke-pory-compiler`, `toolkit pory-compile`)**: Poryscript transpiler to decomp ASM (`.inc`) and XSE bytecode.
- **`tmeff_matrix.py` (`poke-tmeff-matrix`, `toolkit tm-matrix`)**: TM/HM species compatibility matrix generator and HTML viewer.
- **`validate_encounters.py` (`poke-validate-encounters`, `toolkit encounters`)**: Wild encounter rate and species ID validator.
- **`trainer_party_builder.py` (`poke-trainer-party-builder`, `toolkit trainers`)**: Compiles YAML/JSON trainer configurations into C structs.
- **`inspect_rom_map.py` (`poke-inspect-rom-map`, `toolkit rom-map`)**: GNU linker `.map` file memory and symbol analyzer.
- **`mart_compiler.py` (`poke-mart-compiler`, `toolkit mart`)**: Poké Mart and vendor inventory compiler.
- **`charmap_converter.py` (`poke-charmap-converter`, `toolkit charmap`)**: Multi-language text converter to proprietary GBA charsets.
- **`rom_patcher.py` (`poke-rom-patcher`, `toolkit patch`)**: Production BPS and IPS patch creator and applier with CRC32 checks.

## Architecture & Integration

All tools import `asset_common.py`, which provides:
- Automatic environment bootstrap (re-executing inside `pokeconfluence/.venv` if Pillow/NumPy are missing).
- Native 15-bit GBA color snapping (`snap_to_gba_15bit`, BGR555 conversion).
- Palette format I/O (JASC-PAL, Adobe ACT, binary GBAPAL, and C header arrays).
- Hardware tile transforms (X-flip, Y-flip, XY-flip) and MSE difference matching.

