#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
POKECONFLUENCE="$REPO_ROOT/pokeconfluence"

echo "============================================================"
echo " Building Pokémon Confluence (pokeconfluence.gba)"
echo "============================================================"

NPROC=$(nproc)
echo "[BUILD] Running multi-core build with ${NPROC} threads..."
make -C "$POKECONFLUENCE" -j"${NPROC}"

if [ -f "$POKECONFLUENCE/pokeconfluence.gba" ]; then
    ROM_SIZE=$(stat -c%s "$POKECONFLUENCE/pokeconfluence.gba")
    ROM_MB=$(awk "BEGIN {printf \"%.2f\", $ROM_SIZE / 1048576}")
    echo "[BUILD SUCCESS] pokeconfluence.gba built successfully!"
    echo "[ROM SIZE] ${ROM_SIZE} bytes (${ROM_MB} MB / 32 MB max GBA size)"
else
    echo "[BUILD ERROR] pokeconfluence.gba was not found after compilation."
    exit 1
fi

