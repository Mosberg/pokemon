#!/usr/bin/env bash
# POKE-CONFLUENCE CI/CD Rebuild & Replay Automated Pipeline
# Rebuilds the ROM, executes headless unit tests, runs script/limit audits,
# runs pytest integration suite, and replays the Johto opening flow.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
WORKSPACE_DIR="$(cd "${PROJECT_DIR}/.." && pwd)"

echo "=========================================================="
echo " Pokémon Confluence CI/CD Pipeline"
echo " Workspace: ${WORKSPACE_DIR}"
echo " Project:   ${PROJECT_DIR}"
echo "=========================================================="

echo ""
echo "[1/6] Building pokeconfluence ROM..."
make -C "${PROJECT_DIR}" -j"$(nproc)"
cp -f "${PROJECT_DIR}/pokeemerald.gba" "${PROJECT_DIR}/pokeconfluence.gba" 2>/dev/null || true
echo "✓ ROM built successfully: $(ls -lh "${PROJECT_DIR}/pokeconfluence.gba" | awk '{print $5}')"

echo ""
echo "[2/6] Running headless C unit test suite..."
bash "${PROJECT_DIR}/scripts/test.sh"
echo "✓ C unit tests passed."

echo ""
echo "[3/6] Running Johto script structural auditor..."
python3 "${PROJECT_DIR}/scripts/audit_johto_scripts.py"
echo "✓ Script auditor passed."

echo ""
echo "[4/6] Running engine & hardware limits auditor..."
python3 "${WORKSPACE_DIR}/.agents/scripts/check_limits.py"
echo "✓ Limits auditor passed."

echo ""
echo "[5/6] Running pytest emulator & flow test suites..."
if [ -f "${PROJECT_DIR}/.venv/bin/pytest" ]; then
    "${PROJECT_DIR}/.venv/bin/pytest" "${PROJECT_DIR}/mgba-agent/tests" -v
else
    pytest "${PROJECT_DIR}/mgba-agent/tests" -v
fi
echo "✓ Pytest suite passed."

echo ""
echo "[6/6] Replaying Johto opening flow via headless emulator agent..."
python3 "${PROJECT_DIR}/mgba-agent/johto_regression.py" "${PROJECT_DIR}" --port 8919 --only elm,mrpokemon,itemball,cut,egg
echo "✓ Johto opening replay completed successfully."

echo ""
echo "=========================================================="
echo " All Pokémon Confluence CI/CD checks PASSED cleanly! 🚀"
echo "=========================================================="

