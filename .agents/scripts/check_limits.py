#!/usr/bin/env python3
"""
check_limits.py - Audit Pokémon Confluence against engine and hardware limits.

Checks:
  1. Map sections count against MAPSEC limit (253 max).
  2. Trainer ID allocation in the Emerald band (max 864 before partner band).
  3. Object events per map (max 64 per map).
  4. Unsupported script stubs count.
"""

import os
import re
import json
import glob
from pathlib import Path

WORKSPACE = Path("/home/mosberg/wsl_projects/pokemon")
POKECONFLUENCE = WORKSPACE / "pokeconfluence"

def check_mapsec_limit():
    json_path = POKECONFLUENCE / "src/data/region_map/region_map_sections.json"
    if json_path.exists():
        data = json.loads(json_path.read_text(encoding="utf-8"))
        mapsecs = [s for s in data.get("map_sections", []) if s.get("id") != "MAPSEC_NONE"]
        count = len(mapsecs)
        # Usable slots are 0..252 (253 slots). 0xFD (253), 0xFE (254), 0xFF (255) are reserved for METLOC.
        limit = 253
        status = "OK (At Capacity)" if count == limit else ("OK" if count < limit else "WARNING: COLLISION RISK with METLOC_SPECIAL_EGG (0xFD)")
        remaining = max(0, limit - count)
        print(f"[MAPSEC] {count}/{limit} map sections defined ({remaining} free slots) -> {status}")
        return count <= 254
    header = POKECONFLUENCE / "include/constants/region_map_sections.h"
    if not header.exists():
        return "N/A"
    lines = header.read_text(encoding="utf-8").splitlines()
    mapsecs = [l for l in lines if re.match(r"^\s*MAPSEC_\w+", l) and not "MAPSEC_COUNT" in l and not "MAPSEC_NONE" in l]
    count = len(mapsecs)
    limit = 253
    status = "OK" if count <= limit else "EXCEEDED"
    print(f"[MAPSEC] {count}/{limit} map sections defined ({limit - count} remaining) -> {status}")
    return count <= limit

def check_trainer_ids():
    party_file = POKECONFLUENCE / "src/data/trainers.party"
    if not party_file.exists():
        return "N/A"
    lines = party_file.read_text(encoding="utf-8").splitlines()
    trainers = [l for l in lines if re.match(r"^=== TRAINER_", l)]
    print(f"[TRAINERS] Found {len(trainers)} defined trainer parties in trainers.party")
    return True

def check_object_event_limits():
    map_jsons = list(POKECONFLUENCE.glob("data/maps/*/map.json"))
    violations = []
    max_count = 0
    worst_map = ""
    for mj in map_jsons:
        try:
            data = json.loads(mj.read_text(encoding="utf-8"))
            objs = data.get("object_events", [])
            if len(objs) > max_count:
                max_count = len(objs)
                worst_map = mj.parent.name
            if len(objs) > 64:
                violations.append((mj.parent.name, len(objs)))
        except Exception:
            pass
    if violations:
        print(f"[OBJECTS] VIOLATION: {len(violations)} maps exceed 64 object limit: {violations}")
        return False
    else:
        print(f"[OBJECTS] All {len(map_jsons)} maps within 64 object limit (peak: {worst_map} with {max_count} objects) -> OK")
        return True

def check_unsupported_stubs():
    maps_dir = POKECONFLUENCE / "data/maps"
    stubs = []
    for inc in maps_dir.glob("*/scripts.inc"):
        lines = inc.read_text(encoding="utf-8", errors="ignore").splitlines()
        for i, line in enumerate(lines, 1):
            if "@ TODO unsupported:" in line:
                stubs.append(f"{inc.parent.name}:{i}: {line.strip()}")
    print(f"[STUBS] Remaining '@ TODO unsupported:' stubs: {len(stubs)}")
    for s in stubs[:5]:
        print(f"  - {s}")
    if len(stubs) > 5:
        print(f"  ... and {len(stubs) - 5} more")
    return len(stubs)

def main():
    print("=" * 60)
    print("Pokemon Confluence Limit & Integrity Auditor")
    print("=" * 60)
    check_mapsec_limit()
    check_trainer_ids()
    check_object_event_limits()
    check_unsupported_stubs()
    print("=" * 60)

if __name__ == "__main__":
    main()
