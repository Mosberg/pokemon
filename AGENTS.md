# Pokémon Multi-Agent Engineering Playbook (AGENTS.md)

This document governs autonomous and assisted agents working in `/home/mosberg/wsl_projects/pokemon`. Every agent interacting with this workspace must follow these protocols, verify invariants, and utilize the specialized toolchain.

## Architectural Mandates

### 1. The Multi-Region Map Hierarchy
The world is partitioned across three core regions (Hoenn, Kanto, Johto) plus special transit/apex zones.
- **Hoenn**: Base vanilla maps (`gMapGroup_TownsAndRoutes` etc.).
- **Kanto**: Converted FRLG maps (`gMapGroup_Kanto*`).
- **Johto**: Converted GBC Crystal maps split into groups of 100 (`gMapGroup_Johto1`, `gMapGroup_Johto2`, `gMapGroup_Johto3`, `gMapGroup_Johto4`).
  - *Hard Engine Invariant*: Map numbers in any group must NOT exceed 127 because `WarpData.mapNum` is signed 8-bit (`s8`). Maps 83 and 84 in `gMapGroup_Johto4` are `MeridianStation_Johto` and `ApexSummit_Johto`.
- **Region Identification**: Checked via `GetCurrentRegion()` in [src/confluence.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/confluence.c).

### 2. Badge Progression & Level Caps
- Badges across all three regions (24 total) are aggregated via `Confluence_CountBadges()`.
  - Hoenn: `FLAG_BADGE01_GET` .. `FLAG_BADGE08_GET`
  - Kanto: `FLAG_BADGE09_GET` .. `FLAG_BADGE16_GET`
  - Johto: `FLAG_JOHTO_ENGINE_ZEPHYRBADGE` .. `FLAG_JOHTO_ENGINE_RISINGBADGE`
- Soft level cap table in [src/caps.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/caps.c):
  - 0 badges: 15
  - 8 badges: 48
  - 24 badges: 80
  - Apex Champion (`FLAG_CONFLUENCE_APEX_CHAMPION`): 100 (cap lifted).
- Scaling: Leaders, Elite Four, and Champions scale up dynamically so their highest level matches the player's level cap (never downscaled).

### 3. Meridian Transit & Convergence Crisis
- Fast travel between Slateport (Hoenn), Vermilion (Kanto), and Olivine (Johto) opens at 2 badges.
- Meridian Station (`MeridianStation_Johto`) connects all three platforms.
- Syndicate Enforcers (Rocket, Magma, Aqua) appear at 6 badges. Defeating all three at 12 badges allows challenging the Chairman, clearing Resonance weather anomalies across all three regions.

### 4. Field Kit System
- Replaces HM requirements without taking bag or party slots.
- Handed out as `ITEM_FIELD_KIT`.
- The first non-egg party member receives an automatic `FIELD KIT` action submenu in [src/party_menu.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/src/party_menu.c) allowing Surf, Fly, Flash, Dig, Teleport, Dive, and Waterfall (badge checks still apply).

### 5. Johto Phone Book & Rematches
- All 37 Crystal phone trainers are supported via `JohtoPhoneRegister`, `JohtoPhoneIsRegistered`, and flags in [include/constants/johto_flags.h](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/include/constants/johto_flags.h).
- Rematch counts stored in `VAR_JOHTO_MEM_W*` scale teams across 5 distinct tiers.

---

## Agent Operational Workflows

### Build & Verification Commands
Before submitting any task, the agent must run the verification pipeline:
```bash
# 1. Compile the ROM
make -C pokeconfluence -j$(nproc)

# 2. Run C unit tests
bash pokeconfluence/scripts/test.sh

# 3. Run limit auditor
python3 .agents/scripts/check_limits.py

# 4. Run emulator agent smoke tests (if Python environment is available)
pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests
```

### Pre-Commit Checklist
1. All changes isolated and marked `// POKE-CONFLUENCE` where applicable.
2. No new `MAPSEC_*` added without checking the 253 limit.
3. No map has more than 64 object events in `map.json`.
4. No C file violates Allman braces, 4-space indentation, or PascalCase/camelCase conventions.
5. All newly converted scripts compile clean without syntax errors.

