#!/usr/bin/env python3
"""
================================================================================
 Pokémon GBA Decomp Region Map Asset & Layout Studio (poke_region_map_tool.py)
 Next-Generation Tooling for pokeemerald, pokefirered, & pokeemerald-expansion
 Standards & Best Practices Edition — 09/11/2026
================================================================================

Highlights & Architectural Invariants:
  1. Palette Bank 7 & 8 Hardware Compliance:
     - Resolves Tilemap Studio palette-splitting corruption by strictly mapping
       the whole canvas to 8bpp affine/text hardware Palette Banks 7 & 8 (indices 112–143)
       and index 0 (transparency key).
     - Supports Euclidean RGB, Perceptual Weighted RGB, and Floyd-Steinberg Dither.
  2. Byte-Exact Hardware Layout:
     - Master Tileset: 128 px wide (16 tiles/row), indexed Mode 'P', 8bpp.
     - Tilemap Binary: Exactly 4096 bytes (64x64 u8 grid, top-left 30x20 active).
     - Palette: 32 colors in JASC-PAL format & 64-byte BGR555 LE binary (.gbapal).
     - GBA BIOS LZ77-0x10 compression built-in for .bin.lz and .8bpp.lz.
  3. Professional Multi-Tool 28×15 Fly Layout Matrix Editor:
     - Tools: Pencil/Brush, Line Corridor, Rectangle Box, Flood Fill, Eyedropper, Eraser.
     - Multi-layer artwork underlay with live opacity slider (0–100%).
     - Adjustable matrix cell zoom (16px to 32px), cell code labels, and coordinate rulers.
     - 4-Way Grid Nudge / Shift controls (← ↑ ↓ →) to align imported layouts.
     - Unlimited Undo / Redo history stack (Ctrl+Z / Ctrl+Y).
     - Live MAPSEC search & filter bar.
     - Section validator (detects disconnected tiles, out-of-bounds, duplicates).
     - Bidirectional C array (.h) and JSON (.json) parser & generator.
  4. Interactive Visual & Tileset Inspection:
     - 1x to 5x pixel-crisp nearest zoom on GBA screen preview.
     - Click any tile in the 128px Master Tileset to highlight all occurrences on screen!
     - Hover inspector showing Tile ID, Palette Index, BGR555, and MAPSEC.
"""

import argparse
import json
import os
import re
import sys
import zipfile
from typing import Any, Dict, List, Optional, Tuple

try:
    import numpy as np
    from PIL import Image, ImageDraw, ImageTk
except ImportError:
    print("[!] Error: Missing requirements. Please install:\n    pip install pillow numpy")
    sys.exit(1)

try:
    import tkinter as tk
    from tkinter import filedialog, messagebox, ttk

    HAS_TK = True
except ImportError:
    HAS_TK = False

# ==============================================================================
# Hardware Constants & Palette Definitions
# ==============================================================================
SCREEN_WIDTH_TILES = 30
SCREEN_HEIGHT_TILES = 20
SCREEN_WIDTH_PX = 240
SCREEN_HEIGHT_PX = 160

FLY_MAP_WIDTH = 28
FLY_MAP_HEIGHT = 15

TILE_SIZE = 8
TILEMAP_FULL_DIM = 64
TILEMAP_FULL_BYTES = 4096

# Generation III Official Region Map Palette (Palette Banks 7 & 8)
DECOMP_REGION_MAP_PALETTE = {
    0: (255, 0, 255),  # 0: Hardware transparency / background key
    # Palette Bank 7 (Indices 112 - 127): Ocean & Landmass Elevation
    113: (156, 213, 255),  # Ocean base light
    114: (164, 180, 255),  # Ocean base scanline
    115: (123, 180, 213),  # Shallow water / coastal shelf
    116: (74, 156, 230),  # Coastal shadow
    117: (41, 131, 230),  # Mid water depth
    118: (65, 106, 205),  # Dark ocean depth
    119: (0, 115, 172),  # Deep ocean
    120: (32, 74, 197),  # Trench blue
    121: (0, 57, 139),  # Abyss navy
    122: (213, 255, 123),  # Land highlight
    123: (172, 238, 49),  # Grass light green
    124: (98, 213, 0),  # Grass base green
    125: (57, 172, 8),  # Mountain dark green
    126: (0, 115, 0),  # Deep foliage
    127: (205, 205, 148),  # Sand / dock border
    # Palette Bank 8 (Indices 128 - 143): Routes, Metropolitan & Landmark Markers
    129: (255, 255, 255),  # Route white dot / border highlight
    130: (238, 230, 172),  # Route path light yellow
    131: (238, 230, 115),  # Route mid-light yellow
    132: (238, 189, 57),  # Route base gold
    133: (246, 213, 82),  # Route yellow accent
    134: (230, 164, 0),  # Route dark border orange
    135: (255, 172, 16),  # City red outline / inner orange
    136: (255, 57, 16),  # City marker red highlight
    137: (246, 0, 0),  # City marker red core
    138: (148, 0, 0),  # City marker dark crimson
    139: (205, 205, 205),  # Gray landmark / facility highlight
    140: (98, 98, 98),  # Gray landmark border
}

QUANT_INDICES = sorted(DECOMP_REGION_MAP_PALETTE.keys())
QUANT_COLORS = np.array([DECOMP_REGION_MAP_PALETTE[i] for i in QUANT_INDICES], dtype=np.float32)

PALETTE_METADATA = {
    0: ("KEY", "Transparency Key", "#FF00FF"),
    113: ("B7", "Ocean base light", "#9CD5FF"),
    114: ("B7", "Ocean base scanline", "#A4B4FF"),
    115: ("B7", "Shallow water / coastal shelf", "#7BB4D5"),
    116: ("B7", "Coastal shadow", "#4A9CE6"),
    117: ("B7", "Mid water depth", "#2983E6"),
    118: ("B7", "Dark ocean depth", "#416ACD"),
    119: ("B7", "Deep ocean", "#0073AC"),
    120: ("B7", "Trench blue", "#204AC5"),
    121: ("B7", "Abyss navy", "#00398B"),
    122: ("B7", "Land highlight", "#D5FF7B"),
    123: ("B7", "Grass light green", "#ACEE31"),
    124: ("B7", "Grass base green", "#62D500"),
    125: ("B7", "Mountain dark green", "#39AC08"),
    126: ("B7", "Deep foliage", "#007300"),
    127: ("B7", "Sand / dock border", "#CDCD94"),
    129: ("B8", "Route white dot / highlight", "#FFFFFF"),
    130: ("B8", "Route path light yellow", "#EEE6AC"),
    131: ("B8", "Route mid-light yellow", "#EEE673"),
    132: ("B8", "Route base gold", "#EEBD39"),
    133: ("B8", "Route yellow accent", "#F6D552"),
    134: ("B8", "Route dark border orange", "#E6A400"),
    135: ("B8", "City outline orange", "#FFAC10"),
    136: ("B8", "City red highlight", "#FF3910"),
    137: ("B8", "City red core", "#F60000"),
    138: ("B8", "City dark crimson", "#940000"),
    139: ("B8", "Gray landmark highlight", "#CDCDCD"),
    140: ("B8", "Gray landmark border", "#626262"),
}

# Extensive Preset Map Sections Library
PRESET_REGIONS = {
    "JOHTO": [
        {"id": "MAPSEC_JOHTO_NEW_BARK_TOWN", "name": "NEW BARK TOWN", "x": 19, "y": 10, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_CHERRYGROVE_CITY", "name": "CHERRYGROVE CITY", "x": 13, "y": 10, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_VIOLET_CITY", "name": "VIOLET CITY", "x": 11, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_AZALEA_TOWN", "name": "AZALEA TOWN", "x": 8, "y": 13, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_GOLDENROD_CITY", "name": "GOLDENROD CITY", "x": 6, "y": 8, "width": 1, "height": 2},
        {"id": "MAPSEC_JOHTO_ECRUTEAK_CITY", "name": "ECRUTEAK CITY", "x": 8, "y": 3, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_OLIVINE_CITY", "name": "OLIVINE CITY", "x": 3, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_CIANWOOD_CITY", "name": "CIANWOOD CITY", "x": 0, "y": 10, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_MAHOGANY_TOWN", "name": "MAHOGANY TOWN", "x": 17, "y": 3, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_BLACKTHORN_CITY", "name": "BLACKTHORN CITY", "x": 20, "y": 7, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_LAKE_OF_RAGE", "name": "LAKE OF RAGE", "x": 14, "y": 1, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_SILVER_CAVE", "name": "SILVER CAVE", "x": 23, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_APEX_SUMMIT", "name": "APEX SUMMIT", "x": 23, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_BATTLE_TOWER", "name": "BATTLE TOWER", "x": 1, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_DARK_CAVE", "name": "DARK CAVE", "x": 20, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_FAST_SHIP", "name": "FAST SHIP", "x": 3, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_ILEX_FOREST", "name": "ILEX FOREST", "x": 6, "y": 12, "width": 2, "height": 2},
        {"id": "MAPSEC_JOHTO_MERIDIAN_STATION", "name": "MERIDIAN STATION", "x": 4, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_MT_MORTAR", "name": "MT. MORTAR", "x": 14, "y": 3, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_NATIONAL_PARK", "name": "NATIONAL PARK", "x": 8, "y": 5, "width": 2, "height": 1},
        {"id": "MAPSEC_JOHTO_RUINS_OF_ALPH", "name": "RUINS OF ALPH", "x": 10, "y": 7, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_SPROUT_TOWER", "name": "SPROUT TOWER", "x": 11, "y": 4, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_TOHJO_FALLS", "name": "TOHJO FALLS", "x": 21, "y": 10, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_UNION_CAVE", "name": "UNION CAVE", "x": 11, "y": 13, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_WHIRL_ISLANDS", "name": "WHIRL ISLANDS", "x": 1, "y": 8, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_26", "name": "ROUTE 26", "x": 22, "y": 8, "width": 1, "height": 3},
        {"id": "MAPSEC_JOHTO_ROUTE_29", "name": "ROUTE 29", "x": 14, "y": 10, "width": 5, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_30", "name": "ROUTE 30", "x": 13, "y": 6, "width": 1, "height": 4},
        {"id": "MAPSEC_JOHTO_ROUTE_31", "name": "ROUTE 31", "x": 12, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_32", "name": "ROUTE 32", "x": 11, "y": 6, "width": 1, "height": 7},
        {"id": "MAPSEC_JOHTO_ROUTE_33", "name": "ROUTE 33", "x": 10, "y": 13, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_34", "name": "ROUTE 34", "x": 6, "y": 10, "width": 1, "height": 2},
        {"id": "MAPSEC_JOHTO_ROUTE_35", "name": "ROUTE 35", "x": 6, "y": 6, "width": 1, "height": 2},
        {"id": "MAPSEC_JOHTO_ROUTE_36", "name": "ROUTE 36", "x": 7, "y": 5, "width": 4, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_37", "name": "ROUTE 37", "x": 8, "y": 4, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_38", "name": "ROUTE 38", "x": 4, "y": 3, "width": 4, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_39", "name": "ROUTE 39", "x": 3, "y": 3, "width": 1, "height": 2},
        {"id": "MAPSEC_JOHTO_ROUTE_40", "name": "ROUTE 40", "x": 1, "y": 6, "width": 2, "height": 2},
        {"id": "MAPSEC_JOHTO_ROUTE_41", "name": "ROUTE 41", "x": 0, "y": 8, "width": 2, "height": 3},
        {"id": "MAPSEC_JOHTO_ROUTE_42", "name": "ROUTE 42", "x": 9, "y": 3, "width": 8, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_43", "name": "ROUTE 43", "x": 14, "y": 2, "width": 1, "height": 1},
        {"id": "MAPSEC_JOHTO_ROUTE_44", "name": "ROUTE 44", "x": 17, "y": 4, "width": 1, "height": 3},
        {"id": "MAPSEC_JOHTO_ROUTE_45", "name": "ROUTE 45", "x": 16, "y": 7, "width": 1, "height": 3},
        {"id": "MAPSEC_JOHTO_ROUTE_46", "name": "ROUTE 46", "x": 16, "y": 10, "width": 1, "height": 1},
    ],
    "HOENN": [
        {"id": "MAPSEC_LITTLEROOT_TOWN", "name": "LITTLEROOT TOWN", "x": 4, "y": 11, "width": 1, "height": 1},
        {"id": "MAPSEC_OLDALE_TOWN", "name": "OLDALE TOWN", "x": 4, "y": 9, "width": 1, "height": 1},
        {"id": "MAPSEC_DEWFORD_TOWN", "name": "DEWFORD TOWN", "x": 2, "y": 14, "width": 1, "height": 1},
        {"id": "MAPSEC_LAVARIDGE_TOWN", "name": "LAVARIDGE TOWN", "x": 5, "y": 3, "width": 1, "height": 1},
        {"id": "MAPSEC_FALLARBOR_TOWN", "name": "FALLARBOR TOWN", "x": 3, "y": 0, "width": 1, "height": 1},
        {"id": "MAPSEC_VERDANTURF_TOWN", "name": "VERDANTURF TOWN", "x": 4, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_PACIFIDLOG_TOWN", "name": "PACIFIDLOG TOWN", "x": 17, "y": 10, "width": 1, "height": 1},
        {"id": "MAPSEC_PETALBURG_CITY", "name": "PETALBURG CITY", "x": 1, "y": 9, "width": 1, "height": 1},
        {"id": "MAPSEC_SLATEPORT_CITY", "name": "SLATEPORT CITY", "x": 8, "y": 10, "width": 1, "height": 2},
        {"id": "MAPSEC_MAUVILLE_CITY", "name": "MAUVILLE CITY", "x": 8, "y": 6, "width": 2, "height": 1},
        {"id": "MAPSEC_RUSTBORO_CITY", "name": "RUSTBORO CITY", "x": 0, "y": 5, "width": 1, "height": 2},
        {"id": "MAPSEC_FORTREE_CITY", "name": "FORTREE CITY", "x": 12, "y": 1, "width": 1, "height": 1},
        {"id": "MAPSEC_LILYCOVE_CITY", "name": "LILYCOVE CITY", "x": 18, "y": 3, "width": 2, "height": 1},
        {"id": "MAPSEC_MOSSDEEP_CITY", "name": "MOSSDEEP CITY", "x": 24, "y": 5, "width": 2, "height": 1},
        {"id": "MAPSEC_SOOTOPOLIS_CITY", "name": "SOOTOPOLIS CITY", "x": 21, "y": 7, "width": 1, "height": 1},
        {"id": "MAPSEC_EVER_GRANDE_CITY", "name": "EVER GRANDE CITY", "x": 27, "y": 8, "width": 1, "height": 2},
        {"id": "MAPSEC_ROUTE_101", "name": "ROUTE 101", "x": 4, "y": 10, "width": 1, "height": 1},
        {"id": "MAPSEC_ROUTE_102", "name": "ROUTE 102", "x": 2, "y": 9, "width": 2, "height": 1},
        {"id": "MAPSEC_ROUTE_103", "name": "ROUTE 103", "x": 4, "y": 8, "width": 4, "height": 1},
        {"id": "MAPSEC_ROUTE_104", "name": "ROUTE 104", "x": 0, "y": 7, "width": 1, "height": 3},
    ],
    "KANTO": [
        {"id": "MAPSEC_PALLET_TOWN", "name": "PALLET TOWN", "x": 4, "y": 11, "width": 1, "height": 1},
        {"id": "MAPSEC_VIRIDIAN_CITY", "name": "VIRIDIAN CITY", "x": 4, "y": 8, "width": 1, "height": 1},
        {"id": "MAPSEC_PEWTER_CITY", "name": "PEWTER CITY", "x": 4, "y": 4, "width": 1, "height": 1},
        {"id": "MAPSEC_CERULEAN_CITY", "name": "CERULEAN CITY", "x": 14, "y": 3, "width": 1, "height": 1},
        {"id": "MAPSEC_LAVENDER_TOWN", "name": "LAVENDER TOWN", "x": 18, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_VERMILION_CITY", "name": "VERMILION CITY", "x": 14, "y": 9, "width": 1, "height": 1},
        {"id": "MAPSEC_CELADON_CITY", "name": "CELADON CITY", "x": 11, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_FUCHSIA_CITY", "name": "FUCHSIA CITY", "x": 13, "y": 12, "width": 1, "height": 1},
        {"id": "MAPSEC_CINNABAR_ISLAND", "name": "CINNABAR ISLAND", "x": 4, "y": 14, "width": 1, "height": 1},
        {"id": "MAPSEC_INDIGO_PLATEAU", "name": "INDIGO PLATEAU", "x": 2, "y": 3, "width": 1, "height": 1},
        {"id": "MAPSEC_SAFFRON_CITY", "name": "SAFFRON CITY", "x": 14, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_ROUTE_1", "name": "ROUTE 1", "x": 4, "y": 9, "width": 1, "height": 2},
        {"id": "MAPSEC_ROUTE_2", "name": "ROUTE 2", "x": 4, "y": 5, "width": 1, "height": 3},
        {"id": "MAPSEC_ROUTE_3", "name": "ROUTE 3", "x": 5, "y": 4, "width": 4, "height": 1},
        {"id": "MAPSEC_ROUTE_4", "name": "ROUTE 4", "x": 9, "y": 3, "width": 5, "height": 1},
    ],
    "SEVII123": [
        {"id": "MAPSEC_ONE_ISLAND", "name": "ONE ISLAND", "x": 5, "y": 6, "width": 1, "height": 1},
        {"id": "MAPSEC_TWO_ISLAND", "name": "TWO ISLAND", "x": 12, "y": 8, "width": 1, "height": 1},
        {"id": "MAPSEC_THREE_ISLAND", "name": "THREE ISLAND", "x": 19, "y": 9, "width": 1, "height": 1},
    ],
    "SEVII45": [
        {"id": "MAPSEC_FOUR_ISLAND", "name": "FOUR ISLAND", "x": 8, "y": 8, "width": 1, "height": 1},
        {"id": "MAPSEC_FIVE_ISLAND", "name": "FIVE ISLAND", "x": 18, "y": 10, "width": 1, "height": 1},
    ],
    "SEVII67": [
        {"id": "MAPSEC_SIX_ISLAND", "name": "SIX ISLAND", "x": 9, "y": 5, "width": 1, "height": 1},
        {"id": "MAPSEC_SEVEN_ISLAND", "name": "SEVEN ISLAND", "x": 17, "y": 7, "width": 1, "height": 1},
    ],
}


# ==============================================================================
# Helper Math, Line Drawing & GBA Compression
# ==============================================================================
def rgb_to_gba(r: int, g: int, b: int) -> int:
    """Pack 8-bit RGB into 15-bit BGR555 unsigned 16-bit integer."""
    return ((r >> 3) & 0x1F) | (((g >> 3) & 0x1F) << 5) | (((b >> 3) & 0x1F) << 10)


def bresenham_line(x0: int, y0: int, x1: int, y1: int) -> List[Tuple[int, int]]:
    """Computes discrete grid coordinates along a line between (x0, y0) and (x1, y1)."""
    points = []
    dx = abs(x1 - x0)
    dy = -abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx + dy
    while True:
        points.append((x0, y0))
        if x0 == x1 and y0 == y1:
            break
        e2 = 2 * err
        if e2 >= dy:
            err += dy
            x0 += sx
        if e2 <= dx:
            err += dx
            y0 += sy
    return points


def compress_gba_lz77(data: bytes) -> bytes:
    """
    Pure Python implementation of GBA BIOS LZ77 Type 0x10 compression.
    Emits byte-accurate .lz buffers ready for INCBIN_U32 or decompression.
    """
    in_len = len(data)
    out = bytearray()
    out.append(0x10)
    out.append(in_len & 0xFF)
    out.append((in_len >> 8) & 0xFF)
    out.append((in_len >> 16) & 0xFF)

    in_pos = 0
    while in_pos < in_len:
        flag_byte_pos = len(out)
        out.append(0)
        flag_byte = 0

        for block in range(8):
            if in_pos >= in_len:
                break

            window_start = max(0, in_pos - 4096)
            window = data[window_start:in_pos]
            max_len = min(18, in_len - in_pos)

            best_len = 0
            best_disp = 0

            if max_len >= 3:
                for match_len in range(max_len, 2, -1):
                    pat = data[in_pos : in_pos + match_len]
                    found = window.rfind(pat)
                    if found != -1:
                        best_len = match_len
                        best_disp = in_pos - (window_start + found)
                        break

            if best_len >= 3:
                flag_byte |= 1 << (7 - block)
                disp = best_disp - 1
                b1 = ((best_len - 3) << 4) | ((disp >> 8) & 0x0F)
                b2 = disp & 0xFF
                out.append(b1)
                out.append(b2)
                in_pos += best_len
            else:
                out.append(data[in_pos])
                in_pos += 1

        out[flag_byte_pos] = flag_byte

    while len(out) % 4 != 0:
        out.append(0)
    return bytes(out)


def abbreviate_mapsec(sec_id: str) -> str:
    """Produces a short 2-3 character badge code for cell display."""
    if not sec_id or sec_id == "MAPSEC_NONE":
        return ""
    s = sec_id.replace("MAPSEC_JOHTO_", "").replace("MAPSEC_", "")
    if s.startswith("ROUTE_"):
        return "R" + s.replace("ROUTE_", "")
    parts = [p for p in s.split("_") if p]
    if len(parts) >= 2:
        return (parts[0][0] + parts[1][0]).upper()
    return s[:3].upper()


# ==============================================================================
# RegionMapCompiler: The Core Hardware Engine
# ==============================================================================
class RegionMapCompiler:
    @staticmethod
    def quantize_canvas(px_rgb: np.ndarray, mode: str = "euclidean", dither: bool = False) -> np.ndarray:
        """
        Quantizes a (160, 240, 3) RGB array to hardware palette indices.
        Modes: 'euclidean', 'perceptual'
        """
        work = px_rgb.astype(np.float32).copy()
        quantized = np.zeros((SCREEN_HEIGHT_PX, SCREEN_WIDTH_PX), dtype=np.uint8)
        weights = (
            np.array([0.299, 0.587, 0.114], dtype=np.float32)
            if mode == "perceptual"
            else np.array([1.0, 1.0, 1.0], dtype=np.float32)
        )

        for y in range(SCREEN_HEIGHT_PX):
            for x in range(SCREEN_WIDTH_PX):
                old_px = np.clip(work[y, x], 0, 255)
                diffs = (QUANT_COLORS - old_px) * weights
                dists = np.sum(diffs**2, axis=1)
                best_idx = int(np.argmin(dists))
                hw_idx = QUANT_INDICES[best_idx]
                quantized[y, x] = hw_idx

                if dither:
                    new_px = QUANT_COLORS[best_idx]
                    quant_err = old_px - new_px
                    if x + 1 < SCREEN_WIDTH_PX:
                        work[y, x + 1] += quant_err * (7.0 / 16.0)
                    if y + 1 < SCREEN_HEIGHT_PX:
                        if x - 1 >= 0:
                            work[y + 1, x - 1] += quant_err * (3.0 / 16.0)
                        work[y + 1, x] += quant_err * (5.0 / 16.0)
                        if x + 1 < SCREEN_WIDTH_PX:
                            work[y + 1, x + 1] += quant_err * (1.0 / 16.0)

        return quantized

    @staticmethod
    def compile_map(
        input_image_or_path: Any,
        output_dir: str,
        map_prefix: str = "map_johto",
        compress_lz: bool = True,
        quant_mode: str = "euclidean",
        dither: bool = False,
    ) -> Dict[str, Any]:
        """
        Executes the full GBA hardware compilation pipeline:
          1. Conforms canvas to 240x160 px.
          2. Quantizes to Banks 7 & 8 indices.
          3. Deduplicates 8x8 tiles into a 128px-wide master tileset.
          4. Emits 4096-byte tilemap (.bin), JASC-PAL (.pal), BGR555 (.gbapal),
             master PNG, raw 8bpp tiles, and optional LZ-compressed buffers.
        """
        os.makedirs(output_dir, exist_ok=True)

        if isinstance(input_image_or_path, str):
            if not os.path.exists(input_image_or_path):
                raise FileNotFoundError(f"Source image '{input_image_or_path}' does not exist.")
            src = Image.open(input_image_or_path).convert("RGB")
        elif isinstance(input_image_or_path, Image.Image):
            src = input_image_or_path.convert("RGB")
        else:
            raise TypeError("Expected file path string or PIL.Image instance.")

        if src.size != (SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX):
            src = src.resize((SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX), Image.Resampling.NEAREST)

        px_rgb = np.array(src)
        quantized_map = RegionMapCompiler.quantize_canvas(px_rgb, mode=quant_mode, dither=dither)

        # Deduplicate 8x8 Hardware Tiles & Track Usage Counts
        tile_dict: Dict[bytes, int] = {}
        unique_tiles: List[np.ndarray] = []
        tile_usage_counts: Dict[int, int] = {}
        active_tilemap = np.zeros((SCREEN_HEIGHT_TILES, SCREEN_WIDTH_TILES), dtype=np.uint8)

        for ty in range(SCREEN_HEIGHT_TILES):
            for tx in range(SCREEN_WIDTH_TILES):
                tile = quantized_map[ty * TILE_SIZE : (ty + 1) * TILE_SIZE, tx * TILE_SIZE : (tx + 1) * TILE_SIZE]
                tile_bytes = tile.tobytes()
                if tile_bytes not in tile_dict:
                    tid = len(unique_tiles)
                    tile_dict[tile_bytes] = tid
                    unique_tiles.append(tile)
                    tile_usage_counts[tid] = 0
                tid = tile_dict[tile_bytes]
                active_tilemap[ty, tx] = tid
                tile_usage_counts[tid] += 1

        tile_count = len(unique_tiles)

        # Construct 128px-wide Master Tileset Image
        tiles_x = 16
        tiles_y = max(1, (tile_count + tiles_x - 1) // tiles_x)
        tilesheet = np.zeros((tiles_y * TILE_SIZE, tiles_x * TILE_SIZE), dtype=np.uint8)

        for i, t in enumerate(unique_tiles):
            gy = (i // tiles_x) * TILE_SIZE
            gx = (i % tiles_x) * TILE_SIZE
            tilesheet[gy : gy + TILE_SIZE, gx : gx + TILE_SIZE] = t

        flat_palette = [0, 0, 0] * 256
        for idx, rgb in DECOMP_REGION_MAP_PALETTE.items():
            flat_palette[idx * 3 : idx * 3 + 3] = list(rgb)

        out_png = Image.fromarray(tilesheet, mode="P")
        out_png.putpalette(flat_palette)

        png_path = os.path.join(output_dir, f"{map_prefix}.png")
        pal_path = os.path.join(output_dir, f"{map_prefix}.pal")
        gbapal_path = os.path.join(output_dir, f"{map_prefix}.gbapal")
        bin_path = os.path.join(output_dir, f"{map_prefix}.bin")
        raw8bpp_path = os.path.join(output_dir, f"{map_prefix}.8bpp")

        out_png.save(png_path)

        # JASC-PAL Format (32 colors: Banks 7 & 8)
        pal_lines = ["JASC-PAL", "0100", "32"]
        for i in range(112, 128):
            rgb = DECOMP_REGION_MAP_PALETTE.get(i, (0, 0, 0))
            pal_lines.append(f"{rgb[0]} {rgb[1]} {rgb[2]}")
        for i in range(128, 144):
            rgb = DECOMP_REGION_MAP_PALETTE.get(i, (0, 0, 0))
            pal_lines.append(f"{rgb[0]} {rgb[1]} {rgb[2]}")

        with open(pal_path, "w", encoding="utf-8") as f:
            f.write("\n".join(pal_lines) + "\n")

        # .gbapal (64 bytes BGR555 LE)
        gbapal_bytes = bytearray(64)
        for i in range(32):
            idx = 112 + i
            rgb = DECOMP_REGION_MAP_PALETTE.get(idx, (0, 0, 0))
            packed = rgb_to_gba(rgb[0], rgb[1], rgb[2])
            gbapal_bytes[i * 2] = packed & 0xFF
            gbapal_bytes[i * 2 + 1] = (packed >> 8) & 0xFF

        with open(gbapal_path, "wb") as f:
            f.write(gbapal_bytes)

        # 4096-Byte Tilemap Binary (.bin)
        full_bin = np.zeros((TILEMAP_FULL_DIM, TILEMAP_FULL_DIM), dtype=np.uint8)
        full_bin[:SCREEN_HEIGHT_TILES, :SCREEN_WIDTH_TILES] = active_tilemap
        bin_bytes = full_bin.tobytes()

        with open(bin_path, "wb") as f:
            f.write(bin_bytes)

        # Raw 8bpp Tiles
        raw_8bpp = bytearray()
        for t in unique_tiles:
            raw_8bpp.extend(t.tobytes())

        with open(raw8bpp_path, "wb") as f:
            f.write(raw_8bpp)

        bin_lz_path = None
        raw8bpp_lz_path = None
        if compress_lz:
            bin_lz_path = os.path.join(output_dir, f"{map_prefix}.bin.lz")
            raw8bpp_lz_path = os.path.join(output_dir, f"{map_prefix}.8bpp.lz")
            with open(bin_lz_path, "wb") as f:
                f.write(compress_gba_lz77(bin_bytes))
            with open(raw8bpp_lz_path, "wb") as f:
                f.write(compress_gba_lz77(raw_8bpp))

        return {
            "tile_count": tile_count,
            "png_path": png_path,
            "pal_path": pal_path,
            "gbapal_path": gbapal_path,
            "bin_path": bin_path,
            "raw8bpp_path": raw8bpp_path,
            "bin_lz_path": bin_lz_path,
            "raw8bpp_lz_path": raw8bpp_lz_path,
            "quantized_map": quantized_map,
            "active_tilemap": active_tilemap,
            "tilesheet": tilesheet,
            "unique_tiles": unique_tiles,
            "tile_usage_counts": tile_usage_counts,
        }

    @staticmethod
    def decompile_map(bin_path: str, png_path: str) -> Image.Image:
        """Reconstructs a full 240x160 RGB image from a 4096-byte .bin and 128px tileset .png."""
        with open(bin_path, "rb") as f:
            bin_data = f.read()

        if len(bin_data) < TILEMAP_FULL_BYTES:
            raise ValueError(f"Tilemap too small: expected {TILEMAP_FULL_BYTES} bytes, got {len(bin_data)}")

        tilemap = np.frombuffer(bin_data, dtype=np.uint8).reshape((TILEMAP_FULL_DIM, TILEMAP_FULL_DIM))
        tileset_img = Image.open(png_path).convert("P")
        tileset_arr = np.array(tileset_img)

        tiles_x = 16
        total_tiles_h = tileset_arr.shape[0] // TILE_SIZE
        tiles = []
        for ty in range(total_tiles_h):
            for tx in range(tiles_x):
                tile = tileset_arr[ty * TILE_SIZE : (ty + 1) * TILE_SIZE, tx * TILE_SIZE : (tx + 1) * TILE_SIZE]
                tiles.append(tile)

        out_indices = np.zeros((SCREEN_HEIGHT_PX, SCREEN_WIDTH_PX), dtype=np.uint8)
        for row in range(SCREEN_HEIGHT_TILES):
            for col in range(SCREEN_WIDTH_TILES):
                tile_idx = tilemap[row, col]
                if tile_idx < len(tiles):
                    out_indices[row * TILE_SIZE : (row + 1) * TILE_SIZE, col * TILE_SIZE : (col + 1) * TILE_SIZE] = (
                        tiles[tile_idx]
                    )

        flat_pal = tileset_img.getpalette() or [0, 0, 0] * 256
        out_img = Image.fromarray(out_indices, mode="P")
        out_img.putpalette(flat_pal)
        return out_img.convert("RGB")

    @staticmethod
    def generate_layout_header(region_name: str, grid_matrix: List[List[str]], prefix: str = "map_johto") -> str:
        """Emits standard C region_map_layout_<region>.h matrix."""
        reg_clean = region_name.lower().replace("map_", "").strip()
        reg_cap = reg_clean.capitalize()
        guard = f"GUARD_DATA_REGION_MAP_LAYOUT_{reg_clean.upper()}_H"

        lines = [
            "// ============================================================================",
            f"// POKE-CONFLUENCE / GEN III REGION MAP LAYOUT: {reg_clean.upper()}",
            "// Canvas: 240x160 px (30x20 tiles) | Fly Cursor Window: 28x15 tiles",
            "// Auto-generated by Pokemon GBA Region Map Studio",
            "// ============================================================================",
            f"#ifndef {guard}",
            f"#define {guard}",
            "",
            '#include "constants/region_map_sections.h"',
            "",
            f"static const mapsec_u8_t sRegionMapSections_{reg_cap}[MAP_HEIGHT][MAP_WIDTH] = {{",
        ]

        for y in range(FLY_MAP_HEIGHT):
            row_items = []
            for x in range(FLY_MAP_WIDTH):
                sec = grid_matrix[y][x] if y < len(grid_matrix) and x < len(grid_matrix[y]) else "MAPSEC_NONE"
                row_items.append(sec or "MAPSEC_NONE")
            comma = "," if y < FLY_MAP_HEIGHT - 1 else ""
            lines.append(f"    {{{', '.join(row_items)}}}{comma}")

        lines.extend(["};", "", f"#endif // {guard}", ""])
        return "\n".join(lines)

    @staticmethod
    def generate_entries_header(region_name: str, entries: List[Dict[str, Any]]) -> str:
        """Emits C region_map_entries_<region>.h array."""
        reg_clean = region_name.lower().replace("map_", "").strip()
        reg_cap = reg_clean.capitalize()
        guard = f"GUARD_DATA_REGION_MAP_ENTRIES_{reg_clean.upper()}_H"

        lines = [
            "// ============================================================================",
            f"// POKE-CONFLUENCE REGION MAP ENTRIES: {reg_clean.upper()}",
            f"// Total Map Sections Defined: {len(entries)}",
            "// Auto-generated by Pokemon GBA Region Map Studio",
            "// ============================================================================",
            f"#ifndef {guard}",
            f"#define {guard}",
            "",
            f"static const struct RegionMapLocation gRegionMapEntries_{reg_cap}[] = {{",
        ]

        for e in entries:
            sec_id = e.get("id", "MAPSEC_NONE")
            x = e.get("x", 0)
            y = e.get("y", 0)
            w = e.get("width", e.get("w", 1))
            h = e.get("height", e.get("h", 1))
            name = e.get("name", sec_id.replace("MAPSEC_", "").replace("_", " "))
            lines.append(f"    [{sec_id}] = {{")
            lines.append(f"        .x = {x},")
            lines.append(f"        .y = {y},")
            lines.append(f"        .width = {w},")
            lines.append(f"        .height = {h},")
            lines.append(f'        .name = COMPOUND_STRING("{name}"),')
            lines.append("    },")

        lines.extend(["};", "", f"#endif // {guard}", ""])
        return "\n".join(lines)

    @staticmethod
    def generate_sections_json(entries: List[Dict[str, Any]]) -> str:
        """Emits region_map_sections.json format."""
        out_list = []
        for e in entries:
            out_list.append(
                {
                    "id": e.get("id", "MAPSEC_NONE"),
                    "name": e.get("name", ""),
                    "x": e.get("x", 0),
                    "y": e.get("y", 0),
                    "width": e.get("width", e.get("w", 1)),
                    "height": e.get("height", e.get("h", 1)),
                }
            )
        return json.dumps({"map_sections": out_list}, indent=2, ensure_ascii=False) + "\n"

    @staticmethod
    def parse_layout_header(c_code: str) -> List[List[str]]:
        """Parses an existing region_map_layout_*.h C array back into a 28x15 grid."""
        grid = [["MAPSEC_NONE" for _ in range(FLY_MAP_WIDTH)] for _ in range(FLY_MAP_HEIGHT)]
        m = re.search(r"sRegionMapSections_\w+\[MAP_HEIGHT\]\[MAP_WIDTH\]\s*=\s*\{(.*?)\};", c_code, re.DOTALL)
        if not m:
            m = re.search(r"\{\s*\{(.*?)\}\s*\}", c_code, re.DOTALL)

        if m:
            block = m.group(1).strip()
            row_matches = re.findall(r"\{(.*?)\}", block)
            for y, row_str in enumerate(row_matches[:FLY_MAP_HEIGHT]):
                tokens = [t.strip() for t in row_str.split(",") if t.strip()]
                for x, tok in enumerate(tokens[:FLY_MAP_WIDTH]):
                    grid[y][x] = tok
        return grid

    @staticmethod
    def parse_sections_json(json_str: str) -> List[Dict[str, Any]]:
        """Parses region_map_sections.json."""
        data = json.loads(json_str)
        items = data.get("map_sections", data if isinstance(data, list) else [])
        entries = []
        for item in items:
            if "x" in item and "y" in item:
                entries.append(
                    {
                        "id": item.get("id", "MAPSEC_NONE"),
                        "name": item.get("name", ""),
                        "x": int(item.get("x", 0)),
                        "y": int(item.get("y", 0)),
                        "width": int(item.get("width", 1)),
                        "height": int(item.get("height", 1)),
                    }
                )
        return entries


# ==============================================================================
# Undo / Redo Command History
# ==============================================================================
class HistoryManager:
    def __init__(self, max_depth: int = 60):
        self.undo_stack: List[Tuple[List[List[str]], List[Dict[str, Any]]]] = []
        self.redo_stack: List[Tuple[List[List[str]], List[Dict[str, Any]]]] = []
        self.max_depth = max_depth

    def push(self, grid: List[List[str]], entries: List[Dict[str, Any]]):
        grid_copy = [row[:] for row in grid]
        entries_copy = [dict(e) for e in entries]
        self.undo_stack.append((grid_copy, entries_copy))
        if len(self.undo_stack) > self.max_depth:
            self.undo_stack.pop(0)
        self.redo_stack.clear()

    def can_undo(self) -> bool:
        return len(self.undo_stack) > 1

    def can_redo(self) -> bool:
        return len(self.redo_stack) > 0

    def undo(
        self, current_grid: List[List[str]], current_entries: List[Dict[str, Any]]
    ) -> Optional[Tuple[List[List[str]], List[Dict[str, Any]]]]:
        if not self.can_undo():
            return None
        curr_state = ([row[:] for row in current_grid], [dict(e) for e in current_entries])
        self.redo_stack.append(curr_state)
        self.undo_stack.pop()
        prev_grid, prev_entries = self.undo_stack[-1]
        return ([row[:] for row in prev_grid], [dict(e) for e in prev_entries])

    def redo(
        self, current_grid: List[List[str]], current_entries: List[Dict[str, Any]]
    ) -> Optional[Tuple[List[List[str]], List[Dict[str, Any]]]]:
        if not self.can_redo():
            return None
        curr_state = ([row[:] for row in current_grid], [dict(e) for e in current_entries])
        self.undo_stack.append(curr_state)
        next_grid, next_entries = self.redo_stack.pop()
        return ([row[:] for row in next_grid], [dict(e) for e in next_entries])


# ==============================================================================
# GUI: Modern Desktop Application Implementation
# ==============================================================================
if HAS_TK:

    class RegionMapStudio(tk.Tk):
        def __init__(self):
            super().__init__()
            self.title("Pokémon GBA Decomp Region Map Asset & Layout Studio — 2026 Edition")
            self.geometry("1320x880")
            self.minsize(1060, 740)
            self.configure(bg="#090d16")

            # Data Models
            self.input_file = tk.StringVar()
            self.output_dir = tk.StringVar(value=os.getcwd())
            self.prefix_var = tk.StringVar(value="map_johto")
            self.region_var = tk.StringVar(value="JOHTO")
            self.quant_mode_var = tk.StringVar(value="euclidean")
            self.dither_var = tk.BooleanVar(value=False)

            # Matrix Editor Controls & Settings
            self.current_tool = tk.StringVar(value="PENCIL")  # PENCIL, LINE, RECT, BUCKET, PICK, ERASE
            self.active_brush = tk.StringVar(value="MAPSEC_JOHTO_NEW_BARK_TOWN")
            self.brush_filter_var = tk.StringVar()
            self.matrix_cell_size = tk.IntVar(value=24)
            self.zoom_level = tk.IntVar(value=3)
            self.underlay_opacity = tk.DoubleVar(value=0.55)
            self.show_grid = tk.BooleanVar(value=True)
            self.show_rulers = tk.BooleanVar(value=True)
            self.show_cell_codes = tk.BooleanVar(value=True)
            self.show_rect_overlay = tk.BooleanVar(value=True)
            self.compress_lz_var = tk.BooleanVar(value=True)

            # Live Images & Matrix Data
            self.source_img: Optional[Image.Image] = None
            self.compiled_data: Optional[Dict[str, Any]] = None
            self.highlighted_tile_id: Optional[int] = None
            self.grid_matrix: List[List[str]] = [
                ["MAPSEC_NONE" for _ in range(FLY_MAP_WIDTH)] for _ in range(FLY_MAP_HEIGHT)
            ]
            self.entries: List[Dict[str, Any]] = [dict(e) for e in PRESET_REGIONS.get("JOHTO", [])]
            self.selected_table_idx: Optional[int] = None

            # Drag Interaction States
            self.drag_start_tile: Optional[Tuple[int, int]] = None
            self.drag_cur_tile: Optional[Tuple[int, int]] = None

            # Undo / Redo Manager
            self.history = HistoryManager()
            self.rebuild_grid_from_entries(record_history=False)
            self.history.push(self.grid_matrix, self.entries)

            self.apply_theme()
            self.build_ui()
            self.bind_shortcuts()

            # Load default demo map
            self.load_demo("johto")

        def apply_theme(self):
            """Applies modern high-contrast 2026 dark UI styling."""
            style = ttk.Style(self)
            try:
                style.theme_use("clam")
            except Exception:
                pass

            style.configure(".", background="#0e1726", foreground="#e2e8f0", font=("Segoe UI", 9))
            style.configure("TLabel", background="#0e1726", foreground="#e2e8f0")
            style.configure("TFrame", background="#0e1726")
            style.configure("TLabelframe", background="#0e1726", foreground="#06b6d4", relief=tk.SOLID, borderwidth=1)
            style.configure(
                "TLabelframe.Label", background="#0e1726", foreground="#06b6d4", font=("Segoe UI", 9, "bold")
            )

            style.configure("TButton", background="#1e293b", foreground="#f8fafc", borderwidth=1, padding=5)
            style.map(
                "TButton",
                background=[("active", "#06b6d4"), ("pressed", "#0891b2")],
                foreground=[("active", "#090d16"), ("pressed", "#090d16")],
            )

            style.configure("TNotebook", background="#090d16", tabmargins=[4, 6, 4, 0])
            style.configure(
                "TNotebook.Tab",
                background="#1e293b",
                foreground="#94a3b8",
                padding=[14, 7],
                font=("Segoe UI", 9, "bold"),
            )
            style.map("TNotebook.Tab", background=[("selected", "#06b6d4")], foreground=[("selected", "#090d16")])

            style.configure(
                "Treeview",
                background="#090d16",
                fieldbackground="#090d16",
                foreground="#f1f5f9",
                font=("Segoe UI", 9),
                rowheight=22,
            )
            style.configure(
                "Treeview.Heading", background="#1e293b", foreground="#38bdf8", font=("Segoe UI", 9, "bold")
            )
            style.map("Treeview", background=[("selected", "#0284c7")])

        def build_ui(self):
            # Top Header Banner
            top_bar = tk.Frame(self, bg="#0e1726", height=48, bd=1, relief=tk.SOLID)
            top_bar.pack(fill=tk.X, side=tk.TOP)

            tk.Label(
                top_bar, text="🗺️ GBA Region Map Studio", font=("Segoe UI", 13, "bold"), fg="#06b6d4", bg="#0e1726"
            ).pack(side=tk.LEFT, padx=14)
            tk.Label(
                top_bar,
                text="Gen III Decomp Suite · 8bpp Affine / Banks 7 & 8 · 4096-B Tilemap",
                font=("Segoe UI", 9),
                fg="#64748b",
                bg="#0e1726",
            ).pack(side=tk.LEFT, padx=4)

            # Quick Shortcuts on Right Top Bar
            r_tools = tk.Frame(top_bar, bg="#0e1726")
            r_tools.pack(side=tk.RIGHT, padx=10)

            tk.Button(
                r_tools,
                text="↶ Undo",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8, "bold"),
                padx=6,
                command=self.undo,
            ).pack(side=tk.LEFT, padx=2)
            tk.Button(
                r_tools,
                text="↷ Redo",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8, "bold"),
                padx=6,
                command=self.redo,
            ).pack(side=tk.LEFT, padx=2)
            tk.Button(
                r_tools,
                text="⚡ Compile ROM Assets",
                bg="#10b981",
                fg="#090d16",
                font=("Segoe UI", 9, "bold"),
                padx=10,
                command=self.compile_all,
            ).pack(side=tk.LEFT, padx=4)
            tk.Button(
                r_tools,
                text="📦 Export .ZIP",
                bg="#06b6d4",
                fg="#090d16",
                font=("Segoe UI", 9, "bold"),
                padx=8,
                command=self.export_zip,
            ).pack(side=tk.LEFT, padx=4)

            # Split Panes: Left Config (400px) | Right Multi-Tab View
            panes = tk.PanedWindow(self, orient=tk.HORIZONTAL, bg="#090d16", bd=0, sashwidth=4)
            panes.pack(fill=tk.BOTH, expand=True, padx=8, pady=6)

            left_frame = tk.Frame(panes, bg="#090d16", width=400)
            right_frame = tk.Frame(panes, bg="#090d16")
            panes.add(left_frame, minsize=360)
            panes.add(right_frame, minsize=680)

            # --- Left Panel 1: Source & Output Configuration ---
            grp_io = ttk.LabelFrame(left_frame, text=" 1. Project Paths & Compiler Config ", padding=8)
            grp_io.pack(fill=tk.X, pady=(0, 6))

            ttk.Label(grp_io, text="Source Art (240x160):").grid(row=0, column=0, sticky=tk.W)
            ent_src = ttk.Entry(grp_io, textvariable=self.input_file, width=24)
            ent_src.grid(row=0, column=1, padx=4, pady=2, sticky=tk.EW)
            ttk.Button(grp_io, text="Open...", width=7, command=self.browse_source).grid(row=0, column=2, padx=2)

            btn_demo = tk.Frame(grp_io, bg="#0e1726")
            btn_demo.grid(row=1, column=0, columnspan=3, pady=(2, 4), sticky=tk.W)
            tk.Button(
                btn_demo,
                text="🎨 Hoenn Demo",
                bg="#1e293b",
                fg="#06b6d4",
                font=("Segoe UI", 8),
                command=lambda: self.load_demo("hoenn"),
            ).pack(side=tk.LEFT, padx=2)
            tk.Button(
                btn_demo,
                text="🎨 Johto Demo",
                bg="#1e293b",
                fg="#06b6d4",
                font=("Segoe UI", 8),
                command=lambda: self.load_demo("johto"),
            ).pack(side=tk.LEFT, padx=2)
            tk.Button(
                btn_demo,
                text="📂 Load Sample",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=self.load_shipped_sample,
            ).pack(side=tk.LEFT, padx=2)

            ttk.Label(grp_io, text="Output Directory:").grid(row=2, column=0, sticky=tk.W, pady=(4, 0))
            ent_out = ttk.Entry(grp_io, textvariable=self.output_dir, width=24)
            ent_out.grid(row=2, column=1, padx=4, pady=(4, 0), sticky=tk.EW)
            ttk.Button(grp_io, text="Browse...", width=7, command=self.browse_output).grid(
                row=2, column=2, padx=2, pady=(4, 0)
            )

            ttk.Label(grp_io, text="Prefix & Region:").grid(row=3, column=0, sticky=tk.W, pady=(4, 0))
            row_p = tk.Frame(grp_io, bg="#0e1726")
            row_p.grid(row=3, column=1, columnspan=2, sticky=tk.W, pady=(4, 0))
            ttk.Entry(row_p, textvariable=self.prefix_var, width=12).pack(side=tk.LEFT)
            ttk.Label(row_p, text=" Region: ").pack(side=tk.LEFT)
            cb_reg = ttk.Combobox(row_p, textvariable=self.region_var, values=list(PRESET_REGIONS.keys()), width=9)
            cb_reg.pack(side=tk.LEFT)
            cb_reg.bind("<<ComboboxSelected>>", self.on_region_changed)

            # Quantization & Compression Options
            row_q = tk.Frame(grp_io, bg="#0e1726")
            row_q.grid(row=4, column=0, columnspan=3, sticky=tk.EW, pady=(6, 0))
            ttk.Label(row_q, text="Quantizer:").pack(side=tk.LEFT)
            cb_q = ttk.Combobox(row_q, textvariable=self.quant_mode_var, values=["euclidean", "perceptual"], width=10)
            cb_q.pack(side=tk.LEFT, padx=4)
            tk.Checkbutton(
                row_q,
                text="Dither",
                variable=self.dither_var,
                bg="#0e1726",
                fg="#94a3b8",
                selectcolor="#090d16",
                command=self.compile_all,
            ).pack(side=tk.LEFT, padx=2)
            tk.Checkbutton(
                row_q,
                text="LZ77 (.lz)",
                variable=self.compress_lz_var,
                bg="#0e1726",
                fg="#94a3b8",
                selectcolor="#090d16",
            ).pack(side=tk.LEFT, padx=2)

            # --- Left Panel 2: Fly Layout Matrix Editor Suite ---
            grp_tool = ttk.LabelFrame(left_frame, text=" 2. Fly Matrix Editor Controls (28×15) ", padding=8)
            grp_tool.pack(fill=tk.X, pady=(0, 6))

            # Drawing Tool Selector
            r_tools_bar = tk.Frame(grp_tool, bg="#0e1726")
            r_tools_bar.pack(fill=tk.X, pady=(0, 6))

            for t_code, t_label in [
                ("PENCIL", "✏️ Brush"),
                ("LINE", "📏 Line"),
                ("RECT", "⬚ Rect"),
                ("BUCKET", "🪣 Fill"),
                ("PICK", "💧 Pick"),
                ("ERASE", "🧹 Erase"),
            ]:
                rb = tk.Radiobutton(
                    r_tools_bar,
                    text=t_label,
                    value=t_code,
                    variable=self.current_tool,
                    indicatoron=False,
                    bg="#1e293b",
                    fg="#e2e8f0",
                    selectcolor="#06b6d4",
                    font=("Segoe UI", 8, "bold"),
                    padx=4,
                    pady=3,
                )
                rb.pack(side=tk.LEFT, padx=1, expand=True, fill=tk.X)

            # Filter & Brush Picker
            r_flt = tk.Frame(grp_tool, bg="#0e1726")
            r_flt.pack(fill=tk.X, pady=2)
            ttk.Label(r_flt, text="Filter MAPSEC:").pack(side=tk.LEFT)
            ent_flt = ttk.Entry(r_flt, textvariable=self.brush_filter_var, width=18)
            ent_flt.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)
            ent_flt.bind("<KeyRelease>", self.on_brush_filter_changed)

            r_brush = tk.Frame(grp_tool, bg="#0e1726")
            r_brush.pack(fill=tk.X, pady=2)
            ttk.Label(r_brush, text="Active Brush:").pack(side=tk.LEFT)
            self.cb_brush = ttk.Combobox(r_brush, textvariable=self.active_brush, width=25)
            self.cb_brush.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)

            # Underlay Opacity & Cell Size
            r_op = tk.Frame(grp_tool, bg="#0e1726")
            r_op.pack(fill=tk.X, pady=(4, 2))
            ttk.Label(r_op, text="Art Opacity:").pack(side=tk.LEFT)
            s_op = tk.Scale(
                r_op,
                variable=self.underlay_opacity,
                from_=0.0,
                to=1.0,
                resolution=0.05,
                orient=tk.HORIZONTAL,
                bg="#0e1726",
                fg="#06b6d4",
                highlightthickness=0,
                length=110,
                command=lambda v: self.render_matrix_editor(),
            )
            s_op.pack(side=tk.LEFT, padx=4)

            ttk.Label(r_op, text="Cell px:").pack(side=tk.LEFT)
            cb_cs = ttk.Combobox(r_op, textvariable=self.matrix_cell_size, values=[18, 20, 24, 28, 32], width=4)
            cb_cs.pack(side=tk.LEFT, padx=2)
            cb_cs.bind("<<ComboboxSelected>>", lambda e: self.render_matrix_editor())

            # Overlay Toggles
            r_chk = tk.Frame(grp_tool, bg="#0e1726")
            r_chk.pack(fill=tk.X, pady=2)
            tk.Checkbutton(
                r_chk,
                text="Rulers",
                variable=self.show_rulers,
                bg="#0e1726",
                fg="#94a3b8",
                selectcolor="#090d16",
                command=self.render_matrix_editor,
            ).pack(side=tk.LEFT, padx=1)
            tk.Checkbutton(
                r_chk,
                text="Grid",
                variable=self.show_grid,
                bg="#0e1726",
                fg="#94a3b8",
                selectcolor="#090d16",
                command=self.render_matrix_editor,
            ).pack(side=tk.LEFT, padx=1)
            tk.Checkbutton(
                r_chk,
                text="Codes",
                variable=self.show_cell_codes,
                bg="#0e1726",
                fg="#94a3b8",
                selectcolor="#090d16",
                command=self.render_matrix_editor,
            ).pack(side=tk.LEFT, padx=1)
            tk.Checkbutton(
                r_chk,
                text="Boxes",
                variable=self.show_rect_overlay,
                bg="#0e1726",
                fg="#94a3b8",
                selectcolor="#090d16",
                command=self.render_matrix_editor,
            ).pack(side=tk.LEFT, padx=1)

            # 4-Way Grid Shift / Nudge Controls
            r_nudge = tk.Frame(grp_tool, bg="#0e1726")
            r_nudge.pack(fill=tk.X, pady=(4, 2))
            ttk.Label(r_nudge, text="Nudge All:").pack(side=tk.LEFT)
            tk.Button(
                r_nudge,
                text="← West",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=lambda: self.nudge_grid(-1, 0),
            ).pack(side=tk.LEFT, padx=2, expand=True, fill=tk.X)
            tk.Button(
                r_nudge,
                text="↑ North",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=lambda: self.nudge_grid(0, -1),
            ).pack(side=tk.LEFT, padx=2, expand=True, fill=tk.X)
            tk.Button(
                r_nudge,
                text="↓ South",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=lambda: self.nudge_grid(0, 1),
            ).pack(side=tk.LEFT, padx=2, expand=True, fill=tk.X)
            tk.Button(
                r_nudge,
                text="→ East",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=lambda: self.nudge_grid(1, 0),
            ).pack(side=tk.LEFT, padx=2, expand=True, fill=tk.X)

            # Matrix Sync & Import/Export Actions
            r_act = tk.Frame(grp_tool, bg="#0e1726")
            r_act.pack(fill=tk.X, pady=(4, 2))
            tk.Button(
                r_act,
                text="⤺ Derive Table",
                bg="#1e293b",
                fg="#06b6d4",
                font=("Segoe UI", 8, "bold"),
                command=self.derive_table_from_grid,
            ).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
            tk.Button(
                r_act,
                text="⤻ Rebuild Grid",
                bg="#1e293b",
                fg="#06b6d4",
                font=("Segoe UI", 8, "bold"),
                command=self.rebuild_grid_from_table,
            ).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
            tk.Button(
                r_act,
                text="🔍 Audit",
                bg="#1e293b",
                fg="#f59e0b",
                font=("Segoe UI", 8, "bold"),
                command=self.validate_matrix,
            ).pack(side=tk.LEFT, padx=1)
            tk.Button(
                r_act, text="🗑️ Clear", bg="#1e293b", fg="#ef4444", font=("Segoe UI", 8), command=self.clear_matrix
            ).pack(side=tk.LEFT, padx=1)

            r_imp = tk.Frame(grp_tool, bg="#0e1726")
            r_imp.pack(fill=tk.X, pady=(2, 0))
            tk.Button(
                r_imp,
                text="📂 Import Layout .h",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=self.import_layout_header_file,
            ).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
            tk.Button(
                r_imp,
                text="📂 Import Sections .json",
                bg="#1e293b",
                fg="#e2e8f0",
                font=("Segoe UI", 8),
                command=self.import_sections_json_file,
            ).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)

            # --- Left Panel 3: Live Verification Console ---
            grp_con = ttk.LabelFrame(left_frame, text=" 3. Hardware Verification Log ", padding=6)
            grp_con.pack(fill=tk.BOTH, expand=True)

            self.txt_log = tk.Text(grp_con, wrap=tk.WORD, font=("Consolas", 8), bg="#04070f", fg="#cfe3ff", bd=0)
            self.txt_log.pack(fill=tk.BOTH, expand=True)

            # --- Right Panel: Multi-Tab Studio ---
            self.notebook = ttk.Notebook(right_frame)
            self.notebook.pack(fill=tk.BOTH, expand=True)

            # Tab 1: Interactive 28x15 Fly Layout Matrix Editor
            self.tab_matrix = ttk.Frame(self.notebook)
            self.notebook.add(self.tab_matrix, text=" ✏️ Fly Matrix Editor (28×15) ")
            self.build_matrix_tab()

            # Tab 2: Quantized GBA Screen Preview
            self.tab_screen = ttk.Frame(self.notebook)
            self.notebook.add(self.tab_screen, text=" 📺 GBA Screen Preview (240×160) ")
            self.build_screen_tab()

            # Tab 3: Master Tileset Viewer & Interactive Highlighter
            self.tab_tiles = ttk.Frame(self.notebook)
            self.notebook.add(self.tab_tiles, text=" 🧱 128px Tileset & Usage ")
            self.build_tileset_tab()

            # Tab 4: 4096-Byte Tilemap Hex Inspector
            self.tab_hex = ttk.Frame(self.notebook)
            self.notebook.add(self.tab_hex, text=" 🔬 Tilemap (4096 B) & Hex ")
            self.build_hex_tab()

            # Tab 5: Palette Banks 7 & 8 Inspector
            self.tab_pal = ttk.Frame(self.notebook)
            self.notebook.add(self.tab_pal, text=" 🎨 Palette Swatches (112–143) ")
            self.build_palette_tab()

            # Tab 6: Decomp Code & Snippets
            self.tab_code = ttk.Frame(self.notebook)
            self.notebook.add(self.tab_code, text=" 💻 Decomp Code & Snippets ")
            self.build_code_tab()

            # Bottom Status Bar
            self.status_bar = tk.Frame(self, bg="#0e1726", height=24, bd=1, relief=tk.SOLID)
            self.status_bar.pack(fill=tk.X, side=tk.BOTTOM)

            self.lbl_status_pos = tk.Label(
                self.status_bar,
                text="Tile: (--, --) | Screen: (---, ---)",
                font=("Consolas", 8),
                fg="#06b6d4",
                bg="#0e1726",
            )
            self.lbl_status_pos.pack(side=tk.LEFT, padx=10)

            self.lbl_status_sec = tk.Label(
                self.status_bar, text="Hover: MAPSEC_NONE", font=("Segoe UI", 8), fg="#94a3b8", bg="#0e1726"
            )
            self.lbl_status_sec.pack(side=tk.LEFT, padx=10)

            self.lbl_status_info = tk.Label(
                self.status_bar,
                text="Ready · 240x160 GBA · 32 Colors · 4096 B Bin",
                font=("Segoe UI", 8),
                fg="#10b981",
                bg="#0e1726",
            )
            self.lbl_status_info.pack(side=tk.RIGHT, padx=10)

        def log(self, msg: str, tag: str = "INFO"):
            prefix = "[✓] " if tag == "OK" else ("[!] " if tag == "WARN" else ("[-] " if tag == "ERR" else ""))
            self.txt_log.insert(tk.END, f"{prefix}{msg}\n")
            self.txt_log.see(tk.END)

        def bind_shortcuts(self):
            self.bind("<Control-z>", lambda e: self.undo())
            self.bind("<Control-y>", lambda e: self.redo())
            self.bind("<Control-s>", lambda e: self.export_zip())
            self.bind("<Control-b>", lambda e: self.compile_all())

        # ----------------------------------------------------------------------
        # Tab 1: Fly Layout Matrix Editor (Expanded Multi-Tool)
        # ----------------------------------------------------------------------
        def build_matrix_tab(self):
            panes = tk.PanedWindow(self.tab_matrix, orient=tk.VERTICAL, bg="#090d16", bd=0, sashwidth=4)
            panes.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

            # Upper Editor Canvas + Color Legend
            top_holder = tk.Frame(panes, bg="#04070f", bd=1, relief=tk.SOLID)
            panes.add(top_holder, minsize=430)

            legend = tk.Frame(top_holder, bg="#0e1726", padx=8, pady=3)
            legend.pack(fill=tk.X, side=tk.TOP)
            tk.Label(legend, text="Legend:", font=("Segoe UI", 8, "bold"), fg="#94a3b8", bg="#0e1726").pack(
                side=tk.LEFT, padx=(0, 6)
            )
            for col_hex, label in [
                ("#dc2626", "■ City / Town"),
                ("#b45309", "■ Route Corridor"),
                ("#15803d", "■ Dungeon / Cave / Landmark"),
                ("#0284c7", "■ Water / Island"),
                ("#6d28d9", "■ Special Zone"),
            ]:
                tk.Label(legend, text=label, fg=col_hex, bg="#0e1726", font=("Segoe UI", 8, "bold")).pack(
                    side=tk.LEFT, padx=6
                )

            self.matrix_canvas = tk.Canvas(top_holder, bg="#04070f", highlightthickness=0)
            self.matrix_canvas.pack(fill=tk.BOTH, expand=True, padx=4, pady=4)

            self.matrix_canvas.bind("<Button-1>", self.on_matrix_click)
            self.matrix_canvas.bind("<B1-Motion>", self.on_matrix_drag)
            self.matrix_canvas.bind("<ButtonRelease-1>", self.on_matrix_release)
            self.matrix_canvas.bind("<Button-3>", self.on_matrix_right_click)
            self.matrix_canvas.bind("<B3-Motion>", self.on_matrix_right_click)
            self.matrix_canvas.bind("<Motion>", self.on_matrix_hover)

            # Lower Entries Table
            tbl_frame = tk.Frame(panes, bg="#0e1726")
            panes.add(tbl_frame, minsize=180)

            t_ctrl = tk.Frame(tbl_frame, bg="#0e1726")
            t_ctrl.pack(fill=tk.X, pady=(0, 4))
            tk.Label(
                t_ctrl,
                text="Map Sections Table (Double-click row to edit coordinates / name):",
                font=("Segoe UI", 9, "bold"),
                fg="#06b6d4",
                bg="#0e1726",
            ).pack(side=tk.LEFT)

            tk.Button(
                t_ctrl,
                text="+ Add Section",
                bg="#1e293b",
                fg="#10b981",
                font=("Segoe UI", 8, "bold"),
                command=self.add_entry_dialog,
            ).pack(side=tk.RIGHT, padx=2)
            tk.Button(
                t_ctrl,
                text="✕ Delete Selected",
                bg="#1e293b",
                fg="#ef4444",
                font=("Segoe UI", 8),
                command=self.delete_selected_entry,
            ).pack(side=tk.RIGHT, padx=2)

            self.tree_entries = ttk.Treeview(
                tbl_frame, columns=("id", "name", "x", "y", "w", "h"), show="headings", height=6
            )
            self.tree_entries.heading("id", text="Map Section ID")
            self.tree_entries.heading("name", text="In-Game Display Name")
            self.tree_entries.heading("x", text="X (0–27)")
            self.tree_entries.heading("y", text="Y (0–14)")
            self.tree_entries.heading("w", text="Width")
            self.tree_entries.heading("h", text="Height")

            self.tree_entries.column("id", width=240)
            self.tree_entries.column("name", width=200)
            self.tree_entries.column("x", width=65, anchor=tk.CENTER)
            self.tree_entries.column("y", width=65, anchor=tk.CENTER)
            self.tree_entries.column("w", width=65, anchor=tk.CENTER)
            self.tree_entries.column("h", width=65, anchor=tk.CENTER)

            sb_y = ttk.Scrollbar(tbl_frame, orient=tk.VERTICAL, command=self.tree_entries.yview)
            self.tree_entries.configure(yscrollcommand=sb_y.set)
            sb_y.pack(side=tk.RIGHT, fill=tk.Y)
            self.tree_entries.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

            self.tree_entries.bind("<<TreeviewSelect>>", self.on_entry_selected)
            self.tree_entries.bind("<Double-1>", self.on_entry_double_click)

        def get_mapsec_color(self, sec_id: str) -> str:
            if not sec_id or sec_id == "MAPSEC_NONE":
                return "#090d16"
            if "ROUTE" in sec_id:
                return "#b45309"  # Amber
            if any(k in sec_id for k in ["CITY", "TOWN", "VILLAGE"]):
                return "#dc2626"  # Red
            if any(k in sec_id for k in ["CAVE", "MT", "TOWER", "PARK", "FOREST", "FALLS", "WELL", "RUINS"]):
                return "#15803d"  # Green
            if any(k in sec_id for k in ["ISLAND", "SEA", "WATER", "WHIRL", "LAKE"]):
                return "#0284c7"  # Light Blue
            return "#6d28d9"  # Purple Special

        def render_matrix_editor(self):
            """Redraws the 28x15 matrix editor with rulers, underlay, cell codes, and drag previews."""
            self.matrix_canvas.delete("all")
            cs = self.matrix_cell_size.get()
            ro = 24 if self.show_rulers.get() else 4

            # 1. Underlay Map Artwork
            op = self.underlay_opacity.get()
            if self.source_img is not None and op > 0.01:
                grid_px_w = FLY_MAP_WIDTH * cs
                grid_px_h = FLY_MAP_HEIGHT * cs
                # Extract the inner 28x15 fly window from the 30x20 screen (offset x=1 tile, y=2 tiles)
                full_240 = self.source_img.resize((SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX), Image.Resampling.NEAREST)
                fly_crop = full_240.crop((8, 16, 8 + FLY_MAP_WIDTH * 8, 16 + FLY_MAP_HEIGHT * 8))
                bg_preview = fly_crop.resize((grid_px_w, grid_px_h), Image.Resampling.NEAREST)

                bg_arr = np.array(bg_preview, dtype=np.float32) * op
                bg_blended = Image.fromarray(bg_arr.astype(np.uint8))
                self.matrix_underlay_tk = ImageTk.PhotoImage(bg_blended)
                self.matrix_canvas.create_image(ro, ro, image=self.matrix_underlay_tk, anchor="nw")

            # 2. Draw Column and Row Rulers
            if self.show_rulers.get():
                for x in range(FLY_MAP_WIDTH):
                    tx = ro + x * cs + cs // 2
                    self.matrix_canvas.create_text(tx, 12, text=str(x), fill="#06b6d4", font=("Consolas", 8, "bold"))
                for y in range(FLY_MAP_HEIGHT):
                    ty = ro + y * cs + cs // 2
                    self.matrix_canvas.create_text(12, ty, text=str(y), fill="#06b6d4", font=("Consolas", 8, "bold"))

            # 3. Draw Grid Cells, Section Colors & Short Labels
            show_codes = self.show_cell_codes.get()
            for y in range(FLY_MAP_HEIGHT):
                for x in range(FLY_MAP_WIDTH):
                    sec = self.grid_matrix[y][x]
                    x0 = ro + x * cs
                    y0 = ro + y * cs
                    x1 = x0 + cs
                    y1 = y0 + cs

                    if sec != "MAPSEC_NONE":
                        fill_col = self.get_mapsec_color(sec)
                        self.matrix_canvas.create_rectangle(
                            x0, y0, x1, y1, fill=fill_col, outline="", stipple="gray50" if op > 0.25 else ""
                        )
                        if show_codes and cs >= 20:
                            code = abbreviate_mapsec(sec)
                            self.matrix_canvas.create_text(
                                x0 + cs // 2, y0 + cs // 2, text=code, fill="#ffffff", font=("Consolas", 7, "bold")
                            )

                    if self.show_grid.get():
                        self.matrix_canvas.create_rectangle(x0, y0, x1, y1, outline="#1e293b", width=1)

            # 4. Draw Rect Bounding Boxes Overlay for Entries
            if self.show_rect_overlay.get():
                for i, e in enumerate(self.entries):
                    x = e.get("x", 0)
                    y = e.get("y", 0)
                    w = e.get("width", 1)
                    h = e.get("height", 1)
                    x0 = ro + x * cs
                    y0 = ro + y * cs
                    x1 = x0 + w * cs
                    y1 = y0 + h * cs

                    is_sel = self.selected_table_idx == i
                    box_color = "#38bdf8" if is_sel else "#f43f5e"
                    self.matrix_canvas.create_rectangle(x0, y0, x1, y1, outline=box_color, width=2 if is_sel else 1)
                    if is_sel:
                        self.matrix_canvas.create_rectangle(x0 + 1, y0 + 1, x1 - 1, y1 - 1, outline="#ffffff", width=1)

            # 5. Live Drag Tool Preview (RECT or LINE)
            tool = self.current_tool.get()
            if self.drag_start_tile and self.drag_cur_tile:
                sx, sy = self.drag_start_tile
                cx, cy = self.drag_cur_tile
                if tool == "RECT":
                    rx0 = ro + min(sx, cx) * cs
                    ry0 = ro + min(sy, cy) * cs
                    rx1 = ro + (max(sx, cx) + 1) * cs
                    ry1 = ro + (max(sy, cy) + 1) * cs
                    self.matrix_canvas.create_rectangle(rx0, ry0, rx1, ry1, outline="#22c55e", width=2, dash=(4, 2))
                elif tool == "LINE":
                    for lx, ly in bresenham_line(sx, sy, cx, cy):
                        px0 = ro + lx * cs
                        py0 = ro + ly * cs
                        self.matrix_canvas.create_rectangle(px0, py0, px0 + cs, py0 + cs, outline="#22c55e", width=2)

        def get_tile_under_mouse(self, event) -> Optional[Tuple[int, int]]:
            ro = 24 if self.show_rulers.get() else 4
            cs = self.matrix_cell_size.get()
            x = (event.x - ro) // cs
            y = (event.y - ro) // cs
            if 0 <= x < FLY_MAP_WIDTH and 0 <= y < FLY_MAP_HEIGHT:
                return (x, y)
            return None

        def ensure_entry_exists(self, sec_id: str, x: int, y: int):
            """Automatically registers a new painted MAPSEC in the table if not yet present."""
            if not sec_id or sec_id == "MAPSEC_NONE":
                return
            if not any(e["id"] == sec_id for e in self.entries):
                disp_name = sec_id.replace("MAPSEC_JOHTO_", "").replace("MAPSEC_", "").replace("_", " ")
                self.entries.append(
                    {
                        "id": sec_id,
                        "name": disp_name,
                        "x": x,
                        "y": y,
                        "width": 1,
                        "height": 1,
                    }
                )
                self.refresh_entries_table()

        def on_matrix_click(self, event):
            tile = self.get_tile_under_mouse(event)
            if not tile:
                return

            x, y = tile
            tool = self.current_tool.get()
            brush = self.active_brush.get().strip() or "MAPSEC_NONE"

            if tool == "PENCIL":
                self.history.push(self.grid_matrix, self.entries)
                self.grid_matrix[y][x] = brush
                self.ensure_entry_exists(brush, x, y)
                self.render_matrix_editor()
                self.update_code_snippets()
            elif tool in ("RECT", "LINE"):
                self.drag_start_tile = tile
                self.drag_cur_tile = tile
                self.render_matrix_editor()
            elif tool == "BUCKET":
                self.history.push(self.grid_matrix, self.entries)
                target = self.grid_matrix[y][x]
                if target != brush:
                    self.flood_fill(x, y, target, brush)
                    self.ensure_entry_exists(brush, x, y)
                    self.render_matrix_editor()
                    self.update_code_snippets()
            elif tool == "PICK":
                picked = self.grid_matrix[y][x]
                self.active_brush.set(picked)
                self.current_tool.set("PENCIL")
                self.log(f"Eyedropper picked: {picked}")
            elif tool == "ERASE":
                self.history.push(self.grid_matrix, self.entries)
                self.grid_matrix[y][x] = "MAPSEC_NONE"
                self.render_matrix_editor()
                self.update_code_snippets()

        def on_matrix_drag(self, event):
            tile = self.get_tile_under_mouse(event)
            if not tile:
                return

            x, y = tile
            tool = self.current_tool.get()
            brush = self.active_brush.get().strip() or "MAPSEC_NONE"

            if tool == "PENCIL":
                if self.grid_matrix[y][x] != brush:
                    self.grid_matrix[y][x] = brush
                    self.render_matrix_editor()
                    self.update_code_snippets()
            elif tool in ("RECT", "LINE"):
                self.drag_cur_tile = tile
                self.render_matrix_editor()
            elif tool == "ERASE":
                if self.grid_matrix[y][x] != "MAPSEC_NONE":
                    self.grid_matrix[y][x] = "MAPSEC_NONE"
                    self.render_matrix_editor()
                    self.update_code_snippets()

        def on_matrix_release(self, event):
            tool = self.current_tool.get()
            if tool in ("RECT", "LINE") and self.drag_start_tile and self.drag_cur_tile:
                self.history.push(self.grid_matrix, self.entries)
                sx, sy = self.drag_start_tile
                cx, cy = self.drag_cur_tile
                brush = self.active_brush.get().strip() or "MAPSEC_NONE"

                if tool == "RECT":
                    min_x, max_x = min(sx, cx), max(sx, cx)
                    min_y, max_y = min(sy, cy), max(sy, cy)
                    for ry in range(min_y, max_y + 1):
                        for rx in range(min_x, max_x + 1):
                            self.grid_matrix[ry][rx] = brush
                    self.ensure_entry_exists(brush, min_x, min_y)
                elif tool == "LINE":
                    for lx, ly in bresenham_line(sx, sy, cx, cy):
                        if 0 <= lx < FLY_MAP_WIDTH and 0 <= ly < FLY_MAP_HEIGHT:
                            self.grid_matrix[ly][lx] = brush
                    self.ensure_entry_exists(brush, sx, sy)

                self.drag_start_tile = None
                self.drag_cur_tile = None
                self.render_matrix_editor()
                self.update_code_snippets()

        def on_matrix_right_click(self, event):
            tile = self.get_tile_under_mouse(event)
            if not tile:
                return
            x, y = tile
            if self.grid_matrix[y][x] != "MAPSEC_NONE":
                self.grid_matrix[y][x] = "MAPSEC_NONE"
                self.render_matrix_editor()
                self.update_code_snippets()

        def on_matrix_hover(self, event):
            tile = self.get_tile_under_mouse(event)
            if tile:
                x, y = tile
                sec = self.grid_matrix[y][x]
                px_x = (x + 1) * TILE_SIZE
                px_y = (y + 2) * TILE_SIZE
                self.lbl_status_pos.config(text=f"Fly Tile: ({x:02d}, {y:02d}) | Screen px: ({px_x:03d}, {px_y:03d})")
                self.lbl_status_sec.config(text=f"Hover: {sec}")
            else:
                self.lbl_status_pos.config(text="Fly Tile: (--, --) | Screen px: (---, ---)")
                self.lbl_status_sec.config(text="Hover: Outside Grid")

        def flood_fill(self, x: int, y: int, target_sec: str, fill_sec: str):
            if target_sec == fill_sec:
                return
            queue = [(x, y)]
            visited = set()

            while queue:
                cx, cy = queue.pop(0)
                if (cx, cy) in visited:
                    continue
                visited.add((cx, cy))

                if 0 <= cx < FLY_MAP_WIDTH and 0 <= cy < FLY_MAP_HEIGHT:
                    if self.grid_matrix[cy][cx] == target_sec:
                        self.grid_matrix[cy][cx] = fill_sec
                        queue.extend([(cx + 1, cy), (cx - 1, cy), (cx, cy + 1), (cx, cy - 1)])

        def nudge_grid(self, dx: int, dy: int):
            """Shifts the entire 28x15 matrix and entry coordinates by (dx, dy)."""
            self.history.push(self.grid_matrix, self.entries)
            new_grid = [["MAPSEC_NONE" for _ in range(FLY_MAP_WIDTH)] for _ in range(FLY_MAP_HEIGHT)]
            for y in range(FLY_MAP_HEIGHT):
                for x in range(FLY_MAP_WIDTH):
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < FLY_MAP_WIDTH and 0 <= ny < FLY_MAP_HEIGHT:
                        new_grid[ny][nx] = self.grid_matrix[y][x]
            self.grid_matrix = new_grid

            for e in self.entries:
                e["x"] = max(0, min(FLY_MAP_WIDTH - 1, e.get("x", 0) + dx))
                e["y"] = max(0, min(FLY_MAP_HEIGHT - 1, e.get("y", 0) + dy))

            self.refresh_entries_table()
            self.render_matrix_editor()
            self.redraw_screen_preview()
            self.update_code_snippets()
            self.log(f"Nudged matrix and entries by ({dx:+d}, {dy:+d}).")

        def clear_matrix(self):
            self.history.push(self.grid_matrix, self.entries)
            self.grid_matrix = [["MAPSEC_NONE" for _ in range(FLY_MAP_WIDTH)] for _ in range(FLY_MAP_HEIGHT)]
            self.render_matrix_editor()
            self.update_code_snippets()
            self.log("Cleared matrix to MAPSEC_NONE.")

        def on_brush_filter_changed(self, event=None):
            q = self.brush_filter_var.get().strip().upper()
            all_ids = ["MAPSEC_NONE"] + sorted(list({e["id"] for e in self.entries if e["id"] != "MAPSEC_NONE"}))
            if q:
                filtered = [s for s in all_ids if q in s]
                self.cb_brush["values"] = filtered if filtered else all_ids
                if filtered:
                    self.active_brush.set(filtered[0])
            else:
                self.cb_brush["values"] = all_ids

        def import_layout_header_file(self):
            f = filedialog.askopenfilename(filetypes=[("C Header Files", "*.h"), ("All Files", "*.*")])
            if f:
                try:
                    with open(f, "r", encoding="utf-8") as fp:
                        code = fp.read()
                    self.history.push(self.grid_matrix, self.entries)
                    self.grid_matrix = RegionMapCompiler.parse_layout_header(code)
                    self.derive_table_from_grid()
                    self.log(f"Imported layout matrix from {os.path.basename(f)}", "OK")
                except Exception as e:
                    messagebox.showerror("Import Error", f"Failed to parse header:\n{e}")

        def import_sections_json_file(self):
            f = filedialog.askopenfilename(filetypes=[("JSON Files", "*.json"), ("All Files", "*.*")])
            if f:
                try:
                    with open(f, "r", encoding="utf-8") as fp:
                        raw = fp.read()
                    parsed = RegionMapCompiler.parse_sections_json(raw)
                    if parsed:
                        self.history.push(self.grid_matrix, self.entries)
                        self.entries = parsed
                        self.rebuild_grid_from_entries(record_history=False)
                        self.refresh_entries_table()
                        self.render_matrix_editor()
                        self.redraw_screen_preview()
                        self.update_code_snippets()
                        self.log(f"Imported {len(parsed)} entries from {os.path.basename(f)}", "OK")
                except Exception as e:
                    messagebox.showerror("Import Error", f"Failed to parse JSON:\n{e}")

        # ----------------------------------------------------------------------
        # Entries Table Operations & Synchronization
        # ----------------------------------------------------------------------
        def refresh_entries_table(self):
            for row in self.tree_entries.get_children():
                self.tree_entries.delete(row)

            for e in self.entries:
                self.tree_entries.insert(
                    "",
                    tk.END,
                    values=(
                        e.get("id", "MAPSEC_NONE"),
                        e.get("name", ""),
                        e.get("x", 0),
                        e.get("y", 0),
                        e.get("width", 1),
                        e.get("height", 1),
                    ),
                )

            all_ids = ["MAPSEC_NONE"] + sorted(list({e["id"] for e in self.entries if e["id"] != "MAPSEC_NONE"}))
            self.cb_brush["values"] = all_ids

        def on_entry_selected(self, event):
            sel = self.tree_entries.selection()
            if sel:
                item = sel[0]
                idx = self.tree_entries.index(item)
                self.selected_table_idx = idx
                e = self.entries[idx]
                self.active_brush.set(e["id"])
                self.render_matrix_editor()

        def on_entry_double_click(self, event):
            sel = self.tree_entries.selection()
            if not sel:
                return
            idx = self.tree_entries.index(sel[0])
            self.edit_entry_dialog(idx)

        def add_entry_dialog(self):
            self.show_entry_form(None)

        def edit_entry_dialog(self, idx: int):
            self.show_entry_form(idx)

        def show_entry_form(self, idx: Optional[int]):
            dlg = tk.Toplevel(self)
            dlg.title("Edit Map Section" if idx is not None else "Add Map Section")
            dlg.geometry("420x280")
            dlg.configure(bg="#0e1726")
            dlg.transient(self)
            dlg.grab_set()

            entry_data = (
                self.entries[idx]
                if idx is not None
                else {
                    "id": f"MAPSEC_CUSTOM_{len(self.entries) + 1}",
                    "name": "NEW LOCATION",
                    "x": 0,
                    "y": 0,
                    "width": 1,
                    "height": 1,
                }
            )

            v_id = tk.StringVar(value=entry_data["id"])
            v_name = tk.StringVar(value=entry_data["name"])
            v_x = tk.IntVar(value=entry_data["x"])
            v_y = tk.IntVar(value=entry_data["y"])
            v_w = tk.IntVar(value=entry_data["width"])
            v_h = tk.IntVar(value=entry_data["height"])

            frm = tk.Frame(dlg, bg="#0e1726", padx=16, pady=16)
            frm.pack(fill=tk.BOTH, expand=True)

            fields = [
                ("Section ID:", v_id),
                ("Display Name:", v_name),
                ("Tile X (0-27):", v_x),
                ("Tile Y (0-14):", v_y),
                ("Width in Tiles:", v_w),
                ("Height in Tiles:", v_h),
            ]

            for r, (label, var) in enumerate(fields):
                tk.Label(frm, text=label, bg="#0e1726", fg="#94a3b8", font=("Segoe UI", 9)).grid(
                    row=r, column=0, sticky=tk.W, pady=3
                )
                tk.Entry(frm, textvariable=var, bg="#090d16", fg="#f8fafc", insertbackground="#06b6d4").grid(
                    row=r, column=1, sticky=tk.EW, padx=8, pady=3
                )

            def save_entry():
                new_e = {
                    "id": v_id.get().strip().upper(),
                    "name": v_name.get().strip(),
                    "x": max(0, min(FLY_MAP_WIDTH - 1, v_x.get())),
                    "y": max(0, min(FLY_MAP_HEIGHT - 1, v_y.get())),
                    "width": max(1, min(FLY_MAP_WIDTH, v_w.get())),
                    "height": max(1, min(FLY_MAP_HEIGHT, v_h.get())),
                }
                self.history.push(self.grid_matrix, self.entries)
                if idx is not None:
                    self.entries[idx] = new_e
                else:
                    self.entries.append(new_e)

                self.refresh_entries_table()
                self.render_matrix_editor()
                self.redraw_screen_preview()
                self.update_code_snippets()
                dlg.destroy()

            tk.Button(
                frm, text="Save Entry", bg="#06b6d4", fg="#090d16", font=("Segoe UI", 9, "bold"), command=save_entry
            ).grid(row=6, column=0, columnspan=2, pady=(12, 0), sticky=tk.EW)

        def delete_selected_entry(self):
            sel = self.tree_entries.selection()
            if not sel:
                return
            idx = self.tree_entries.index(sel[0])
            self.history.push(self.grid_matrix, self.entries)
            deleted = self.entries.pop(idx)
            self.selected_table_idx = None
            self.refresh_entries_table()
            self.render_matrix_editor()
            self.redraw_screen_preview()
            self.update_code_snippets()
            self.log(f"Deleted entry: {deleted['id']}")

        def derive_table_from_grid(self):
            """Scans the 28x15 grid and auto-generates bounding boxes for each section."""
            boxes: Dict[str, Dict[str, int]] = {}
            for y in range(FLY_MAP_HEIGHT):
                for x in range(FLY_MAP_WIDTH):
                    sec = self.grid_matrix[y][x]
                    if sec == "MAPSEC_NONE":
                        continue
                    if sec not in boxes:
                        boxes[sec] = {"min_x": x, "max_x": x, "min_y": y, "max_y": y}
                    else:
                        boxes[sec]["min_x"] = min(boxes[sec]["min_x"], x)
                        boxes[sec]["max_x"] = max(boxes[sec]["max_x"], x)
                        boxes[sec]["min_y"] = min(boxes[sec]["min_y"], y)
                        boxes[sec]["max_y"] = max(boxes[sec]["max_y"], y)

            prev_names = {e["id"]: e.get("name", "") for e in self.entries}
            new_entries = []
            for sec, b in sorted(boxes.items()):
                w = b["max_x"] - b["min_x"] + 1
                h = b["max_y"] - b["min_y"] + 1
                disp_name = prev_names.get(sec) or sec.replace("MAPSEC_JOHTO_", "").replace("MAPSEC_", "").replace(
                    "_", " "
                )
                new_entries.append(
                    {
                        "id": sec,
                        "name": disp_name,
                        "x": b["min_x"],
                        "y": b["min_y"],
                        "width": w,
                        "height": h,
                    }
                )

            self.history.push(self.grid_matrix, self.entries)
            self.entries = new_entries
            self.refresh_entries_table()
            self.render_matrix_editor()
            self.redraw_screen_preview()
            self.update_code_snippets()
            self.log(f"Derived {len(new_entries)} bounding box entries from matrix.", "OK")

        def rebuild_grid_from_entries(self, record_history: bool = True):
            if record_history:
                self.history.push(self.grid_matrix, self.entries)

            self.grid_matrix = [["MAPSEC_NONE" for _ in range(FLY_MAP_WIDTH)] for _ in range(FLY_MAP_HEIGHT)]
            for e in self.entries:
                sec_id = e.get("id", "MAPSEC_NONE")
                x = e.get("x", 0)
                y = e.get("y", 0)
                w = e.get("width", 1)
                h = e.get("height", 1)
                for dy in range(h):
                    for dx in range(w):
                        gx, gy = x + dx, y + dy
                        if 0 <= gx < FLY_MAP_WIDTH and 0 <= gy < FLY_MAP_HEIGHT:
                            self.grid_matrix[gy][gx] = sec_id

        def rebuild_grid_from_table(self):
            self.rebuild_grid_from_entries(record_history=True)
            self.render_matrix_editor()
            self.redraw_screen_preview()
            self.update_code_snippets()
            self.log("Grid completely rebuilt from entries table.", "OK")

        def validate_matrix(self):
            """Audits the layout matrix for anomalies, overlaps, and non-contiguous shapes."""
            warnings = []
            tile_counts = {}
            for y in range(FLY_MAP_HEIGHT):
                for x in range(FLY_MAP_WIDTH):
                    sec = self.grid_matrix[y][x]
                    if sec != "MAPSEC_NONE":
                        tile_counts[sec] = tile_counts.get(sec, 0) + 1

            for e in self.entries:
                sec_id = e["id"]
                w = e.get("width", 1)
                h = e.get("height", 1)
                expected_tiles = w * h
                actual_tiles = tile_counts.get(sec_id, 0)

                if actual_tiles == 0:
                    warnings.append(f"• Section '{sec_id}' is defined in table but has 0 painted tiles on matrix.")
                elif actual_tiles != expected_tiles:
                    warnings.append(
                        f"• Section '{sec_id}' has {actual_tiles} tiles painted, vs bounding box {w}x{h} ({expected_tiles} tiles)."
                    )

            if not warnings:
                messagebox.showinfo("Validation Passed", "All map sections and matrix hover areas are aligned!")
            else:
                msg = "Audit Findings:\n\n" + "\n".join(warnings[:15])
                messagebox.showwarning("Layout Audit Findings", msg)

        def undo(self):
            res = self.history.undo(self.grid_matrix, self.entries)
            if res:
                self.grid_matrix, self.entries = res
                self.refresh_entries_table()
                self.render_matrix_editor()
                self.redraw_screen_preview()
                self.update_code_snippets()
                self.log("Undo performed.")

        def redo(self):
            res = self.history.redo(self.grid_matrix, self.entries)
            if res:
                self.grid_matrix, self.entries = res
                self.refresh_entries_table()
                self.render_matrix_editor()
                self.redraw_screen_preview()
                self.update_code_snippets()
                self.log("Redo performed.")

        # ----------------------------------------------------------------------
        # Tab 2: Quantized GBA Screen Preview
        # ----------------------------------------------------------------------
        def build_screen_tab(self):
            frame = tk.Frame(self.tab_screen, bg="#04070f")
            frame.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)

            t_bar = tk.Frame(frame, bg="#0e1726", padx=6, pady=4)
            t_bar.pack(fill=tk.X, pady=(0, 6))

            ttk.Label(t_bar, text="Screen Zoom:").pack(side=tk.LEFT)
            for z in [1, 2, 3, 4, 5]:
                tk.Radiobutton(
                    t_bar,
                    text=f"{z}x",
                    value=z,
                    variable=self.zoom_level,
                    bg="#1e293b",
                    fg="#e2e8f0",
                    selectcolor="#06b6d4",
                    indicatoron=False,
                    font=("Segoe UI", 8, "bold"),
                    padx=6,
                    command=self.redraw_screen_preview,
                ).pack(side=tk.LEFT, padx=2)

            tk.Button(
                t_bar,
                text="Clear Tile Highlight",
                bg="#1e293b",
                fg="#94a3b8",
                font=("Segoe UI", 8),
                command=self.clear_tile_highlight,
            ).pack(side=tk.RIGHT, padx=4)

            self.canvas_screen = tk.Canvas(frame, bg="#04070f", highlightthickness=1, highlightbackground="#1e293b")
            self.canvas_screen.pack(anchor=tk.CENTER, pady=10)

        def clear_tile_highlight(self):
            self.highlighted_tile_id = None
            self.redraw_screen_preview()

        def redraw_screen_preview(self):
            if self.source_img is None:
                return

            z = self.zoom_level.get()
            w = SCREEN_WIDTH_PX * z
            h = SCREEN_HEIGHT_PX * z

            if self.compiled_data is not None:
                q = self.compiled_data["quantized_map"]
                rgb_arr = np.zeros((SCREEN_HEIGHT_PX, SCREEN_WIDTH_PX, 3), dtype=np.uint8)
                for y in range(SCREEN_HEIGHT_PX):
                    for x in range(SCREEN_WIDTH_PX):
                        rgb_arr[y, x] = DECOMP_REGION_MAP_PALETTE.get(q[y, x], (0, 0, 0))
                base_img = Image.fromarray(rgb_arr, mode="RGB")
            else:
                base_img = self.source_img.resize((SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX), Image.Resampling.NEAREST)

            disp_img = base_img.resize((w, h), Image.Resampling.NEAREST)
            draw = ImageDraw.Draw(disp_img)

            if self.show_grid.get():
                for tx in range(SCREEN_WIDTH_TILES + 1):
                    x = tx * TILE_SIZE * z
                    draw.line([(x, 0), (x, h)], fill=(30, 41, 59), width=1)
                for ty in range(SCREEN_HEIGHT_TILES + 1):
                    y = ty * TILE_SIZE * z
                    draw.line([(0, y), (w, y)], fill=(30, 41, 59), width=1)

            # Draw entry bounding boxes (offset by +1 col, +2 rows for screen space)
            if self.show_rect_overlay.get():
                for e in self.entries:
                    ex = (e.get("x", 0) + 1) * TILE_SIZE * z
                    ey = (e.get("y", 0) + 2) * TILE_SIZE * z
                    ew = e.get("width", 1) * TILE_SIZE * z
                    eh = e.get("height", 1) * TILE_SIZE * z
                    draw.rectangle([ex, ey, ex + ew, ey + eh], outline=(244, 63, 94), width=2)

            # Highlight occurrences of selected tile ID from Tileset Tab
            if self.highlighted_tile_id is not None and self.compiled_data is not None:
                active = self.compiled_data["active_tilemap"]
                for ty in range(SCREEN_HEIGHT_TILES):
                    for tx in range(SCREEN_WIDTH_TILES):
                        if int(active[ty, tx]) == self.highlighted_tile_id:
                            hx = tx * TILE_SIZE * z
                            hy = ty * TILE_SIZE * z
                            hw = TILE_SIZE * z
                            draw.rectangle([hx, hy, hx + hw, hy + hw], outline=(34, 211, 238), width=2)

            self.screen_tk = ImageTk.PhotoImage(disp_img)
            self.canvas_screen.config(width=w, height=h)
            self.canvas_screen.delete("all")
            self.canvas_screen.create_image(0, 0, image=self.screen_tk, anchor="nw")

        # ----------------------------------------------------------------------
        # Tab 3: Master Tileset Viewer & Interactive Highlighter
        # ----------------------------------------------------------------------
        def build_tileset_tab(self):
            frame = tk.Frame(self.tab_tiles, bg="#04070f")
            frame.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)

            self.lbl_tileset_meta = tk.Label(
                frame,
                text="Master Tileset: 128px Wide (Click any tile to highlight all occurrences on GBA Screen)",
                font=("Segoe UI", 10, "bold"),
                fg="#06b6d4",
                bg="#04070f",
            )
            self.lbl_tileset_meta.pack(anchor=tk.W, pady=(0, 6))

            can_box = tk.Frame(frame, bg="#04070f")
            can_box.pack(fill=tk.BOTH, expand=True)

            self.canvas_tileset = tk.Canvas(can_box, bg="#04070f", highlightthickness=1, highlightbackground="#1e293b")
            sb = tk.Scrollbar(can_box, orient=tk.VERTICAL, command=self.canvas_tileset.yview)
            self.canvas_tileset.configure(yscrollcommand=sb.set)

            sb.pack(side=tk.RIGHT, fill=tk.Y)
            self.canvas_tileset.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

            self.canvas_tileset.bind("<Button-1>", self.on_tileset_click)

        def on_tileset_click(self, event):
            if self.compiled_data is None:
                return
            scale = 4
            tx = (event.x - 10) // (TILE_SIZE * scale)
            ty = (event.y - 10) // (TILE_SIZE * scale)
            if 0 <= tx < 16:
                tid = ty * 16 + tx
                if 0 <= tid < self.compiled_data["tile_count"]:
                    self.highlighted_tile_id = tid
                    usage = self.compiled_data["tile_usage_counts"].get(tid, 0)
                    self.log(f"Selected Tile ID #{tid} (0x{tid:02X}) — Used {usage} times in active 30x20 map.")
                    self.redraw_tileset_view()
                    self.redraw_screen_preview()

        def redraw_tileset_view(self):
            if self.compiled_data is None:
                return

            tilesheet = self.compiled_data["tilesheet"]
            th, tw = tilesheet.shape
            scale = 4

            rgb_arr = np.zeros((th, tw, 3), dtype=np.uint8)
            for y in range(th):
                for x in range(tw):
                    rgb_arr[y, x] = DECOMP_REGION_MAP_PALETTE.get(tilesheet[y, x], (0, 0, 0))

            im = Image.fromarray(rgb_arr, mode="RGB").resize((tw * scale, th * scale), Image.Resampling.NEAREST)
            draw = ImageDraw.Draw(im)

            # Draw 8x8 tile grid on tileset
            for gx in range(0, tw * scale + 1, TILE_SIZE * scale):
                draw.line([(gx, 0), (gx, th * scale)], fill=(30, 41, 59), width=1)
            for gy in range(0, th * scale + 1, TILE_SIZE * scale):
                draw.line([(0, gy), (tw * scale, gy)], fill=(30, 41, 59), width=1)

            # Highlight selected tile
            if self.highlighted_tile_id is not None:
                htx = (self.highlighted_tile_id % 16) * TILE_SIZE * scale
                hty = (self.highlighted_tile_id // 16) * TILE_SIZE * scale
                s_px = TILE_SIZE * scale
                draw.rectangle([htx, hty, htx + s_px, hty + s_px], outline=(34, 211, 238), width=2)

            self.tileset_tk = ImageTk.PhotoImage(im)
            self.canvas_tileset.delete("all")
            self.canvas_tileset.create_image(10, 10, image=self.tileset_tk, anchor="nw")
            self.canvas_tileset.config(scrollregion=(0, 0, tw * scale + 20, th * scale + 20))

            n = self.compiled_data["tile_count"]
            self.lbl_tileset_meta.config(
                text=f"Master Tileset: 128×{th}px ({n} unique 8×8 tiles | Click any tile to inspect usage)"
            )

        # ----------------------------------------------------------------------
        # Tab 4: Tilemap (4096 B) & Hex Inspector
        # ----------------------------------------------------------------------
        def build_hex_tab(self):
            frame = tk.Frame(self.tab_hex, bg="#04070f")
            frame.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)

            tk.Label(
                frame,
                text="Active 30×20 Tile IDs Matrix & 4096-Byte (.bin) Hex Dump:",
                font=("Segoe UI", 10, "bold"),
                fg="#06b6d4",
                bg="#04070f",
            ).pack(anchor=tk.W)

            self.txt_hex = tk.Text(frame, font=("Consolas", 9), bg="#04070f", fg="#cfe3ff", bd=0)
            self.txt_hex.pack(fill=tk.BOTH, expand=True, pady=6)

        def redraw_hex_dump(self):
            if self.compiled_data is None:
                return

            active = self.compiled_data["active_tilemap"]
            lines = [
                "=== ACTIVE 30x20 TILE IDs MATRIX (TOP-LEFT OF 64x64 TILEMAP) ===",
                "      " + " ".join(f"{c:02d}" for c in range(30)),
                "     +" + "---" * 30,
            ]
            for r in range(SCREEN_HEIGHT_TILES):
                row_str = " ".join(f"{active[r, c]:02X}" for c in range(SCREEN_WIDTH_TILES))
                lines.append(f"R{r:02d} | {row_str}")

            lines.append("\n=== FIRST 512 BYTES OF 4096-BYTE TILEMAP BINARY (.bin) ===")
            full_bin = np.zeros((TILEMAP_FULL_DIM, TILEMAP_FULL_DIM), dtype=np.uint8)
            full_bin[:SCREEN_HEIGHT_TILES, :SCREEN_WIDTH_TILES] = active
            raw = full_bin.tobytes()

            for i in range(0, 512, 16):
                hex_chunk = " ".join(f"{raw[i + k]:02X}" for k in range(16))
                lines.append(f"0x{i:04X}: {hex_chunk}")

            lines.append("... [Remaining 3584 bytes are 0x00 padded to satisfy hardware 64x64 tilemap dimension]")

            self.txt_hex.delete("1.0", tk.END)
            self.txt_hex.insert("1.0", "\n".join(lines))

        # ----------------------------------------------------------------------
        # Tab 5: Palette Banks 7 & 8 Inspector
        # ----------------------------------------------------------------------
        def build_palette_tab(self):
            frame = tk.Frame(self.tab_pal, bg="#04070f")
            frame.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)

            tk.Label(
                frame,
                text="Authentic GBA Hardware Palette Banks 7 & 8 (Indices 112–143):",
                font=("Segoe UI", 10, "bold"),
                fg="#06b6d4",
                bg="#04070f",
            ).pack(anchor=tk.W, pady=(0, 6))

            can_box = tk.Frame(frame, bg="#04070f")
            can_box.pack(fill=tk.BOTH, expand=True)

            can_swatch = tk.Canvas(can_box, bg="#04070f", highlightthickness=0)
            sb = tk.Scrollbar(can_box, orient=tk.VERTICAL, command=can_swatch.yview)
            can_swatch.configure(yscrollcommand=sb.set)

            sb.pack(side=tk.RIGHT, fill=tk.Y)
            can_swatch.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

            inner = tk.Frame(can_swatch, bg="#04070f")
            can_swatch.create_window((0, 0), window=inner, anchor="nw")

            col_count = 4
            for idx, (pal_idx, (bank, desc, hex_c)) in enumerate(PALETTE_METADATA.items()):
                rgb = DECOMP_REGION_MAP_PALETTE.get(pal_idx, (0, 0, 0))
                bgr555 = rgb_to_gba(rgb[0], rgb[1], rgb[2])
                r, c = idx // col_count, idx % col_count

                card = tk.Frame(inner, bg="#0e1726", bd=1, relief=tk.SOLID, padx=8, pady=6)
                card.grid(row=r, column=c, padx=4, pady=4, sticky="nsew")

                swatch = tk.Canvas(
                    card, width=32, height=32, bg=hex_c, highlightthickness=1, highlightbackground="#ffffff"
                )
                swatch.pack(side=tk.LEFT, padx=(0, 8))

                txt = f"Idx {pal_idx} [{bank}] {hex_c}\nBGR555: 0x{bgr555:04X}\n{desc}"
                tk.Label(card, text=txt, font=("Consolas", 8), justify=tk.LEFT, bg="#0e1726", fg="#e2e8f0").pack(
                    side=tk.LEFT
                )

            inner.update_idletasks()
            can_swatch.config(scrollregion=can_swatch.bbox("all"))

        # ----------------------------------------------------------------------
        # Tab 6: Decomp Code & Snippets
        # ----------------------------------------------------------------------
        def build_code_tab(self):
            frame = tk.Frame(self.tab_code, bg="#04070f")
            frame.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

            nb_code = ttk.Notebook(frame)
            nb_code.pack(fill=tk.BOTH, expand=True)

            f1 = ttk.Frame(nb_code)
            nb_code.add(f1, text=" region_map_layout_*.h ")
            self.txt_code_layout = tk.Text(f1, font=("Consolas", 9), bg="#04070f", fg="#cfe3ff")
            self.txt_code_layout.pack(fill=tk.BOTH, expand=True)

            f2 = ttk.Frame(nb_code)
            nb_code.add(f2, text=" region_map_entries_*.h ")
            self.txt_code_entries = tk.Text(f2, font=("Consolas", 9), bg="#04070f", fg="#cfe3ff")
            self.txt_code_entries.pack(fill=tk.BOTH, expand=True)

            f3 = ttk.Frame(nb_code)
            nb_code.add(f3, text=" region_map_sections.json ")
            self.txt_code_json = tk.Text(f3, font=("Consolas", 9), bg="#04070f", fg="#cfe3ff")
            self.txt_code_json.pack(fill=tk.BOTH, expand=True)

            f4 = ttk.Frame(nb_code)
            nb_code.add(f4, text=" Makefile & C Registration ")
            self.txt_code_snips = tk.Text(f4, font=("Consolas", 9), bg="#04070f", fg="#cfe3ff")
            self.txt_code_snips.pack(fill=tk.BOTH, expand=True)

        def update_code_snippets(self):
            reg = self.region_var.get().strip() or "JOHTO"
            pref = self.prefix_var.get().strip() or "map_johto"

            layout_h = RegionMapCompiler.generate_layout_header(reg, self.grid_matrix, pref)
            self.txt_code_layout.delete("1.0", tk.END)
            self.txt_code_layout.insert("1.0", layout_h)

            entries_h = RegionMapCompiler.generate_entries_header(reg, self.entries)
            self.txt_code_entries.delete("1.0", tk.END)
            self.txt_code_entries.insert("1.0", entries_h)

            sec_json = RegionMapCompiler.generate_sections_json(self.entries)
            self.txt_code_json.delete("1.0", tk.END)
            self.txt_code_json.insert("1.0", sec_json)

            make_snip = f"""# ------------------------------------------------------------------------------
# 8bpp affine background rule for PokeNav / Town Map graphics
# Place in graphics_file_rules.mk (pokenav section):
# ------------------------------------------------------------------------------
graphics/pokenav/region_map/{pref}.8bpp: graphics/pokenav/region_map/{pref}.png
\t$(GBAGFX) $< $@
"""

            c_snip = f"""// ------------------------------------------------------------------------------
// src/region_map.c registration for {reg.upper()}:
// ------------------------------------------------------------------------------
#include "data/region_map/region_map_layout_{reg.lower()}.h"

static const u16 ALIGNED(4) sRegionMap{reg.capitalize()}_Pal[] = INCGFX_U16("graphics/pokenav/region_map/{pref}.pal", ".gbapal");
static const u32 sRegionMap{reg.capitalize()}_Gfx[] = INCGFX_U32("graphics/pokenav/region_map/{pref}.png", ".8bpp.smol");
static const u32 sRegionMap{reg.capitalize()}_Tilemap[] = INCGFX_U32("graphics/pokenav/region_map/{pref}.bin", ".smolTM");

// Inside gRegionMapInfos[REGION_MAP_{reg.upper()}]:
[REGION_MAP_{reg.upper()}] =
{{
    .dexMapPalette = sRegionMap{reg.capitalize()}_Pal,
    .dexMapGfx = sRegionMap{reg.capitalize()}_Gfx,
    .dexMapTilemap = sRegionMap{reg.capitalize()}_Tilemap,
    .dexMapPaletteSize = sizeof(sRegionMap{reg.capitalize()}_Pal),
    .regionMapPalette = sRegionMap{reg.capitalize()}_Pal,
    .regionMapGfx = sRegionMap{reg.capitalize()}_Gfx,
    .regionMapTilemap = sRegionMap{reg.capitalize()}_Tilemap,
}},
"""
            self.txt_code_snips.delete("1.0", tk.END)
            self.txt_code_snips.insert("1.0", f"{make_snip}\n\n{c_snip}")

        # ----------------------------------------------------------------------
        # Top Actions & File Operations
        # ----------------------------------------------------------------------
        def browse_source(self):
            f = filedialog.askopenfilename(filetypes=[("Image Files", "*.png;*.webp;*.bmp;*.jpg")])
            if f:
                self.input_file.set(f)
                self.source_img = Image.open(f).convert("RGB")
                self.compile_all()

        def browse_output(self):
            d = filedialog.askdirectory()
            if d:
                self.output_dir.set(d)

        def on_region_changed(self, event=None):
            reg = self.region_var.get().strip().upper()
            if reg in PRESET_REGIONS:
                self.history.push(self.grid_matrix, self.entries)
                self.entries = [dict(e) for e in PRESET_REGIONS[reg]]
                self.rebuild_grid_from_entries(record_history=False)
                self.refresh_entries_table()
                self.render_matrix_editor()
                self.redraw_screen_preview()
                self.update_code_snippets()
                self.log(f"Switched to preset region '{reg}' ({len(self.entries)} map sections).", "OK")

        def load_demo(self, kind: str):
            self.source_img = create_demo_map(kind)
            self.input_file.set(f"[Procedural Demo: {kind.capitalize()}]")
            self.compile_all()

        def load_shipped_sample(self):
            sample_dir = os.path.join(os.path.dirname(__file__), "samples")
            if not os.path.exists(sample_dir):
                sample_dir = os.path.join(os.getcwd(), "tools", "poke_region_map_tool", "samples")

            f = filedialog.askopenfilename(
                initialdir=sample_dir if os.path.exists(sample_dir) else os.getcwd(),
                title="Select Shipped Tileset Image",
                filetypes=[("PNG Files", "*.png")],
            )
            if f:
                self.input_file.set(f)
                self.source_img = Image.open(f).convert("RGB")
                self.compile_all()

        def compile_all(self):
            if self.source_img is None:
                messagebox.showerror("Error", "No source image available to compile.")
                return

            prefix = self.prefix_var.get().strip() or "map_johto"
            out_dir = self.output_dir.get().strip() or os.getcwd()
            reg = self.region_var.get().strip() or "JOHTO"

            self.txt_log.delete("1.0", tk.END)
            self.log(f"--- Compiling Region Map '{prefix}' for {reg} ---")

            try:
                res = RegionMapCompiler.compile_map(
                    self.source_img,
                    out_dir,
                    prefix,
                    compress_lz=self.compress_lz_var.get(),
                    quant_mode=self.quant_mode_var.get(),
                    dither=self.dither_var.get(),
                )
                self.compiled_data = res

                layout_path = os.path.join(out_dir, f"region_map_layout_{reg.lower()}.h")
                entries_path = os.path.join(out_dir, f"region_map_entries_{reg.lower()}.h")
                json_path = os.path.join(out_dir, f"region_map_sections_{reg.lower()}.json")

                with open(layout_path, "w", encoding="utf-8") as f:
                    f.write(RegionMapCompiler.generate_layout_header(reg, self.grid_matrix, prefix))
                with open(entries_path, "w", encoding="utf-8") as f:
                    f.write(RegionMapCompiler.generate_entries_header(reg, self.entries))
                with open(json_path, "w", encoding="utf-8") as f:
                    f.write(RegionMapCompiler.generate_sections_json(self.entries))

                n = res["tile_count"]
                self.log(f"Quantized 240x160 canvas ({self.quant_mode_var.get()}).", "OK")
                self.log(f"Extracted {n} unique 8x8 tiles (Budget: <= 256).", "OK")
                self.log(f"Generated Tileset PNG: {res['png_path']}", "OK")
                self.log(f"Generated JASC-PAL (32 colors): {res['pal_path']}", "OK")
                self.log(f"Generated GBA Binary Palette (64 B): {res['gbapal_path']}", "OK")
                self.log(f"Generated 4096-B Tilemap (.bin): {res['bin_path']}", "OK")
                self.log(f"Generated Raw 8bpp Tiles: {res['raw8bpp_path']}", "OK")
                if res["bin_lz_path"]:
                    self.log(f"Generated LZ77 Tilemap: {res['bin_lz_path']}", "OK")
                self.log(f"Generated Layout Header: {layout_path}", "OK")
                self.log(f"Generated Sections JSON: {json_path}", "OK")

                if n > 256:
                    self.log(f"WARNING: Tile count {n} exceeds 256. Unsigned 8-bit tilemap IDs will wrap!", "WARN")

                self.refresh_entries_table()
                self.render_matrix_editor()
                self.redraw_screen_preview()
                self.redraw_tileset_view()
                self.redraw_hex_dump()
                self.update_code_snippets()
                self.lbl_status_info.config(text=f"Compiled: {n} Unique Tiles | 4096 B Bin | Palette B7+B8")

            except Exception as e:
                self.log(f"Compilation Failed: {e}", "ERR")
                messagebox.showerror("Compilation Error", str(e))

        def export_zip(self):
            """Packages all compiled assets and snippets into a production-ready ZIP."""
            if self.compiled_data is None:
                self.compile_all()
                if self.compiled_data is None:
                    return

            prefix = self.prefix_var.get().strip() or "map_johto"
            out_dir = self.output_dir.get().strip() or os.getcwd()
            reg = self.region_var.get().strip() or "JOHTO"
            zip_path = os.path.join(out_dir, f"{prefix}_decomp_bundle.zip")

            try:
                with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as zf:
                    zf.write(self.compiled_data["png_path"], f"graphics/pokenav/region_map/{prefix}.png")
                    zf.write(self.compiled_data["pal_path"], f"graphics/pokenav/region_map/{prefix}.pal")
                    zf.write(self.compiled_data["gbapal_path"], f"graphics/pokenav/region_map/{prefix}.gbapal")
                    zf.write(self.compiled_data["bin_path"], f"graphics/pokenav/region_map/{prefix}.bin")
                    zf.write(self.compiled_data["raw8bpp_path"], f"graphics/pokenav/region_map/{prefix}.8bpp")

                    if self.compiled_data.get("bin_lz_path") and os.path.exists(self.compiled_data["bin_lz_path"]):
                        zf.write(self.compiled_data["bin_lz_path"], f"graphics/pokenav/region_map/{prefix}.bin.lz")
                    if self.compiled_data.get("raw8bpp_lz_path") and os.path.exists(
                        self.compiled_data["raw8bpp_lz_path"]
                    ):
                        zf.write(self.compiled_data["raw8bpp_lz_path"], f"graphics/pokenav/region_map/{prefix}.8bpp.lz")

                    zf.writestr(
                        f"src/data/region_map/region_map_layout_{reg.lower()}.h",
                        RegionMapCompiler.generate_layout_header(reg, self.grid_matrix, prefix),
                    )
                    zf.writestr(
                        f"src/data/region_map/region_map_entries_{reg.lower()}.h",
                        RegionMapCompiler.generate_entries_header(reg, self.entries),
                    )
                    zf.writestr(
                        f"src/data/region_map/region_map_sections_{reg.lower()}.json",
                        RegionMapCompiler.generate_sections_json(self.entries),
                    )

                    zf.writestr(
                        "graphics_file_rules.mk.snippet",
                        f"graphics/pokenav/region_map/{prefix}.8bpp: graphics/pokenav/region_map/{prefix}.png\n\t$(GBAGFX) $< $@\n",
                    )

                self.log(f"Exported complete decomp bundle: {zip_path}", "OK")
                messagebox.showinfo("ZIP Exported", f"Decomp package generated:\n{zip_path}")
            except Exception as e:
                self.log(f"ZIP Export Failed: {e}", "ERR")
                messagebox.showerror("Export Error", str(e))

        # Backwards-compatibility alias methods for unit tests
        def derive_entries_from_grid(self):
            self.derive_table_from_grid()

        def run_compile(self):
            self.compile_all()

        def export_zip_bundle(self):
            self.export_zip()

    # Alias for backwards compatibility
    RegionMapToolGUI = RegionMapStudio


# ==============================================================================
# Procedural Demo Mockup Generator
# ==============================================================================
def create_demo_map(kind: str = "hoenn") -> Image.Image:
    """Creates a 240x160 RGB mockup using strict HW palette colors."""
    img = Image.new("RGB", (SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX), DECOMP_REGION_MAP_PALETTE[113])
    draw = ImageDraw.Draw(img)

    if kind.lower() == "johto":
        draw.rectangle([0, 0, 240, 160], fill=DECOMP_REGION_MAP_PALETTE[113])
        draw.rectangle([0, 120, 240, 160], fill=DECOMP_REGION_MAP_PALETTE[117])
        draw.rectangle([180, 0, 240, 160], fill=DECOMP_REGION_MAP_PALETTE[119])

        draw.rectangle([32, 24, 184, 112], fill=DECOMP_REGION_MAP_PALETTE[124])
        draw.rectangle([24, 16, 192, 120], outline=DECOMP_REGION_MAP_PALETTE[115], width=8)
        draw.rectangle([64, 24, 144, 48], fill=DECOMP_REGION_MAP_PALETTE[125])
        draw.rectangle([112, 8, 128, 24], fill=DECOMP_REGION_MAP_PALETTE[117])

        draw.line([(56, 64), (56, 104)], fill=DECOMP_REGION_MAP_PALETTE[132], width=8)
        draw.line([(56, 104), (160, 104)], fill=DECOMP_REGION_MAP_PALETTE[132], width=8)
        draw.line([(152, 24), (152, 104)], fill=DECOMP_REGION_MAP_PALETTE[132], width=8)

        cities = [(152, 104), (104, 104), (88, 40), (48, 64), (64, 24), (136, 24), (160, 56)]
        for cx, cy in cities:
            draw.rectangle([cx - 4, cy - 4, cx + 4, cy + 4], fill=DECOMP_REGION_MAP_PALETTE[135])
            draw.rectangle([cx - 3, cy - 3, cx + 3, cy + 3], fill=DECOMP_REGION_MAP_PALETTE[137])
            draw.point((cx, cy), fill=DECOMP_REGION_MAP_PALETTE[129])
    else:
        draw.rectangle([0, 0, 240, 160], fill=DECOMP_REGION_MAP_PALETTE[113])
        draw.rectangle([0, 60, 240, 120], fill=DECOMP_REGION_MAP_PALETTE[117])
        draw.rectangle([140, 80, 240, 160], fill=DECOMP_REGION_MAP_PALETTE[119])
        draw.rectangle([0, 128, 240, 160], fill=DECOMP_REGION_MAP_PALETTE[121])

        draw.rectangle([24, 24, 152, 96], fill=DECOMP_REGION_MAP_PALETTE[124])
        draw.rectangle([16, 16, 160, 104], outline=DECOMP_REGION_MAP_PALETTE[115], width=8)
        draw.rectangle([64, 40, 120, 72], fill=DECOMP_REGION_MAP_PALETTE[125])
        draw.rectangle([32, 88, 72, 96], fill=DECOMP_REGION_MAP_PALETTE[127])

        draw.line([(32, 72), (96, 72)], fill=DECOMP_REGION_MAP_PALETTE[132], width=8)
        draw.line([(64, 48), (64, 96)], fill=DECOMP_REGION_MAP_PALETTE[132], width=8)

        cities = [(40, 72), (64, 48), (64, 96), (112, 72)]
        for cx, cy in cities:
            draw.rectangle([cx - 4, cy - 4, cx + 4, cy + 4], fill=DECOMP_REGION_MAP_PALETTE[135])
            draw.rectangle([cx - 3, cy - 3, cx + 3, cy + 3], fill=DECOMP_REGION_MAP_PALETTE[137])
            draw.point((cx, cy), fill=DECOMP_REGION_MAP_PALETTE[129])

    return img


# ==============================================================================
# CLI Entrypoint
# ==============================================================================
def main():
    parser = argparse.ArgumentParser(
        description="Pokémon Gen 3 Decomp Region Map Asset & Layout Studio",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""Examples:
  # Launch the Desktop GUI Application:
  python3 poke_region_map_tool.py

  # Headless CLI compilation:
  python3 poke_region_map_tool.py my_map.png -o graphics/pokenav/region_map -p map_johto -r JOHTO

  # Decompile 4096-B tilemap back into full 240x160 map:
  python3 poke_region_map_tool.py --decompile-bin map.bin --tileset map.png -o reconstructed.png
""",
    )
    parser.add_argument("input", nargs="?", help="Input map image (conformed to 240x160)")
    parser.add_argument("-o", "--out", default=".", help="Output directory (default: .)")
    parser.add_argument("-p", "--prefix", default="map_johto", help="Asset filename prefix (default: map_johto)")
    parser.add_argument("-r", "--region", default="JOHTO", help="Region identifier (JOHTO, HOENN, KANTO, etc.)")
    parser.add_argument(
        "--quant", choices=["euclidean", "perceptual"], default="euclidean", help="Color quantization metric"
    )
    parser.add_argument("--dither", action="store_true", help="Enable Floyd-Steinberg dithering")
    parser.add_argument("--decompile-bin", help="Decompile a 4096-byte .bin tilemap")
    parser.add_argument("--tileset", help="Tileset .png required for decompilation")
    parser.add_argument("--no-lz", action="store_true", help="Disable emitting .bin.lz and .8bpp.lz")
    parser.add_argument("--gui", action="store_true", help="Force launching GUI")

    args = parser.parse_args()

    # Decompile Mode
    if args.decompile_bin:
        if not args.tileset:
            print("[!] Error: --tileset is required when decompiling a .bin tilemap.")
            sys.exit(1)
        out_img_path = args.out if args.out.endswith(".png") else os.path.join(args.out, "reconstructed_map.png")
        print(f"[*] Decompiling {args.decompile_bin} using tileset {args.tileset}...")
        reconstructed = RegionMapCompiler.decompile_map(args.decompile_bin, args.tileset)
        reconstructed.save(out_img_path)
        print(f"[✓] Saved reconstructed 240x160 map image to {out_img_path}")
        return

    # Headless CLI Mode
    if args.input and not args.gui:
        print("[*] Running Headless Region Map Compiler...")
        print(f"    Source Image: {args.input}")
        print(f"    Output Path:  {args.out}")
        print(f"    Prefix:       {args.prefix}")
        print(f"    Region:       {args.region}")

        res = RegionMapCompiler.compile_map(
            args.input, args.out, args.prefix, compress_lz=not args.no_lz, quant_mode=args.quant, dither=args.dither
        )

        print(f"[✓] Extracted & Deduplicated: {res['tile_count']} unique 8x8 tiles.")
        print(f"[✓] Saved PNG Tileset:        {res['png_path']} (128px wide, Indexed Mode P)")
        print(f"[✓] Saved JASC-PAL:           {res['pal_path']} (32 colors)")
        print(f"[✓] Saved GBAPAL:             {res['gbapal_path']} (64 bytes BGR555 LE)")
        print(f"[✓] Saved Tilemap:            {res['bin_path']} (4096 bytes 64x64 u8 grid)")
        print(f"[✓] Saved Raw 8BPP:           {res['raw8bpp_path']} ({len(res['unique_tiles']) * 64} bytes)")

        if res["bin_lz_path"]:
            print(f"[✓] Saved LZ77 Tilemap:       {res['bin_lz_path']}")

        reg_entries = PRESET_REGIONS.get(args.region.upper(), PRESET_REGIONS["JOHTO"])
        grid_matrix = [["MAPSEC_NONE" for _ in range(FLY_MAP_WIDTH)] for _ in range(FLY_MAP_HEIGHT)]
        for e in reg_entries:
            for dy in range(e.get("height", 1)):
                for dx in range(e.get("width", 1)):
                    gx, gy = e["x"] + dx, e["y"] + dy
                    if 0 <= gx < FLY_MAP_WIDTH and 0 <= gy < FLY_MAP_HEIGHT:
                        grid_matrix[gy][gx] = e["id"]

        layout_h = RegionMapCompiler.generate_layout_header(args.region, grid_matrix, args.prefix)
        entries_h = RegionMapCompiler.generate_entries_header(args.region, reg_entries)
        sec_json = RegionMapCompiler.generate_sections_json(reg_entries)

        layout_path = os.path.join(args.out, f"region_map_layout_{args.region.lower()}.h")
        entries_path = os.path.join(args.out, f"region_map_entries_{args.region.lower()}.h")
        json_path = os.path.join(args.out, f"region_map_sections_{args.region.lower()}.json")

        with open(layout_path, "w", encoding="utf-8") as f:
            f.write(layout_h)
        with open(entries_path, "w", encoding="utf-8") as f:
            f.write(entries_h)
        with open(json_path, "w", encoding="utf-8") as f:
            f.write(sec_json)

        print(f"[✓] Saved Layout Header:      {layout_path}")
        print(f"[✓] Saved Entries Header:     {entries_path}")
        print(f"[✓] Saved Sections JSON:      {json_path}")
        print("[✓] All hardware invariants verified successfully.")
        return

    # Desktop GUI Mode
    if not HAS_TK:
        print("[!] Error: Tkinter not available in this environment. Cannot launch GUI.")
        sys.exit(1)

    print("[*] Launching Pokémon GBA Region Map Studio GUI...")
    app = RegionMapStudio()
    app.mainloop()


if __name__ == "__main__":
    main()
