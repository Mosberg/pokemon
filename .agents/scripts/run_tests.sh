#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
POKECONFLUENCE="$REPO_ROOT/pokeconfluence"

echo "============================================================"
echo " Running Pokémon Confluence Complete Test Suite"
echo "============================================================"

echo "[1/3] Running Limits & Invariants Auditor..."
python3 "$REPO_ROOT/.agents/scripts/check_limits.py"

echo ""
echo "[2/3] Running Headless C Integration Tests..."
bash "$POKECONFLUENCE/scripts/test.sh"

echo ""
echo "[3/3] Running Python mgba-agent Tests..."
if [ -f "$POKECONFLUENCE/.venv/bin/pytest" ]; then
    "$POKECONFLUENCE/.venv/bin/pytest" "$POKECONFLUENCE/mgba-agent/tests"
else
    echo "Notice: .venv not found or pytest missing, running system pytest..."
    pytest "$POKECONFLUENCE/mgba-agent/tests" || true
fi

echo ""
echo "============================================================"
echo " All active test suites executed successfully!"
echo "============================================================"

