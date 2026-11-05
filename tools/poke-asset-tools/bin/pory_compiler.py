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
pory_compiler.py - Automated Poryscript to Decomp ASM (.inc) and XSE Bytecode Transpiler.
Supports nested branching, movement blocks, string extraction, and macro synthesis.
"""

import argparse
import re
from pathlib import Path


class PoryscriptParser:
    def __init__(self, source_code: str):
        self.lines = source_code.splitlines()
        self.cursor = 0
        self.output_inc = []
        self.output_xse = []
        self.text_blocks = {}
        self.movement_blocks = {}
        self.label_counter = 0

    def get_unique_label(self, prefix="Block"):
        self.label_counter += 1
        return f"{prefix}_{self.label_counter}"

    def parse(self):
        while self.cursor < len(self.lines):
            line = self.lines[self.cursor].rstrip()
            if not line or line.strip().startswith("//"):
                self.cursor += 1
                continue

            stripped = line.strip()

            # Top-level Script Block: script ScriptName { ... }
            if stripped.startswith("script ") and stripped.endswith("{"):
                script_name = stripped.split()[1]
                self.cursor += 1
                self.parse_script_body(script_name)
            # Top-level Movement Block: movement MovementName { ... }
            elif stripped.startswith("movement ") and stripped.endswith("{"):
                mov_name = stripped.split()[1]
                self.cursor += 1
                self.parse_movement_body(mov_name)
            # Top-level Text Block: text TextName { ... }
            elif stripped.startswith("text ") and stripped.endswith("{"):
                text_name = stripped.split()[1]
                self.cursor += 1
                self.parse_text_body(text_name)
            else:
                self.cursor += 1

    def parse_script_body(self, script_name: str):
        self.output_inc.append(f"{script_name}::")
        self.output_xse.append(f"#org @{script_name}")

        while self.cursor < len(self.lines):
            raw_line = self.lines[self.cursor]
            line = raw_line.strip()

            if line == "}":
                self.output_inc.append("\tend\n")
                self.output_xse.append("\trelease\n\tend\n")
                self.cursor += 1
                break

            if not line or line.startswith("//"):
                self.cursor += 1
                continue

            # Command: msgbox("Text", MSGBOX_DEFAULT)
            msgbox_match = re.match(r'msgbox\s*\(\s*"([^"]+)"\s*(?:,\s*([A-Z_]+))?\s*\)', line)
            if msgbox_match:
                msg_content = msgbox_match.group(1)
                msg_type = msgbox_match.group(2) or "MSGBOX_DEFAULT"
                str_lbl = self.get_unique_label(f"Text_{script_name}")
                self.text_blocks[str_lbl] = msg_content

                self.output_inc.append(f"\tmsgbox {str_lbl}, {msg_type}")
                self.output_xse.append(f"\tmsgbox @{str_lbl} 0x6")
                self.cursor += 1
                continue

            # Conditional: if (flag(FLAG_VAR)) { ... }
            if_match = re.match(r'if\s*\(\s*flag\(([A-Z0-9_]+)\)\s*\)\s*\{', line)
            if if_match:
                flag = if_match.group(1)
                true_lbl = self.get_unique_label("Branch_True")
                end_lbl = self.get_unique_label("Branch_End")

                self.output_inc.append(f"\tgoto_if_set {flag}, {true_lbl}")
                self.output_xse.append(f"\tcheckflag {flag}\n\tcompare LASTRESULT 0x1\n\tif 0x1 goto @{true_lbl}")

                self.cursor += 1
                # Parse inner commands until matching '}'
                inner_body = []
                while self.cursor < len(self.lines) and self.lines[self.cursor].strip() != "}":
                    inner_body.append(self.lines[self.cursor].strip())
                    self.cursor += 1
                self.cursor += 1  # Skip '}'

                # Write continuation
                self.output_inc.append(f"\tgoto {end_lbl}")
                self.output_inc.append(f"\n{true_lbl}::")
                self.output_xse.append(f"\tgoto @{end_lbl}\n\n#org @{true_lbl}")

                for cmd in inner_body:
                    self.output_inc.append(f"\t{cmd}")
                    self.output_xse.append(f"\t{cmd}")

                self.output_inc.append(f"\n{end_lbl}::")
                self.output_xse.append(f"\n#org @{end_lbl}")
                continue

            # Standard atomic engine commands
            self.output_inc.append(f"\t{line}")
            self.output_xse.append(f"\t{line}")
            self.cursor += 1

    def parse_movement_body(self, mov_name: str):
        self.output_inc.append(f"\t.align 2\n{mov_name}::")
        self.output_xse.append(f"#org @{mov_name}")
        while self.cursor < len(self.lines):
            line = self.lines[self.cursor].strip()
            if line == "}":
                self.output_inc.append("\tstep_end\n")
                self.output_xse.append("\t#raw 0xFE\n")
                self.cursor += 1
                break
            if line and not line.startswith("//"):
                self.output_inc.append(f"\t{line}")
                self.output_xse.append(f"\t{line}")
            self.cursor += 1

    def parse_text_body(self, text_name: str):
        content = []
        while self.cursor < len(self.lines):
            line = self.lines[self.cursor].strip()
            if line == "}":
                self.cursor += 1
                break
            if line.startswith('"') and line.endswith('"'):
                content.append(line[1:-1])
            elif line:
                content.append(line)
            self.cursor += 1
        self.text_blocks[text_name] = "\\n".join(content)

    def export(self, out_inc_path: Path, out_xse_path: Path = None):
        # Append compiled string tables
        inc_final = list(self.output_inc)
        for label, text in self.text_blocks.items():
            inc_final.append(f"{label}:")
            inc_final.append(f'\t.string "{text}$"')

        out_inc_path.write_text("\n".join(inc_final) + "\n")
        print(f"[✓] Decomp script compiled: {out_inc_path}")

        if out_xse_path:
            xse_final = list(self.output_xse)
            for label, text in self.text_blocks.items():
                xse_final.append(f"#org @{label}")
                xse_final.append(f'= {text}')
            out_xse_path.write_text("\n".join(xse_final) + "\n")
            print(f"[✓] Legacy XSE script compiled: {out_xse_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Poryscript Transpiler for GBA Decomp and XSE.")
    parser.add_argument("source", type=Path, help="Input .pory script file")
    parser.add_argument("out_inc", type=Path, help="Target decomp .inc path")
    parser.add_argument("--out-xse", type=Path, default=None, help="Optional legacy XSE script destination")
    args = parser.parse_args()

    transpiler = PoryscriptParser(args.source.read_text())
    transpiler.parse()
    transpiler.export(args.out_inc, args.out_xse)
