#!/usr/bin/env python3
import sys
import json
import subprocess
from pathlib import Path

WORKSPACE = Path("/home/mosberg/wsl_projects/pokemon")
CHECK_LIMITS = WORKSPACE / ".agents/scripts/check_limits.py"

def main():
    try:
        input_data = json.load(sys.stdin)
    except Exception:
        input_data = {}

    tool_name = input_data.get("toolName", "")
    
    # Run limit check
    res = subprocess.run([sys.executable, str(CHECK_LIMITS)], capture_output=True, text=True)
    
    output = {}
    if "EXCEEDED" in res.stdout or "CRITICAL" in res.stdout:
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

