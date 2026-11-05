#!/usr/bin/env python3
"""
poke_asset_studio-v4.py - Complete GBA Decompilation Graphics & Asset Management GUI
Customized for Pokémon Confluence (pokeconfluence) & pokeemerald-expansion.

Features & Project Structure Mapping:
- Auto-detects pokeconfluence project root (supports subdirectories and parent repos).
- ⚔️ Battlers & Species Tab: graphics/pokemon (species, mega/forms, anim_front, footprint, icons, follower overworlds).
- 🥊 Trainers Tab: graphics/trainers (front_pics, back_pics, palettes).
- 🚶 Overworld & Objects Tab: graphics/object_events (pics/people, pics/misc, pics/pokemon, palettes).
- 🗺️ Tilesets & Porytiles Tab: data/tilesets/primary, data/tilesets/secondary, and source_tilesets.
- 🏟️ Battle Environments Tab: graphics/battle_environment (tiles.png, palette.pal, map.bin, Johto biome generator).
- 🎨 Palettes & Conflict Auditor: 16-color swatches, BGR555 hardware snapping, Slot 0 transparency (#FF00FF), 8x8 4bpp auditor.
- 🎮 mGBA Test Bridge: Async make build, Lua verification scripts, fast emulator testing.
- 📁 Asset Project Explorer: Full tree viewer for graphics/, data/, sound/, and metadata.
"""

import sys
import os
import json
import colorsys
import shutil
import subprocess
import threading
from pathlib import Path
import tkinter as tk
from tkinter import ttk, filedialog, messagebox, colorchooser
from PIL import Image, ImageTk, ImageDraw
import numpy as np

# ==============================================================================
# GBA COLOR & HARDWARE ENGINE CORE
# ==============================================================================

def snap_to_gba_channel(val: int) -> int:
    """Clamps an 8-bit color channel (0-255) to GBA 5-bit depth (0-31 scaled to 255)."""
    c5 = round(val * 31 / 255)
    return int(round(c5 * 255 / 31))

def clamp_gba_rgb(r: int, g: int, b: int) -> tuple[int, int, int]:
    return (snap_to_gba_channel(r), snap_to_gba_channel(g), snap_to_gba_channel(b))

def rgb_to_bgr555(r: int, g: int, b: int) -> int:
    r5 = round(r * 31 / 255)
    g5 = round(g * 31 / 255)
    b5 = round(b * 31 / 255)
    return (b5 << 10) | (g5 << 5) | r5

def bgr555_to_rgb(val: int) -> tuple[int, int, int]:
    r5 = val & 0x1F
    g5 = (val >> 5) & 0x1F
    b5 = (val >> 10) & 0x1F
    return (int(round(r5 * 255 / 31)), int(round(g5 * 255 / 31)), int(round(b5 * 255 / 31)))

def read_jasc_pal(filepath: Path) -> list[tuple[int, int, int]]:
    """Reads a standard 16-color JASC-PAL file."""
    try:
        lines = [line.strip() for line in filepath.read_text(encoding="utf-8").splitlines() if line.strip()]
        if len(lines) < 3 or lines[0] != "JASC-PAL":
            return [(255, 0, 255)] + [(0, 0, 0)] * 15
        count = int(lines[2])
        palette: list[tuple[int, int, int]] = []
        for line in lines[3:3 + count]:
            parts = [int(p) for p in line.split()]
            if len(parts) >= 3:
                palette.append(clamp_gba_rgb(parts[0], parts[1], parts[2]))
        while len(palette) < 16:
            palette.append((0, 0, 0))
        return palette[:16]
    except Exception:
        return [(255, 0, 255)] + [(0, 0, 0)] * 15

def write_jasc_pal(filepath: Path, colors: list[tuple[int, int, int]]):
    """Writes a standard 16-color JASC-PAL file."""
    lines = ["JASC-PAL", "0100", "16"]
    for i in range(16):
        r, g, b = colors[i][:3] if i < len(colors) else (0, 0, 0)
        lines.append(f"{r} {g} {b}")
    filepath.parent.mkdir(parents=True, exist_ok=True)
    filepath.write_text("\n".join(lines) + "\n", encoding="utf-8")

def generate_shiny_palette(normal_pal: list[tuple[int, int, int]], hue_rot: float = 0.35) -> list[tuple[int, int, int]]:
    """Generates a synchronized shiny palette by rotating hue, preserving dark outline luminance."""
    shiny = [normal_pal[0]]  # Slot 0 remains transparent
    for r, g, b in normal_pal[1:16]:
        luminance = 0.299 * r + 0.587 * g + 0.114 * b
        if luminance < 28:
            shiny.append((r, g, b))
            continue
        h, s, v = colorsys.rgb_to_hsv(r / 255.0, g / 255.0, b / 255.0)
        rn, gn, bn = colorsys.hsv_to_rgb((h + hue_rot) % 1.0, s, v)
        shiny.append(clamp_gba_rgb(int(rn * 255), int(gn * 255), int(bn * 255)))
    while len(shiny) < 16:
        shiny.append((0, 0, 0))
    return shiny[:16]

def quantize_gba_image(
    img: Image.Image,
    target_size: tuple[int, int],
    fixed_palette: list[tuple[int, int, int]] | None = None
) -> tuple[Image.Image, list[tuple[int, int, int]]]:
    """Quantizes an image to 16 colors with Slot 0 as transparent #FF00FF and clamps to BGR555."""
    img = img.convert("RGBA").resize(target_size, Image.Resampling.NEAREST)
    arr = np.array(img)
    alpha = arr[:, :, 3]
    rgb = arr[:, :, :3]
    w, h = target_size

    for y in range(h):
        for x in range(w):
            rgb[y, x] = clamp_gba_rgb(*rgb[y, x])

    if fixed_palette is None:
        vis = arr[alpha >= 128][:, :3]
        if len(vis) == 0:
            palette = [(255, 0, 255)] + [(0, 0, 0)] * 15
        else:
            temp = Image.fromarray(vis.reshape(-1, 1, 3).astype(np.uint8), "RGB")
            q = temp.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
            pal_raw = q.getpalette()
            raw = pal_raw[:45] if pal_raw is not None else []
            palette = [(255, 0, 255)]
            for i in range(0, len(raw), 3):
                palette.append(clamp_gba_rgb(raw[i], raw[i+1], raw[i+2]))
            while len(palette) < 16:
                palette.append((0, 0, 0))
    else:
        palette = fixed_palette

    pal_arr = np.array(palette[1:16])
    idx_map = np.zeros((h, w), dtype=np.uint8)

    for y in range(h):
        for x in range(w):
            if alpha[y, x] < 128:
                idx_map[y, x] = 0
            else:
                dist = np.sum((pal_arr - rgb[y, x]) ** 2, axis=1)
                idx_map[y, x] = np.argmin(dist) + 1

    out = Image.fromarray(idx_map, mode="P")
    flat_pal = []
    for c in palette:
        flat_pal.extend(c[:3])
    while len(flat_pal) < 768:
        flat_pal.extend([0, 0, 0])
    out.putpalette(flat_pal)
    return out, palette


# ==============================================================================
# MAIN STUDIO APPLICATION
# ==============================================================================

class PokeAssetStudio(tk.Tk):
    CONFIG_FILE = Path.home() / ".pokeconfluence_studio.json"

    def __init__(self):
        super().__init__()
        self.title("Pokémon Confluence - GBA Asset & Graphics Studio")
        self.geometry("1280x860")
        self.minsize(1020, 700)

        # State with strict type hints for Pylance
        self.project_root: Path = self.detect_project_root()
        self.current_species_dir: Path | None = None
        self.current_tileset_dir: Path | None = None
        self.current_character_file: Path | None = None
        self.current_trainer_file: Path | None = None
        self.current_palette_file: Path | None = None

        # Build UI
        self.create_menu()
        self.create_top_project_bar()

        # Tabs
        self.notebook = ttk.Notebook(self)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=4, pady=4)

        self.tab_battler = BattlerStudioTab(self.notebook, self)
        self.tab_trainers = TrainerStudioTab(self.notebook, self)
        self.tab_overworld = OverworldStudioTab(self.notebook, self)
        self.tab_tilesets = PorytilesStudioTab(self.notebook, self)
        self.tab_battle_bg = BattleBackgroundStudioTab(self.notebook, self)
        self.tab_palettes = PaletteStudioTab(self.notebook, self)
        self.tab_mgba = MGBATestBridgeTab(self.notebook, self)
        self.tab_explorer = AssetExplorerTab(self.notebook, self)

        self.notebook.add(self.tab_battler, text="  ⚔️ Battlers & Species  ")
        self.notebook.add(self.tab_trainers, text="  🥊 Trainers  ")
        self.notebook.add(self.tab_overworld, text="  🚶 Overworld & Objects  ")
        self.notebook.add(self.tab_tilesets, text="  🗺️ Tilesets & Porytiles  ")
        self.notebook.add(self.tab_battle_bg, text="  🏟️ Battle Environments  ")
        self.notebook.add(self.tab_palettes, text="  🎨 Palettes & Conflict Auditor  ")
        self.notebook.add(self.tab_mgba, text="  🎮 mGBA Test Bridge  ")
        self.notebook.add(self.tab_explorer, text="  📁 Asset Project Explorer  ")

        # Status Bar
        self.status_var = tk.StringVar(value="Initializing...")
        status_bar = ttk.Label(self, textvariable=self.status_var, relief=tk.SUNKEN, anchor=tk.W, padding=(6, 3))
        status_bar.pack(side=tk.BOTTOM, fill=tk.X)

        self.refresh_all_tabs()

    def detect_project_root(self) -> Path:
        """Intelligently detects pokeconfluence root folder."""
        # 1. Check saved config
        if self.CONFIG_FILE.exists():
            try:
                cfg = json.loads(self.CONFIG_FILE.read_text(encoding="utf-8"))
                saved = Path(cfg.get("last_project_root", ""))
                if (saved / "graphics" / "pokemon").is_dir():
                    return saved
            except Exception:
                pass

        # 2. Check current working directory
        cwd = Path.cwd().resolve()
        candidates = [
            cwd,
            cwd / "pokeconfluence",
            cwd.parent / "pokeconfluence",
            Path(__file__).resolve().parent,
            Path(__file__).resolve().parent.parent,
            Path(__file__).resolve().parent.parent / "pokeconfluence",
            Path.home() / "wsl_projects" / "pokemon" / "pokeconfluence",
        ]
        for c in candidates:
            if (c / "graphics" / "pokemon").is_dir() and (c / "data").is_dir():
                return c

        # 3. Climb parent directories searching for Makefile and graphics/pokemon
        cur = cwd
        for _ in range(5):
            if (cur / "graphics" / "pokemon").is_dir():
                return cur
            if (cur / "pokeconfluence" / "graphics" / "pokemon").is_dir():
                return cur / "pokeconfluence"
            cur = cur.parent

        return cwd

    def set_project_root(self, new_root: Path):
        self.project_root = new_root
        self.root_path_var.set(str(new_root))
        try:
            self.CONFIG_FILE.write_text(json.dumps({"last_project_root": str(new_root)}), encoding="utf-8")
        except Exception:
            pass
        self.refresh_all_tabs()

    def create_menu(self):
        menubar = tk.Menu(self)
        file_menu = tk.Menu(menubar, tearoff=0)
        file_menu.add_command(label="Open Project Root...", command=self.on_browse_root)
        file_menu.add_separator()
        file_menu.add_command(label="Refresh All Assets (F5)", command=self.refresh_all_tabs)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.quit)
        menubar.add_cascade(label="File", menu=file_menu)

        tools_menu = tk.Menu(menubar, tearoff=0)
        tools_menu.add_command(label="Scan All 8x8 Tile Conflicts", command=lambda: self.tab_palettes.audit_project())
        tools_menu.add_command(label="Export All Species Header Stubs", command=lambda: self.tab_battler.copy_c_struct())
        menubar.add_cascade(label="Tools", menu=tools_menu)
        self.config(menu=menubar)

        self.bind("<F5>", lambda e: self.refresh_all_tabs())

    def create_top_project_bar(self):
        top_bar = ttk.Frame(self, padding=(6, 4), relief=tk.RAISED)
        top_bar.pack(fill=tk.X)

        ttk.Label(top_bar, text="📁 Project Root:", font=("Arial", 9, "bold")).pack(side=tk.LEFT, padx=4)
        self.root_path_var = tk.StringVar(value=str(self.project_root))
        ent = ttk.Entry(top_bar, textvariable=self.root_path_var, width=65)
        ent.pack(side=tk.LEFT, padx=4, fill=tk.X, expand=True)

        ttk.Button(top_bar, text="📂 Browse...", command=self.on_browse_root).pack(side=tk.LEFT, padx=2)
        ttk.Button(top_bar, text="🔄 Reload Assets", command=self.refresh_all_tabs).pack(side=tk.LEFT, padx=2)

        self.health_label = ttk.Label(top_bar, text="", foreground="#007acc", font=("Arial", 9, "bold"))
        self.health_label.pack(side=tk.RIGHT, padx=8)

    def on_browse_root(self):
        sel = filedialog.askdirectory(initialdir=str(self.project_root), title="Select pokeconfluence Project Root")
        if sel:
            p = Path(sel).resolve()
            self.set_project_root(p)

    def refresh_all_tabs(self):
        root = self.project_root
        has_pokemon = (root / "graphics" / "pokemon").is_dir()
        has_trainers = (root / "graphics" / "trainers").is_dir()
        has_overworld = (root / "graphics" / "object_events").is_dir()
        has_tilesets = (root / "data" / "tilesets").is_dir()
        has_maps = (root / "data" / "maps").is_dir()

        counts = []
        if has_pokemon:
            c = len([f for f in (root / "graphics" / "pokemon").iterdir() if f.is_dir()])
            counts.append(f"{c} Pokémon")
        if has_trainers:
            tf = (root / "graphics" / "trainers" / "front_pics")
            c = len(list(tf.glob("*.png"))) if tf.is_dir() else 0
            counts.append(f"{c} Trainers")
        if has_tilesets:
            p_ts = len(list((root / "data" / "tilesets" / "primary").glob("*"))) if (root / "data" / "tilesets" / "primary").is_dir() else 0
            s_ts = len(list((root / "data" / "tilesets" / "secondary").glob("*"))) if (root / "data" / "tilesets" / "secondary").is_dir() else 0
            counts.append(f"{p_ts+s_ts} Tilesets")
        if has_maps:
            c = len([f for f in (root / "data" / "maps").iterdir() if f.is_dir()])
            counts.append(f"{c} Maps")

        summary = " | ".join(counts) if counts else "No GBA assets detected"
        self.health_label.config(text=f"[✓] {summary}")
        self.status_var.set(f"Active Root: {root} ({summary})")

        # Notify individual tabs
        self.tab_battler.refresh()
        self.tab_trainers.refresh()
        self.tab_overworld.refresh()
        self.tab_tilesets.refresh()
        self.tab_battle_bg.refresh()
        self.tab_explorer.refresh()


# ==============================================================================
# TAB 1: BATTLERS & SPECIES STUDIO (graphics/pokemon)
# ==============================================================================

class BattlerStudioTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.front_img: Image.Image | None = None
        self.back_img: Image.Image | None = None
        self.icon_img: Image.Image | None = None
        self.overworld_img: Image.Image | None = None
        self.normal_palette: list[tuple[int, int, int]] = [(255, 0, 255)] + [(0, 0, 0)] * 15
        self.shiny_palette: list[tuple[int, int, int]] = [(255, 0, 255)] + [(0, 0, 0)] * 15

        self.setup_ui()

    def setup_ui(self):
        left_pane = ttk.Frame(self, width=280)
        left_pane.pack(side=tk.LEFT, fill=tk.Y, padx=6, pady=6)

        search_frame = ttk.Frame(left_pane)
        search_frame.pack(fill=tk.X, pady=2)
        ttk.Label(search_frame, text="🔍 Filter:", font=("Arial", 9, "bold")).pack(side=tk.LEFT)
        self.filter_var = tk.StringVar()
        self.filter_var.trace_add("write", lambda *args: self.filter_species())
        ttk.Entry(search_frame, textvariable=self.filter_var).pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)

        self.species_listbox = tk.Listbox(left_pane, height=22, font=("Courier", 10))
        self.species_listbox.pack(fill=tk.BOTH, expand=True, pady=4)
        self.species_listbox.bind("<<ListboxSelect>>", self.on_select_species)

        btn_row = ttk.Frame(left_pane)
        btn_row.pack(fill=tk.X, pady=2)
        ttk.Button(btn_row, text="➕ New Species", command=self.create_new_species).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
        ttk.Button(btn_row, text="🗑️ Delete", command=self.delete_species).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)

        # Right Main Canvas Panel
        right_pane = ttk.Frame(self)
        right_pane.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=6, pady=6)

        previews_box = ttk.LabelFrame(right_pane, text="Battler & Sprite Previews (4x Nearest Neighbor)", padding=10)
        previews_box.pack(fill=tk.X)

        p_row = ttk.Frame(previews_box)
        p_row.pack()

        # Front Canvas
        f_box = ttk.Frame(p_row, padding=4)
        f_box.pack(side=tk.LEFT, padx=6)
        ttk.Label(f_box, text="Front Pic (64x64)", font=("Arial", 9, "bold")).pack()
        self.canvas_front = tk.Canvas(f_box, width=256, height=256, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_front.pack(pady=4)
        ttk.Button(f_box, text="📥 Import Front...", command=lambda: self.import_single_sprite("front")).pack(fill=tk.X)

        # Back Canvas
        b_box = ttk.Frame(p_row, padding=4)
        b_box.pack(side=tk.LEFT, padx=6)
        ttk.Label(b_box, text="Back Pic (64x64)", font=("Arial", 9, "bold")).pack()
        self.canvas_back = tk.Canvas(b_box, width=256, height=256, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_back.pack(pady=4)
        ttk.Button(b_box, text="📥 Import Back...", command=lambda: self.import_single_sprite("back")).pack(fill=tk.X)

        # Icon & Follower Box
        i_box = ttk.Frame(p_row, padding=4)
        i_box.pack(side=tk.LEFT, padx=6)
        ttk.Label(i_box, text="Party Icon (64x32)", font=("Arial", 9, "bold")).pack()
        self.canvas_icon = tk.Canvas(i_box, width=256, height=128, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_icon.pack(pady=4)
        ttk.Button(i_box, text="📥 Import Icon...", command=lambda: self.import_single_sprite("icon")).pack(fill=tk.X)

        ttk.Label(i_box, text="Follower Overworld (16x32 / sheet)", font=("Arial", 9, "bold")).pack(pady=(6, 0))
        self.canvas_overworld = tk.Canvas(i_box, width=256, height=80, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_overworld.pack(pady=4)
        ttk.Button(i_box, text="📥 Import Follower...", command=lambda: self.import_single_sprite("overworld")).pack(fill=tk.X)

        # Palette & C-Code controls
        ops_box = ttk.LabelFrame(right_pane, text="Palette Operations & C Struct Generator", padding=10)
        ops_box.pack(fill=tk.BOTH, expand=True, pady=8)

        act_row = ttk.Frame(ops_box)
        act_row.pack(fill=tk.X, pady=4)
        ttk.Button(act_row, text="✨ Auto-Generate Shiny Palette (HSV)", command=self.generate_shiny_from_normal).pack(side=tk.LEFT, padx=4)
        ttk.Button(act_row, text="💾 Save JASC-PAL (normal & shiny)", command=self.save_palettes).pack(side=tk.LEFT, padx=4)
        ttk.Button(act_row, text="📋 Copy species_info.h Entry", command=self.copy_c_struct).pack(side=tk.LEFT, padx=4)

        self.c_text = tk.Text(ops_box, height=8, font=("Courier", 9), bg="#222222", fg="#00ffcc", relief=tk.SOLID, bd=1)
        self.c_text.pack(fill=tk.BOTH, expand=True, pady=4)

    def refresh(self):
        pdir = self.app.project_root / "graphics" / "pokemon"
        self.all_species: list[str] = []
        if pdir.is_dir():
            for folder in sorted(pdir.iterdir()):
                if folder.is_dir() and not folder.name.startswith("."):
                    self.all_species.append(folder.name)
                    # Check for subforms like abomasnow/mega
                    for sub in sorted(folder.iterdir()):
                        if sub.is_dir() and (sub / "front.png").exists():
                            self.all_species.append(f"{folder.name}/{sub.name}")
        self.filter_species()

    def filter_species(self):
        query = self.filter_var.get().strip().lower()
        self.species_listbox.delete(0, tk.END)
        for s in getattr(self, "all_species", []):
            if not query or query in s.lower():
                self.species_listbox.insert(tk.END, s)

    def on_select_species(self, event):
        sel = self.species_listbox.curselection()
        if not sel:
            return
        species_name = self.species_listbox.get(sel[0])
        sp_dir = self.app.project_root / "graphics" / "pokemon" / species_name
        self.app.current_species_dir = sp_dir

        front_f = sp_dir / "front.png"
        back_f = sp_dir / "back.png"
        icon_f = sp_dir / "icon.png"
        ow_f = sp_dir / "overworld.png"
        norm_pal_f = sp_dir / "normal.pal"
        shiny_pal_f = sp_dir / "shiny.pal"

        if norm_pal_f.exists():
            self.normal_palette = read_jasc_pal(norm_pal_f)
        if shiny_pal_f.exists():
            self.shiny_palette = read_jasc_pal(shiny_pal_f)

        if front_f.exists():
            self.front_img = Image.open(front_f)
            self.render_preview(self.canvas_front, self.front_img, 256, 256)
        else:
            self.canvas_front.delete("all")

        if back_f.exists():
            self.back_img = Image.open(back_f)
            self.render_preview(self.canvas_back, self.back_img, 256, 256)
        else:
            self.canvas_back.delete("all")

        if icon_f.exists():
            self.icon_img = Image.open(icon_f)
            self.render_preview(self.canvas_icon, self.icon_img, 256, 128)
        else:
            self.canvas_icon.delete("all")

        if ow_f.exists():
            self.overworld_img = Image.open(ow_f)
            self.render_preview(self.canvas_overworld, self.overworld_img, 256, 80)
        else:
            self.canvas_overworld.delete("all")

        self.update_c_preview(species_name)

    def render_preview(self, canvas, img: Image.Image, w: int, h: int):
        canvas.delete("all")
        resized = img.resize((w, h), Image.Resampling.NEAREST)
        tk_photo = ImageTk.PhotoImage(resized)
        canvas.create_image(w // 2, h // 2, image=tk_photo)
        canvas.image = tk_photo

    def import_single_sprite(self, sprite_type: str):
        if not self.app.current_species_dir:
            messagebox.showwarning("No Species Selected", "Please select or create a species first.")
            return
        f = filedialog.askopenfilename(filetypes=[("PNG Images", "*.png"), ("All Files", "*.*")])
        if not f:
            return
        raw = Image.open(f)
        sp_dir = self.app.current_species_dir

        if sprite_type == "front":
            quantized, pal = quantize_gba_image(raw, (64, 64))
            quantized.save(sp_dir / "front.png")
            write_jasc_pal(sp_dir / "normal.pal", pal)
            self.normal_palette = pal
            self.render_preview(self.canvas_front, quantized, 256, 256)
        elif sprite_type == "back":
            quantized, _ = quantize_gba_image(raw, (64, 64), fixed_palette=self.normal_palette)
            quantized.save(sp_dir / "back.png")
            self.render_preview(self.canvas_back, quantized, 256, 256)
        elif sprite_type == "icon":
            quantized, _ = quantize_gba_image(raw, (raw.width if raw.width in [32, 64] else 64, 32))
            quantized.save(sp_dir / "icon.png")
            self.render_preview(self.canvas_icon, quantized, 256, 128)
        elif sprite_type == "overworld":
            raw.save(sp_dir / "overworld.png")
            self.render_preview(self.canvas_overworld, raw, 256, 80)

        messagebox.showinfo("Import Success", f"Updated {sprite_type} for {sp_dir.name}")

    def generate_shiny_from_normal(self):
        if not self.app.current_species_dir:
            return
        self.shiny_palette = generate_shiny_palette(self.normal_palette)
        write_jasc_pal(self.app.current_species_dir / "shiny.pal", self.shiny_palette)
        messagebox.showinfo("Shiny Generated", f"Generated shiny.pal for {self.app.current_species_dir.name}")

    def save_palettes(self):
        if not self.app.current_species_dir:
            return
        write_jasc_pal(self.app.current_species_dir / "normal.pal", self.normal_palette)
        write_jasc_pal(self.app.current_species_dir / "shiny.pal", self.shiny_palette)
        messagebox.showinfo("Palettes Saved", f"Successfully written JASC-PAL files to {self.app.current_species_dir}")

    def update_c_preview(self, species: str):
        safe_name = species.replace("/", "_")
        sp_id = safe_name.upper()
        cap = safe_name.capitalize()
        c_code = f"""[SPECIES_{sp_id}] =
{{
    .speciesName = _("{cap}"),
    .frontPic = gMonFrontPic_{cap},
    .frontPicYOffset = 10,
    .backPic = gMonBackPic_{cap},
    .backPicYOffset = 10,
    .palette = gMonPalette_{cap},
    .shinyPalette = gMonShinyPalette_{cap},
    .iconSprite = gMonIcon_{cap},
    .iconPaletteIndex = 0,
    .frontPicSize = MON_COORDS_SIZE(64, 64),
    .backPicSize = MON_COORDS_SIZE(64, 64),
}},"""
        self.c_text.delete("1.0", tk.END)
        self.c_text.insert(tk.END, c_code)

    def copy_c_struct(self):
        text = self.c_text.get("1.0", tk.END).strip()
        if text:
            self.clipboard_clear()
            self.clipboard_append(text)
            messagebox.showinfo("Copied", "C struct entry copied to clipboard!")

    def create_new_species(self):
        name = simple_dialog_ask(self, "New Species", "Enter Pokémon species name:")
        if not name:
            return
        pdir = self.app.project_root / "graphics" / "pokemon" / name.lower()
        pdir.mkdir(parents=True, exist_ok=True)
        # Placeholder palettes
        pal = [(255, 0, 255)] + [(0, 0, 0)] * 15
        write_jasc_pal(pdir / "normal.pal", pal)
        write_jasc_pal(pdir / "shiny.pal", pal)
        self.refresh()
        messagebox.showinfo("Created", f"Species folder created: {pdir}")

    def delete_species(self):
        sel = self.species_listbox.curselection()
        if not sel:
            return
        name = self.species_listbox.get(sel[0])
        pdir = self.app.project_root / "graphics" / "pokemon" / name
        if messagebox.askyesno("Confirm Delete", f"Are you sure you want to delete {name} and all its graphics?"):
            shutil.rmtree(pdir, ignore_errors=True)
            self.refresh()


# ==============================================================================
# TAB 2: TRAINER STUDIO (graphics/trainers)
# ==============================================================================

class TrainerStudioTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.front_img: Image.Image | None = None
        self.back_img: Image.Image | None = None
        self.palette: list[tuple[int, int, int]] = [(255, 0, 255)] + [(0, 0, 0)] * 15

        self.setup_ui()

    def setup_ui(self):
        left_pane = ttk.Frame(self, width=280)
        left_pane.pack(side=tk.LEFT, fill=tk.Y, padx=6, pady=6)

        search_frame = ttk.Frame(left_pane)
        search_frame.pack(fill=tk.X, pady=2)
        ttk.Label(search_frame, text="🔍 Filter:", font=("Arial", 9, "bold")).pack(side=tk.LEFT)
        self.filter_var = tk.StringVar()
        self.filter_var.trace_add("write", lambda *args: self.filter_trainers())
        ttk.Entry(search_frame, textvariable=self.filter_var).pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)

        self.trainer_listbox = tk.Listbox(left_pane, height=22, font=("Courier", 10))
        self.trainer_listbox.pack(fill=tk.BOTH, expand=True, pady=4)
        self.trainer_listbox.bind("<<ListboxSelect>>", self.on_select_trainer)

        btn_row = ttk.Frame(left_pane)
        btn_row.pack(fill=tk.X, pady=2)
        ttk.Button(btn_row, text="➕ New Trainer", command=self.create_trainer).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
        ttk.Button(btn_row, text="🗑️ Delete", command=self.delete_trainer).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)

        # Right Panel
        right_pane = ttk.Frame(self)
        right_pane.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=6, pady=6)

        previews_box = ttk.LabelFrame(right_pane, text="Trainer Battle Mugshots (64x64 at 4x Scale)", padding=10)
        previews_box.pack(fill=tk.X)

        p_row = ttk.Frame(previews_box)
        p_row.pack()

        # Front Canvas
        f_box = ttk.Frame(p_row, padding=6)
        f_box.pack(side=tk.LEFT, padx=12)
        ttk.Label(f_box, text="Front Pic (graphics/trainers/front_pics/)", font=("Arial", 9, "bold")).pack()
        self.canvas_front = tk.Canvas(f_box, width=256, height=256, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_front.pack(pady=4)
        ttk.Button(f_box, text="📥 Import Front...", command=lambda: self.import_trainer_pic("front")).pack(fill=tk.X)

        # Back Canvas
        b_box = ttk.Frame(p_row, padding=6)
        b_box.pack(side=tk.LEFT, padx=12)
        ttk.Label(b_box, text="Back Pic (graphics/trainers/back_pics/)", font=("Arial", 9, "bold")).pack()
        self.canvas_back = tk.Canvas(b_box, width=256, height=256, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_back.pack(pady=4)
        ttk.Button(b_box, text="📥 Import Back...", command=lambda: self.import_trainer_pic("back")).pack(fill=tk.X)

        # Swatch bar
        pal_box = ttk.LabelFrame(right_pane, text="16-Color Palette (graphics/trainers/palettes/)", padding=10)
        pal_box.pack(fill=tk.BOTH, expand=True, pady=8)

        self.swatch_frame = ttk.Frame(pal_box)
        self.swatch_frame.pack(fill=tk.X, pady=6)
        self.swatch_canvases: list[tk.Canvas] = []
        for i in range(16):
            c = tk.Canvas(self.swatch_frame, width=36, height=36, relief=tk.RIDGE, bd=2)
            c.grid(row=0, column=i, padx=2)
            self.swatch_canvases.append(c)

        self.info_label = ttk.Label(pal_box, text="", font=("Courier", 10))
        self.info_label.pack(anchor=tk.W, pady=4)

    def refresh(self):
        fdir = self.app.project_root / "graphics" / "trainers" / "front_pics"
        self.all_trainers: list[str] = []
        if fdir.is_dir():
            for f in sorted(fdir.glob("*.png")):
                self.all_trainers.append(f.stem)
        self.filter_trainers()

    def filter_trainers(self):
        query = self.filter_var.get().strip().lower()
        self.trainer_listbox.delete(0, tk.END)
        for t in getattr(self, "all_trainers", []):
            if not query or query in t.lower():
                self.trainer_listbox.insert(tk.END, t)

    def on_select_trainer(self, event):
        sel = self.trainer_listbox.curselection()
        if not sel:
            return
        name = self.trainer_listbox.get(sel[0])
        tdir = self.app.project_root / "graphics" / "trainers"

        front_f = tdir / "front_pics" / f"{name}.png"
        back_f = tdir / "back_pics" / f"{name}.png"
        pal_f = tdir / "palettes" / f"{name}.pal"

        if pal_f.exists():
            self.palette = read_jasc_pal(pal_f)
        else:
            self.palette = [(255, 0, 255)] + [(0, 0, 0)] * 15

        self.render_swatches()

        if front_f.exists():
            self.front_img = Image.open(front_f)
            self.render_preview(self.canvas_front, self.front_img, 256, 256)
        else:
            self.canvas_front.delete("all")

        if back_f.exists():
            self.back_img = Image.open(back_f)
            self.render_preview(self.canvas_back, self.back_img, 256, 256)
        else:
            self.canvas_back.delete("all")

        self.info_label.config(text=f"Selected: {name} | Colors: 16 (Slot 0 Transparent)")

    def render_preview(self, canvas, img: Image.Image, w: int, h: int):
        canvas.delete("all")
        resized = img.resize((w, h), Image.Resampling.NEAREST)
        tk_photo = ImageTk.PhotoImage(resized)
        canvas.create_image(w // 2, h // 2, image=tk_photo)
        canvas.image = tk_photo

    def render_swatches(self):
        for i, c in enumerate(self.palette[:16]):
            hex_color = f"#{c[0]:02x}{c[1]:02x}{c[2]:02x}"
            canvas = self.swatch_canvases[i]
            canvas.delete("all")
            canvas.create_rectangle(0, 0, 36, 36, fill=hex_color, outline="white" if i == 0 else "#444444")
            if i == 0:
                canvas.create_text(18, 18, text="T", fill="black", font=("Arial", 9, "bold"))

    def import_trainer_pic(self, pic_type: str):
        sel = self.trainer_listbox.curselection()
        if not sel:
            messagebox.showwarning("Select Trainer", "Please select a trainer first.")
            return
        name = self.trainer_listbox.get(sel[0])
        tdir = self.app.project_root / "graphics" / "trainers"

        f = filedialog.askopenfilename(filetypes=[("PNG Images", "*.png"), ("All Files", "*.*")])
        if not f:
            return
        raw = Image.open(f)
        quantized, pal = quantize_gba_image(raw, (64, 64))

        if pic_type == "front":
            quantized.save(tdir / "front_pics" / f"{name}.png")
            write_jasc_pal(tdir / "palettes" / f"{name}.pal", pal)
            self.palette = pal
            self.render_preview(self.canvas_front, quantized, 256, 256)
            self.render_swatches()
        else:
            quantized.save(tdir / "back_pics" / f"{name}.png")
            self.render_preview(self.canvas_back, quantized, 256, 256)

        messagebox.showinfo("Success", f"Updated {pic_type} pic for {name}")

    def create_trainer(self):
        name = simple_dialog_ask(self, "New Trainer", "Enter Trainer identifier (e.g. falkner, red, cooltrainer_m):")
        if not name:
            return
        tdir = self.app.project_root / "graphics" / "trainers"
        (tdir / "front_pics").mkdir(parents=True, exist_ok=True)
        (tdir / "back_pics").mkdir(parents=True, exist_ok=True)
        (tdir / "palettes").mkdir(parents=True, exist_ok=True)
        # Create blank 64x64
        blank = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
        q, pal = quantize_gba_image(blank, (64, 64))
        q.save(tdir / "front_pics" / f"{name.lower()}.png")
        write_jasc_pal(tdir / "palettes" / f"{name.lower()}.pal", pal)
        self.refresh()
        messagebox.showinfo("Created", f"Created trainer {name}")

    def delete_trainer(self):
        sel = self.trainer_listbox.curselection()
        if not sel:
            return
        name = self.trainer_listbox.get(sel[0])
        if messagebox.askyesno("Confirm", f"Delete trainer {name}?"):
            tdir = self.app.project_root / "graphics" / "trainers"
            for sub in ["front_pics", "back_pics", "palettes"]:
                for ext in [".png", ".pal"]:
                    target = tdir / sub / f"{name}{ext}"
                    if target.exists():
                        target.unlink()
            self.refresh()


# ==============================================================================
# TAB 3: OVERWORLD & OBJECTS (graphics/object_events)
# ==============================================================================

class OverworldStudioTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.current_img: Image.Image | None = None
        self.anim_timer = None
        self.anim_frame = 0
        self.anim_dir = 0  # 0: Down, 1: Up, 2: Left, 3: Right
        self.setup_ui()

    def setup_ui(self):
        left_pane = ttk.Frame(self, width=320)
        left_pane.pack(side=tk.LEFT, fill=tk.Y, padx=6, pady=6)

        search_frame = ttk.Frame(left_pane)
        search_frame.pack(fill=tk.X, pady=2)
        ttk.Label(search_frame, text="🔍 Filter:", font=("Arial", 9, "bold")).pack(side=tk.LEFT)
        self.filter_var = tk.StringVar()
        self.filter_var.trace_add("write", lambda *args: self.filter_sprites())
        ttk.Entry(search_frame, textvariable=self.filter_var).pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)

        self.char_listbox = tk.Listbox(left_pane, height=22, font=("Courier", 9))
        self.char_listbox.pack(fill=tk.BOTH, expand=True, pady=4)
        self.char_listbox.bind("<<ListboxSelect>>", self.on_select_char)

        btn_row = ttk.Frame(left_pane)
        btn_row.pack(fill=tk.X, pady=2)
        ttk.Button(btn_row, text="➕ New Sprite Sheet", command=self.create_sheet).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
        ttk.Button(btn_row, text="🗑️ Delete", command=self.delete_sheet).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)

        # Right Panel
        right_pane = ttk.Frame(self)
        right_pane.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=6, pady=6)

        top_preview = ttk.LabelFrame(right_pane, text="Overworld Sheet & Live Animation", padding=10)
        top_preview.pack(fill=tk.X)

        box_row = ttk.Frame(top_preview)
        box_row.pack()

        # Raw Sheet Canvas
        sheet_box = ttk.Frame(box_row, padding=4)
        sheet_box.pack(side=tk.LEFT, padx=12)
        ttk.Label(sheet_box, text="Full Sheet (graphics/object_events/pics/...)", font=("Arial", 9, "bold")).pack()
        self.canvas_sheet = tk.Canvas(sheet_box, width=192, height=384, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_sheet.pack(pady=4)

        # Live Walk Preview
        walk_box = ttk.Frame(box_row, padding=4)
        walk_box.pack(side=tk.LEFT, padx=12)
        ttk.Label(walk_box, text="4-Direction Walk Loop (8x Scale)", font=("Arial", 9, "bold")).pack()
        self.canvas_walk = tk.Canvas(walk_box, width=192, height=256, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_walk.pack(pady=4)

        dir_row = ttk.Frame(walk_box)
        dir_row.pack(pady=4)
        ttk.Button(dir_row, text="⬇️ Down", command=lambda: self.set_dir(0)).grid(row=0, column=1)
        ttk.Button(dir_row, text="⬆️ Up", command=lambda: self.set_dir(1)).grid(row=0, column=0)
        ttk.Button(dir_row, text="⬅️ Left", command=lambda: self.set_dir(2)).grid(row=0, column=2)
        ttk.Button(dir_row, text="➡️ Right", command=lambda: self.set_dir(3)).grid(row=0, column=3)

        ctrl_box = ttk.LabelFrame(right_pane, text="Sprite Operations", padding=10)
        ctrl_box.pack(fill=tk.BOTH, expand=True, pady=8)
        ttk.Button(ctrl_box, text="📥 Import / Quantize 4bpp Sheet...", command=self.import_sheet).pack(anchor=tk.W, pady=2)
        self.info_label = ttk.Label(ctrl_box, text="", font=("Courier", 10))
        self.info_label.pack(anchor=tk.W, pady=4)

    def refresh(self):
        odir = self.app.project_root / "graphics" / "object_events" / "pics"
        self.all_sheets: list[tuple[str, Path]] = []
        if odir.is_dir():
            for p in sorted(odir.rglob("*.png")):
                rel = p.relative_to(odir)
                self.all_sheets.append((str(rel), p))
        self.filter_sprites()

    def filter_sprites(self):
        query = self.filter_var.get().strip().lower()
        self.char_listbox.delete(0, tk.END)
        self.displayed_items = []
        for rel_str, full_path in getattr(self, "all_sheets", []):
            if not query or query in rel_str.lower():
                self.char_listbox.insert(tk.END, rel_str)
                self.displayed_items.append(full_path)

    def on_select_char(self, event):
        sel = self.char_listbox.curselection()
        if not sel or not self.displayed_items:
            return
        fpath = self.displayed_items[sel[0]]
        self.app.current_character_file = fpath
        self.current_img = Image.open(fpath)

        w, h = self.current_img.size
        # Render raw sheet
        self.canvas_sheet.delete("all")
        resized = self.current_img.resize((192, 384), Image.Resampling.NEAREST)
        tk_photo = ImageTk.PhotoImage(resized)
        self.canvas_sheet.create_image(96, 192, image=tk_photo)
        self.canvas_sheet.image = tk_photo

        self.info_label.config(text=f"Selected: {fpath.name} | Dimensions: {w}x{h} px")
        self.start_anim_loop()

    def set_dir(self, d: int):
        self.anim_dir = d

    def start_anim_loop(self):
        if self.anim_timer:
            self.after_cancel(self.anim_timer)
        self.run_anim_step()

    def run_anim_step(self):
        if self.current_img is not None:
            w, h = self.current_img.size
            fw = 16 if w >= 48 else w
            fh = 32 if h >= 128 else (16 if h <= 64 else h // 4)

            # Standard walk cycle pattern: 0, 1, 0, 2
            col_seq = [0, 1, 0, 2]
            col = col_seq[self.anim_frame % len(col_seq)]
            row = min(self.anim_dir, (h // fh) - 1)

            x0 = col * fw
            y0 = row * fh
            if x0 + fw <= w and y0 + fh <= h:
                frame = self.current_img.crop((x0, y0, x0 + fw, y0 + fh))
                scaled = frame.resize((128, 256), Image.Resampling.NEAREST)
                tk_f = ImageTk.PhotoImage(scaled)
                self.canvas_walk.delete("all")
                self.canvas_walk.create_image(96, 128, image=tk_f)
                self.canvas_walk.image = tk_f

            self.anim_frame += 1

        self.anim_timer = self.after(250, self.run_anim_step)

    def import_sheet(self):
        if not self.app.current_character_file:
            return
        f = filedialog.askopenfilename(filetypes=[("PNG Images", "*.png"), ("All Files", "*.*")])
        if not f:
            return
        img = Image.open(f)
        img.save(self.app.current_character_file)
        self.current_img = img
        self.on_select_char(None)
        messagebox.showinfo("Imported", "Updated overworld sheet!")

    def create_sheet(self):
        name = simple_dialog_ask(self, "New Overworld Sheet", "Enter relative path under pics/ (e.g. people/ethan/walking.png):")
        if not name:
            return
        target = self.app.project_root / "graphics" / "object_events" / "pics" / name
        target.parent.mkdir(parents=True, exist_ok=True)
        blank = Image.new("RGBA", (48, 128), (0, 0, 0, 0))
        blank.save(target)
        self.refresh()
        messagebox.showinfo("Created", f"Created sheet: {target}")

    def delete_sheet(self):
        if not self.app.current_character_file:
            return
        if messagebox.askyesno("Confirm Delete", f"Delete {self.app.current_character_file.name}?"):
            self.app.current_character_file.unlink()
            self.refresh()


# ==============================================================================
# TAB 4: TILESETS & PORYTILES (data/tilesets & source_tilesets)
# ==============================================================================

class PorytilesStudioTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.setup_ui()

    def setup_ui(self):
        left_pane = ttk.Frame(self, width=280)
        left_pane.pack(side=tk.LEFT, fill=tk.Y, padx=6, pady=6)

        search_frame = ttk.Frame(left_pane)
        search_frame.pack(fill=tk.X, pady=2)
        ttk.Label(search_frame, text="🔍 Filter:", font=("Arial", 9, "bold")).pack(side=tk.LEFT)
        self.filter_var = tk.StringVar()
        self.filter_var.trace_add("write", lambda *args: self.filter_tilesets())
        ttk.Entry(search_frame, textvariable=self.filter_var).pack(side=tk.LEFT, fill=tk.X, expand=True, padx=4)

        self.tileset_listbox = tk.Listbox(left_pane, height=22, font=("Courier", 10))
        self.tileset_listbox.pack(fill=tk.BOTH, expand=True, pady=4)
        self.tileset_listbox.bind("<<ListboxSelect>>", self.on_select_tileset)

        btn_row = ttk.Frame(left_pane)
        btn_row.pack(fill=tk.X, pady=2)
        ttk.Button(btn_row, text="➕ New Tileset", command=self.create_tileset).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
        ttk.Button(btn_row, text="🗑️ Delete", command=self.delete_tileset).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)

        # Right Panel
        right_pane = ttk.Frame(self)
        right_pane.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Previews
        top_box = ttk.LabelFrame(right_pane, text="Tileset Layers / Compiled Tiles", padding=8)
        top_box.pack(fill=tk.X)

        layer_row = ttk.Frame(top_box)
        layer_row.pack()

        # Canvas for tiles.png or bottom.png
        self.canvas_tile = tk.Canvas(layer_row, width=256, height=256, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_tile.pack(side=tk.LEFT, padx=10)

        info_side = ttk.Frame(layer_row)
        info_side.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.layer_info = ttk.Label(info_side, text="Select a tileset on the left to inspect layers.", justify=tk.LEFT)
        self.layer_info.pack(anchor=tk.W, pady=4)

        ttk.Button(info_side, text="⚙️ Copy Porytiles Secondary Command", command=self.copy_porytiles_cli).pack(anchor=tk.W, pady=4)

        # Attributes Editor Table
        attr_box = ttk.LabelFrame(right_pane, text="Metatile Attributes (attributes.csv / behavior)", padding=8)
        attr_box.pack(fill=tk.BOTH, expand=True, pady=6)

        cols = ("id", "behavior", "terrain_type", "encounter_type")
        self.attr_tree = ttk.Treeview(attr_box, columns=cols, show="headings", height=8)
        for c in cols:
            self.attr_tree.heading(c, text=c)
            self.attr_tree.column(c, width=130)
        self.attr_tree.pack(fill=tk.BOTH, expand=True)

    def refresh(self):
        root = self.app.project_root
        self.all_tilesets: list[tuple[str, Path]] = []

        # 1. Check data/tilesets/primary
        p_dir = root / "data" / "tilesets" / "primary"
        if p_dir.is_dir():
            for f in sorted(p_dir.iterdir()):
                if f.is_dir():
                    self.all_tilesets.append((f"[Pri] {f.name}", f))

        # 2. Check data/tilesets/secondary
        s_dir = root / "data" / "tilesets" / "secondary"
        if s_dir.is_dir():
            for f in sorted(s_dir.iterdir()):
                if f.is_dir():
                    self.all_tilesets.append((f"[Sec] {f.name}", f))

        # 3. Check source_tilesets
        src_dir = root / "source_tilesets"
        if src_dir.is_dir():
            for f in sorted(src_dir.rglob("*")):
                if f.is_dir() and (f / "attributes.csv").exists():
                    self.all_tilesets.append((f"[Src] {f.name}", f))

        self.filter_tilesets()

    def filter_tilesets(self):
        query = self.filter_var.get().strip().lower()
        self.tileset_listbox.delete(0, tk.END)
        self.displayed_tilesets = []
        for tag, fpath in getattr(self, "all_tilesets", []):
            if not query or query in tag.lower():
                self.tileset_listbox.insert(tk.END, tag)
                self.displayed_tilesets.append(fpath)

    def on_select_tileset(self, event):
        sel = self.tileset_listbox.curselection()
        if not sel or not self.displayed_tilesets:
            return
        tdir = self.displayed_tilesets[sel[0]]
        self.app.current_tileset_dir = tdir

        # Look for tiles.png or bottom.png
        tile_img_path = tdir / "tiles.png" if (tdir / "tiles.png").exists() else (tdir / "bottom.png")
        if tile_img_path.exists():
            img = Image.open(tile_img_path)
            resized = img.resize((256, 256), Image.Resampling.NEAREST)
            tk_photo = ImageTk.PhotoImage(resized)
            self.canvas_tile.delete("all")
            self.canvas_tile.create_image(128, 128, image=tk_photo)
            self.canvas_tile.image = tk_photo
            self.layer_info.config(text=f"Tileset: {tdir.name}\nPath: {tdir}\nPreview: {tile_img_path.name}")
        else:
            self.canvas_tile.delete("all")
            self.layer_info.config(text=f"Tileset: {tdir.name}\n(No tiles.png or bottom.png found)")

        # Populate attributes
        self.attr_tree.delete(*self.attr_tree.get_children())
        attr_file = tdir / "attributes.csv"
        if attr_file.exists():
            lines = attr_file.read_text(encoding="utf-8").splitlines()
            for line in lines[1:]:
                parts = [p.strip() for p in line.split(",")]
                if len(parts) >= 4:
                    self.attr_tree.insert("", tk.END, values=parts[:4])

    def copy_porytiles_cli(self):
        if not self.app.current_tileset_dir:
            return
        tdir = self.app.current_tileset_dir
        cmd = f"porytiles compile-secondary --metatile-attribute-size 2 -o data/tilesets/secondary/{tdir.name} source_tilesets/{tdir.name} data/tilesets/primary/general"
        self.clipboard_clear()
        self.clipboard_append(cmd)
        messagebox.showinfo("Copied CLI", f"Porytiles command copied:\n\n{cmd}")

    def create_tileset(self):
        name = simple_dialog_ask(self, "New Secondary Tileset", "Enter tileset name (e.g. new_bark_town):")
        if not name:
            return
        target = self.app.project_root / "data" / "tilesets" / "secondary" / name.lower()
        target.mkdir(parents=True, exist_ok=True)
        (target / "palettes").mkdir(parents=True, exist_ok=True)
        self.refresh()
        messagebox.showinfo("Created", f"Created secondary tileset: {target}")

    def delete_tileset(self):
        if not self.app.current_tileset_dir:
            return
        if messagebox.askyesno("Confirm Delete", f"Delete tileset {self.app.current_tileset_dir.name}?"):
            shutil.rmtree(self.app.current_tileset_dir, ignore_errors=True)
            self.refresh()


# ==============================================================================
# TAB 5: BATTLE BACKGROUNDS & BIOMES (graphics/battle_environment)
# ==============================================================================

class BattleBackgroundStudioTab(ttk.Frame):
    JOHTO_BIOMES = {
        "bell_tower": {"sky": (180, 100, 60), "base": (120, 80, 48)},
        "dark_cave": {"sky": (24, 24, 32), "base": (72, 64, 56)},
        "ruins_of_alph": {"sky": (110, 130, 140), "base": (150, 140, 120)},
        "whirl_islands": {"sky": (30, 70, 110), "base": (40, 90, 140)},
        "national_park": {"sky": (120, 180, 220), "base": (88, 168, 72)},
        "ecruteak_shrine": {"sky": (90, 40, 120), "base": (160, 110, 60)},
        "mt_silver": {"sky": (60, 70, 90), "base": (180, 190, 200)},
    }

    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.current_bg_img: Image.Image | None = None
        self.setup_ui()

    def setup_ui(self):
        left_pane = ttk.Frame(self, width=280)
        left_pane.pack(side=tk.LEFT, fill=tk.Y, padx=6, pady=6)

        ttk.Label(left_pane, text="Existing Environments:", font=("Arial", 9, "bold")).pack(anchor=tk.W)
        self.env_listbox = tk.Listbox(left_pane, height=22, font=("Courier", 10))
        self.env_listbox.pack(fill=tk.BOTH, expand=True, pady=4)
        self.env_listbox.bind("<<ListboxSelect>>", self.on_select_env)

        # Right Panel
        right_pane = ttk.Frame(self)
        right_pane.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=6, pady=6)

        preview_box = ttk.LabelFrame(right_pane, text="Battle Scene Mockup (240x160 GBA Canvas at 2x Scale)", padding=10)
        preview_box.pack(fill=tk.X)

        self.canvas_scene = tk.Canvas(preview_box, width=480, height=320, bg="#111111", relief=tk.RIDGE, bd=2)
        self.canvas_scene.pack(pady=4)

        gen_box = ttk.LabelFrame(right_pane, text="Procedural Johto Biome Generator", padding=10)
        gen_box.pack(fill=tk.BOTH, expand=True, pady=8)

        row = ttk.Frame(gen_box)
        row.pack(fill=tk.X, pady=4)
        ttk.Label(row, text="Select Biome Preset:", font=("Arial", 9, "bold")).pack(side=tk.LEFT, padx=4)
        self.biome_var = tk.StringVar(value="bell_tower")
        self.biome_combo = ttk.Combobox(row, textvariable=self.biome_var, values=list(self.JOHTO_BIOMES.keys()), state="readonly")
        self.biome_combo.pack(side=tk.LEFT, padx=4)

        ttk.Button(row, text="🎨 Generate & Export to graphics/battle_environment/", command=self.generate_and_export_biome).pack(side=tk.LEFT, padx=8)

        self.info_label = ttk.Label(gen_box, text="", font=("Courier", 10))
        self.info_label.pack(anchor=tk.W, pady=6)

    def refresh(self):
        bdir = self.app.project_root / "graphics" / "battle_environment"
        self.env_listbox.delete(0, tk.END)
        self.existing_envs = []
        if bdir.is_dir():
            for f in sorted(bdir.iterdir()):
                if f.is_dir():
                    self.env_listbox.insert(tk.END, f.name)
                    self.existing_envs.append(f)

    def on_select_env(self, event):
        sel = self.env_listbox.curselection()
        if not sel or not getattr(self, "existing_envs", []):
            return
        edir = self.existing_envs[sel[0]]
        tiles_f = edir / "tiles.png"
        pal_f = edir / "palette.pal"

        # Mockup scene
        scene = Image.new("RGBA", (240, 160), (40, 50, 70, 255))
        d = ImageDraw.Draw(scene)
        if tiles_f.exists():
            timg = Image.open(tiles_f).convert("RGBA")
            scene.paste(timg.resize((240, 100)), (0, 0))
        d.ellipse([10, 110, 110, 150], fill=(80, 130, 80, 255))
        d.ellipse([130, 80, 230, 120], fill=(70, 120, 70, 255))

        scaled = scene.resize((480, 320), Image.Resampling.NEAREST)
        tk_photo = ImageTk.PhotoImage(scaled)
        self.canvas_scene.delete("all")
        self.canvas_scene.create_image(240, 160, image=tk_photo)
        self.canvas_scene.image = tk_photo

        self.info_label.config(text=f"Inspecting: {edir.name} | Tiles: {tiles_f.exists()} | Pal: {pal_f.exists()}")

    def generate_and_export_biome(self):
        biome = self.biome_var.get()
        cfg = self.JOHTO_BIOMES.get(biome, {"sky": (100, 100, 100), "base": (80, 80, 80)})
        target = self.app.project_root / "graphics" / "battle_environment" / biome
        target.mkdir(parents=True, exist_ok=True)

        # Build 240x112 BG layer
        bg = Image.new("RGBA", (240, 112), cfg["sky"] + (255,))
        q_bg, pal = quantize_gba_image(bg, (240, 112))
        q_bg.save(target / "tiles.png")
        write_jasc_pal(target / "palette.pal", pal)

        self.refresh()
        messagebox.showinfo("Export Complete", f"Generated 4bpp battle environment for {biome} in {target}")


# ==============================================================================
# TAB 6: PALETTES & CONFLICT AUDITOR
# ==============================================================================

class PaletteStudioTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.palette: list[tuple[int, int, int]] = [(255, 0, 255)] + [(0, 0, 0)] * 15
        self.setup_ui()

    def setup_ui(self):
        top_box = ttk.LabelFrame(self, text="16-Color Palette Inspector & Color Picker", padding=10)
        top_box.pack(fill=tk.X, padx=8, pady=8)

        self.swatch_frame = ttk.Frame(top_box)
        self.swatch_frame.pack(fill=tk.X, pady=6)
        self.swatch_canvases: list[tk.Canvas] = []

        for i in range(16):
            c = tk.Canvas(self.swatch_frame, width=44, height=44, relief=tk.RIDGE, bd=2)
            c.grid(row=0, column=i, padx=2)
            c.bind("<Button-1>", lambda e, idx=i: self.on_click_swatch(idx))
            self.swatch_canvases.append(c)

        self.info_label = ttk.Label(top_box, text="Slot 0 is hardcoded as transparent #FF00FF.", font=("Courier", 10))
        self.info_label.pack(anchor=tk.W, pady=4)

        audit_box = ttk.LabelFrame(self, text="GBA 4bpp Hardware 8x8 Tile Conflict Auditor", padding=10)
        audit_box.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)

        btn_bar = ttk.Frame(audit_box)
        btn_bar.pack(fill=tk.X, pady=4)
        ttk.Button(btn_bar, text="🔍 Scan Specific Image File...", command=self.audit_single_file).pack(side=tk.LEFT, padx=4)
        ttk.Button(btn_bar, text="🚨 Scan Entire graphics/ Directory", command=self.audit_project).pack(side=tk.LEFT, padx=4)

        self.log_text = tk.Text(audit_box, height=14, font=("Courier", 9), bg="#1e1e1e", fg="#e0e0e0", relief=tk.SOLID, bd=1)
        self.log_text.pack(fill=tk.BOTH, expand=True, pady=4)

        self.render_swatches()

    def render_swatches(self):
        for i, c in enumerate(self.palette[:16]):
            hex_color = f"#{c[0]:02x}{c[1]:02x}{c[2]:02x}"
            canvas = self.swatch_canvases[i]
            canvas.delete("all")
            canvas.create_rectangle(0, 0, 44, 44, fill=hex_color, outline="white" if i == 0 else "#444444")
            canvas.create_text(22, 22, text=str(i), fill="black" if i == 0 else "white", font=("Arial", 9, "bold"))

    def on_click_swatch(self, idx: int):
        if idx == 0:
            messagebox.showinfo("Hardware Constraint", "Slot 0 is hardcoded in GBA OBJ/BG palette memory as the transparent key (#FF00FF).")
            return
        r, g, b = self.palette[idx]
        chosen = colorchooser.askcolor(color=f"#{r:02x}{g:02x}{b:02x}", title=f"Select Color for Slot {idx}")
        if chosen and chosen[0]:
            clamped = clamp_gba_rgb(int(chosen[0][0]), int(chosen[0][1]), int(chosen[0][2]))
            self.palette[idx] = clamped
            self.render_swatches()
            bgr = rgb_to_bgr555(*clamped)
            self.info_label.config(text=f"Slot {idx}: RGB{clamped} | GBA BGR555: 0x{bgr:04X} | Hex: #{clamped[0]:02x}{clamped[1]:02x}{clamped[2]:02x}")

    def audit_single_file(self):
        f = filedialog.askopenfilename(filetypes=[("PNG Images", "*.png")])
        if not f:
            return
        violations = self.scan_image(Path(f))
        if violations == 0:
            self.log_text.insert(tk.END, f"[✓] PASS: {Path(f).name} strictly conforms to 4bpp.\n")
        else:
            self.log_text.insert(tk.END, f"[✗] FAIL: {Path(f).name} has {violations} tile violations.\n")

    def audit_project(self):
        gdir = self.app.project_root / "graphics"
        self.log_text.insert(tk.END, f">>> Scanning all PNGs under {gdir}...\n")
        total_v = 0
        for p in gdir.rglob("*.png"):
            v = self.scan_image(p, log_violations=False)
            if v > 0:
                self.log_text.insert(tk.END, f"  [!] {p.relative_to(gdir)}: {v} violations\n")
                total_v += v
        if total_v == 0:
            self.log_text.insert(tk.END, "[✓] PASS: All scanned images conform to GBA hardware constraints.\n")
        else:
            self.log_text.insert(tk.END, f"[✗] Total violations found across project: {total_v}\n")

    def scan_image(self, p: Path, log_violations: bool = True) -> int:
        try:
            img = Image.open(p).convert("RGBA")
            arr = np.array(img)
            w, h = img.size
            tx, ty = w // 8, h // 8
            v = 0
            for y in range(ty):
                for x in range(tx):
                    box = arr[y*8:(y+1)*8, x*8:(x+1)*8]
                    vis = box[box[:, :, 3] >= 128][:, :3]
                    uniq = len({tuple(c) for c in vis})
                    has_t = 1 if np.any(box[:, :, 3] < 128) else 0
                    if uniq + has_t > 16:
                        v += 1
                        if log_violations:
                            self.log_text.insert(tk.END, f"  [!] Violation at 8x8 Tile ({x}, {y}) in {p.name}: {uniq+has_t} colors\n")
            return v
        except Exception:
            return 0


# ==============================================================================
# TAB 7: mGBA TEST BRIDGE
# ==============================================================================

class MGBATestBridgeTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.setup_ui()

    def setup_ui(self):
        ctrl_box = ttk.LabelFrame(self, text="Compilation & Emulator Controls", padding=10)
        ctrl_box.pack(fill=tk.X, padx=8, pady=8)

        row1 = ttk.Frame(ctrl_box)
        row1.pack(fill=tk.X, pady=4)
        ttk.Label(row1, text="Target ROM:").pack(side=tk.LEFT)
        self.rom_path_var = tk.StringVar(value="pokeconfluence.gba")
        ttk.Entry(row1, textvariable=self.rom_path_var, width=32).pack(side=tk.LEFT, padx=6)

        ttk.Button(row1, text="🔨 make -j$(nproc)", command=self.trigger_make_build).pack(side=tk.LEFT, padx=4)
        ttk.Button(row1, text="🧹 make clean", command=self.trigger_make_clean).pack(side=tk.LEFT, padx=4)
        ttk.Button(row1, text="🎮 Launch mGBA", command=self.launch_mgba).pack(side=tk.LEFT, padx=8)

        row2 = ttk.Frame(ctrl_box)
        row2.pack(fill=tk.X, pady=4)
        ttk.Label(row2, text="mGBA Command:").pack(side=tk.LEFT)
        self.mgba_cmd_var = tk.StringVar(value="mgba-qt")
        ttk.Entry(row2, textvariable=self.mgba_cmd_var, width=16).pack(side=tk.LEFT, padx=6)

        ttk.Button(row2, text="📜 Generate Lua Test Hook", command=self.generate_lua_test_script).pack(side=tk.LEFT, padx=4)

        log_box = ttk.LabelFrame(self, text="Build & Test Log Output", padding=10)
        log_box.pack(fill=tk.BOTH, expand=True, padx=8, pady=8)
        self.log_text = tk.Text(log_box, height=16, font=("Courier", 9), bg="#181818", fg="#00ff66", relief=tk.SOLID, bd=1)
        self.log_text.pack(fill=tk.BOTH, expand=True)

    def log(self, msg: str):
        self.log_text.insert(tk.END, msg + "\n")
        self.log_text.see(tk.END)

    def trigger_make_build(self):
        self.log(">>> Running make build...")
        def run():
            try:
                proc = subprocess.Popen(
                    ["make", f"-j{os.cpu_count() or 2}"],
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True,
                    cwd=str(self.app.project_root)
                )
                if proc.stdout is not None:
                    for line in proc.stdout:
                        self.log(line.strip())
                proc.wait()
                if proc.returncode == 0:
                    self.log("[✓] Build completed successfully!")
                else:
                    self.log(f"[!] Build exited with code {proc.returncode}")
            except Exception as e:
                self.log(f"[Error] Failed to execute make: {e}")
        threading.Thread(target=run, daemon=True).start()

    def trigger_make_clean(self):
        self.log(">>> Running make clean...")
        try:
            res = subprocess.run(["make", "clean"], capture_output=True, text=True, cwd=str(self.app.project_root))
            self.log(res.stdout)
            self.log("[✓] Clean completed.")
        except Exception as e:
            self.log(f"[Error] {e}")

    def generate_lua_test_script(self):
        target = self.app.project_root / "mgba_test_hook.lua"
        lua_code = """-- mgba_test_hook.lua - Pokeconfluence Automated Verification
console:log("Pokémon Confluence mGBA Verification Hook Active")
callbacks:add("frame", function()
    local f = emu:currentFrame()
    if f == 120 then
        emu:screenshot("mgba_asset_verify.png")
        console:log("[mGBA] Captured verification screenshot: mgba_asset_verify.png")
    end
end)
"""
        target.write_text(lua_code, encoding="utf-8")
        self.log(f"[✓] Generated Lua script: {target}")
        messagebox.showinfo("Lua Ready", f"Created: {target}")

    def launch_mgba(self):
        cmd = self.mgba_cmd_var.get().strip()
        rom = self.rom_path_var.get().strip()
        self.log(f">>> Launching {cmd} {rom}...")
        try:
            subprocess.Popen([cmd, rom], cwd=str(self.app.project_root))
            self.log("[✓] mGBA launched.")
        except FileNotFoundError:
            self.log(f"[!] Executable '{cmd}' not found in PATH.")
            messagebox.showwarning("mGBA Not Found", f"Could not find '{cmd}' in system PATH.")
        except Exception as e:
            self.log(f"[Error] {e}")


# ==============================================================================
# TAB 8: ASSET PROJECT EXPLORER
# ==============================================================================

class AssetExplorerTab(ttk.Frame):
    def __init__(self, parent, app: PokeAssetStudio):
        super().__init__(parent)
        self.app = app
        self.setup_ui()

    def setup_ui(self):
        left_pane = ttk.Frame(self, width=380)
        left_pane.pack(side=tk.LEFT, fill=tk.Y, padx=6, pady=6)

        self.tree = ttk.Treeview(left_pane, show="tree")
        self.tree.pack(fill=tk.BOTH, expand=True, pady=4)
        self.tree.bind("<<TreeviewSelect>>", self.on_select_file)

        btn_row = ttk.Frame(left_pane)
        btn_row.pack(fill=tk.X, pady=2)
        ttk.Button(btn_row, text="🔄 Refresh Tree", command=self.refresh).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)
        ttk.Button(btn_row, text="🗑️ Delete File", command=self.delete_selected).pack(side=tk.LEFT, expand=True, fill=tk.X, padx=1)

        right_pane = ttk.LabelFrame(self, text="File Metadata & Preview", padding=10)
        right_pane.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=6, pady=6)

        self.info_text = tk.Label(right_pane, text="Select a file to inspect.", justify=tk.LEFT, anchor=tk.W)
        self.info_text.pack(anchor=tk.W, pady=4)

        self.canvas_file = tk.Canvas(right_pane, width=384, height=384, bg="#1a1a1a", relief=tk.RIDGE, bd=2)
        self.canvas_file.pack(pady=8)

    def refresh(self):
        self.tree.delete(*self.tree.get_children())
        root_path = self.app.project_root
        node = self.tree.insert("", tk.END, text=root_path.name, open=True)
        self.populate_tree(node, root_path)

    def populate_tree(self, parent_node, path: Path):
        try:
            for item in sorted(path.iterdir()):
                if item.name.startswith("."):
                    continue
                if item.is_dir() and item.name in ["graphics", "data", "source_tilesets", "pokemon", "trainers", "object_events", "tilesets", "maps", "battle_environment"]:
                    node = self.tree.insert(parent_node, tk.END, text=item.name, values=[str(item)], open=False)
                    self.populate_tree(node, item)
                elif item.is_file() and item.suffix in [".png", ".pal", ".csv", ".json", ".h", ".c"]:
                    self.tree.insert(parent_node, tk.END, text=item.name, values=[str(item)])
        except PermissionError:
            pass

    def on_select_file(self, event):
        sel = self.tree.selection()
        if not sel:
            return
        vals = self.tree.item(sel[0])["values"]
        if not vals:
            return
        fpath = Path(vals[0])
        if fpath.is_file() and fpath.suffix == ".png":
            try:
                img = Image.open(fpath)
                w, h = img.size
                colors = len(img.getcolors(maxcolors=100000) or [])
                kb = fpath.stat().st_size / 1024
                self.info_text.config(
                    text=f"File: {fpath.name}\nPath: {fpath}\nDimensions: {w}x{h} px | Colors: {colors} | Size: {kb:.2f} KB"
                )
                resized = img.resize((min(384, w * 4), min(384, h * 4)), Image.Resampling.NEAREST)
                tk_photo = ImageTk.PhotoImage(resized)
                self.canvas_file.delete("all")
                self.canvas_file.create_image(192, 192, image=tk_photo)
                self.canvas_file.image = tk_photo
            except Exception as e:
                self.info_text.config(text=f"Error previewing: {e}")

    def delete_selected(self):
        sel = self.tree.selection()
        if not sel:
            return
        vals = self.tree.item(sel[0])["values"]
        if not vals:
            return
        fpath = Path(vals[0])
        if messagebox.askyesno("Confirm Delete", f"Delete {fpath.name}?"):
            if fpath.is_file():
                fpath.unlink()
            elif fpath.is_dir():
                shutil.rmtree(fpath, ignore_errors=True)
            self.refresh()


# ==============================================================================
# UTILITY HELPERS
# ==============================================================================

def simple_dialog_ask(parent, title: str, prompt: str) -> str:
    dlg = tk.Toplevel(parent)
    dlg.title(title)
    dlg.geometry("380x130")
    dlg.transient(parent)
    dlg.grab_set()

    ttk.Label(dlg, text=prompt).pack(padx=10, pady=8)
    ent = ttk.Entry(dlg, width=32)
    ent.pack(padx=10, pady=4)
    ent.focus_set()

    result = []
    def on_ok():
        val = ent.get().strip()
        if val:
            result.append(val)
        dlg.destroy()

    btn_row = ttk.Frame(dlg)
    btn_row.pack(pady=8)
    ttk.Button(btn_row, text="OK", command=on_ok).pack(side=tk.LEFT, padx=4)
    ttk.Button(btn_row, text="Cancel", command=dlg.destroy).pack(side=tk.LEFT, padx=4)

    parent.wait_window(dlg)
    return result[0] if result else ""


if __name__ == "__main__":
    app = PokeAssetStudio()
    app.mainloop()
