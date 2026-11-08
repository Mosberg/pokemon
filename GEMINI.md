# Pokémon Workspace Agent Guidelines (GEMINI.md)

This workspace contains the complete development environment for **Pokémon Confluence Version** (`pokeconfluence`), the multi-region GBA ROM hack (Hoenn + Kanto + Johto) built on `pokeemerald-expansion`, alongside reference decompilations (`pokecrystal`, `pokeyellow`, `pokefirered`, `pokeemerald`), tooling (`poke-migrator-pro`, `porymap`, `porytiles`, `poryscript`, `porypal`), and the headless test & mGBA agent harness.

## Workspace Layout

```
/home/mosberg/wsl_projects/pokemon/
├── pokeconfluence/               # Primary ROM project (multi-region pokeemerald-expansion)
│   ├── include/                  # C header files & configurations
│   ├── src/                      # C source code (confluence.c, johto_scripts.c, etc.)
│   ├── data/maps/                # Map layouts, headers, and event scripts (.inc/.pory)
│   ├── data/scripts/             # Overworld & system scripts (confluence.inc, johto_common.inc)
│   ├── docs/                     # Design docs (CONFLUENCE.md, STYLEGUIDE.md, tutorials/)
│   ├── scripts/                  # Build, test, and emulator launch scripts
│   ├── mgba-agent/               # Headless Python mGBA emulator test agent
│   └── test/                     # C headless unit/integration test suite
├── tools/                        # Conversion & map editing tools
│   ├── poke-migrator-pro/        # 53 Python CLI tools for map, tileset, & script migration
│   ├── porymap/                  # GBA map editor
│   ├── porytiles/                # Modern RGBA -> GBA tileset compiler
│   ├── poryscript/               # High-level scripting compiler
│   └── porypal/                  # GBA palette assignment tool
├── games/                        # Reference disassemblies & decompilations
│   ├── gbc/pokecrystal/          # Gen 2 reference for Johto events, audio, & tilesets
│   ├── gbc/pokeyellow/           # Gen 1 reference
│   ├── gba/pokefirered/          # Gen 3 FRLG reference
│   └── gba/pokeemerald/          # Vanilla Emerald reference
└── .agents/                      # Antigravity customization suite (rules, skills, knowledge, hooks)
```

## Core Principles & Coding Standards

1. **POKE-CONFLUENCE Tagging**: All custom logic, overrides, and additions in `pokeconfluence` must be labeled with `// POKE-CONFLUENCE` comments to maintain traceability against upstream `pokeemerald-expansion`.
2. **C Styleguide Compliance**:
   - PascalCase for functions (`Confluence_CountBadges`) and structs (`struct ConfluenceState`).
   - camelCase for variables (`badgeCount`) and struct fields.
   - Global variables prefixed with `g` (`gPlayerPartyCount`), static variables with `s` (`sFieldKitMoves`).
   - Constants/macros UPPER_SNAKE_CASE (`FLAG_CONFLUENCE_APEX_CHAMPION`).
   - 4 spaces for indentation (no tabs in `.c`/`.h`).
   - Allman bracing style: opening curly braces on their own line.
3. **Engine Limits Enforcement**:
   - `MAPSEC_*` limit: Maximum 253 usable (0x00..0xFC). 0xFD-0xFF are reserved for met locations (`METLOC_SPECIAL_EGG`, `METLOC_IN_GAME_TRADE`, `METLOC_FATEFUL_ENCOUNTER`).
   - Map group sizes: `s8` warp map number in `WarpData` requires <= 127 maps per map group. Johto is grouped into `gMapGroup_Johto1..4`.
   - Object events per map: Max 64 (`OBJECT_EVENT_TEMPLATES_COUNT`).
   - Metatile limits: 512 primary + 512 secondary metatiles. Secondary palette slots 6-12. Pixel 0 is strictly transparent.
   - Trainer IDs: IDs 855-862 use free slots in the Hoenn band. ID 863 is the last free slot before the partner trainer band (864+).
4. **Build & Test Verification**:
   - Always verify compilation with `make -C pokeconfluence -j$(nproc)` before claiming completion.
   - Always run the headless test suite with `bash pokeconfluence/scripts/test.sh`.
   - Always run the limit auditor with `python3 .agents/scripts/check_limits.py`.
   - Always run the event script auditor with `python3 .agents/scripts/audit_scripts.py`.
   - Run python emulator tests with `pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests`.
   - Run full workspace health audits with `python3 .agents/scripts/workspace_doctor.py`.

