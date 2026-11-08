#!/usr/bin/env bash
# Opens this project in Porymap (needs a display: WSLg on Windows 11, or an X server).
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
export PATH="$HOME/.local/bin:$PATH"
command -v porymap >/dev/null || { echo "porymap not found: scripts/setup.sh --extras" >&2; exit 1; }
exec porymap "$ROOT" "$@"
