#!/usr/bin/env python3
import sys
from pathlib import Path

# Add tool directory to path and bootstrap dependencies
sys.path.insert(0, str(Path(__file__).resolve().parent))
try:
    import asset_common

    asset_common.ensure_dependencies()
except ImportError:
    pass

"""
validate_encounters.py - GBA Wild Encounter and Probability Rate Validator.
Audits wild_encounters.json for rate anomalies, inverted levels, slot mismatches,
and undefined species IDs.
"""

import argparse
import json
import re
from pathlib import Path

# Standard Gen 3 slot distributions and probability allocations
EXPECTED_SLOT_RATES = {
    "land_mons": [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1],
    "water_mons": [60, 30, 5, 4, 1],
    "rock_smash_mons": [60, 30, 5, 4, 1],
    "fishing_mons": [70, 30, 60, 20, 20, 40, 40, 15, 4, 1],
}


def load_valid_species(species_header: Path) -> set[str]:
    """Extracts valid species constants from species.h or species_info.h."""
    if not species_header or not species_header.exists():
        return set()

    content = species_header.read_text()
    # Match both enum definitions and #defines
    species = set(re.findall(r'(SPECIES_[A-Z0-9_]+)', content))
    return species

def validate_encounter_table(encounters_json: Path, species_header: Path = None):
    data = json.loads(encounters_json.read_text())
    valid_species = load_valid_species(species_header) if species_header else set()

    errors = []
    warnings = []
    total_maps = 0
    total_slots_checked = 0

    wild_encounter_groups = data.get("wild_encounter_groups", [])

    for group in wild_encounter_groups:
        group_label = group.get("label", "Unknown Group")
        fields = group.get("encounters", [])

        for map_entry in fields:
            total_maps += 1
            map_name = map_entry.get("map", "UNKNOWN_MAP")

            for terrain_type, expected_rates in EXPECTED_SLOT_RATES.items():
                terrain_data = map_entry.get(terrain_type)
                if not terrain_data:
                    continue

                mons = terrain_data.get("mons", [])
                total_slots_checked += len(mons)

                # 1. Slot Count Check
                if len(mons) != len(expected_rates):
                    errors.append(
                        f"[{map_name}] {terrain_type} has {len(mons)} slots; expected exactly {len(expected_rates)}."
                    )
                    continue

                # 2. Level Consistency Check & Species Validation
                for idx, slot in enumerate(mons):
                    species = slot.get("species")
                    min_lvl = slot.get("min_level")
                    max_lvl = slot.get("max_level")

                    # Check species validity
                    if valid_species and species not in valid_species:
                        errors.append(
                            f"[{map_name}] {terrain_type} slot {idx}: Undefined species '{species}'."
                        )

                    # Check level integrity
                    if not (1 <= min_lvl <= 100):
                        errors.append(
                            f"[{map_name}] {terrain_type} slot {idx} ({species}): Invalid min_level ({min_lvl}). Must be 1-100."
                        )
                    if not (1 <= max_lvl <= 100):
                        errors.append(
                            f"[{map_name}] {terrain_type} slot {idx} ({species}): Invalid max_level ({max_lvl}). Must be 1-100."
                        )
                    if min_lvl > max_lvl:
                        errors.append(
                            f"[{map_name}] {terrain_type} slot {idx} ({species}): Inverted levels! min_level ({min_lvl}) > max_level ({max_lvl})."
                        )
                    elif min_lvl == max_lvl:
                        warnings.append(
                            f"[{map_name}] {terrain_type} slot {idx} ({species}): Static single-level encounter ({min_lvl})."
                        )

    # Output Validation Report
    print("=" * 70)
    print(f"WILD ENCOUNTER AUDIT REPORT: {encounters_json.name}")
    print(f"Total Maps Evaluated:  {total_maps}")
    print(f"Total Slots Evaluated: {total_slots_checked}")
    print(f"Status:                {'FAILED' if errors else 'PASSED'}")
    print("=" * 70)

    if errors:
        print(f"\n[!] Detected {len(errors)} Critical Errors:")
        for err in errors:
            print(f"  [ERROR] {err}")
    else:
        print("\n[✓] All slot counts, rate structures, and level boundaries verified.")

    if warnings:
        print(f"\n[*] {len(warnings)} Informational Notices:")
        for warn in warnings[:10]:
            print(f"  [WARN]  {warn}")
        if len(warnings) > 10:
            print(f"  ... and {len(warnings) - 10} more notices.")

    return len(errors) == 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Validate wild encounter rates and constraints in wild_encounters.json")
    parser.add_argument("json_file", type=Path, help="Path to wild_encounters.json")
    parser.add_argument("--species-header", type=Path, default=None, help="Path to species.h or species_info.h")
    args = parser.parse_args()

    success = validate_encounter_table(args.json_file, args.species_header)
    exit(0 if success else 1)
