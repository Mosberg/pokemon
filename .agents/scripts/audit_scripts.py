#!/usr/bin/env python3
"""
audit_scripts.py - Comprehensive script analyzer for Pokémon Confluence.

Audits:
  1. Unimplemented script stubs (@ TODO unsupported:).
  2. Trailing '$' character termination in all .string definitions.
  3. Checks for forbidden commands in ON_TRANSITION callbacks.
"""

import re
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
                stubs.append((map_name, i, line.strip()))
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
            elif in_string_block and (stripped.startswith(".") or stripped.endswith("::") or stripped == ""):
                # End of string block, check if last line ended in '$"'
                if not last_str_content.endswith('$"') and not last_str_content.endswith("$"):
                    unterminated.append((map_name, last_str_line, last_str_content))
                in_string_block = False
    return unterminated


def audit_on_transition_safety():
    violations = []
    forbidden_tokens = ["msgbox", "message", "waitmessage", "removeobject", "addobject"]
    for inc in POKECONFLUENCE.glob("data/maps/*/scripts.inc"):
        map_name = inc.parent.name
        lines = inc.read_text(encoding="utf-8", errors="ignore").splitlines()

        # Find transition callback label
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
                if (
                    stripped == "end"
                    or stripped.startswith(".2byte")
                    or (stripped.endswith(":") and not stripped.startswith("."))
                ):
                    in_cb = False
                    continue
                for tok in forbidden_tokens:
                    if re.search(r"\b" + tok + r"\b", stripped):
                        violations.append((map_name, i, tok, stripped))
    return violations


def main():
    print("=" * 60)
    print("Pokémon Confluence Script Audit")
    print("=" * 60)

    stubs = audit_stubs()
    print(f"[STUBS] Remaining '@ TODO unsupported:' stubs: {len(stubs)}")
    for map_name, line_num, stub_text in stubs[:5]:
        print(f"  - {map_name}:{line_num}: {stub_text}")
    if len(stubs) > 5:
        print(f"  ... and {len(stubs) - 5} more")

    unterminated = audit_string_termination()
    if unterminated:
        print(f"[STRINGS] WARNING: Found {len(unterminated)} potentially unterminated strings:")
        for map_name, line_num, content in unterminated[:5]:
            print(f"  - {map_name}:{line_num}: {content}")
    else:
        print("[STRINGS] All .string definitions end with '$' -> OK")

    cb_violations = audit_on_transition_safety()
    if cb_violations:
        print(f"[ON_TRANSITION] WARNING: Found {len(cb_violations)} forbidden commands in transition callbacks:")
        for map_name, line_num, tok, content in cb_violations:
            print(f"  - {map_name}:{line_num} (uses {tok}): {content}")
    else:
        print("[ON_TRANSITION] No forbidden blocking commands in map load callbacks -> OK")

    print("=" * 60)


if __name__ == "__main__":
    main()
