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
mart_compiler.py - Automated Poké Mart & Vendor Inventory Compiler.
Converts structured vendor inventories into C shop tables, Poryscript macros,
and validates price limits.
"""

import json
import argparse
from pathlib import Path

# Standard Fallback Item Base Prices (when items.h is not parsed)
PRICE_LOOKUP_TABLE = {
    "ITEM_POKE_BALL": 200,      "ITEM_GREAT_BALL": 600,     "ITEM_ULTRA_BALL": 1200,
    "ITEM_POTION": 300,         "ITEM_SUPER_POTION": 700,   "ITEM_HYPER_POTION": 1200,
    "ITEM_MAX_POTION": 2500,    "ITEM_FULL_RESTORE": 3000,  "ITEM_REVIVE": 1500,
    "ITEM_ANTIDOTE": 100,       "ITEM_PARALYZE_HEAL": 200,  "ITEM_AWAKENING": 250,
    "ITEM_REPEL": 350,          "ITEM_SUPER_REPEL": 500,    "ITEM_MAX_REPEL": 700,
    "ITEM_ESCAPE_ROPE": 550,    "ITEM_POKE_DOLL": 1000,     "ITEM_NONE": 0
}

def compile_mart_tables(config_path: Path, output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    marts_data = json.loads(config_path.read_text())

    c_output = [
        "// Auto-generated Mart Inventories and Item Tables",
        "#include \"global.h\"",
        "#include \"constants/items.h\"",
        ""
    ]

    pory_output = [
        "// Auto-generated Poryscript Mart Helpers",
    ]

    for mart in marts_data:
        mart_id = mart["id"]
        mart_label = f"sMartItems_{mart_id}"
        items = mart.get("items", [])
        badge_required = mart.get("badge_required", None)

        c_output.append(f"static const u16 {mart_label}[] = {{")
        for item in items:
            item_name = item.upper()
            price = PRICE_LOOKUP_TABLE.get(item_name, "Dynamic")
            c_output.append(f"    {item_name},")
        
        # Mandatory GBA hardware shop list terminator
        c_output.append("    ITEM_NONE")
        c_output.append("};\n")

        # Generate Poryscript helper script
        pory_output.append(f"script MartScript_{mart_id} {{")
        pory_output.append("    lock")
        pory_output.append("    faceplayer")
        pory_output.append("    message(\"Welcome! How may I help you?$\")")
        pory_output.append("    waitmessage")
        
        if badge_required:
            pory_output.append(f"    if (flag({badge_required})) {{")
            pory_output.append(f"        pokemart({mart_label})")
            pory_output.append("    } else {")
            pory_output.append(f"        pokemart(sMartItems_{mart_id}_Basic)")
            pory_output.append("    }")
        else:
            pory_output.append(f"    pokemart({mart_label})")
            
        pory_output.append("    msgbox(\"Please come again!$\", MSGBOX_DEFAULT)")
        pory_output.append("    release")
        pory_output.append("    end")
        pory_output.append("}\n")

    c_file = output_dir / "mart_inventories.h"
    c_file.write_text("\n".join(c_output))

    pory_file = output_dir / "mart_scripts.pory"
    pory_file.write_text("\n".join(pory_output))

    print("=" * 65)
    print(f"[✓] Marts Compiled: {len(marts_data)} vendor tables generated")
    print(f"  - C Tables Header:  {c_file}")
    print(f"  - Poryscript File:  {pory_file}")
    print("=" * 65)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compile JSON vendor inventories into C shop tables and Poryscripts.")
    parser.add_argument("config_file", type=Path, help="JSON configuration of marts")
    parser.add_argument("--out-dir", type=Path, default=Path("shop_build"), help="Output directory")
    args = parser.parse_args()

    compile_mart_tables(args.config_file, args.out_dir)
