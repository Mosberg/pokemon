# mgba-agent: AI control and RL toolkit for pokemultiregion.gba

Everything from `.docs/To give LLM tools and coding agents like.md`, rebuilt for **this** ROM
(`../pokemultiregion/pokemultiregion.gba`, Emerald-based pokeemerald-expansion with Kanto added).

The document used vanilla FireRed v1.0 addresses. Those are wrong for this ROM, so every address and
struct offset here comes from the real build (`addresses.py`; `refresh_addresses.py` regenerates the
symbol addresses after a rebuild). Other corrections to the document are listed at the bottom.

## Pieces

| File | What it is |
| --- | --- |
| `lua/mgba_agent_bridge.lua` | TCP control server that runs inside mGBA (read/write RAM, buttons, frames, screenshots, states) |
| `lua/watcher.lua` | logs map, tile, battle flag and lead HP once a second |
| `mgba_client.py` | Python client for the bridge |
| `mgba_mcp_server.py` | MCP server: memory, buttons, screenshots, savestates, `game_state`, `party`, `battle_state` |
| `agent_common.py`, `gemini_agent_loop.py`, `lmstudio_agent_controller.py` | screenshot + RAM agents (Gemini, local LM Studio with A* `goto`) |
| `pkmn_decrypt.py` | 100-byte `struct Pokemon` decoder (expansion's bit-packed layout) |
| `battle_engine.py` | `gBattleMons` parser, outcome and status flags |
| `pathfinding.py` | collision map from `gBackupMapLayout` plus A* |
| `memory_patcher.py` | money, bag items, event flags, best-effort warp |
| `headless_mgba.py`, `mgba_gym_env.py` | headless core and Gymnasium env (9 actions, screen + 9 telemetry values) |
| `train_distributed.py`, `curriculum_engine.py`, `custom_policy.py` | PPO over `SubprocVecEnv`, flag-based curriculum, Impala CNN + frame stack |
| `evaluate_policy.py`, `export_onnx.py`, `onnx_runner.py` | live HUD evaluation, ONNX export, ONNX Runtime inference |
| `tests/test_units.py` | offline tests (decrypt, battle parse, A*, collision parse, flag ids) |

## Which emulator

The bridge protocol is served by **either** native mGBA (Lua script) **or** the embedded emulator of the VS Code extension
(`bin/poke-emulator --rom <game.gba> --port 8899`, see `knowledge/embedded-emulator.md`). Python tools use port 8888 by default;
set `MGBA_BRIDGE_PORT=<port>` to attach to another one. Save-state files are emulator-specific.
Struct offsets in `addresses.py` (SB1 flags 0x123C, vars 0x1510) must be re-measured with the build's ABI flags whenever a flag/var band changes (`knowledge/gotchas.md`).

## Quick start

1. Install: `pip install -r requirements.txt`
2. Open the ROM in mGBA, then **Tools -> Scripting -> File -> Load script** and pick `lua/mgba_agent_bridge.lua`.
   The scripting console prints `listening on port 8888`.
3. Register the MCP server with Claude Code:
   `claude mcp add mgba -- python C:/Projects/Games/Poke-Migrator/mgba-agent/mgba_mcp_server.py`
   (other clients: `{"mcpServers": {"mgba": {"command": "python", "args": [".../mgba_mcp_server.py"]}}}`).
4. Offline sanity check: `python -m unittest discover -s tests -v`.

## Bridge protocol

One line per command, one line back (`OK ...` or `ERR ...`): `READ8|16|32 addr`, `WRITE8|16|32 addr value`,
`READBLOCK addr len`, `WRITEBLOCK addr hex`, `PRESS button [frames]`, `SETKEYS mask`, `STEP frames`,
`SCREENSHOT path`, `SAVESTATE n`, `LOADSTATE n`, `SAVEFILE path`, `LOADFILE path`, `FRAME`, `TITLE`.

## Memory map highlights (pokemultiregion)

- `gSaveBlock1Ptr` 0x030051D4 and `gSaveBlock2Ptr` 0x030051D0 are pointers; always dereference.
- SaveBlock1: x/y at +0/+2, map group/num at +4/+5, money +0x490, bag +0x560, flags +0x1270 (392 bytes), vars +0x13F8.
- Money is XORed with SaveBlock2+0xAC (the encryption key); bag quantities with its low 16 bits.
- `gPlayerParty` 0x02031C40 (6 x 100 bytes), `gBattleMons` 0x020004F0 (4 x 140 bytes), `gBattleOutcome` 0x020000D8.
- In battle: bit 1 of the byte at `gMain + 0x439`.
- Badges: Hoenn flags 0x867-0x86E, Kanto 0x961-0x968 (`FLAG_BADGE09_GET`..`16`).

## Corrections to the source document

- Offsets: all FireRed v1.0 addresses replaced (they would read garbage here).
- `status1`/`status2` offsets, stat-stage position and the party struct tail (`level` is followed by a padding byte) were wrong.
- Pokemon data is bit-packed in expansion (species 11 bits, moves 11, item 10, experience 21).
- Bridge: `client:hasdata()` and `emu:runFrame()` in a callback do not exist or recurse; it now uses the documented `received` socket callbacks and a deferred `STEP` reply. `READ16` was used by the agents but missing from the bridge.
- `libmgba` through ctypes cannot work (opaque `mCore`); the headless env uses mGBA's Python bindings.
- SB3's `VecFrameStack` cannot stack just one key of a dict observation (it demands an entry for every key, including the 1-D telemetry), so `vec_wrappers.ScreenFrameStack` stacks only the screen.
- Warping by writing a "pending transition flag" is not how the game works; `warp_player` sets the destination and jumps to `CB2_LoadMap`.

## Verification status (tested against a running mGBA 0.10.5 with this ROM)

Verified live: every bridge command (read/write/blocks/press/step/screenshot/savestate files), money, bag items
and flag patching (offsets confirmed by round trip), `warp_player` (Pallet house -> Vermilion dock), the
collision map plus A* walking, the MCP tools, the Gym env against SB3's `check_env`, a PPO run with the Impala
extractor and frame stack (128 steps), and ONNX export with 20/20 action parity against PyTorch.

Not verified: `party` decoding on a real Pokemon (only synthetic structs, the test save has no party yet),
battle parsing in a real battle, the Gemini and LM Studio loops (need an API key / a local server), the
headless `mgba` bindings (they cannot be installed here: no wheel, no cmake, no sudo in WSL), and long training
runs. Use `backend="bridge"` for the Gym env until the bindings are built:

    PokemonMultiRegionEnv(state_path="states/stage0_start.ss1", backend="bridge")

`states/stage0_start.ss1` is a real savestate in Red's house (Kanto start). Record the other stages with
`record_state.py`.

## Map smoke test

`python map_smoke_test.py ../pokemultiregion --filter _Frlg` warps into every Kanto map and checks the player
arrives and the overworld callback is still running. Result on the current ROM: **414 of 417 clean**. Union Room
shows the expected "no link adapter" error screen; Five Island and Viridian Pokemon Center 1F tripped once
(summary-screen callback) but loaded fine when warped to again, so they look like leftover state from the
previous map rather than map bugs. This proves the maps load; it does not prove their scripts play correctly.

## Playtest log (pokemultiregion)

Played through the bridge: Kanto start -> Pallet Town -> Oak's scene and lab -> Pewter Gym. Camper Liam fights with
his real FireRed team (Geodude lv10 with Tackle/Defense Curl) and sets a flag in the Kanto trainer block, not Hoenn's;
Brock gives the Boulder Badge (`FLAG_BADGE09_GET` set, Hoenn `BADGE01` untouched), prize money and a TM.
`memory_patcher.give_mon` builds a valid party member (checksum + encryption) so a fresh save can fight. The injected
test mon first kept falling asleep: it was level 40 with a foreign OT and 0 badges, i.e. a disobedient traded Pokemon
(thanks for the explanation). `give_mon` now uses the player's own trainer id by default.

Obedience, tested live with a level-18 foreign-OT Pokemon in Kanto: 0 badges -> disobeys (cap 10); Kanto badge 9 ->
obeys (cap 20); Hoenn badge 1 only -> still disobeys. Own-OT level 40 with 0 badges obeys. So the regional obedience
patch reads the right badge set per region. `states/post_brock.ss1` is a savestate right after beating Brock.

## Bugs found while verifying

- The reference feature extractor permuted channels itself, but SB3 already hands the policy channels-first,
  normalised images, so it built a network with 120 input channels. Fixed.
- The bridge bound to every network interface (it can write RAM); it now binds to 127.0.0.1.
- `mcp` 2.x renamed `FastMCP` to `MCPServer`; the server supports both.
