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
trainer_party_builder.py - Compiles YAML/JSON Trainer configurations into
validated C structures for pokeemerald / pokeemerald-expansion.
"""

import argparse
import json
from pathlib import Path

# Common competitive AI script combinations
DEFAULT_AI_FLAGS = [
    "AI_FLAG_CHECK_BAD_MOVE",
    "AI_FLAG_TRY_TO_FAINT",
    "AI_FLAG_CHECK_VIABILITY",
    "AI_FLAG_SETUP_FIRST_TURN"
]

def format_trainer_c(trainer_data: dict) -> tuple[str, str]:
    t_id = trainer_data["trainer_id"].upper()
    t_class = trainer_data.get("trainer_class", "TRAINER_CLASS_PKMN_TRAINER_1")
    t_name = trainer_data.get("name", "Trainer")
    ai_flags = trainer_data.get("ai_flags", DEFAULT_AI_FLAGS)
    double_battle = "TRUE" if trainer_data.get("double_battle", False) else "FALSE"
    party = trainer_data.get("party", [])

    party_var = f"sParty_{t_id}"

    # 1. Build Party Array
    party_lines = [
        f"static const struct TrainerMonItemCustomMoves {party_var}[] = {{"
    ]

    for mon in party:
        species = mon["species"].upper()
        lvl = mon.get("level", 50)
        item = mon.get("held_item", "ITEM_NONE").upper()
        ability = mon.get("ability", "0")
        ball = mon.get("ball", "ITEM_POKE_BALL").upper()

        # IVs (0-31 per stat) and EVs (0-252 per stat)
        ivs = mon.get("ivs", [31, 31, 31, 31, 31, 31])
        evs = mon.get("evs", [0, 0, 0, 0, 0, 0])
        nature = mon.get("nature", "NATURE_HARDY").upper()

        moves = [m.upper() for m in mon.get("moves", [])]
        while len(moves) < 4:
            moves.append("MOVE_NONE")

        party_lines.append("    {")
        party_lines.append(f"        .species = {species},")
        party_lines.append(f"        .lvl = {lvl},")
        party_lines.append(f"        .heldItem = {item},")
        party_lines.append(f"        .nature = {nature},")
        party_lines.append(
            f"        .iv = TRAINER_PARTY_IVS({ivs[0]}, {ivs[1]}, {ivs[2]}, {ivs[3]}, {ivs[4]}, {ivs[5]}),"
        )
        party_lines.append(
            f"        .ev = TRAINER_PARTY_EVS({evs[0]}, {evs[1]}, {evs[2]}, {evs[3]}, {evs[4]}, {evs[5]}),"
        )
        party_lines.append(f"        .moves = {{ {', '.join(moves)} }},")
        party_lines.append(f"        .ball = {ball},")
        party_lines.append("    },")

    party_lines.append("};\n")

    # 2. Build Trainer Metadata Entry
    ai_flags_str = " | ".join(ai_flags) if ai_flags else "0"
    trainer_entry = [
        f"    [{t_id}] = {{",
        f"        .trainerClass = {t_class},",
        "        .encounterMusic_gender = F_TRAINER_FEMALE | TRAINER_ENCOUNTER_MUSIC_MALE,",
        f"        .trainerPic = TRAINER_PIC_{t_id},",
        f'        .trainerName = _("{t_name}"),',
        f"        .aiFlags = {ai_flags_str},",
        f"        .doubleBattle = {double_battle},",
        f"        .partySize = ARRAY_COUNT({party_var}),",
        f"        .party = {{ .ItemCustomMoves = {party_var} }},",
        "    },",
    ]

    return "\n".join(party_lines), "\n".join(trainer_entry)


def process_trainer_file(config_path: Path, out_dir: Path):
    out_dir.mkdir(parents=True, exist_ok=True)
    raw_cfg = json.loads(config_path.read_text())

    all_parties = []
    all_trainers = []

    for t in raw_cfg:
        party_code, trainer_code = format_trainer_c(t)
        all_parties.append(party_code)
        all_trainers.append(trainer_code)

    (out_dir / "trainer_parties_generated.h").write_text("\n".join(all_parties))
    (out_dir / "trainers_generated.h").write_text(
        "const struct Trainer gTrainers[] = {\n" + "\n".join(all_trainers) + "\n};\n"
    )

    print("=" * 60)
    print(f"[✓] Compiled {len(raw_cfg)} Trainers:")
    print(f"  - Parties Code: {out_dir / 'trainer_parties_generated.h'}")
    print(f"  - Trainer Code: {out_dir / 'trainers_generated.h'}")
    print("=" * 60)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compile JSON trainer configurations into C headers.")
    parser.add_argument("config_file", type=Path, help="Path to trainers_config.json")
    parser.add_argument("--out-dir", type=Path, default=Path("trainer_build"), help="Output directory")
    args = parser.parse_args()

    process_trainer_file(args.config_file, args.out_dir)
