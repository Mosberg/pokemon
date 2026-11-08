#!/usr/bin/env python3
"""
hook_post_tool.py - Post-tool execution hook for Antigravity.
Automatically validates engine limits whenever files in pokeconfluence are modified.
"""

import sys
import json
import subprocess
from pathlib import Path

WORKSPACE = Path("/home/mosberg/wsl_projects/pokemon")
CHECK_LIMITS = WORKSPACE / ".agents/scripts/check_limits.py"

RELEVANT_PATTERNS = [
    "pokeconfluence/src/",
    "pokeconfluence/include/",
    "pokeconfluence/data/maps/",
    "pokeconfluence/data/layouts/",
    "pokeconfluence/data/tilesets/",
    "pokeconfluence/porymap.project.cfg",
]


def is_relevant_path(path_str: str) -> bool:
    if not path_str:
        return True
    return any(pattern in path_str for pattern in RELEVANT_PATTERNS)


def main():
    try:
        input_data = json.load(sys.stdin)
    except Exception:
        input_data = {}

    tool_name = input_data.get("toolName", "")
    tool_input = input_data.get("toolInput", {})
    file_path = tool_input.get("Path", "")

    # Skip auditing if the file is completely unrelated to game code/assets/maps
    if file_path and not is_relevant_path(file_path):
        print(json.dumps({}))
        return

    # Run check_limits in JSON mode
    res = subprocess.run([sys.executable, str(CHECK_LIMITS), "--json"], capture_output=True, text=True)

    output = {}
    try:
        audit_data = json.loads(res.stdout)
        if audit_data.get("has_violations", False) or res.returncode != 0:
            violations = []
            for name, audit in audit_data.get("audits", {}).items():
                if audit.get("violation", False):
                    violations.append(f"• {name.upper()}: {audit.get('message')}")

            violation_summary = "\n".join(violations)
            output = {
                "injectSteps": [
                    {
                        "ephemeralMessage": (
                            f"[CRITICAL ENGINE LIMIT VIOLATION] after {tool_name} on {Path(file_path).name if file_path else 'workspace'}:\n"
                            f"{violation_summary}\n"
                            f"Action required: Revert or fix this violation before continuing."
                        )
                    }
                ]
            }
    except Exception:
        if "CRITICAL" in res.stdout or "VIOLATION" in res.stdout:
            output = {
                "injectSteps": [
                    {
                        "ephemeralMessage": f"[HOOK ALERT] Engine Limit Violated after {tool_name}!\n{res.stdout.strip()}"
                    }
                ]
            }

    print(json.dumps(output))


if __name__ == "__main__":
    main()
