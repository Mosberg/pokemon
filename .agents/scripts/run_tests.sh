#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
POKECONFLUENCE="$REPO_ROOT/pokeconfluence"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

RUN_LIMITS=1
RUN_SCRIPTS=1
RUN_C_TESTS=1
RUN_EMULATOR=1
RUN_PORYMAP=1

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS]

Options:
  -a, --all         Run all test suites (default)
  -q, --quick       Quick test (limits, scripts, and C tests; skips emulator & porymap)
  -l, --limits      Run hardware & engine limits audit only
  -s, --scripts     Run event script syntax & safety audit only
  -c, --c-tests     Run headless C unit/integration tests only
  -e, --emulator    Run mGBA Python emulator agent tests only
  -p, --porymap     Run Porymap map/layout load verification only
  -h, --help        Show this help message
EOF
    exit 0
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        -a|--all)
            RUN_LIMITS=1; RUN_SCRIPTS=1; RUN_C_TESTS=1; RUN_EMULATOR=1; RUN_PORYMAP=1; shift ;;
        -q|--quick)
            RUN_LIMITS=1; RUN_SCRIPTS=1; RUN_C_TESTS=1; RUN_EMULATOR=0; RUN_PORYMAP=0; shift ;;
        -l|--limits)
            RUN_LIMITS=1; RUN_SCRIPTS=0; RUN_C_TESTS=0; RUN_EMULATOR=0; RUN_PORYMAP=0; shift ;;
        -s|--scripts)
            RUN_LIMITS=0; RUN_SCRIPTS=1; RUN_C_TESTS=0; RUN_EMULATOR=0; RUN_PORYMAP=0; shift ;;
        -c|--c-tests)
            RUN_LIMITS=0; RUN_SCRIPTS=0; RUN_C_TESTS=1; RUN_EMULATOR=0; RUN_PORYMAP=0; shift ;;
        -e|--emulator)
            RUN_LIMITS=0; RUN_SCRIPTS=0; RUN_C_TESTS=0; RUN_EMULATOR=1; RUN_PORYMAP=0; shift ;;
        -p|--porymap)
            RUN_LIMITS=0; RUN_SCRIPTS=0; RUN_C_TESTS=0; RUN_EMULATOR=0; RUN_PORYMAP=1; shift ;;
        -h|--help)
            show_help ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}" >&2
            show_help ;;
    esac
done

echo -e "${CYAN}${BOLD}================================================================${NC}"
echo -e "${CYAN}${BOLD} Pokémon Confluence Multi-Region Test & Verification Suite${NC}"
echo -e "${CYAN}${BOLD}================================================================${NC}"

FAILURES=()

if [[ $RUN_LIMITS -eq 1 ]]; then
    echo -e "\n${BOLD}[1/5] Hardware & Engine Limits Audit${NC}"
    if python3 "$REPO_ROOT/.agents/scripts/check_limits.py"; then
        echo -e "${GREEN}✓ Limits audit passed.${NC}"
    else
        echo -e "${RED}✗ Limits audit failed.${NC}"
        FAILURES+=("Hardware Limits Audit")
    fi
fi

if [[ $RUN_SCRIPTS -eq 1 ]]; then
    echo -e "\n${BOLD}[2/5] Event Script Integrity & Safety Audit${NC}"
    if python3 "$REPO_ROOT/.agents/scripts/audit_scripts.py"; then
        echo -e "${GREEN}✓ Script audit passed.${NC}"
    else
        echo -e "${RED}✗ Script audit failed.${NC}"
        FAILURES+=("Script Integrity Audit")
    fi
fi

if [[ $RUN_C_TESTS -eq 1 ]]; then
    echo -e "\n${BOLD}[3/5] Headless C Integration Test Suite${NC}"
    if bash "$POKECONFLUENCE/scripts/test.sh"; then
        echo -e "${GREEN}✓ C integration test suite passed.${NC}"
    else
        echo -e "${RED}✗ C integration test suite failed.${NC}"
        FAILURES+=("C Integration Tests")
    fi
fi

if [[ $RUN_EMULATOR -eq 1 ]]; then
    echo -e "\n${BOLD}[4/5] Python mGBA Agent Emulator Tests${NC}"
    if [ -f "$POKECONFLUENCE/.venv/bin/pytest" ]; then
        if "$POKECONFLUENCE/.venv/bin/pytest" "$POKECONFLUENCE/mgba-agent/tests"; then
            echo -e "${GREEN}✓ Emulator agent tests passed.${NC}"
        else
            echo -e "${RED}✗ Emulator agent tests failed.${NC}"
            FAILURES+=("mGBA Agent Pytest")
        fi
    else
        echo -e "${YELLOW}Notice: .venv not found, testing system pytest...${NC}"
        if pytest "$POKECONFLUENCE/mgba-agent/tests"; then
            echo -e "${GREEN}✓ Emulator agent tests passed.${NC}"
        else
            echo -e "${RED}✗ Emulator agent tests failed.${NC}"
            FAILURES+=("mGBA Agent Pytest")
        fi
    fi
fi

if [[ $RUN_PORYMAP -eq 1 ]]; then
    echo -e "\n${BOLD}[5/5] Porymap Multi-Region Map Load Validation${NC}"
    if command -v porymap >/dev/null 2>&1 || [ -f "$REPO_ROOT/tools/porymap/porymap" ]; then
        PORYMAP_BIN="${HOME}/.local/bin/porymap"
        [ -x "$PORYMAP_BIN" ] || PORYMAP_BIN="$REPO_ROOT/tools/porymap/porymap"
        if QT_QPA_PLATFORM=offscreen "$PORYMAP_BIN" "$POKECONFLUENCE" --check; then
            echo -e "${GREEN}✓ Porymap project load check passed.${NC}"
        else
            echo -e "${RED}✗ Porymap project load check failed.${NC}"
            FAILURES+=("Porymap Validation")
        fi
    else
        echo -e "${YELLOW}Notice: porymap binary not found, skipping validation.${NC}"
    fi
fi

echo -e "\n${CYAN}${BOLD}================================================================${NC}"
if [[ ${#FAILURES[@]} -eq 0 ]]; then
    echo -e "${GREEN}${BOLD} ALL ACTIVE TEST SUITES PASSED! ROM IS READY FOR PRODUCTION.${NC}"
    echo -e "${CYAN}${BOLD}================================================================${NC}"
    exit 0
else
    echo -e "${RED}${BOLD} VERIFICATION FAILED! The following suites reported errors:${NC}"
    for f in "${FAILURES[@]}"; do
        echo -e "  ${RED}• $f${NC}"
    done
    echo -e "${CYAN}${BOLD}================================================================${NC}"
    exit 1
fi
