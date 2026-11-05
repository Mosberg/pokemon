#!/usr/bin/env bash
# Starts the embedded GBA emulator as a bridge server on 127.0.0.1:<port> (default 8888) so that the mgba-agent scripts,
# the MCP server and the VS Code extension can drive the ROM without a desktop emulator.
#   scripts/play.sh [port] [--live]
# Then e.g.:  MGBA_BRIDGE_PORT=8888 .venv/bin/python mgba-agent/new_game_kanto.py
# Any desktop mGBA (>= 0.10) can also open pokeconfluence.gba directly.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TOOLS="$(cd "$ROOT/.." && pwd)/tools"
export PATH="$HOME/.local/bin:$PATH"
PORT="${1:-8888}"
shift || true

[[ -f "$ROOT/pokeconfluence.gba" ]] || { echo "build the ROM first: scripts/build.sh" >&2; exit 1; }
command -v node >/dev/null || { echo "node not found: scripts/setup.sh --extras" >&2; exit 1; }
exec python3 "$TOOLS/poke-migrator-pro/bin/poke-emulator" --rom "$ROOT/pokeconfluence.gba" --port "$PORT" \
    --ext "$TOOLS/pokeemerald-ai-bridge" "$@"
