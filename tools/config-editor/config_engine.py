#!/usr/bin/env python3
"""
config_engine.py - High-fidelity parser, updater, and documentation extractor
for pokeconfluence/include/config C headers.
"""

import difflib
import glob
import os
import re
import shutil
from datetime import datetime
from pathlib import Path

GEN_CHOICES = ["GEN_LATEST", "GEN_1", "GEN_2", "GEN_3", "GEN_4", "GEN_5", "GEN_6", "GEN_7", "GEN_8", "GEN_9"]

# Safe Unicode symbols that render cleanly across Linux X11/Tkinter, WSLg, and Web
FILE_METADATA = {
    "ai.h": {
        "title": "Battle AI Behavior",
        "category": "Battle & AI",
        "icon": "[AI]",
        "glyph": "🧠",
        "description": "Configure AI switching thresholds, damage prediction, move scoring, and tactical decision logic.",
    },
    "battle.h": {
        "title": "Battle Engine Mechanics",
        "category": "Battle & AI",
        "icon": "[BAT]",
        "glyph": "⚔",
        "description": "Damage calculations, critical hits, battle gimmicks, experience distribution, and generational battle rules.",
    },
    "caps.h": {
        "title": "Level & EV Caps",
        "category": "Progression",
        "icon": "[CAP]",
        "glyph": "⚑",
        "description": "Multi-region 24-badge level caps, soft/hard caps, EV caps, and Rare Candy limits across Kanto, Johto, and Hoenn.",
    },
    "contest.h": {
        "title": "Contests & Visuals",
        "category": "Minigames",
        "icon": "[CON]",
        "glyph": "★",
        "description": "Contest mechanics, judging algorithms, and generational appeal formulas.",
    },
    "debug.h": {
        "title": "Debug Menus & Tools",
        "category": "System & Debug",
        "icon": "[DBG]",
        "glyph": "⚙",
        "description": "Overworld debug menu, key combinations, battle debug menus, sprite visualizers, and frame delay timers.",
    },
    "dexnav.h": {
        "title": "DexNav Mechanics",
        "category": "Overworld",
        "icon": "[DEX]",
        "glyph": "◎",
        "description": "DexNav search chaining, search levels, hidden abilities, egg moves, and shiny probability boosts.",
    },
    "fishing.h": {
        "title": "Fishing Mechanics",
        "category": "Overworld",
        "icon": "[FSH]",
        "glyph": "≈",
        "description": "Old/Good/Super Rod timing, bite intervals, mini-game behavior, and chain fishing.",
    },
    "follower_npc.h": {
        "title": "Follower Pokémon & NPCs",
        "category": "Overworld",
        "icon": "[FOL]",
        "glyph": "♠",
        "description": "Walking Pokémon companions, interaction dialogs, emote bubbles, and pathing algorithms.",
    },
    "general.h": {
        "title": "General System & Engine",
        "category": "System & Debug",
        "icon": "[SYS]",
        "glyph": "⚙",
        "description": "Compiler options, mGBA/AGB debug printing, UB bug fixes, and expansion macros.",
    },
    "item.h": {
        "title": "Items & Medicine",
        "category": "Items & Pokémon",
        "icon": "[ITM]",
        "glyph": "◆",
        "description": "Reusable TMs, Exp. Share modes, Repel prompts, bag sorting, healing amounts, and item sell prices.",
    },
    "map_preview_screen.h": {
        "title": "Map Preview Screens",
        "category": "UI & Display",
        "icon": "[MAP]",
        "glyph": "▤",
        "description": "FRLG/HGSS-style area entry banner screens and duration settings.",
    },
    "name_box.h": {
        "title": "Speaker Name Box",
        "category": "UI & Display",
        "icon": "[NAM]",
        "glyph": "💬",
        "description": "Overworld dialog speaker nameplates, colors, and positioning.",
    },
    "overworld.h": {
        "title": "Overworld Mechanics",
        "category": "Overworld",
        "icon": "[OVW]",
        "glyph": "▲",
        "description": "Indoor running, poison field damage, PC deposit healing, Berry growth/soil watering, and overworld sprites.",
    },
    "pokedex_plus_hgss.h": {
        "title": "HGSS Pokédex UI",
        "category": "UI & Display",
        "icon": "[PDX]",
        "glyph": "📖",
        "description": "Touch-screen style modernized Pokédex visual layouts and navigation features.",
    },
    "pokemon.h": {
        "title": "Pokémon Core Rules",
        "category": "Items & Pokémon",
        "icon": "[PKM]",
        "glyph": "⚡",
        "description": "Shiny rates, nature stat boosts, trade evolutions, experience curves, and IV calculations.",
    },
    "pokerus.h": {
        "title": "Pokérus Mechanics",
        "category": "Items & Pokémon",
        "icon": "[RUS]",
        "glyph": "✦",
        "description": "Pokérus infection chance, spread rate across party members, and strain durations.",
    },
    "quickstart.h": {
        "title": "Quickstart & Testing",
        "category": "System & Debug",
        "icon": "[QCK]",
        "glyph": "▶",
        "description": "Intro skipping, direct spawn warp coordinates, and quick testing profile overrides.",
    },
    "save.h": {
        "title": "Save System & Flash",
        "category": "Progression",
        "icon": "[SAV]",
        "glyph": "💾",
        "description": "Saveblock layout limits, modern save validation, backup sectors, and auto-repair.",
    },
    "species_enabled.h": {
        "title": "Enabled Species & Forms",
        "category": "Items & Pokémon",
        "icon": "[SPC]",
        "glyph": "🐲",
        "description": "Toggle Pokémon Generations 1-9, Regional Forms (Alolan, Galarian, Hisuian, Paldean), and individual evolution families.",
    },
    "summary_screen.h": {
        "title": "Pokémon Summary Screen",
        "category": "UI & Display",
        "icon": "[SUM]",
        "glyph": "📊",
        "description": "Stat screen enhancements, IV/EV graphs, nature coloring, move description popups, and shiny stars.",
    },
    "test.h": {
        "title": "Unit Test Configurations",
        "category": "System & Debug",
        "icon": "[TST]",
        "glyph": "🧪",
        "description": "Overrides used during automated C unit testing and integration suites.",
    },
    "text.h": {
        "title": "Text & Dialog Speeds",
        "category": "UI & Display",
        "icon": "[TXT]",
        "glyph": "≡",
        "description": "Text print speeds, auto-scroll delays, and font rendering configs.",
    },
    "wild_encounter.h": {
        "title": "Wild Encounters & Roamers",
        "category": "Overworld",
        "icon": "[WLD]",
        "glyph": "≈",
        "description": "Encounter rate multipliers, Sweet Scent, ability wild modifiers (Synchronize/Cute Charm), and roamer behaviors.",
    },
}

PRESETS = {
    "modern_gen9": {
        "title": "Modern Gen 9 Experience (Recommended)",
        "description": "Applies modern Pokémon Scarlet/Violet mechanics: reusable TMs, full Exp Share, Gen 9 critical and battle formulas, running indoors, and all species enabled.",
        "icon": "⚡",
        "updates": {
            "battle.h": {
                "B_CRIT_CHANCE": "GEN_LATEST",
                "B_CRIT_MULTIPLIER": "GEN_LATEST",
                "B_EXP_CATCH": "GEN_LATEST",
                "B_SPLIT_EXP": "GEN_LATEST",
                "B_SCALED_EXP": "GEN_LATEST",
                "B_BURN_DAMAGE": "GEN_LATEST",
                "B_PARALYSIS_SPEED": "GEN_LATEST",
            },
            "caps.h": {
                "B_EXP_CAP_TYPE": "EXP_CAP_SOFT",
                "B_LEVEL_CAP_TYPE": "LEVEL_CAP_BADGE_COUNT",
                "B_RARE_CANDY_CAP": "FALSE",
            },
            "item.h": {
                "I_REUSABLE_TMS": "TRUE",
                "I_KEY_ESCAPE_ROPE": "GEN_LATEST",
                "I_HEALTH_RECOVERY": "GEN_LATEST",
                "I_REPEL_LURE_MENU": "TRUE",
            },
            "overworld.h": {
                "OW_RUNNING_INDOORS": "GEN_LATEST",
                "OW_POISON_DAMAGE": "GEN_LATEST",
                "OW_CHOOSE_FROM_PC_AND_PARTY": "TRUE",
                "OW_PC_MOVE_ORDER": "GEN_LATEST",
            },
            "species_enabled.h": {
                "P_GEN_1_POKEMON": "TRUE",
                "P_GEN_2_POKEMON": "TRUE",
                "P_GEN_3_POKEMON": "TRUE",
                "P_GEN_4_POKEMON": "TRUE",
                "P_GEN_5_POKEMON": "TRUE",
                "P_GEN_6_POKEMON": "TRUE",
                "P_GEN_7_POKEMON": "TRUE",
                "P_GEN_8_POKEMON": "TRUE",
                "P_GEN_9_POKEMON": "TRUE",
                "P_MEGA_EVOLUTIONS": "TRUE",
                "P_REGIONAL_FORMS": "TRUE",
            },
        },
    },
    "hardcore_nuzlocke": {
        "title": "Hardcore Nuzlocke Challenge",
        "description": "Enforces strict level caps (Pokémon stop gaining exp at cap), Rare Candy cap lock, overworld poison damage, Gen 3 battle rules, and disables debug menus.",
        "icon": "☠",
        "updates": {
            "caps.h": {
                "B_EXP_CAP_TYPE": "EXP_CAP_HARD",
                "B_LEVEL_CAP_TYPE": "LEVEL_CAP_BADGE_COUNT",
                "B_RARE_CANDY_CAP": "TRUE",
                "B_LEVEL_CAP_EXP_UP": "FALSE",
                "B_EV_ITEMS_CAP": "TRUE",
            },
            "battle.h": {"B_SPLIT_EXP": "GEN_3", "B_SCALED_EXP": "GEN_3", "B_FRIENDSHIP_BOOST": "FALSE"},
            "overworld.h": {"OW_POISON_DAMAGE": "GEN_3", "OW_DOUBLE_APPROACH_WITH_ONE_MON": "TRUE"},
            "debug.h": {"DEBUG_OVERWORLD_MENU": "FALSE", "DEBUG_BATTLE_MENU": "FALSE"},
        },
    },
    "vanilla_gen3": {
        "title": "Vanilla Generation 3 (RSE Purist)",
        "description": "Reverts battle, overworld, and item behavior to authentic Ruby/Sapphire/Emerald 2004 mechanics: no indoor running, single-use TMs, and 200% crit damage.",
        "icon": "🌿",
        "updates": {
            "battle.h": {
                "B_CRIT_CHANCE": "GEN_3",
                "B_CRIT_MULTIPLIER": "GEN_3",
                "B_EXP_CATCH": "GEN_3",
                "B_TRAINER_EXP_MULTIPLIER": "GEN_3",
                "B_SPLIT_EXP": "GEN_3",
                "B_SCALED_EXP": "GEN_3",
                "B_BURN_DAMAGE": "GEN_3",
                "B_PARALYSIS_SPEED": "GEN_3",
            },
            "caps.h": {
                "B_EXP_CAP_TYPE": "EXP_CAP_NONE",
                "B_LEVEL_CAP_TYPE": "LEVEL_CAP_NONE",
                "B_EV_CAP_TYPE": "EV_CAP_NONE",
            },
            "item.h": {"I_REUSABLE_TMS": "FALSE", "I_KEY_ESCAPE_ROPE": "GEN_3", "I_HEALTH_RECOVERY": "GEN_3"},
            "overworld.h": {"OW_RUNNING_INDOORS": "GEN_3", "OW_POISON_DAMAGE": "GEN_3"},
        },
    },
    "sandbox_dev": {
        "title": "Developer & Sandbox Mode",
        "description": "Enables full overworld debug menus in start menu, battle debug menus, AI timer displays, fast text, and lifts level caps.",
        "icon": "🛠",
        "updates": {
            "debug.h": {
                "DEBUG_OVERWORLD_MENU": "TRUE",
                "DEBUG_OVERWORLD_IN_MENU": "TRUE",
                "DEBUG_BATTLE_MENU": "TRUE",
                "DEBUG_AI_DELAY_TIMER": "TRUE",
                "DEBUG_POKEMON_SPRITE_VISUALIZER": "TRUE",
            },
            "caps.h": {"B_EXP_CAP_TYPE": "EXP_CAP_NONE", "B_LEVEL_CAP_TYPE": "LEVEL_CAP_NONE"},
            "item.h": {"I_REUSABLE_TMS": "TRUE", "I_REPEL_LURE_MENU": "TRUE"},
            "overworld.h": {"OW_RUNNING_INDOORS": "GEN_LATEST", "OW_CHOOSE_FROM_PC_AND_PARTY": "TRUE"},
        },
    },
}


class ConfigEngine:
    def __init__(self, config_dir="/home/mosberg/wsl_projects/pokemon/pokeconfluence/include/config"):
        self.config_dir = Path(config_dir).resolve()
        self.backup_dir = self.config_dir / ".backups"
        self.backup_dir.mkdir(exist_ok=True)
        self.define_regex = re.compile(
            r"^(?P<prefix>\s*#define\s+)(?P<name>[A-Za-z0-9_]+)(?P<mid>\s+)(?P<val>.*?)(?P<trail>\s*(?://\s*(?P<comment>.*))?)$"
        )

    def list_files(self):
        """Return list of all configuration files with rich metadata."""
        files = sorted(glob.glob(str(self.config_dir / "*.h")))
        result = []
        for f in files:
            bname = os.path.basename(f)
            meta = FILE_METADATA.get(
                bname,
                {
                    "title": bname,
                    "category": "Other",
                    "icon": "[CFG]",
                    "glyph": "📄",
                    "description": f"Configuration header {bname}",
                },
            )
            cfgs = self.parse_file(bname)
            result.append(
                {
                    "filename": bname,
                    "path": f,
                    "title": meta["title"],
                    "category": meta["category"],
                    "icon": meta["icon"],
                    "glyph": meta.get("glyph", "📄"),
                    "description": meta["description"],
                    "config_count": len(cfgs),
                    "size_bytes": os.path.getsize(f),
                }
            )
        return result

    def parse_file(self, filename):
        """Parse a single config header into structured configuration records."""
        filepath = self.config_dir / filename
        if not filepath.exists():
            return []

        with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
            lines = f.readlines()

        configs = []
        current_section = "General Settings"
        doc_accumulator = []

        defined_constants = set()
        for line in lines:
            m = re.match(r"^\s*#define\s+([A-Za-z0-9_]+)\s+([A-Za-z0-9_]+)", line)
            if m:
                defined_constants.add(m.group(1))

        for idx, line in enumerate(lines):
            stripped = line.strip()

            if (
                not stripped
                or stripped.startswith("#ifndef")
                or stripped.startswith("#endif")
                or stripped.startswith("#undef")
            ):
                continue

            if stripped.startswith("//") and not stripped.startswith("///"):
                comment_text = stripped.lstrip("/ ").strip()
                if (
                    re.match(r"^[A-Z][A-Za-z0-9\s\.\-_/&]+$", comment_text)
                    and len(comment_text) < 45
                    and not any(
                        kw in comment_text
                        for kw in ["In Gen", "If set", "Setting", "Eg:", "Replace", "Note that", "See "]
                    )
                ):
                    current_section = comment_text
                    doc_accumulator = []
                    continue
                else:
                    doc_accumulator.append(comment_text)
                    continue

            m = self.define_regex.match(line)
            if m:
                name = m.group("name")
                val = m.group("val").strip() if m.group("val") else ""
                inline_comment = m.group("comment").strip() if m.group("comment") else ""

                if name.startswith("GUARD_CONFIG_") or name in [
                    "RHH_EXPANSION",
                    "UBFIX",
                    "BATTLE_ENGINE",
                    "POKEMON_EXPANSION",
                    "ITEM_EXPANSION",
                ]:
                    continue

                doc_lines = list(doc_accumulator)
                if inline_comment:
                    doc_lines.append(inline_comment)
                doc_text = " ".join(doc_lines).strip()
                doc_accumulator = []

                options = []
                bracket_m = re.search(r"\[([A-Za-z0-9_,\s]+)\]", doc_text)
                if bracket_m:
                    options = [o.strip() for o in bracket_m.group(1).split(",") if o.strip()]

                cfg_type = "text"
                if val in ["TRUE", "FALSE"]:
                    cfg_type = "boolean"
                    options = ["TRUE", "FALSE"]
                elif val.startswith("GEN_") or any(o.startswith("GEN_") for o in options):
                    cfg_type = "gen"
                    if not options:
                        options = GEN_CHOICES
                elif options:
                    cfg_type = "enum"
                elif (
                    val.startswith("P_GEN_")
                    or val.startswith("P_REGIONAL_")
                    or val.startswith("P_PIKACHU_")
                    or val.startswith("P_CROSS_")
                ):
                    cfg_type = "family"
                    options = ["Inherit (" + val + ")", "TRUE", "FALSE"]
                elif val.isdigit() or (val.startswith("-") and val[1:].isdigit()):
                    cfg_type = "number"
                elif val.startswith("0x") or val.startswith("0X"):
                    cfg_type = "hex"
                elif val in defined_constants:
                    cfg_type = "enum"
                    if not options:
                        options = [val]

                notices = []
                if "SAVE-BREAKING" in doc_text:
                    notices.append({"type": "danger", "text": "SAVE-BREAKING: Requires new save"})
                if "WIP" in doc_text:
                    notices.append({"type": "warning", "text": "WIP / Experimental"})
                if "POKE-CONFLUENCE" in doc_text or "POKE-CONFLUENCE" in line:
                    notices.append({"type": "info", "text": "Confluence Custom"})

                configs.append(
                    {
                        "name": name,
                        "value": val,
                        "type": cfg_type,
                        "options": options,
                        "section": current_section,
                        "description": doc_text,
                        "file": filename,
                        "line": idx + 1,
                        "notices": notices,
                        "raw_line": line,
                    }
                )

        return configs

    def get_all_configs(self):
        """Parse all 23 configuration files and return combined list."""
        all_configs = {}
        for f in sorted(glob.glob(str(self.config_dir / "*.h"))):
            bname = os.path.basename(f)
            all_configs[bname] = self.parse_file(bname)
        return all_configs

    def compute_diff(self, file_updates):
        """Compute unified diff for proposed changes without modifying files on disk."""
        results = {}
        for filename, updates in file_updates.items():
            filepath = self.config_dir / filename
            if not filepath.exists():
                continue

            with open(filepath, "r", encoding="utf-8") as f:
                original_lines = f.readlines()

            modified_lines = list(original_lines)
            changed_count = 0

            for idx, line in enumerate(modified_lines):
                m = self.define_regex.match(line)
                if m:
                    name = m.group("name")
                    if name in updates:
                        new_val = str(updates[name]).strip()
                        if new_val.startswith("Inherit ("):
                            new_val = new_val[9:-1]

                        old_val = m.group("val").strip()
                        if new_val != old_val:
                            prefix = m.group("prefix")
                            mid = m.group("mid")
                            trail = m.group("trail") or "\n"
                            if not trail.endswith("\n"):
                                trail += "\n"

                            modified_lines[idx] = f"{prefix}{name}{mid}{new_val}{trail}"
                            changed_count += 1

            if changed_count > 0:
                diff = "".join(
                    difflib.unified_diff(
                        original_lines, modified_lines, fromfile=f"a/{filename}", tofile=f"b/{filename}", lineterm=""
                    )
                )
                results[filename] = {"diff": diff, "changed_count": changed_count}

        return results

    def save_changes(self, file_updates):
        """Apply updates to configuration files with automatic timestamped backup."""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        backup_subfolder = self.backup_dir / f"backup_{timestamp}"
        backup_subfolder.mkdir(exist_ok=True)

        applied_summary = {}

        for filename, updates in file_updates.items():
            filepath = self.config_dir / filename
            if not filepath.exists() or not updates:
                continue

            with open(filepath, "r", encoding="utf-8") as f:
                original_lines = f.readlines()

            shutil.copy2(filepath, backup_subfolder / filename)
            modified_lines = list(original_lines)
            changed_names = []

            for idx, line in enumerate(modified_lines):
                m = self.define_regex.match(line)
                if m:
                    name = m.group("name")
                    if name in updates:
                        new_val = str(updates[name]).strip()
                        if new_val.startswith("Inherit ("):
                            new_val = new_val[9:-1]

                        old_val = m.group("val").strip()
                        if new_val != old_val:
                            prefix = m.group("prefix")
                            mid = m.group("mid")
                            trail = m.group("trail") or "\n"
                            if not trail.endswith("\n"):
                                trail += "\n"

                            modified_lines[idx] = f"{prefix}{name}{mid}{new_val}{trail}"
                            changed_names.append(name)

            if changed_names:
                with open(filepath, "w", encoding="utf-8") as f:
                    f.writelines(modified_lines)
                applied_summary[filename] = changed_names

        return {"success": True, "backup_folder": str(backup_subfolder), "applied": applied_summary}

    def list_backups(self):
        """List all previous backup snapshots."""
        backups = []
        for d in sorted(self.backup_dir.glob("backup_*"), reverse=True):
            if d.is_dir():
                files = [f.name for f in d.glob("*.h")]
                backups.append(
                    {"id": d.name, "timestamp": d.name.replace("backup_", ""), "path": str(d), "files": files}
                )
        return backups

    def restore_backup(self, backup_id):
        """Restore files from a specific backup snapshot."""
        target_dir = self.backup_dir / backup_id
        if not target_dir.exists():
            return {"success": False, "error": f"Backup {backup_id} not found"}

        restored_files = []
        for f in target_dir.glob("*.h"):
            shutil.copy2(f, self.config_dir / f.name)
            restored_files.append(f.name)

        return {"success": True, "restored": restored_files}

    def get_presets(self):
        """Return available configuration presets."""
        return PRESETS


if __name__ == "__main__":
    engine = ConfigEngine()
    files = engine.list_files()
    print(f"Found {len(files)} config files.")
    for f in files:
        print(f" - {f['icon']} {f['filename']}: {f['title']} ({f['config_count']} settings)")
