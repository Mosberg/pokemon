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

import struct
import sys
from pathlib import Path


def rgb888_to_bgr555(r: int, g: int, b: int) -> int:
    """Converts 8-bit RGB channels to 15-bit GBA BGR555 integer."""
    r5 = (r >> 3) & 0x1F
    g5 = (g >> 3) & 0x1F
    b5 = (b >> 3) & 0x1F
    return (b5 << 10) | (g5 << 5) | r5

def bgr555_to_rgb888(bgr: int) -> tuple[int, int, int]:
    """Converts 15-bit GBA BGR555 integer to 8-bit RGB channels."""
    r = (bgr & 0x1F) << 3
    g = ((bgr >> 5) & 0x1F) << 3
    b = ((bgr >> 10) & 0x1F) << 3
    return (r, g, b)

def read_jasc_pal(path: Path) -> list[tuple[int, int, int]]:
    lines = [line.strip() for line in path.read_text().splitlines() if line.strip()]
    if lines[0] != "JASC-PAL":
        raise ValueError("Invalid JASC-PAL header.")
    count = int(lines[2])
    colors = []
    for line in lines[3:3 + count]:
        parts = [int(p) for p in line.split()]
        colors.append((parts[0], parts[1], parts[2]))
    return colors

def write_jasc_pal(path: Path, colors: list[tuple[int, int, int]]):
    lines = ["JASC-PAL", "0100", str(len(colors))]
    for r, g, b in colors:
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def read_act(path: Path) -> list[tuple[int, int, int]]:
    raw = path.read_bytes()
    colors = []
    # An ACT file is 768 bytes (256 colors * 3 bytes)
    for i in range(0, min(len(raw), 768), 3):
        colors.append((raw[i], raw[i+1], raw[i+2]))
    return colors

def write_act(path: Path, colors: list[tuple[int, int, int]]):
    buf = bytearray()
    for r, g, b in colors[:256]:
        buf.extend([r, g, b])
    while len(buf) < 768:
        buf.extend([0, 0, 0])
    path.write_bytes(buf)

def read_gbapal(path: Path) -> list[tuple[int, int, int]]:
    raw = path.read_bytes()
    colors = []
    for i in range(0, len(raw), 2):
        val = struct.unpack("<H", raw[i:i+2])[0]
        colors.append(bgr555_to_rgb888(val))
    return colors

def write_gbapal(path: Path, colors: list[tuple[int, int, int]]):
    buf = bytearray()
    for r, g, b in colors[:16]:
        bgr = rgb888_to_bgr555(r, g, b)
        buf.extend(struct.pack("<H", bgr))
    path.write_bytes(buf)

def write_c_header(path: Path, colors: list[tuple[int, int, int]], var_name="gCustomPalette"):
    hex_values = [f"0x{rgb888_to_bgr555(r, g, b):04X}" for r, g, b in colors[:16]]
    content = f"// Generated GBA BGR555 Palette\nconst u16 {var_name}[16] = {{\n    "
    content += ", ".join(hex_values)
    content += "\n};\n"
    path.write_text(content)

def convert_palette(input_file: str, output_file: str):
    inp = Path(input_file)
    out = Path(output_file)

    if inp.suffix.lower() == ".pal":
        colors = read_jasc_pal(inp)
    elif inp.suffix.lower() == ".act":
        colors = read_act(inp)
    elif inp.suffix.lower() in [".gbapal", ".bin"]:
        colors = read_gbapal(inp)
    else:
        raise ValueError(f"Unsupported input format: {inp.suffix}")

    out_suffix = out.suffix.lower()
    if out_suffix == ".pal":
        write_jasc_pal(out, colors)
    elif out_suffix == ".act":
        write_act(out, colors)
    elif out_suffix in [".gbapal", ".bin"]:
        write_gbapal(out, colors)
    elif out_suffix == ".h":
        write_c_header(out, colors, var_name=out.stem)
    else:
        raise ValueError(f"Unsupported output format: {out_suffix}")

    print(f"[✓] Converted {inp} -> {out}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python pal_converter.py <input.pal|.act|.gbapal> <output.pal|.act|.gbapal|.h>")
        sys.exit(1)
    convert_palette(sys.argv[1], sys.argv[2])
