---
name: pokeconfluence-qa-emulator
description: Automated QA, emulator integration, pytest harnesses, and RAM inspection using mGBA and Python. Activates when running smoke tests, emulator tests, or debugging RAM.
---

# Pokémon Confluence QA & Emulator Skill

This skill guides running automated playtests, inspecting RAM symbols, and executing regression smoke tests via `mGBA` and Python.

## 1. Automated Test Harness (`mgba-agent`)
The test framework is located in [pokeconfluence/mgba-agent/](file:///home/mosberg/wsl_projects/pokemon/pokeconfluence/mgba-agent/).

### Running Unit Tests
```bash
pokeconfluence/.venv/bin/pytest pokeconfluence/mgba-agent/tests
```

### Running Headless Smoke Tests
Smoke tests boot the ROM in headless mGBA, start a new game, execute inputs, and check RAM memory values:
```bash
# Verify Meridian transit, Field Kit, and Apex Summit flow
python3 pokeconfluence/mgba-agent/confluence_smoke.py

# Verify Field Kit party menu integration
python3 pokeconfluence/mgba-agent/field_kit_menu.py

# Verify Johto phone rematch loop and tier progression
python3 pokeconfluence/mgba-agent/johto_phone_rematch.py
```

## 2. Interactive Emulator Playtesting
To launch an interactive session with socket debugging:
```bash
bash pokeconfluence/scripts/play.sh 8921
```
- Starts mGBA listening on port 8921.
- Scripts can connect over IPC/GDB socket to inject button presses, read variables, or trigger save states.

## 3. Key Memory Addresses & Watch Variables
When inspecting RAM with mGBA or Python:
- `gSaveBlock1Ptr`: Overworld coordinates, current map, trainer flags, badge flags.
- `gSaveBlock2Ptr`: Player name, gender, Hall of Fame entries.
- `gSpecialVar_Result` (`0x020370DC` or symbol lookup in `pokeconfluence.elf`): Return value of the last executed `special`.
- `gPlayerParty`: Array of 6 `Pokemon` structs (`100` bytes each).

