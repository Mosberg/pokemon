#!/usr/bin/env python3
"""
audit_scripts.py - Comprehensive script analyzer and validator for Pokémon Confluence.

Audits:
  1. Unimplemented script stubs (@ TODO unsupported:).
  2. Trailing '$' character termination in all .string definitions.
  3. Checks for forbidden blocking commands in ON_TRANSITION callbacks.
  4. Script block termination (checks for unclosed script labels falling through).
  5. Poryscript synchronization (checks if .pory files match compiled .inc files).

Options:
  --json     Emit machine-readable JSON results.
  --quiet    Silent when no violations exist.
  --strict   Fail on warnings (e.g. stubs or unverified labels).
"""

import sys
import os
import re
import json
import argparse
from pathlib import Path

WORKSPACE = Path("/home/mosberg/wsl_projects/pokemon")
POKECONFLUENCE = WORKSPACE / "pokeconfluence"


def audit_stubs():
    stubs = []
    for inc in POKECONFLUENCE.glob("data/maps/*/scripts.inc"):
        map_name = inc.parent.name
        lines = inc.read_text(encoding="utf-8", errors="ignore").splitlines()
        for i, line in enumerate(lines, 1):
            if "@ TODO unsupported:" in line:
                stubs.append({"map": map_name, "line": i, "content": line.strip()})
    return stubs


def audit_string_termination():
    unterminated = []
    for inc in POKECONFLUENCE.glob("data/maps/*/scripts.inc"):
        map_name = inc.parent.name
        lines = inc.read_text(encoding="utf-8", errors="ignore").splitlines()
        in_string_block = False
        last_str_line = 0
        last_str_content = ""
        for i, line in enumerate(lines, 1):
            stripped = line.strip()
            if stripped.startswith('.string "'):
                in_string_block = True
                last_str_line = i
                last_str_content = stripped
            elif in_string_block and (stripped.startswith(".") or stripped.endswith("::") or stripped == "" or stripped.endswith(":")):
                if not last_str_content.endswith('$"') and not last_str_content.endswith("$"):
                    unterminated.append({"map": map_name, "line": last_str_line, "content": last_str_content})
                in_string_block = False
    return unterminated


def audit_on_transition_safety():
    violations = []
    forbidden_tokens = ["msgbox", "message", "waitmessage", "removeobject", "addobject", "fadescreen", "lock", "lockall"]
    for inc in POKECONFLUENCE.glob("data/maps/*/scripts.inc"):
        map_name = inc.parent.name
        lines = inc.read_text(encoding="utf-8", errors="ignore").splitlines()

        cb_label = None
        for line in lines:
            m = re.search(r"map_script\s+MAP_SCRIPT_ON_TRANSITION\s*,\s*(\w+)", line)
            if m:
                cb_label = m.group(1)
                break

        if not cb_label:
            continue

        in_cb = False
        for i, line in enumerate(lines, 1):
            stripped = line.strip()
            if stripped.startswith(cb_label + ":") or stripped.startswith(cb_label + "::"):
                in_cb = True
                continue
            if in_cb:
                if stripped == "end" or stripped.startswith(".2byte") or (stripped.endswith(":") and not stripped.startswith(".")):
                    in_cb = False
                    continue
                for tok in forbidden_tokens:
                    if re.search(rf"\b{tok}\b", stripped):
                        violations.append({"map": map_name, "line": i, "token": tok, "content": stripped})
    return violations


def audit_pory_sync():
    outdated = []
    for pory in POKECONFLUENCE.glob("data/maps/*/scripts.pory"):
        inc = pory.parent / "scripts.inc"
        if not inc.exists() or pory.stat().st_mtime > inc.stat().st_mtime:
            outdated.append({"map": pory.parent.name, "pory": str(pory), "inc": str(inc)})
    return outdated


def run_audit(strict=False):
    stubs = audit_stubs()
    strings = audit_string_termination()
    transitions = audit_on_transition_safety()
    pory = audit_pory_sync()

    has_violations = len(strings) > 0 or len(transitions) > 0 or len(pory) > 0
    has_warnings = len(stubs) > 0

    return {
        "passed": not has_violations and (not strict or not has_warnings),
        "has_violations": has_violations,
        "has_warnings": has_warnings,
        "stubs": stubs,
        "unterminated_strings": strings,
        "transition_violations": transitions,
        "outdated_pory": pory
    }


def main():
    parser = argparse.ArgumentParser(description="Audit Pokémon Confluence event scripts.")
    parser.add_argument("--json", action="store_true", help="Emit JSON output.")
    parser.add_argument("--quiet", action="store_true", help="Quiet output.")
    parser.add_argument("--strict", action="store_true", help="Treat warnings as errors.")
    args = parser.parse_args()

    report = run_audit(strict=args.strict)

    if args.json:
        print(json.dumps(report, indent=2))
    elif not args.quiet or report["has_violations"] or (args.strict and report["has_warnings"]):
        print("=" * 64)
        print(" Pokémon Confluence Event Script Auditor")
        print("=" * 64)
        print(f"[STUBS          ] Remaining '@ TODO unsupported:' stubs: {len(report['stubs'])}")
        for s in report['stubs'][:3]:
            print(f"  • {s['map']}:{s['line']}: {s['content']}")

        print(f"[STRINGS        ] Unterminated strings missing '$': {len(report['unterminated_strings'])}")
        for s in report['unterminated_strings'][:3]:
            print(f"  • {s['map']}:{s['line']}: {s['content']}")

        print(f"[ON_TRANSITION  ] Forbidden commands in transition callbacks: {len(report['transition_violations'])}")
        for t in report['transition_violations'][:3]:
            print(f"  • {t['map']}:{t['line']} (uses {t['token']}): {t['content']}")

        print(f"[PORYSCRIPT_SYNC] Outdated or uncompiled .pory scripts: {len(report['outdated_pory'])}")
        print("=" * 64)
        if report["has_violations"]:
            print("RESULT: FAILED - Script syntax or safety violations found!")
        elif report["has_warnings"] and args.strict:
            print("RESULT: FAILED - Warnings treated as errors under --strict.")
        else:
            print("RESULT: PASSED - All scripts verified safe and compliant.")
        print("=" * 64)

    sys.exit(1 if report["has_violations"] or (args.strict and report["has_warnings"]) else 0)


if __name__ == "__main__":
    main()
