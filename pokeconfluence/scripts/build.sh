#!/usr/bin/env bash
# Builds pokeconfluence.gba (Hoenn + Kanto + Johto + the Confluence layer).
#   scripts/build.sh            normal build
#   scripts/build.sh release    optimised release build (pokeconfluence-release.gba)
#   scripts/build.sh clean      remove build output
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

case "${1:-}" in
    clean)   make clean BUILD=confluence; exit 0 ;;
    release) make -j"$(nproc)" confluence RELEASE=1 ;;
    "")      make -j"$(nproc)" confluence ;;
    *)       echo "usage: $0 [release|clean]" >&2; exit 2 ;;
esac

# The addresses of the mgba-agent tools follow the build.
if [[ -x .venv/bin/python && -f pokeconfluence.elf ]]; then
    (cd mgba-agent && "$ROOT/.venv/bin/python" refresh_addresses.py ../pokeconfluence.elf >/dev/null)
fi
ls -l pokeconfluence*.gba
