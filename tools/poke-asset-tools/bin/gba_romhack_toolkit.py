#!/usr/bin/env python3
import subprocess
import sys
from pathlib import Path

# Add tool directory to path and bootstrap dependencies
TOOL_BIN = Path(__file__).resolve().parent
sys.path.insert(0, str(TOOL_BIN))
try:
    import asset_common

    asset_common.ensure_dependencies()
except ImportError:
    pass

"""
gba_romhack_toolkit.py - Comprehensive GBA ROM Hack Master Pipeline & Dispatcher.
Unifies all 38 production tools across:
  - Sprites & Shinies (gba_asset_tool, split_overworld, generate_shiny, etc.)
  - Tilesets & Maps (tile_optimizer, package_porymap_tileset, map_asset_pipeline, etc.)
  - Battle & UI (slice_battle_bg, package_battle_ui, render_dynamic_hp, etc.)
  - Audio & Cries (gba_audio_pipeline, convert_cry)
  - Shaders & Environmental (dns_tint_engine, build_weather_fx, generate_parallax)
  - Scripting & Engine (pory_compiler, validate_encounters, gba_save_analyzer, rom_patcher)
"""

TOOL_MAP = {
    # Sprites & Shinies
    "sprite": (
        "gba_asset_tool.py",
        "Enforces 15-bit color, 15-color quantization, and generates indexed PNG/JASC-PAL/4bpp header",
    ),
    "split-ow": (
        "split_overworld.py",
        "Automated overworld sprite sheet frame splitter and horizontal strip generator",
    ),
    "harmonize": ("harmonize_palette.py", "Harmonizes multiple sprites into a shared 15-color palette"),
    "pal-convert": (
        "pal_converter.py",
        "Lossless format converter between JASC-PAL, Adobe ACT, GBA binary .gbapal, and C .h",
    ),
    "shiny": ("generate_shiny.py", "Generates hue-rotated shiny palette preserving luminance & shadow contrast"),
    "species-import": (
        "species_batch_importer.py",
        "Batch-imports front/back/shiny sprites, footprints, and generates C structs",
    ),
    "check-conflicts": (
        "check_palette_conflicts.py",
        "Detects metatiles/tiles with >16 colors and outputs debug collision heatmap",
    ),
    "tile-opt": ("tile_optimizer.py", "Lossless 8x8 tile deduplicator with hardware X/Y/XY flip matching"),
    "porymap-tileset": (
        "package_porymap_tileset.py",
        "Packages raw tilesets into tiles.png, metatiles.bin, and 16 JASC palettes",
    ),
    "anim-sprite": (
        "assemble_anim_sprite.py",
        "Compiles multi-frame front animation sheets with frame delays for pokeemerald",
    ),
    "battle-bg": ("slice_battle_bg.py", "Slices battle terrain into entry bars, player bases, and enemy platforms"),
    "trainer-sprites": (
        "package_trainer_sprites.py",
        "Packages 64x64 trainer front and back sprites with palette quantization",
    ),
    "battle-ui": ("package_battle_ui.py", "Compiles HP boxes, battle text windows, and action selector menus"),
    "ow-effects": ("build_ow_effects.py", "Generates water reflections and shadow sprites for overworld characters"),
    "summary-icons": (
        "build_summary_and_icons.py",
        "Compiles 32x32 party menu icons and summary screen layout mockups",
    ),
    "font": ("pack_gba_font.py", "Compiles variable or fixed-width font sheets into 1bpp or 2bpp binary font tables"),
    "region-map": (
        "package_region_map.py",
        "Packages 240x160 PokéNav/Town Map tiles, metatiles, and player cursor icons",
    ),
    "title-screen": (
        "package_title_screen.py",
        "Packages 240x160 title background with compressed tilemaps and logo sprites",
    ),
    "audio": ("gba_audio_pipeline.py", "DirectSound and MIDI soundfont resampler and .s voicegroup compiler"),
    "particle": (
        "build_battle_particles.py",
        "Compiles battle animation particle sheets and 16-step affine rotation tables",
    ),
    "cry": ("convert_cry.py", "Resamples and normalizes Pokémon cries into signed 8-bit PCM GBA binary"),
    "save": ("gba_save_analyzer.py", "Analyzes GBA save files, saveblocks, checksums, and RTC day/time states"),
    "dns": ("dns_tint_engine.py", "Calculates 24-hour day/night/dusk/dawn and seasonal palette transformation LUTs"),
    "pokedex": ("pokedex_asset_tool.py", "Builds 16x16 1bpp footprints and Pokémon height comparison silhouettes"),
    "pory-compile": ("pory_compiler.py", "Compiles Poryscript into decomp ASM (.inc) or XSE bytecode macros"),
    "tm-matrix": ("tmeff_matrix.py", "Generates TM/HM species compatibility matrix and HTML interactive visualizer"),
    "weather": ("build_weather_fx.py", "Generates animated weather particles and transparency fog sheets for GBA"),
    "encounters": ("validate_encounters.py", "Validates wild encounter rates, mapsec groups, and species ID integrity"),
    "trainers": ("trainer_party_builder.py", "Compiles YAML/JSON trainer configurations into C structs and AI flags"),
    "parallax": (
        "generate_parallax.py",
        "Slices multi-layer parallax battle backgrounds and generates HBlank C drivers",
    ),
    "rom-map": ("inspect_rom_map.py", "Inspects GNU linker .map files and reports section/symbol memory consumption"),
    "mart": ("mart_compiler.py", "Compiles JSON/YAML mart inventory tables into decomp item list arrays"),
    "charmap": ("charmap_converter.py", "Converts plain UTF-8 text into proprietary GBA Pokémon character encodings"),
    "patch": ("rom_patcher.py", "Production-grade BPS and IPS patch creator and applier with CRC32 verification"),
    "verify-map": ("verify_map_matrix.py", "Audits map layouts for warp softlocks, elevation bugs, and boundary traps"),
    "hp-bar": (
        "render_dynamic_hp.py",
        "Generates dynamic 48px multi-palette battle HUD health bar fill sheets and C drivers",
    ),
    "map-pipeline": (
        "map_asset_pipeline.py",
        "Complete automated map, layout, metatile compilation, and collision auditor suite",
    ),
}

BANNER = r"""
================================================================
   ______ ____   ___     ____   ____   __  ___   __  _____   ________ __
  / ____// __ ) /   |   / __ \ / __ \ /  |/  /  / / / /   | / ____/ //_/
 / / __ / __  |/ /| |  / /_/ // / / // /|_/ /  / /_/ / /| |/ /   / ,<
/ /_/ // /_/ // ___ | / _, _// /_/ // /  / /  / __  / ___ / /___/ /| |
\____//_____//_/  |_|/_/ |_| \____//_/  /_/  /_/ /_/_/  |_\____/_/ |_|
               GBA ASSET PIPELINE & COMPILATION SUITE
================================================================
"""


def print_help():
    print(BANNER)
    print("Usage: gba_romhack_toolkit.py <command> [args...]")
    print("       python -m gba_romhack_toolkit <command> [args...]\n")
    print("Available Commands:")

    categories = [
        (
            "Sprites & Shinies",
            [
                "sprite",
                "split-ow",
                "harmonize",
                "pal-convert",
                "shiny",
                "species-import",
                "check-conflicts",
                "anim-sprite",
                "trainer-sprites",
                "pokedex",
            ],
        ),
        ("Tilesets & Maps", ["tile-opt", "porymap-tileset", "map-pipeline", "verify-map", "parallax"]),
        (
            "Battle & UI",
            [
                "battle-bg",
                "battle-ui",
                "particle",
                "summary-icons",
                "font",
                "region-map",
                "title-screen",
                "ow-effects",
                "hp-bar",
            ],
        ),
        ("Audio & Sound", ["audio", "cry"]),
        ("Shaders & Environment", ["dns", "weather"]),
        (
            "Engine & Automation",
            ["save", "pory-compile", "tm-matrix", "encounters", "trainers", "rom-map", "mart", "charmap", "patch"],
        ),
    ]

    for cat_name, cmds in categories:
        print(f"\n  [{cat_name}]")
        for cmd in cmds:
            script, desc = TOOL_MAP[cmd]
            print(f"    {cmd:18s} -> {desc}")
    print("\nRun 'gba_romhack_toolkit.py <command> --help' for options on any command.\n")

def main():
    if len(sys.argv) < 2 or sys.argv[1] in ("-h", "--help", "help", "list"):
        print_help()
        sys.exit(0)

    cmd = sys.argv[1].lower()
    if cmd in TOOL_MAP:
        script_name, _ = TOOL_MAP[cmd]
        script_path = TOOL_BIN / script_name
        args = [sys.executable, str(script_path)] + sys.argv[2:]
        sys.exit(subprocess.call(args))
    else:
        # Check if direct script name was passed
        target = TOOL_BIN / cmd
        if not target.exists() and not cmd.endswith(".py"):
            target = TOOL_BIN / f"{cmd}.py"
        if target.exists():
            args = [sys.executable, str(target)] + sys.argv[2:]
            sys.exit(subprocess.call(args))
        print(f"Unknown command or tool: '{cmd}'")
        print("Run 'gba_romhack_toolkit.py help' to see all available commands.")
        sys.exit(1)

if __name__ == "__main__":
    main()
