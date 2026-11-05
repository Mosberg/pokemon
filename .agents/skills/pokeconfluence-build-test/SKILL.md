---
name: pokeconfluence-build-test
description: Builds the Pokémon Confluence ROM, runs headless C integration tests, and executes unit tests. Activates whenever building, compiling, or verifying pokeconfluence.
---

# Pokémon Confluence Build & Test Skill

This skill guides building the Pokémon Confluence ROM, executing C test suites, running pytest harnesses, and diagnosing build failures.

## Quick Runbook

```bash
# Compile pokeconfluence ROM
make -C pokeconfluence -j$(nproc)

# Run headless C integration tests
bash pokeconfluence/scripts/test.sh

# Run pytest unit test suite
pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests
```

## Detailed Build Instructions

1. **Target Artifacts**:
   - `pokeconfluence/pokeconfluence.gba`: GBA ROM image (header title `POKECONFLUEN`, game code `BPEE`).
   - `pokeconfluence/pokeconfluence.elf`: ELF binary with debug symbols used for symbol table parsing and address resolution.

2. **Parallel Compilation**:
   - Use `make -C pokeconfluence -j$(nproc)` for multi-threaded builds.
   - If clean build is required: `make -C pokeconfluence clean && make -C pokeconfluence -j$(nproc)`.

3. **Diagnosing Compilation Errors**:
   - Missing symbols in `.inc` scripts: Check `include/constants/` headers to verify flag, var, or special macro spelling.
   - Undefined reference in C linking: Ensure the function definition is marked with proper linkage and not shadowed by an internal `static` keyword.
   - Deprecated warnings (e.g. `gPlayerPartyCount`): In pokeemerald-expansion, prefer `gPartiesCount[B_TRAINER_PLAYER]` where supported, or verify `gPlayerPartyCount` compatibility.

4. **Headless C Test Suite**:
   - Source: [test/confluence.c](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/test/confluence.c)
   - Runner: [scripts/test.sh](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/scripts/test.sh)
   - Evaluates:
     - 24-badge accumulation (`test_badge_counting`)
     - Badge-count level cap table (`test_level_cap_table`)
     - Apex Summit level cap lift to 100 (`test_apex_level_cap_lift`)
     - Meridian Transit gate badge checks (`test_meridian_transit_gate`)
     - Apex Summit entry prerequisites (`test_apex_summit_gate`)
     - Resonance legend calming count (`test_resonance_counting`)
     - Apex Summit trainer ID allocations (`test_apex_trainer_ids`)
     - Gym leader / Elite Four scaling boost (`test_trainer_level_boost`)
     - Resonance weather anomaly dispatch (`test_weather_anomalies`)
     - Field Kit move retrieval (`test_field_kit_moves`)
     - Yellow gift starters flags and generation (`test_yellow_gift_starters`)

