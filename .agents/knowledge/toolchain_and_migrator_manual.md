# Complete Toolchain & Migration Engineering Manual

## 1. Toolchain Overview

The repository integrates a comprehensive suite of native and cross-platform tools located in `/home/mosberg/wsl_projects/pokemon/tools/`.

```
tools/
├── poke-migrator-pro/      # 53 Python CLI tools for map, tileset, and script migration
├── porymap/                # Visual GBA Map, Event, and Connection Editor
├── porytiles/              # Modern RGBA -> GBA Dual-Layer Tileset Compiler
├── poryscript/             # High-level scripting dialect compiler for GBA event scripts
├── porypal/                # GBA Palette assignment and slot allocation tool
└── agbcc/                  # Ancient GNU C Compiler (GCC 2.95) targeting GBA ARM7TDMI
```

## 2. Poke-Migrator-Pro Tool Suite
Located in [tools/poke-migrator-pro/bin/](file:///home/mosberg/wsl_projects/pokemon/tools/poke-migrator-pro/bin/):
- **Map Extraction & Assembly**:
  - `poke-crystal-maps`: Extracts all 383 Crystal map layouts, connection matrices, and block sets.
  - `poke-map-extract`: Deconstructs ROM map headers and metatile structures into JSON format.
  - `poke-event-merge`: Merges object events, warps, and trigger coordinates into target map JSON files.
- **Script Translation**:
  - `poke-script-convert`: Converts GBC assembly scripts to GBA `.inc` bytecode macros.
  - `poke-crystal-scripts`: Disassembles Crystal script bytecodes, handling special registers and flags.
- **Palette & Visual Processing**:
  - `poke-palette-shift`: Shifts 4-color tiles so that opaque color 0 avoids GBA hardware transparency.
  - `poke-palette-fit`: Remaps 8-palette GBC tilesets into GBA secondary slots (slots 6..12).
  - `poke-assets`: Manages trainer sprites, Pokémon front/back frames, and icon palettes.
- **Diagnostics & Testing**:
  - `poke-audit`: Comprehensive integrity audit checking for dangling warp pointers and flag collisions.
  - `poke-doctor`: Automated health check diagnosing broken map warps, invalid flags, and missing headers.
  - `poke-flag-index`: Scans all `.inc` and `.c` files to map used vs unused engine flags and variables.
  - `poke-wsl-build`: WSL-optimized multi-core build orchestrator with real-time error filtering.
  - `poke-emulator`: Launches embedded mGBA with remote GDB socket debugging enabled.

## 3. Porytiles Dual-Layer Compilation
`porytiles` compiles dual-layer 16x16 metatiles from raw RGBA PNG artwork:
- Layer 1 (bottom): Ground terrain, water, flooring.
- Layer 2 (top): Walls, tree canopies, rooftops, overhead archways.
- Enforces color counts (max 15 colors + 1 transparent color per palette slot).

## 4. Headless Testing with mGBA & Python
- Headless mGBA test harness is implemented in `pokeconfluence/mgba-agent/`.
- Runs via `pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests`.
- Enables rapid automated playtesting without launching GUI windows.

