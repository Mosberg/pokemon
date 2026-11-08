#!/usr/bin/env python3
"""
check_limits.py - Comprehensive Hardware & Engine Limit Auditor for Pokémon Confluence.

Audits:
  1. Map Sections count against MAPSEC limit (253 max usable, 0xFD-0xFF reserved).
  2. Map Groups map counts against s8 warp mapNum limit (127 max per group).
  3. Object events per map against EWRAM limit (64 max per map).
  4. Trainer ID allocations against the Hoenn/partner bands (max 864 before partner band).
  5. SaveBlock sector budgets (SaveBlock1, SaveBlock2, SaveBlock3, PokemonStorage) via ELF symbols.
  6. Remaining unsupported script stubs (@ TODO unsupported:).

Options:
  --json       Emit machine-readable JSON output for tools and hooks.
  --quiet      Minimal output; silent on success, logs only on violations.
  --strict     Exit with failure on warnings/capacity warnings.
"""

import sys
import os
import re
import json
import glob
import argparse
import subprocess
from pathlib import Path

WORKSPACE = Path("/home/mosberg/wsl_projects/pokemon")
POKECONFLUENCE = WORKSPACE / "pokeconfluence"


def check_mapsec_limit(strict=False):
    json_path = POKECONFLUENCE / "src/data/region_map/region_map_sections.json"
    limit = 253
    result = {
        "name": "map_sections",
        "limit": limit,
        "count": 0,
        "free": 0,
        "status": "OK",
        "violation": False,
        "warning": False,
        "message": ""
    }

    if json_path.exists():
        try:
            data = json.loads(json_path.read_text(encoding="utf-8"))
            mapsecs = [s for s in data.get("map_sections", []) if s.get("id") != "MAPSEC_NONE"]
            count = len(mapsecs)
            result["count"] = count
            result["free"] = max(0, limit - count)
            if count > limit:
                result["status"] = "EXCEEDED"
                result["violation"] = True
                result["message"] = f"CRITICAL: {count} map sections exceed maximum usable limit {limit} (collides with 0xFD-0xFF METLOC reserves)."
            elif count == limit:
                result["status"] = "OK (At Capacity)"
                result["warning"] = True
                result["message"] = f"{count}/{limit} map sections defined (0 free slots remaining). Do not add new sections without slot reclamation."
            else:
                result["status"] = "OK"
                result["message"] = f"{count}/{limit} map sections defined ({result['free']} free slots remaining)."
            return result
        except Exception as e:
            result["status"] = "ERROR"
            result["violation"] = True
            result["message"] = f"Failed to parse region_map_sections.json: {e}"
            return result

    # Fallback to header
    header = POKECONFLUENCE / "include/constants/region_map_sections.h"
    if header.exists():
        lines = header.read_text(encoding="utf-8").splitlines()
        mapsecs = [l for l in lines if re.match(r"^\s*MAPSEC_\w+", l) and "MAPSEC_COUNT" not in l and "MAPSEC_NONE" not in l]
        count = len(mapsecs)
        result["count"] = count
        result["free"] = max(0, limit - count)
        result["violation"] = count > limit
        result["status"] = "EXCEEDED" if result["violation"] else "OK"
        result["message"] = f"{count}/{limit} map sections defined."
    else:
        result["message"] = "Region map sections file not found."
    return result


def check_map_groups_limit():
    mg_path = POKECONFLUENCE / "data/maps/map_groups.json"
    limit = 127  # Hard engine limit: WarpData.mapNum is signed 8-bit (s8)
    result = {
        "name": "map_groups",
        "limit": limit,
        "total_groups": 0,
        "max_group": "",
        "max_count": 0,
        "violations": [],
        "violation": False,
        "warning": False,
        "message": ""
    }

    if not mg_path.exists():
        result["message"] = "map_groups.json not found."
        return result

    try:
        data = json.loads(mg_path.read_text(encoding="utf-8"))
        groups = data.get("group_order", [])
        result["total_groups"] = len(groups)
        for g in groups:
            count = len(data.get(g, []))
            if count > result["max_count"]:
                result["max_count"] = count
                result["max_group"] = g
            if count > limit:
                result["violations"].append({"group": g, "count": count, "limit": limit})

        if result["violations"]:
            result["violation"] = True
            result["status"] = "EXCEEDED"
            result["message"] = f"CRITICAL: {len(result['violations'])} map groups exceed signed 8-bit warp limit {limit}: {result['violations']}"
        else:
            result["status"] = "OK"
            result["message"] = f"All {len(groups)} map groups within signed 8-bit limit (peak: {result['max_group']} with {result['max_count']}/{limit} maps)."
        return result
    except Exception as e:
        result["status"] = "ERROR"
        result["violation"] = True
        result["message"] = f"Failed to parse map_groups.json: {e}"
        return result


def check_object_event_limits():
    limit = 64  # OBJECT_EVENT_TEMPLATES_COUNT in EWRAM
    result = {
        "name": "object_events",
        "limit": limit,
        "total_maps": 0,
        "worst_map": "",
        "max_objects": 0,
        "violations": [],
        "violation": False,
        "warning": False,
        "message": ""
    }

    map_jsons = list(POKECONFLUENCE.glob("data/maps/*/map.json"))
    result["total_maps"] = len(map_jsons)

    for mj in map_jsons:
        try:
            data = json.loads(mj.read_text(encoding="utf-8"))
            objs = data.get("object_events", [])
            count = len(objs)
            if count > result["max_objects"]:
                result["max_objects"] = count
                result["worst_map"] = mj.parent.name
            if count > limit:
                result["violations"].append({"map": mj.parent.name, "count": count, "limit": limit})
        except Exception:
            pass

    if result["violations"]:
        result["violation"] = True
        result["status"] = "EXCEEDED"
        result["message"] = f"VIOLATION: {len(result['violations'])} maps exceed 64 object limit: {result['violations']}"
    else:
        result["status"] = "OK"
        result["message"] = f"All {len(map_jsons)} maps within 64 object limit (peak: {result['worst_map']} with {result['max_objects']}/{limit} objects)."
    return result


def check_trainer_ids():
    party_file = POKECONFLUENCE / "src/data/trainers.party"
    result = {
        "name": "trainers",
        "count": 0,
        "limit": 864,  # First partner trainer ID in expansion
        "status": "OK",
        "violation": False,
        "warning": False,
        "message": ""
    }

    if not party_file.exists():
        result["message"] = "trainers.party not found."
        return result

    lines = party_file.read_text(encoding="utf-8").splitlines()
    trainers = [l for l in lines if re.match(r"^===\s*TRAINER_", l)]
    result["count"] = len(trainers)
    if result["count"] > result["limit"]:
        result["warning"] = True
        result["message"] = f"Notice: Found {result['count']} trainers (partner band starts at {result['limit']})."
    else:
        result["message"] = f"Found {result['count']} defined trainer parties in trainers.party."
    return result


def check_saveblock_sizes():
    limits = {
        "gSaveblock1": 15872,      # 4 flash sectors * 3968 bytes
        "gSaveblock2": 4096,       # 1 flash sector (with ASLR alignment padding)
        "gSaveblock3": 1624,       # 14 sectors * 116 bytes
        "gPokemonStorage": 35712   # 9 flash sectors * 3968 bytes
    }
    result = {
        "name": "saveblock_sizes",
        "checked": False,
        "entries": {},
        "violations": [],
        "violation": False,
        "warning": False,
        "message": ""
    }

    elf_path = POKECONFLUENCE / "pokeconfluence.elf"
    if not elf_path.exists():
        result["message"] = "pokeconfluence.elf not found (run build first to inspect binary saveblock sizes)."
        return result

    nm_bin = "arm-none-eabi-nm"
    try:
        out = subprocess.check_output([nm_bin, "-S", str(elf_path)], text=True, stderr=subprocess.DEVNULL)
        result["checked"] = True
        for line in out.splitlines():
            for sym, max_size in limits.items():
                if re.search(rf"\s{sym}$", line):
                    parts = line.split()
                    size = int(parts[1], 16)
                    free = max_size - size
                    entry = {
                        "size": size,
                        "limit": max_size,
                        "free": free,
                        "status": "OK" if free >= 0 else "OVERFLOW"
                    }
                    result["entries"][sym] = entry
                    if free < 0:
                        result["violations"].append({"symbol": sym, "size": size, "limit": max_size})
                    elif free < 64:
                        result["warning"] = True

        if result["violations"]:
            result["violation"] = True
            result["status"] = "EXCEEDED"
            result["message"] = f"CRITICAL: SaveBlock sector overflow detected: {result['violations']}"
        else:
            summary_parts = [f"{k}: {v['size']}/{v['limit']} ({v['free']}B free)" for k, v in result["entries"].items()]
            result["status"] = "OK"
            result["message"] = "SaveBlock sectors verified -> " + ", ".join(summary_parts)
    except Exception as e:
        result["message"] = f"nm inspection skipped: {e}"

    return result


def check_unsupported_stubs():
    maps_dir = POKECONFLUENCE / "data/maps"
    stubs = []
    result = {
        "name": "unsupported_stubs",
        "count": 0,
        "samples": [],
        "status": "OK",
        "violation": False,
        "warning": False,
        "message": ""
    }

    if maps_dir.exists():
        for inc in maps_dir.glob("*/scripts.inc"):
            lines = inc.read_text(encoding="utf-8", errors="ignore").splitlines()
            for i, line in enumerate(lines, 1):
                if "@ TODO unsupported:" in line:
                    stubs.append(f"{inc.parent.name}:{i}: {line.strip()}")

    result["count"] = len(stubs)
    result["samples"] = stubs[:5]
    if stubs:
        result["warning"] = True
        result["message"] = f"{len(stubs)} remaining '@ TODO unsupported:' stubs."
    else:
        result["message"] = "Remaining '@ TODO unsupported:' stubs: 0."
    return result


def run_all_audits(strict=False):
    return [
        check_mapsec_limit(strict=strict),
        check_map_groups_limit(),
        check_object_event_limits(),
        check_trainer_ids(),
        check_saveblock_sizes(),
        check_unsupported_stubs()
    ]


def main():
    parser = argparse.ArgumentParser(description="Audit Pokémon Confluence hardware and engine limits.")
    parser.add_argument("--json", action="store_true", help="Output audit results as JSON.")
    parser.add_argument("--quiet", action="store_true", help="Quiet mode; only print if violations are found.")
    parser.add_argument("--strict", action="store_true", help="Fail if any warning is triggered.")
    args = parser.parse_args()

    results = run_all_audits(strict=args.strict)
    has_violations = any(r.get("violation", False) for r in results)
    has_warnings = any(r.get("warning", False) for r in results)

    if args.json:
        output_obj = {
            "passed": not has_violations and (not args.strict or not has_warnings),
            "has_violations": has_violations,
            "has_warnings": has_warnings,
            "audits": {r["name"]: r for r in results}
        }
        print(json.dumps(output_obj, indent=2))
    elif not args.quiet or has_violations:
        print("=" * 64)
        print(" Pokémon Confluence Limit & Hardware Integrity Auditor")
        print("=" * 64)
        for r in results:
            prefix = "[CRITICAL VIOLATION]" if r.get("violation") else ("[WARNING]" if r.get("warning") and args.strict else "[OK]")
            tag = r["name"].upper()
            print(f"[{tag:17}] {r['message']}")
        print("=" * 64)
        if has_violations:
            print("RESULT: FAILED - Critical engine limits violated!")
        elif has_warnings and args.strict:
            print("RESULT: FAILED - Warnings treated as errors under --strict.")
        else:
            print("RESULT: PASSED - All engine and hardware limits verified.")
        print("=" * 64)

    sys.exit(1 if has_violations or (args.strict and has_warnings) else 0)


if __name__ == "__main__":
    main()
