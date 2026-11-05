#!/usr/bin/env python3
import os
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
tmeff_matrix.py - TM/HM and Species Move Compatibility Matrix Engine.
Generates validation reports and interactive visual compatibility matrices.
"""

import re
import argparse
from pathlib import Path

# Standard Gen 3 Core TM/HM Map
DEFAULT_TMHM_LIST = [
    ("TM01", "Focus Punch", "Fighting"), ("TM02", "Dragon Claw", "Dragon"),
    ("TM03", "Water Pulse", "Water"),    ("TM04", "Calm Mind", "Psychic"),
    ("TM05", "Roar", "Normal"),          ("TM06", "Toxic", "Poison"),
    ("TM07", "Hail", "Ice"),             ("TM08", "Bulk Up", "Fighting"),
    ("TM09", "Bullet Seed", "Grass"),    ("TM10", "Hidden Power", "Normal"),
    ("HM01", "Cut", "Normal"),           ("HM02", "Fly", "Flying"),
    ("HM03", "Surf", "Water"),           ("HM04", "Strength", "Normal"),
    ("HM05", "Flash", "Normal"),         ("HM06", "Rock Smash", "Fighting"),
    ("HM07", "Waterfall", "Water"),      ("HM08", "Dive", "Water")
]

class CompatibilityMatrixEngine:
    def __init__(self):
        self.species_learnsets = {}  # SPECIES_NAME: set of TM moves

    def add_species(self, species_name: str, tm_list: list[str]):
        clean_moves = {m.strip().upper().replace("MOVE_", "").replace(" ", "_") for m in tm_list}
        self.species_learnsets[species_name.upper()] = clean_moves

    def parse_decomp_species_info(self, file_path: Path):
        """Scans species_info.h for TMHM learnset declarations."""
        content = file_path.read_text()
        blocks = re.findall(r'\[(SPECIES_[A-Z0-9_]+)\]\s*=\s*\{([^}]+)\}', content, re.DOTALL)

        for species_id, body in blocks:
            # Match TMHM_LEARNSET macro: .tmIll = TMHM(MOVE_A | MOVE_B) or .learnset = TMHM(...)
            tm_match = re.search(r'(?:\.tmIll|\.learnset)\s*=\s*TMHM\(([^)]+)\)', body)
            if tm_match:
                moves = [m.strip() for m in tm_match.group(1).split("|")]
                self.add_species(species_id, moves)

    def export_c_bitfield(self, species_name: str) -> str:
        moves = sorted(list(self.species_learnsets.get(species_name.upper(), [])))
        if not moves:
            return f"    [{species_name}] = {{ .learnset = 0 }},"
        moves_formatted = " | ".join([f"MOVE_{m}" for m in moves])
        return f"    [{species_name}] = {{ .learnset = TMHM({moves_formatted}) }},"

    def export_html_matrix(self, out_path: Path):
        """Generates a responsive matrix table with CSS grid formatting."""
        html = [
            "<!DOCTYPE html>",
            "<html><head><meta charset='utf-8'><title>GBA TM/HM Compatibility Matrix</title>",
            "<style>",
            "body { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; background: #1a1a24; color: #e1e1e8; margin: 20px; }",
            "table { border-collapse: collapse; width: 100%; font-size: 13px; }",
            "th, td { border: 1px solid #2e2e3e; padding: 6px 8px; text-align: center; }",
            "th { background: #252536; position: sticky; top: 0; z-index: 2; }",
            ".mon-header { text-align: left; font-weight: bold; background: #222230; position: sticky; left: 0; z-index: 1; }",
            ".learned { background: #2d5a3f; color: #57f287; font-weight: bold; }",
            ".unlearned { background: #22222a; color: #4e4e5e; }",
            ".type-tag { font-size: 10px; padding: 2px 4px; border-radius: 3px; display: block; margin-top: 2px; }",
            "</style></head><body>",
            "<h2>Pokémon TM/HM Compatibility Matrix</h2>",
            "<table><thead><tr><th class='mon-header'>Species</th>"
        ]

        # Table Column Headers (TMs/HMs)
        for code, name, t_type in DEFAULT_TMHM_LIST:
            html.append(f"<th>{code}<br>{name}<span class='type-tag'>{t_type}</span></th>")
        html.append("<th>Total</th></tr></thead><tbody>")

        # Table Rows (Species)
        for species, learned in sorted(self.species_learnsets.items()):
            html.append(f"<tr><td class='mon-header'>{species}</td>")
            count = 0
            for _, name, _ in DEFAULT_TMHM_LIST:
                formatted_name = name.upper().replace(" ", "_")
                if formatted_name in learned:
                    html.append("<td class='learned'>✓</td>")
                    count += 1
                else:
                    html.append("<td class='unlearned'>-</td>")
            html.append(f"<td><strong>{count}</strong></td></tr>")

        html.append("</tbody></table></body></html>")
        out_path.write_text("\n".join(html))
        print(f"[✓] Compatibility matrix exported: {out_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate GBA Pokemon TM/HM compatibility reports.")
    parser.add_argument("--species-info", type=Path, help="Input decomp species_info.h to parse")
    parser.add_argument("--out-html", type=Path, default=Path("tm_compatibility.html"), help="Destination HTML report")
    args = parser.parse_args()

    engine = CompatibilityMatrixEngine()
    if args.species_info and args.species_info.exists():
        engine.parse_decomp_species_info(args.species_info)
    else:
        # Provide sample default species if no path passed
        engine.add_species("SPECIES_AERODACTYL", ["DRAGON_CLAW", "TOXIC", "FLY", "ROCK_SMASH"])
        engine.add_species("SPECIES_CHARIZARD", ["FOCUS_PUNCH", "DRAGON_CLAW", "TOXIC", "FLY", "CUT", "STRENGTH", "ROCK_SMASH"])
        engine.add_species("SPECIES_BLASTOISE", ["WATER_PULSE", "TOXIC", "HAIL", "SURF", "STRENGTH", "WATERFALL", "DIVE"])

    engine.export_html_matrix(args.out_html)
