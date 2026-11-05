#!/usr/bin/env bash
# Pokemon Confluence: one-shot environment setup for WSL2 / Linux (no root needed).
#
#   scripts/setup.sh            check the toolchain, fix tool permissions, build the native tools, create .venv
#   scripts/setup.sh --extras   also install Node.js and Go into ~/.local and build poryscript and porymap and builds porymap
#
# Missing system packages are reported with the apt command that installs them; nothing is installed with sudo.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TOOLS_ROOT="$(cd "$ROOT/.." && pwd)/tools"
NODE_VERSION="${NODE_VERSION:-v26.13.0}"
GO_VERSION="${GO_VERSION:-go1.27.3}"
LOCAL="$HOME/.local"
EXTRAS=0
[[ "${1:-}" == "--extras" ]] && EXTRAS=1

say() { printf '\033[1;36m[confluence]\033[0m %s\n' "$*"; }
warn() { printf '\033[1;33m[confluence]\033[0m %s\n' "$*"; }
missing=()

say "Checking the build toolchain"
for cmd in arm-none-eabi-gcc arm-none-eabi-ld arm-none-eabi-objcopy make gcc g++ git python3 perl; do
    command -v "$cmd" >/dev/null 2>&1 || missing+=("$cmd")
done
if ! echo '#include <png.h>' | gcc -E -x c - >/dev/null 2>&1; then
    missing+=("libpng headers")
fi
if ((${#missing[@]})); then
    warn "Missing: ${missing[*]}"
    warn "Install with: sudo apt install build-essential binutils-arm-none-eabi gcc-arm-none-eabi libpng-dev git python3 perl"
    exit 1
fi
say "arm-none-eabi-gcc $(arm-none-eabi-gcc -dumpversion), make $(make --version | head -1 | awk '{print $NF}')"

say "Fixing executable bits on bundled tools and scripts"
chmod +x "$ROOT"/scripts/*.sh "$ROOT"/*.sh "$ROOT/tools/mgba/mgba-rom-test" "$ROOT/tools/mgba/mgba-rom-test-mac" \
    "$ROOT/tools/mgba-rom-test-hydra/mgba-rom-test-hydra" 2>/dev/null || true

say "Building the native tools (gbagfx, mapjson, preproc, compresSmol, ...)"
make -C "$ROOT" -j"$(nproc)" tools check-tools >/dev/null
say "Tools built"

if [[ ! -x "$ROOT/.venv/bin/python" ]]; then
    say "Creating .venv for the mgba-agent scripts"
    python3 -m venv --without-pip "$ROOT/.venv"
fi
if [[ ! -x "$ROOT/.venv/bin/pip" ]]; then
    say "Bootstrapping pip into .venv"
    curl -fsSL https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py
    "$ROOT/.venv/bin/python" /tmp/get-pip.py -q
fi
"$ROOT/.venv/bin/pip" install -q mcp pillow numpy "pydantic>=2" pytest
say ".venv ready (RL extras: .venv/bin/pip install -r mgba-agent/requirements.txt)"

if ((EXTRAS)); then
    mkdir -p "$LOCAL/opt" "$LOCAL/bin"
    if ! command -v node >/dev/null 2>&1; then
        say "Installing Node.js $NODE_VERSION into $LOCAL/opt (embedded GBA emulator)"
        curl -fsSL "https://nodejs.org/dist/$NODE_VERSION/node-$NODE_VERSION-linux-x64.tar.xz" | tar -xJ -C "$LOCAL/opt"
        ln -sf "$LOCAL/opt/node-$NODE_VERSION-linux-x64/bin/node" "$LOCAL/bin/node"
        ln -sf "$LOCAL/opt/node-$NODE_VERSION-linux-x64/bin/npm" "$LOCAL/bin/npm"
    fi
    if ! command -v go >/dev/null 2>&1; then
        say "Installing $GO_VERSION into $LOCAL/opt"
        curl -fsSL "https://go.dev/dl/$GO_VERSION.linux-amd64.tar.gz" | tar -xz -C "$LOCAL/opt"
        ln -sf "$LOCAL/opt/go/bin/go" "$LOCAL/bin/go"
    fi
    export PATH="$LOCAL/bin:$PATH"
    if [[ -d "$TOOLS_ROOT/poryscript" ]] && ! command -v poryscript >/dev/null 2>&1; then
        say "Building poryscript"
        (cd "$TOOLS_ROOT/poryscript" && go build -o "$LOCAL/bin/poryscript" .)
    fi
fi

if ((EXTRAS)) && ! command -v porymap >/dev/null 2>&1; then
    if command -v qmake6 >/dev/null 2>&1 && [[ -d "$TOOLS_ROOT/porymap" ]]; then
        say "Building porymap (Qt6)"
        mkdir -p "$HOME/.cache/porymap-build"
        (cd "$HOME/.cache/porymap-build" && qmake6 "$TOOLS_ROOT/porymap/porymap.pro" >/dev/null && make -j"$(nproc)" >/dev/null)
        cp "$HOME/.cache/porymap-build/porymap" "$LOCAL/bin/porymap"
    else
        warn "porymap skipped: sudo apt install qt6-declarative-dev (then rerun with --extras)"
    fi
fi

case ":$PATH:" in *":$LOCAL/bin:"*) ;; *) warn "Add $LOCAL/bin to PATH (it is in ~/.profile on Ubuntu after a re-login)";; esac
say "Setup finished. Next: scripts/build.sh, then scripts/test.sh"
