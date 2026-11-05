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
charmap_converter.py - Multi-Language GBA Pokemon Proprietary Charset Transpiler.
Encodes UTF-8 strings to GBA binary/ASM bytes and decodes GBA strings back to UTF-8.
"""

import sys
import argparse
from pathlib import Path

# Core Gen 3 English/European Character Map Defaults
DEFAULT_CHARMAP = {
    ' ': 0x00, '0': 0xA1, '1': 0xA2, '2': 0xA3, '3': 0xA4, '4': 0xA5,
    '5': 0xA6, '6': 0xA7, '7': 0xA8, '8': 0xA9, '9': 0xAA, '!': 0xAB,
    '?': 0xAC, '.': 0xAD, '-': 0xAE, '…': 0xB0, '“': 0xB1, '”': 0xB2,
    '‘': 0xB3, '’': 0xB4, '♂': 0xB5, '♀': 0xB6, '$': 0xB7, ',': 0xB8,
    '×': 0xB9, '/': 0xBA, 'A': 0xBB, 'B': 0xBC, 'C': 0xBD, 'D': 0xBE,
    'E': 0xBF, 'F': 0xC0, 'G': 0xC1, 'H': 0xC2, 'I': 0xC3, 'J': 0xC4,
    'K': 0xC5, 'L': 0xC6, 'M': 0xC7, 'N': 0xC8, 'O': 0xC9, 'P': 0xCA,
    'Q': 0xCB, 'R': 0xCC, 'S': 0xCD, 'T': 0xCE, 'U': 0xCF, 'V': 0xD0,
    'W': 0xD1, 'X': 0xD2, 'Y': 0xD3, 'Z': 0xD4, 'a': 0xD5, 'b': 0xD6,
    'c': 0xD7, 'd': 0xD8, 'e': 0xD9, 'f': 0xDA, 'g': 0xDB, 'h': 0xDC,
    'i': 0xDD, 'j': 0xDE, 'k': 0xDF, 'l': 0xE0, 'm': 0xE1, 'n': 0xE2,
    'o': 0xE3, 'p': 0xE4, 'q': 0xE5, 'r': 0xE6, 's': 0xE7, 't': 0xE8,
    'u': 0xE9, 'v': 0xEA, 'w': 0xEB, 'x': 0xEC, 'y': 0xED, 'z': 0xEE,
    # European accents
    'é': 0x1B, 'É': 0x1C, 'à': 0x1D, 'è': 0x1E, 'ù': 0x1F
}

# Special Control Codes
ESCAPE_CODES = {
    "\\n": 0xFE,  # New line
    "\\l": 0xFA,  # Scroll line
    "\\p": 0xFB,  # New page
    "$":   0xFF   # Terminator
}

class GBACharConverter:
    def __init__(self, charmap_file: Path = None):
        self.char_to_byte = dict(DEFAULT_CHARMAP)
        if charmap_file and charmap_file.exists():
            self.load_charmap(charmap_file)
        self.byte_to_char = {v: k for k, v in self.char_to_byte.items()}

    def load_charmap(self, charmap_path: Path):
        for line in charmap_path.read_text(encoding="utf-8").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            # Format: 'A' = 0xBB or <0xFE> = \n
            if "=" in line:
                parts = line.split("=")
                token = parts[0].strip().strip("'\"")
                byte_val = int(parts[1].strip(), 16)
                self.char_to_byte[token] = byte_val

    def encode(self, text: str) -> bytearray:
        encoded = bytearray()
        i = 0
        while i < len(text):
            # Check for control sequences
            if text[i:i+2] in ESCAPE_CODES:
                encoded.append(ESCAPE_CODES[text[i:i+2]])
                i += 2
                continue
            
            char = text[i]
            if char in self.char_to_byte:
                encoded.append(self.char_to_byte[char])
            else:
                # Fallback to question mark
                encoded.append(self.char_to_byte.get('?', 0xAC))
            i += 1
            
        # Ensure standard GBA string terminator (0xFF)
        if len(encoded) == 0 or encoded[-1] != 0xFF:
            encoded.append(0xFF)
        return encoded

    def decode(self, data: bytes) -> str:
        chars = []
        rev_escape = {v: k for k, v in ESCAPE_CODES.items()}
        for b in data:
            if b == 0xFF:
                break
            if b in rev_escape:
                chars.append(rev_escape[b])
            elif b in self.byte_to_char:
                chars.append(self.byte_to_char[b])
            else:
                chars.append(f"\\x{b:02X}")
        return "".join(chars)

def convert_text(input_file: Path, output_file: Path, decode_mode: bool = False, charmap: Path = None):
    conv = GBACharConverter(charmap)
    if decode_mode:
        raw_bytes = input_file.read_bytes()
        result_text = conv.decode(raw_bytes)
        output_file.write_text(result_text, encoding="utf-8")
        print(f"[✓] Decoded {len(raw_bytes)} GBA bytes -> {output_file}")
    else:
        raw_text = input_file.read_text(encoding="utf-8")
        bin_data = conv.encode(raw_text)
        output_file.write_bytes(bin_data)
        
        # Also emit C array
        hex_dump = ", ".join([f"0x{b:02X}" for b in bin_data])
        c_path = output_file.with_suffix(".h")
        c_path.write_text(f"// Encoded GBA String\nconst u8 sCustomText[{len(bin_data)}] = {{ {hex_dump} }};\n")
        print(f"[✓] Encoded {len(raw_text)} UTF-8 characters -> {output_file} (and {c_path})")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert between UTF-8 and proprietary GBA Pokemon character encodings.")
    parser.add_argument("input", type=Path, help="Input file (UTF-8 text or raw binary)")
    parser.add_argument("output", type=Path, help="Output destination")
    parser.add_argument("--decode", action="store_true", help="Decode GBA binary back to UTF-8")
    parser.add_argument("--charmap", type=Path, default=None, help="Custom charmap.txt table")
    args = parser.parse_args()

    convert_text(args.input, args.output, args.decode, args.charmap)
