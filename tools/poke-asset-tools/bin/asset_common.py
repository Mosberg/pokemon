#!/usr/bin/env python3
"""
asset_common.py - Shared Core Library for GBA Retro Asset Tools & Compilers.
Provides GBA 15-bit color snapping, palette read/write (JASC, ACT, GBAPAL, C),
tile transformations, MSE diffing, and environment bootstrapping.
"""

import os
import struct
import sys
from pathlib import Path


# --- BOOTSTRAP ENVIRONMENT ---
def ensure_dependencies():
    """Ensure Pillow and NumPy are imported, re-executing with workspace venv if needed."""
    try:
        import numpy
        import PIL
    except ImportError:
        ws_root = Path(__file__).resolve().parents[3]
        venv_candidates = [
            ws_root / "pokeconfluence" / ".venv" / "bin" / "python",
            ws_root / ".venv" / "bin" / "python",
            Path("/home/mosberg/wsl_projects/pokemon/pokeconfluence/.venv/bin/python")
        ]
        for venv_py in venv_candidates:
            if venv_py.exists() and sys.executable != str(venv_py):
                os.execv(str(venv_py), [str(venv_py)] + sys.argv)
        raise RuntimeError("Pillow and NumPy are required. Please run inside the project virtualenv.")

# --- COLOR MATH & BGR555 CONVERSION ---
def snap_to_gba_15bit(r: int, g: int, b: int) -> tuple[int, int, int]:
    """Snaps standard 8-bit RGB channels to GBA 5-bit channel values (multiples of 8, scaled 0-255)."""
    r5 = round(int(r) * 31 / 255)
    g5 = round(int(g) * 31 / 255)
    b5 = round(int(b) * 31 / 255)
    return (int(r5 * 255 / 31), int(g5 * 255 / 31), int(b5 * 255 / 31))

to_gba_color = snap_to_gba_15bit

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

# --- PALETTE I/O ---
def read_jasc_pal(path: Path) -> list[tuple[int, int, int]]:
    """Reads a JASC-PAL text file and returns list of (r, g, b) tuples."""
    lines = [line.strip() for line in path.read_text().splitlines() if line.strip()]
    if not lines or lines[0] != "JASC-PAL":
        raise ValueError(f"Invalid JASC-PAL header in: {path}")
    count = int(lines[2])
    colors = []
    for line in lines[3:3 + count]:
        parts = [int(p) for p in line.split()]
        colors.append((parts[0], parts[1], parts[2]))
    return colors

def write_jasc_pal(path: Path, colors: list[tuple[int, int, int]], max_colors: int = 16):
    """Exports RGB colors to a compliant JASC-PAL text format."""
    lines = ["JASC-PAL", "0100", str(max_colors)]
    for i in range(max_colors):
        if i < len(colors):
            r, g, b = colors[i][:3]
        else:
            r, g, b = 0, 0, 0
        lines.append(f"{r} {g} {b}")
    path.write_text("\n".join(lines) + "\n")

def read_act(path: Path) -> list[tuple[int, int, int]]:
    """Reads Photoshop/Aseprite Adobe Color Table (768 bytes)."""
    raw = path.read_bytes()
    colors = []
    for i in range(0, min(len(raw), 768), 3):
        colors.append((raw[i], raw[i+1], raw[i+2]))
    return colors

def write_act(path: Path, colors: list[tuple[int, int, int]]):
    """Writes 768-byte Adobe Color Table."""
    buf = bytearray()
    for r, g, b in colors[:256]:
        buf.extend([r, g, b])
    while len(buf) < 768:
        buf.extend([0, 0, 0])
    path.write_bytes(buf)

def read_gbapal(path: Path) -> list[tuple[int, int, int]]:
    """Reads GBA native little-endian 16-bit BGR555 binary palette."""
    raw = path.read_bytes()
    colors = []
    for i in range(0, len(raw), 2):
        val = struct.unpack("<H", raw[i:i+2])[0]
        colors.append(bgr555_to_rgb888(val))
    return colors

def write_gbapal(path: Path, colors: list[tuple[int, int, int]], num_colors: int = 16):
    """Writes GBA native little-endian 16-bit BGR555 binary palette."""
    buf = bytearray()
    for r, g, b in colors[:num_colors]:
        bgr = rgb888_to_bgr555(r, g, b)
        buf.extend(struct.pack("<H", bgr))
    path.write_bytes(buf)

def write_c_palette_header(path: Path, colors: list[tuple[int, int, int]], var_name: str = "gCustomPalette"):
    """Writes C source header array of 16-bit BGR555 hex values."""
    hex_values = [f"0x{rgb888_to_bgr555(r, g, b):04X}" for r, g, b in colors[:16]]
    content = f"// Generated GBA BGR555 Palette: {var_name}\n"
    content += f"const u16 {var_name}[16] = {{\n    "
    content += ", ".join(hex_values)
    content += "\n};\n"
    path.write_text(content)

# --- TILE OPERATIONS ---
def get_tile_transforms(tile_arr):
    """Computes byte buffers / arrays for Normal, X-flipped, Y-flipped, and XY-flipped versions."""
    import numpy as np
    normal = tile_arr
    x_flip = np.fliplr(tile_arr)
    y_flip = np.flipud(tile_arr)
    xy_flip = np.flipud(np.fliplr(tile_arr))
    return {
        (False, False): normal,
        (True, False): x_flip,
        (False, True): y_flip,
        (True, True): xy_flip
    }

def tile_diff(t1, t2) -> float:
    """Mean squared error difference between two tiles."""
    import numpy as np
    return float(np.mean((t1.astype(float) - t2.astype(float)) ** 2))
