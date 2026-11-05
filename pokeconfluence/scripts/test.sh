#!/usr/bin/env bash
# Runs the headless mGBA test runner.
#   scripts/test.sh                 Confluence-layer tests (test/confluence.c)
#   scripts/test.sh "<prefix>"      any test-name prefix, e.g. "SaveBlock"
#   scripts/test.sh --all           the whole suite (long)
#   scripts/test.sh --agent         mgba-agent unit tests (python)
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

case "${1:-Confluence}" in
    --all)   make -j"$(nproc)" check BUILD=confluence ;;
    --agent) (cd mgba-agent && "$ROOT/.venv/bin/python" -m pytest -q tests) ;;
    *)       make -j"$(nproc)" check BUILD=confluence TESTS="${1:-Confluence}" ;;
esac
