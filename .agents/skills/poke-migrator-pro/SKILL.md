---
name: poke-migrator-pro
description: Operational guide for the 53 Python CLI tools in tools/poke-migrator-pro/bin/ for map, tileset, palette, and script migration. Activates when running poke-* commands.
---

# Poke-Migrator-Pro Operational Skill

The `tools/poke-migrator-pro/` suite contains 53 production-grade CLI tools designed to extract, convert, analyze, and migrate assets between Gen 1/2/3 games and `pokeconfluence`.

## Tool Inventory & Capabilities

All tools reside in [tools/poke-migrator-pro/bin/](file:///home/mosberg/wsl_projects/pokemon/tools/poke-migrator-pro/bin/).

### 1. Map & Script Extraction / Migration
- `poke-map-extract`: Extracts maps from GBC pokecrystal or GBA pokefirered into modern JSON layouts.
- `poke-crystal-maps`: Extracts all 383 Crystal maps, blocks, and event structures.
- `poke-script-convert`: Converts GBC asm scripts to GBA `.inc` or `.pory` bytecode scripts.
- `poke-crystal-scripts`: Translates Crystal script bytecode, handling conditional events and item giving.
- `poke-event-merge`: Merges object events, warp points, and background events into target map JSONs.

### 2. Palette & Graphics Processing
- `poke-palette-shift`: Fixes the GBA transparent pixel 0 bug by shifting opaque color 0 to color 1..4.
- `poke-palette-fit`: Remaps 8-palette GBC tilesets into GBA secondary palette slots (6..12).
- `poke-assets`: Manages trainer front/back pics, icons, overworld sprites, and animation frames.
- `poke-tileset-convert`: Converts raw tile blocks into 16x16 metatiles with collision attributes.

### 3. Engine Analysis & Integrity Auditing
- `poke-audit`: Scans maps and code for out-of-range IDs, missing text labels, or overflowed limits.
- `poke-doctor`: Automated health check diagnosing broken map warps, invalid flags, and missing headers.
- `poke-flag-index`: Scans all `.inc` and `.c` files to map used vs unused engine flags and variables.
- `poke-scan`: Analyzes ROM symbol tables, EWRAM/IWRAM section sizes, and free space buffers.
- `poke-inspect`: Interactive inspector for saveblock offsets, map headers, and trainer data structures.

### 4. Build & Verification Wrappers
- `poke-wsl-build`: WSL-optimized multi-core build orchestrator with real-time error filtering.
- `poke-build-debug`: Builds debug ROM targets with extra assertion checks and symbol maps.
- `poke-emulator`: Launches embedded mGBA with remote GDB socket debugging enabled.
- `poke-play`: Executes automated playtests and controller replay logs against the mGBA core.

## Standard Execution Pattern
```bash
# Example: Audit flags across pokeconfluence
python3 /home/mosberg/wsl_projects/pokemon/tools/poke-migrator-pro/bin/poke-flag-index /home/mosberg/wsl_projects/pokemon/pokeconfluence

# Example: Run doctor diagnostics
python3 /home/mosberg/wsl_projects/pokemon/tools/poke-migrator-pro/bin/poke-doctor /home/mosberg/wsl_projects/pokemon/pokeconfluence
```

