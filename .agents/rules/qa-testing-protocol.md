---
description: Quality assurance and testing protocol for Pokémon Confluence
globs: pokeconfluence/test/**, pokeconfluence/mgba-agent/**
---

# QA Testing & Verification Protocol

No code may be marked completed without passing the full verification suite.

## 1. Test Levels
1. **Compilation Level**:
   - `make -C pokeconfluence -j$(nproc)` must return exit code 0.
   - Zero compilation errors. Deprecation warnings must not hide syntax or memory faults.
2. **C Headless Unit Tests**:
   - Executed via `bash pokeconfluence/scripts/test.sh`.
   - Tests defined in `pokeconfluence/test/confluence.c`.
   - Verifies badge calculation, level cap bounds, Meridian transit gates, Apex summit triggers, gym leader boosts, weather anomaly dispatch, and Field Kit move queries.
   - All 11 tests must report `PASS`.
3. **Limit Auditing**:
   - Executed via `python3 .agents/scripts/check_limits.py`.
   - Confirms `MAPSEC <= 253`, `object_events <= 64`, trainer IDs within valid bounds, and reports remaining script stubs.
4. **Emulator Python Harness**:
   - Executed via `pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests`.
   - Verifies memory map offsets, RAM state reads, and ROM header integrity.

## 2. Regression Testing Runbook
Whenever any changes are made to core files (`src/confluence.c`, `src/caps.c`, `src/party_menu.c`, `src/johto_scripts.c`, `data/scripts/confluence.inc`):
```bash
python3 .agents/scripts/check_limits.py
make -C pokeconfluence -j$(nproc)
bash pokeconfluence/scripts/test.sh
pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests
```

