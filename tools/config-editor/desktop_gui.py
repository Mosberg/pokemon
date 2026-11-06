#!/usr/bin/env python3
"""
desktop_gui.py - World-class Native Desktop GUI for Pokémon Confluence Configuration Studio.
Crafted with high-contrast Obsidian dark styling, responsive layouts, live search,
interactive toggle switches, preset managers, diff inspector, and integrated ROM build runner.
"""

import os
import subprocess
import sys
import threading
import tkinter as tk
from pathlib import Path
from tkinter import messagebox, scrolledtext, ttk

from config_engine import GEN_CHOICES, PRESETS, ConfigEngine

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))


ROM_DIR = Path("/home/mosberg/wsl_projects/pokemon/pokeconfluence").resolve()

# OBSIDIAN PALETTE
C_BG_BASE = "#090d16"  # Deepest dark
C_BG_SIDEBAR = "#0f172a"  # Slate sidebar
C_BG_CARD = "#1e293b"  # Card background
C_BG_INPUT = "#0b1220"  # Input field background
C_BORDER = "#334155"  # Subtle border
C_BORDER_HI = "#3b82f6"  # Blue focus border
C_TEXT_MAIN = "#f8fafc"  # Bright white/slate
C_TEXT_MUTED = "#94a3b8"  # Secondary gray
C_TEXT_SUB = "#64748b"  # Dim footnote gray
C_ACCENT = "#38bdf8"  # Electric sky blue
C_EMERALD = "#10b981"  # Success green
C_GOLD = "#f59e0b"  # Warning gold
C_RUBY = "#ef4444"  # Alert red
C_PURPLE = "#a855f7"  # Generational purple


class SmoothToggleSwitch(tk.Canvas):
    """Custom high-DPI Canvas Toggle Switch with rounded pill rendering."""

    def __init__(self, parent, is_on=False, command=None, width=48, height=24):
        super().__init__(parent, width=width, height=height, bg=C_BG_CARD, highlightthickness=0, cursor="hand2")
        self.is_on = is_on
        self.command = command
        self.w = width
        self.h = height
        self.radius = height // 2
        self.bind("<Button-1>", self._on_click)
        self.draw()

    def set_state(self, is_on):
        self.is_on = is_on
        self.draw()

    def _on_click(self, event=None):
        self.is_on = not self.is_on
        self.draw()
        if self.command:
            self.command(self.is_on)

    def draw(self):
        self.delete("all")
        bg_color = C_EMERALD if self.is_on else "#475569"
        # Pill track
        self.create_arc((0, 0, self.h, self.h), start=90, extent=180, fill=bg_color, outline=bg_color)
        self.create_arc((self.w - self.h, 0, self.w, self.h), start=270, extent=180, fill=bg_color, outline=bg_color)
        self.create_rectangle((self.radius, 0, self.w - self.radius, self.h), fill=bg_color, outline=bg_color)

        # Thumb circle
        pad = 2
        thumb_dia = self.h - (pad * 2)
        cx = (self.w - self.radius) if self.is_on else self.radius
        self.create_oval(cx - thumb_dia / 2, pad, cx + thumb_dia / 2, pad + thumb_dia, fill="#ffffff", outline="")


class ConfigStudioTkApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Pokémon Confluence — Configuration Studio")
        self.root.geometry("1280x820")
        self.root.minsize(1000, 650)
        self.root.configure(bg=C_BG_BASE)

        self.engine = ConfigEngine()
        self.files = self.engine.list_files()
        self.active_filename = "caps.h"
        self.configs = []
        self.original_values = {}
        self.pending_updates = {}
        self.card_widgets = {}
        self.current_filter = "all"
        self.canvas_window_id = None

        self._init_styles()
        self._build_header()
        self._build_body()
        self._load_file(self.active_filename)

    def _init_styles(self):
        self.style = ttk.Style()
        try:
            self.style.theme_use("clam")
        except Exception:
            pass

        # Global theme configuration
        self.style.configure(
            ".",
            background=C_BG_SIDEBAR,
            foreground=C_TEXT_MAIN,
            bordercolor=C_BORDER,
            darkcolor=C_BG_SIDEBAR,
            lightcolor=C_BG_SIDEBAR,
            troughcolor=C_BG_BASE,
            font=("DejaVu Sans", 9),
        )

        # Treeview styling
        self.style.configure(
            "Treeview",
            background=C_BG_SIDEBAR,
            fieldbackground=C_BG_SIDEBAR,
            foreground=C_TEXT_MAIN,
            rowheight=32,
            font=("DejaVu Sans", 9),
            borderwidth=0,
        )
        self.style.map("Treeview", background=[("selected", "#1e40af")], foreground=[("selected", "#ffffff")])
        self.style.configure(
            "Treeview.Heading",
            background="#1e293b",
            foreground="#cbd5e1",
            font=("DejaVu Sans", 8, "bold"),
            relief=tk.FLAT,
            padding=6,
        )

        # Buttons
        self.style.configure(
            "TButton",
            background="#334155",
            foreground="#ffffff",
            padding=6,
            relief=tk.FLAT,
            font=("DejaVu Sans", 9, "bold"),
        )
        self.style.map(
            "TButton", background=[("active", "#475569"), ("disabled", "#1e293b")], foreground=[("disabled", "#64748b")]
        )

        self.style.configure("Accent.TButton", background=C_ACCENT, foreground="#0f172a")
        self.style.map("Accent.TButton", background=[("active", "#7dd3fc")])

        self.style.configure("Success.TButton", background=C_EMERALD, foreground="#ffffff")
        self.style.map("Success.TButton", background=[("active", "#059669")])

        self.style.configure("Danger.TButton", background=C_RUBY, foreground="#ffffff")
        self.style.map("Danger.TButton", background=[("active", "#dc2626")])

        # Combobox
        self.style.configure(
            "TCombobox",
            background=C_BG_INPUT,
            fieldbackground=C_BG_INPUT,
            foreground="#38bdf8",
            arrowcolor="#38bdf8",
            padding=5,
            relief=tk.FLAT,
        )
        self.style.map(
            "TCombobox",
            fieldbackground=[("readonly", C_BG_INPUT)],
            selectbackground=[("readonly", "#1e40af")],
            selectforeground=[("readonly", "#ffffff")],
        )

        # Scrollbar
        self.style.configure(
            "Vertical.TScrollbar", background="#334155", troughcolor=C_BG_BASE, relief=tk.FLAT, borderwidth=0
        )

    def _build_header(self):
        self.header_bar = tk.Frame(self.root, bg=C_BG_SIDEBAR, height=58, padx=16, pady=10)
        self.header_bar.pack(side=tk.TOP, fill=tk.X)

        # Logo / Brand
        brand_frame = tk.Frame(self.header_bar, bg=C_BG_SIDEBAR)
        brand_frame.pack(side=tk.LEFT)

        logo_lbl = tk.Label(
            brand_frame,
            text="⚡ Confluence Config Studio",
            font=("DejaVu Sans", 13, "bold"),
            fg=C_ACCENT,
            bg=C_BG_SIDEBAR,
        )
        logo_lbl.pack(side=tk.LEFT)

        badge_lbl = tk.Label(
            brand_frame, text="v2.5 PRO", font=("DejaVu Sans", 7, "bold"), fg="#ffffff", bg="#8b5cf6", padx=6, pady=2
        )
        badge_lbl.pack(side=tk.LEFT, padx=10)

        # Pending Changes Indicator
        self.pending_badge = tk.Label(
            self.header_bar, text="● 0 changes pending", font=("DejaVu Sans", 9, "bold"), fg=C_GOLD, bg=C_BG_SIDEBAR
        )
        self.pending_badge.pack(side=tk.LEFT, padx=16)

        # Right Action Buttons
        actions_frame = tk.Frame(self.header_bar, bg=C_BG_SIDEBAR)
        actions_frame.pack(side=tk.RIGHT)

        # Presets Menu Button
        self.preset_btn = tk.Menubutton(
            actions_frame,
            text="⚡ Presets ▾",
            font=("DejaVu Sans", 9, "bold"),
            bg="#334155",
            fg="#f8fafc",
            activebackground="#475569",
            activeforeground="#ffffff",
            relief=tk.FLAT,
            padx=10,
            pady=5,
        )
        self.preset_menu = tk.Menu(
            self.preset_btn,
            tearoff=0,
            bg=C_BG_CARD,
            fg=C_TEXT_MAIN,
            activebackground="#1e40af",
            activeforeground="#ffffff",
        )
        for key, p in PRESETS.items():
            self.preset_menu.add_command(label=f"{p['icon']} {p['title']}", command=lambda k=key: self._apply_preset(k))
        self.preset_btn.config(menu=self.preset_menu)
        self.preset_btn.pack(side=tk.LEFT, padx=4)

        # Batch Tools Menu Button
        self.batch_btn = tk.Menubutton(
            actions_frame,
            text="⚙ Batch Tools ▾",
            font=("DejaVu Sans", 9, "bold"),
            bg="#334155",
            fg="#f8fafc",
            activebackground="#475569",
            activeforeground="#ffffff",
            relief=tk.FLAT,
            padx=10,
            pady=5,
        )
        self.batch_menu = tk.Menu(
            self.batch_btn,
            tearoff=0,
            bg=C_BG_CARD,
            fg=C_TEXT_MAIN,
            activebackground="#1e40af",
            activeforeground="#ffffff",
        )
        self.batch_menu.add_command(
            label="✓ Enable All Generations 1-9 in species_enabled.h", command=self._batch_enable_all_species
        )
        self.batch_menu.add_command(
            label="✓ Set All Battle Defines in battle.h to GEN_LATEST", command=self._batch_set_battle_latest
        )
        self.batch_menu.add_separator()
        self.batch_menu.add_command(label="↺ Reset Active File to Original Defaults", command=self._reset_current_file)
        self.batch_btn.config(menu=self.batch_menu)
        self.batch_btn.pack(side=tk.LEFT, padx=4)

        # Discard Button
        self.btn_discard = ttk.Button(
            actions_frame, text="↺ Discard", style="Danger.TButton", state=tk.DISABLED, command=self._discard_changes
        )
        self.btn_discard.pack(side=tk.LEFT, padx=4)

        # Diff Preview Button
        self.btn_diff = ttk.Button(
            actions_frame, text="👁 Diff Preview", style="TButton", state=tk.DISABLED, command=self._show_diff_modal
        )
        self.btn_diff.pack(side=tk.LEFT, padx=4)

        # Save All Button
        self.btn_save = ttk.Button(
            actions_frame,
            text="💾 Save Changes",
            style="Success.TButton",
            state=tk.DISABLED,
            command=self._save_all_changes,
        )
        self.btn_save.pack(side=tk.LEFT, padx=4)

        # Build ROM Button
        self.btn_build = ttk.Button(
            actions_frame, text="🔨 Build ROM", style="Accent.TButton", command=self._show_build_modal
        )
        self.btn_build.pack(side=tk.LEFT, padx=4)

    def _build_body(self):
        paned = tk.PanedWindow(self.root, orient=tk.HORIZONTAL, bg=C_BORDER, sashwidth=4, bd=0)
        paned.pack(fill=tk.BOTH, expand=True)

        # LEFT SIDEBAR (Files list)
        sidebar = tk.Frame(paned, bg=C_BG_SIDEBAR, width=320)
        paned.add(sidebar, minsize=260)

        # Global Search
        search_box_frame = tk.Frame(sidebar, bg=C_BG_SIDEBAR, padx=12, pady=10)
        search_box_frame.pack(fill=tk.X)

        self.global_search_var = tk.StringVar()
        self.global_search_var.trace_add("write", lambda *args: self._on_global_search())
        search_entry = tk.Entry(
            search_box_frame,
            textvariable=self.global_search_var,
            bg=C_BG_INPUT,
            fg=C_TEXT_MAIN,
            insertbackground=C_ACCENT,
            relief=tk.FLAT,
            font=("DejaVu Sans", 9),
            bd=5,
        )
        search_entry.pack(fill=tk.X)
        self._add_placeholder(search_entry, "Search 2,040+ settings...")

        # Treeview for 23 config files
        tree_container = tk.Frame(sidebar, bg=C_BG_SIDEBAR)
        tree_container.pack(fill=tk.BOTH, expand=True, padx=6, pady=2)

        self.file_tree = ttk.Treeview(tree_container, columns=("count",), show="tree headings", selectmode="browse")
        self.file_tree.heading("#0", text="Configuration Category / File", anchor="w")
        self.file_tree.heading("count", text="Opts", anchor="center")
        self.file_tree.column("#0", width=220, anchor="w")
        self.file_tree.column("count", width=45, anchor="center")

        tree_scroll = ttk.Scrollbar(tree_container, orient=tk.VERTICAL, command=self.file_tree.yview)
        self.file_tree.configure(yscrollcommand=tree_scroll.set)

        self.file_tree.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        tree_scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.file_tree.bind("<<TreeviewSelect>>", self._on_tree_select)

        self._populate_file_tree()

        # Sidebar footer
        sb_foot = tk.Frame(sidebar, bg="#0b1220", padx=12, pady=8)
        sb_foot.pack(fill=tk.X, side=tk.BOTTOM)
        tk.Label(
            sb_foot,
            text="23 C Header Files | pokeemerald-expansion",
            font=("DejaVu Sans", 8),
            fg=C_TEXT_SUB,
            bg="#0b1220",
        ).pack(side=tk.LEFT)

        # RIGHT MAIN PANEL
        self.main_panel = tk.Frame(paned, bg=C_BG_BASE)
        paned.add(self.main_panel, minsize=650)

        # File Banner Header
        self.file_banner = tk.Frame(self.main_panel, bg="#0f172a", padx=20, pady=12, bd=1, relief=tk.FLAT)
        self.file_banner.pack(fill=tk.X)

        title_row = tk.Frame(self.file_banner, bg="#0f172a")
        title_row.pack(fill=tk.X)

        self.active_file_title_lbl = tk.Label(
            title_row, text="", font=("DejaVu Sans", 13, "bold"), fg="#ffffff", bg="#0f172a"
        )
        self.active_file_title_lbl.pack(side=tk.LEFT)

        self.active_file_tag_lbl = tk.Label(
            title_row, text="", font=("Courier", 9, "bold"), fg=C_ACCENT, bg="#1e293b", padx=8, pady=2
        )
        self.active_file_tag_lbl.pack(side=tk.LEFT, padx=10)

        self.active_file_desc_lbl = tk.Label(
            self.file_banner,
            text="",
            font=("DejaVu Sans", 9),
            fg=C_TEXT_MUTED,
            bg="#0f172a",
            wraplength=750,
            justify=tk.LEFT,
        )
        self.active_file_desc_lbl.pack(anchor="w", pady=(4, 0))

        # Filter Chips Toolbar
        filter_toolbar = tk.Frame(self.main_panel, bg="#131b2e", padx=16, pady=8)
        filter_toolbar.pack(fill=tk.X)

        filter_lbl = tk.Label(
            filter_toolbar, text="FILTER:", font=("DejaVu Sans", 7, "bold"), fg=C_TEXT_SUB, bg="#131b2e"
        )
        filter_lbl.pack(side=tk.LEFT, padx=(0, 6))

        self.filter_buttons = {}
        filters = [
            ("All", "all"),
            ("Modified", "modified"),
            ("Booleans", "boolean"),
            ("Generations", "gen"),
            ("Numbers", "number"),
            ("Enums", "enum"),
            ("Notices", "warnings"),
        ]
        for label, fkey in filters:
            btn = tk.Button(
                filter_toolbar,
                text=label,
                font=("DejaVu Sans", 8, "bold"),
                bg="#1e293b",
                fg=C_TEXT_MUTED,
                activebackground=C_ACCENT,
                activeforeground="#ffffff",
                relief=tk.FLAT,
                padx=8,
                pady=3,
                command=lambda k=fkey: self._set_filter(k),
            )
            btn.pack(side=tk.LEFT, padx=3)
            self.filter_buttons[fkey] = btn

        self.filter_buttons["all"].config(bg=C_ACCENT, fg="#0f172a")

        # In-File Quick Search
        self.file_search_var = tk.StringVar()
        self.file_search_var.trace_add("write", lambda *args: self._render_settings_list())
        file_search_entry = tk.Entry(
            filter_toolbar,
            textvariable=self.file_search_var,
            bg=C_BG_INPUT,
            fg=C_TEXT_MAIN,
            insertbackground=C_ACCENT,
            relief=tk.FLAT,
            font=("DejaVu Sans", 8),
            width=24,
            bd=3,
        )
        file_search_entry.pack(side=tk.RIGHT)
        self._add_placeholder(file_search_entry, "Filter active file...")

        # Responsive Scrollable Canvas for Settings Cards
        canvas_container = tk.Frame(self.main_panel, bg=C_BG_BASE)
        canvas_container.pack(fill=tk.BOTH, expand=True, padx=12, pady=10)

        self.canvas = tk.Canvas(canvas_container, bg=C_BG_BASE, highlightthickness=0)
        self.scrollbar = ttk.Scrollbar(
            canvas_container, orient=tk.VERTICAL, command=self.canvas.yview, style="Vertical.TScrollbar"
        )
        self.scrollable_inner = tk.Frame(self.canvas, bg=C_BG_BASE)

        self.canvas_window_id = self.canvas.create_window((0, 0), window=self.scrollable_inner, anchor="nw")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)

        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        # STRETCH INNER WINDOW TO FILL 100% CANVAS WIDTH (Fixes right-side void!)
        self.canvas.bind("<Configure>", self._on_canvas_configure)
        self.scrollable_inner.bind("<Configure>", lambda e: self.canvas.configure(scrollregion=self.canvas.bbox("all")))
        self.canvas.bind_all("<MouseWheel>", self._on_mousewheel)

    def _on_canvas_configure(self, event):
        # Dynamically match width of inner frame to canvas width minus padding
        self.canvas.itemconfig(self.canvas_window_id, width=event.width)

    def _on_mousewheel(self, event):
        # Linux MouseWheel delta handling
        if event.num == 4 or event.delta > 0:
            self.canvas.yview_scroll(-2, "units")
        elif event.num == 5 or event.delta < 0:
            self.canvas.yview_scroll(2, "units")

    def _populate_file_tree(self):
        if not hasattr(self, "file_tree"):
            return
        self.file_tree.delete(*self.file_tree.get_children())
        search = self.global_search_var.get().lower().strip()
        if search == "search 2,040+ settings...":
            search = ""

        categories = {}
        for f in self.files:
            cat = f["category"]
            if cat not in categories:
                categories[cat] = []
            categories[cat].append(f)

        for cat, flist in categories.items():
            cat_id = f"cat_{cat}"
            filtered_files = []
            for f in flist:
                if search:
                    match_file = search in f["filename"].lower() or search in f["title"].lower()
                    cfgs = self.engine.parse_file(f["filename"])
                    match_cfg = any(search in c["name"].lower() or search in c["description"].lower() for c in cfgs)
                    if not match_file and not match_cfg:
                        continue
                filtered_files.append(f)

            if filtered_files:
                self.file_tree.insert("", tk.END, iid=cat_id, text=f"📂 {cat}", open=True)
                for f in filtered_files:
                    fname = f["filename"]
                    is_dirty = fname in self.pending_updates and len(self.pending_updates[fname]) > 0
                    dirty_marker = " ●" if is_dirty else ""
                    self.file_tree.insert(
                        cat_id,
                        tk.END,
                        iid=fname,
                        text=f"{f['icon']} {f['filename']}{dirty_marker}",
                        values=(f["config_count"],),
                    )

    def _on_tree_select(self, event):
        selected = self.file_tree.selection()
        if selected:
            sel_id = selected[0]
            if sel_id.endswith(".h"):
                self._load_file(sel_id)

    def _load_file(self, filename):
        self.active_filename = filename
        fmeta = next((f for f in self.files if f["filename"] == filename), None)
        if fmeta:
            self.active_file_title_lbl.config(text=f"{fmeta['icon']} {fmeta['title']}")
            self.active_file_tag_lbl.config(text=filename)
            self.active_file_desc_lbl.config(text=fmeta["description"])

        self.configs = self.engine.parse_file(filename)
        if filename not in self.original_values:
            self.original_values[filename] = {c["name"]: c["value"] for c in self.configs}

        self._render_settings_list()

    def _set_filter(self, filter_key):
        self.current_filter = filter_key
        for k, btn in self.filter_buttons.items():
            if k == filter_key:
                btn.config(bg=C_ACCENT, fg="#0f172a")
            else:
                btn.config(bg="#1e293b", fg=C_TEXT_MUTED)
        self._render_settings_list()

    def _render_settings_list(self):
        if not hasattr(self, "scrollable_inner"):
            return
        for w in self.scrollable_inner.winfo_children():
            w.destroy()
        self.card_widgets.clear()

        query = self.file_search_var.get().lower().strip()
        if query == "filter active file...":
            query = ""
        last_section = None

        file_updates = self.pending_updates.get(self.active_filename, {})
        orig_map = self.original_values.get(self.active_filename, {})

        matched_count = 0

        for cfg in self.configs:
            name = cfg["name"]
            desc = cfg["description"]
            val = file_updates.get(name, cfg["value"])
            orig_val = orig_map.get(name, cfg["value"])
            is_modified = val != orig_val

            # Apply filters
            if query:
                if query not in name.lower() and query not in desc.lower() and query not in val.lower():
                    continue

            if self.current_filter == "modified" and not is_modified:
                continue
            elif self.current_filter == "boolean" and cfg["type"] != "boolean":
                continue
            elif self.current_filter == "gen" and cfg["type"] != "gen":
                continue
            elif self.current_filter == "number" and cfg["type"] != "number":
                continue
            elif self.current_filter == "enum" and cfg["type"] not in ["enum", "family"]:
                continue
            elif self.current_filter == "warnings" and not cfg["notices"]:
                continue

            matched_count += 1

            # Render Section Banner
            if cfg["section"] != last_section:
                last_section = cfg["section"]
                sec_bar = tk.Frame(self.scrollable_inner, bg="#0d1527", padx=12, pady=6)
                sec_bar.pack(fill=tk.X, pady=(14, 6))
                tk.Label(
                    sec_bar,
                    text=f"📁  {last_section.upper()}",
                    font=("DejaVu Sans", 8, "bold"),
                    fg="#38bdf8",
                    bg="#0d1527",
                ).pack(anchor="w")

            # Render Setting Card (100% full width)
            card_border = C_GOLD if is_modified else C_BORDER
            card_bg = "#192231" if is_modified else C_BG_CARD
            card = tk.Frame(self.scrollable_inner, bg=card_bg, bd=1, relief=tk.SOLID, padx=14, pady=12)
            card.pack(fill=tk.X, pady=4)
            card.config(highlightbackground=card_border, highlightthickness=1)

            # Top Header Row: Name, Type Badge, Notices, and Control
            top_row = tk.Frame(card, bg=card_bg)
            top_row.pack(fill=tk.X)

            # Left side: Name & Badges
            left_info = tk.Frame(top_row, bg=card_bg)
            left_info.pack(side=tk.LEFT, fill=tk.X, expand=True)

            name_lbl = tk.Label(
                left_info, text=name, font=("Courier", 10, "bold"), fg="#ffffff", bg=card_bg, cursor="hand2"
            )
            name_lbl.pack(side=tk.LEFT)
            name_lbl.bind("<Button-1>", lambda e, n=name: self._copy_to_clipboard(n))

            type_color = {
                "boolean": "#38bdf8",
                "gen": "#c084fc",
                "number": "#facc15",
                "enum": "#34d399",
                "family": "#f472b6",
                "text": "#94a3b8",
            }.get(cfg["type"], "#94a3b8")

            type_badge = tk.Label(
                left_info,
                text=f" {cfg['type'].upper()} ",
                font=("Courier", 7, "bold"),
                fg=type_color,
                bg="#0f172a",
                padx=4,
                pady=1,
            )
            type_badge.pack(side=tk.LEFT, padx=8)

            if is_modified:
                mod_lbl = tk.Label(left_info, text=f"(Was: {orig_val})", font=("Courier", 8), fg=C_GOLD, bg=card_bg)
                mod_lbl.pack(side=tk.LEFT, padx=6)
                undo_btn = tk.Button(
                    left_info,
                    text="↺ Undo",
                    font=("DejaVu Sans", 7, "bold"),
                    bg="#334155",
                    fg="#f8fafc",
                    activebackground="#475569",
                    relief=tk.FLAT,
                    padx=6,
                    pady=1,
                    command=lambda n=name: self._undo_single_setting(n),
                )
                undo_btn.pack(side=tk.LEFT, padx=4)

            # Right side: Interactive Form Controls
            ctrl_box = tk.Frame(top_row, bg=card_bg)
            ctrl_box.pack(side=tk.RIGHT)

            self._build_card_control(ctrl_box, card_bg, cfg, val)

            # Documentation & Nuances Box
            if desc:
                desc_frame = tk.Frame(card, bg="#0f172a", padx=10, pady=8)
                desc_frame.pack(fill=tk.X, pady=(8, 0))

                desc_lbl = tk.Label(
                    desc_frame,
                    text=desc,
                    font=("DejaVu Sans", 8),
                    fg=C_TEXT_MUTED,
                    bg="#0f172a",
                    wraplength=760,
                    justify=tk.LEFT,
                )
                desc_lbl.pack(anchor="w")

                # Render Notice Tags
                if cfg["notices"]:
                    notice_row = tk.Frame(desc_frame, bg="#0f172a")
                    notice_row.pack(anchor="w", pady=(6, 0))
                    for n in cfg["notices"]:
                        n_color = C_RUBY if n["type"] == "danger" else (C_GOLD if n["type"] == "warning" else C_ACCENT)
                        n_tag = tk.Label(
                            notice_row,
                            text=f" ⚠ {n['text']} ",
                            font=("DejaVu Sans", 7, "bold"),
                            fg="#ffffff",
                            bg=n_color,
                            padx=6,
                            pady=2,
                        )
                        n_tag.pack(side=tk.LEFT, padx=(0, 6))

        if matched_count == 0:
            empty_frame = tk.Frame(self.scrollable_inner, bg=C_BG_BASE, pady=60)
            empty_frame.pack(fill=tk.BOTH, expand=True)
            tk.Label(empty_frame, text="🔍", font=("DejaVu Sans", 32), fg=C_TEXT_SUB, bg=C_BG_BASE).pack()
            tk.Label(
                empty_frame,
                text="No settings match your active search or filter",
                font=("DejaVu Sans", 11, "bold"),
                fg=C_TEXT_MAIN,
                bg=C_BG_BASE,
            ).pack(pady=4)
            tk.Label(
                empty_frame,
                text="Try clearing search or switching to 'All'",
                font=("DejaVu Sans", 9),
                fg=C_TEXT_MUTED,
                bg=C_BG_BASE,
            ).pack()

    def _build_card_control(self, parent, bg_color, cfg, current_val):
        name = cfg["name"]

        if cfg["type"] == "boolean":
            is_on = current_val == "TRUE"
            switch = SmoothToggleSwitch(
                parent,
                is_on=is_on,
                command=lambda state, n=name: self._on_value_change(n, "TRUE" if state else "FALSE"),
            )
            switch.pack(side=tk.RIGHT)
            val_lbl = tk.Label(
                parent,
                text="TRUE" if is_on else "FALSE",
                font=("Courier", 9, "bold"),
                fg=C_EMERALD if is_on else C_TEXT_SUB,
                bg=bg_color,
                width=6,
            )
            val_lbl.pack(side=tk.RIGHT, padx=6)
            # Link toggle to update label text
            old_cmd = switch.command
            switch.command = lambda state, l=val_lbl, oc=old_cmd: (
                l.config(text="TRUE" if state else "FALSE", fg=C_EMERALD if state else C_TEXT_SUB),
                oc(state),
            )

        elif cfg["type"] == "gen":
            box = ttk.Combobox(parent, values=GEN_CHOICES, width=13, state="readonly", style="TCombobox")
            box.set(current_val if current_val in GEN_CHOICES else "GEN_LATEST")
            box.pack(side=tk.RIGHT)
            box.bind("<<ComboboxSelected>>", lambda e, n=name, b=box: self._on_value_change(n, b.get()))

        elif cfg["type"] == "family":
            # Segmented 3-way toggle: Inherit | ON | OFF
            seg_frame = tk.Frame(parent, bg="#0f172a", padx=2, pady=2)
            seg_frame.pack(side=tk.RIGHT)

            is_inherit = (
                current_val.startswith("P_GEN_")
                or current_val.startswith("P_REGIONAL_")
                or current_val.startswith("P_PIKACHU_")
                or current_val.startswith("P_CROSS_")
            )
            is_true = current_val == "TRUE"
            is_false = current_val == "FALSE"
            orig_inherit = self.original_values.get(self.active_filename, {}).get(name, "P_GEN_1_POKEMON")

            btn_inh = tk.Button(
                seg_frame,
                text="Inherit",
                font=("DejaVu Sans", 7, "bold"),
                bg="#be185d" if is_inherit else "#1e293b",
                fg="#ffffff" if is_inherit else C_TEXT_MUTED,
                activebackground="#be185d",
                relief=tk.FLAT,
                padx=6,
                pady=2,
                command=lambda n=name, v=orig_inherit: self._on_value_change(n, v),
            )
            btn_inh.pack(side=tk.LEFT, padx=1)

            btn_on = tk.Button(
                seg_frame,
                text="ON",
                font=("DejaVu Sans", 7, "bold"),
                bg=C_EMERALD if is_true else "#1e293b",
                fg="#ffffff" if is_true else C_TEXT_MUTED,
                activebackground=C_EMERALD,
                relief=tk.FLAT,
                padx=6,
                pady=2,
                command=lambda n=name: self._on_value_change(n, "TRUE"),
            )
            btn_on.pack(side=tk.LEFT, padx=1)

            btn_off = tk.Button(
                seg_frame,
                text="OFF",
                font=("DejaVu Sans", 7, "bold"),
                bg=C_RUBY if is_false else "#1e293b",
                fg="#ffffff" if is_false else C_TEXT_MUTED,
                activebackground=C_RUBY,
                relief=tk.FLAT,
                padx=6,
                pady=2,
                command=lambda n=name: self._on_value_change(n, "FALSE"),
            )
            btn_off.pack(side=tk.LEFT, padx=1)

        elif cfg["type"] == "enum":
            opts = cfg.get("options", [current_val])
            box = ttk.Combobox(parent, values=opts, width=22, state="readonly", style="TCombobox")
            box.set(current_val)
            box.pack(side=tk.RIGHT)
            box.bind("<<ComboboxSelected>>", lambda e, n=name, b=box: self._on_value_change(n, b.get()))

        elif cfg["type"] == "number":
            # Stepper buttons [-10] [-1] [Value] [+1] [+10]
            num_val = int(current_val) if current_val.lstrip("-").isdigit() else 0
            stepper = tk.Frame(parent, bg=bg_color)
            stepper.pack(side=tk.RIGHT)

            btn_m10 = tk.Button(
                stepper,
                text="-10",
                font=("DejaVu Sans", 7, "bold"),
                bg="#334155",
                fg="#cbd5e1",
                relief=tk.FLAT,
                padx=4,
                pady=2,
                command=lambda n=name: self._step_number(n, -10),
            )
            btn_m10.pack(side=tk.LEFT, padx=1)
            btn_m1 = tk.Button(
                stepper,
                text="-1",
                font=("DejaVu Sans", 7, "bold"),
                bg="#334155",
                fg="#cbd5e1",
                relief=tk.FLAT,
                padx=4,
                pady=2,
                command=lambda n=name: self._step_number(n, -1),
            )
            btn_m1.pack(side=tk.LEFT, padx=1)

            entry = tk.Entry(
                stepper,
                width=6,
                bg=C_BG_INPUT,
                fg="#ffffff",
                font=("Courier", 9, "bold"),
                justify="center",
                insertbackground=C_ACCENT,
                relief=tk.FLAT,
                bd=2,
            )
            entry.insert(0, str(current_val))
            entry.pack(side=tk.LEFT, padx=3)
            entry.bind("<FocusOut>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))
            entry.bind("<Return>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))

            btn_p1 = tk.Button(
                stepper,
                text="+1",
                font=("DejaVu Sans", 7, "bold"),
                bg="#334155",
                fg="#cbd5e1",
                relief=tk.FLAT,
                padx=4,
                pady=2,
                command=lambda n=name: self._step_number(n, 1),
            )
            btn_p1.pack(side=tk.LEFT, padx=1)
            btn_p10 = tk.Button(
                stepper,
                text="+10",
                font=("DejaVu Sans", 7, "bold"),
                bg="#334155",
                fg="#cbd5e1",
                relief=tk.FLAT,
                padx=4,
                pady=2,
                command=lambda n=name: self._step_number(n, 10),
            )
            btn_p10.pack(side=tk.LEFT, padx=1)

        else:
            # Code / Text entry
            entry = tk.Entry(
                parent,
                width=18,
                bg=C_BG_INPUT,
                fg="#ffffff",
                font=("Courier", 9),
                insertbackground=C_ACCENT,
                relief=tk.FLAT,
                bd=4,
            )
            entry.insert(0, current_val)
            entry.pack(side=tk.RIGHT)
            entry.bind("<FocusOut>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))
            entry.bind("<Return>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))

    def _step_number(self, name, delta):
        cur = self.pending_updates.get(self.active_filename, {}).get(name)
        if cur is None:
            cur = self.original_values.get(self.active_filename, {}).get(name, "0")
        try:
            num = int(cur) + delta
            self._on_value_change(name, str(max(0, num)))
        except ValueError:
            pass

    def _on_value_change(self, name, new_val):
        new_val = str(new_val).strip()
        orig = self.original_values.get(self.active_filename, {}).get(name)

        if self.active_filename not in self.pending_updates:
            self.pending_updates[self.active_filename] = {}

        if new_val == orig:
            if name in self.pending_updates[self.active_filename]:
                del self.pending_updates[self.active_filename][name]
                if not self.pending_updates[self.active_filename]:
                    del self.pending_updates[self.active_filename]
        else:
            self.pending_updates[self.active_filename][name] = new_val

        self._update_pending_status()
        self._populate_file_tree()
        self._render_settings_list()

    def _undo_single_setting(self, name):
        if self.active_filename in self.pending_updates and name in self.pending_updates[self.active_filename]:
            del self.pending_updates[self.active_filename][name]
            if not self.pending_updates[self.active_filename]:
                del self.pending_updates[self.active_filename]
            self._update_pending_status()
            self._populate_file_tree()
            self._render_settings_list()

    def _update_pending_status(self):
        total = sum(len(v) for v in self.pending_updates.values())
        if total > 0:
            self.pending_badge.config(text=f"● {total} changes pending", fg=C_GOLD)
            self.btn_save.config(state=tk.NORMAL)
            self.btn_diff.config(state=tk.NORMAL)
            self.btn_discard.config(state=tk.NORMAL)
        else:
            self.pending_badge.config(text="● 0 changes pending", fg=C_TEXT_SUB)
            self.btn_save.config(state=tk.DISABLED)
            self.btn_diff.config(state=tk.DISABLED)
            self.btn_discard.config(state=tk.DISABLED)

    def _on_global_search(self):
        self._populate_file_tree()

    def _copy_to_clipboard(self, text):
        self.root.clipboard_clear()
        self.root.clipboard_append(text)
        messagebox.showinfo("Clipboard", f"Copied '{text}' to clipboard!")

    # PRESET & BATCH MANAGERS
    def _apply_preset(self, preset_key):
        p = PRESETS.get(preset_key)
        if not p:
            return
        if messagebox.askyesno("Apply Preset", f"Apply preset '{p['title']}'?\n\n{p['description']}"):
            for fname, updates in p["updates"].items():
                if fname not in self.pending_updates:
                    self.pending_updates[fname] = {}
                for k, v in updates.items():
                    self.pending_updates[fname][k] = v
            self._update_pending_status()
            self._populate_file_tree()
            self._load_file(self.active_filename)
            messagebox.showinfo(
                "Preset Applied",
                f"Preset '{p['title']}' loaded into pending changes.\nClick 'Review Diff' or 'Save Changes' to inspect and apply.",
            )

    def _batch_enable_all_species(self):
        if messagebox.askyesno(
            "Batch Enable",
            "Enable all Generations 1 through 9, Regional forms, and Mega evolutions in species_enabled.h?",
        ):
            fname = "species_enabled.h"
            if fname not in self.pending_updates:
                self.pending_updates[fname] = {}
            for g in range(1, 10):
                self.pending_updates[fname][f"P_GEN_{g}_POKEMON"] = "TRUE"
            self.pending_updates[fname]["P_REGIONAL_FORMS"] = "TRUE"
            self.pending_updates[fname]["P_MEGA_EVOLUTIONS"] = "TRUE"
            self.pending_updates[fname]["P_GIGANTAMAX_FORMS"] = "TRUE"
            self.pending_updates[fname]["P_TERA_FORMS"] = "TRUE"
            self._update_pending_status()
            self._populate_file_tree()
            if self.active_filename == fname:
                self._render_settings_list()
            messagebox.showinfo("Batch Updated", "All generation flags set to TRUE in species_enabled.h.")

    def _batch_set_battle_latest(self):
        if messagebox.askyesno("Batch Update", "Set all battle generational options in battle.h to GEN_LATEST?"):
            fname = "battle.h"
            if fname not in self.pending_updates:
                self.pending_updates[fname] = {}
            cfgs = self.engine.parse_file(fname)
            count = 0
            for c in cfgs:
                if c["type"] == "gen":
                    self.pending_updates[fname][c["name"]] = "GEN_LATEST"
                    count += 1
            self._update_pending_status()
            self._populate_file_tree()
            if self.active_filename == fname:
                self._render_settings_list()
            messagebox.showinfo("Batch Updated", f"Updated {count} battle rules to GEN_LATEST.")

    def _reset_current_file(self):
        if messagebox.askyesno("Reset File", f"Revert all pending changes in {self.active_filename}?"):
            if self.active_filename in self.pending_updates:
                del self.pending_updates[self.active_filename]
                self._update_pending_status()
                self._populate_file_tree()
                self._render_settings_list()

    def _discard_changes(self):
        if messagebox.askyesno("Discard All", "Discard ALL pending changes across all files?"):
            self.pending_updates.clear()
            self._update_pending_status()
            self._populate_file_tree()
            self._render_settings_list()

    # MODALS: DIFF PREVIEW, SAVE, BUILD
    def _show_diff_modal(self):
        diffs = self.engine.compute_diff(self.pending_updates)
        if not diffs:
            messagebox.showinfo("Diff", "No differences found.")
            return

        win = tk.Toplevel(self.root)
        win.title("Unified Diff Preview — Review Code Changes")
        win.geometry("900x600")
        win.configure(bg=C_BG_BASE)

        header = tk.Frame(win, bg="#0f172a", padx=16, pady=12)
        header.pack(fill=tk.X)
        tk.Label(header, text="Unified Code Diff", font=("DejaVu Sans", 11, "bold"), fg="#ffffff", bg="#0f172a").pack(
            side=tk.LEFT
        )
        tk.Label(header, text=f"{len(diffs)} file(s) modified", font=("DejaVu Sans", 9), fg=C_GOLD, bg="#0f172a").pack(
            side=tk.LEFT, padx=12
        )

        txt = scrolledtext.ScrolledText(win, bg="#030712", fg="#e2e8f0", font=("Courier", 9), padx=12, pady=12)
        txt.pack(fill=tk.BOTH, expand=True, padx=12, pady=8)

        # Syntax tags
        txt.tag_config("added", foreground="#34d399", background="#064e3b")
        txt.tag_config("removed", foreground="#f87171", background="#7f1d1d")
        txt.tag_config("header", foreground="#38bdf8", font=("Courier", 9, "bold"))

        for fname, d in diffs.items():
            txt.insert(tk.END, f"\n--- {fname} ({d['changed_count']} modifications) ---\n", "header")
            for line in d["diff"].splitlines():
                if line.startswith("+") and not line.startswith("+++"):
                    txt.insert(tk.END, line + "\n", "added")
                elif line.startswith("-") and not line.startswith("---"):
                    txt.insert(tk.END, line + "\n", "removed")
                elif line.startswith("@"):
                    txt.insert(tk.END, line + "\n", "header")
                else:
                    txt.insert(tk.END, line + "\n")

        txt.config(state=tk.DISABLED)

        foot = tk.Frame(win, bg=C_BG_BASE, padx=16, pady=12)
        foot.pack(fill=tk.X)
        ttk.Button(foot, text="Close", command=win.destroy).pack(side=tk.RIGHT, padx=6)
        ttk.Button(
            foot,
            text="Confirm & Save All Changes",
            style="Success.TButton",
            command=lambda: (win.destroy(), self._save_all_changes()),
        ).pack(side=tk.RIGHT, padx=6)

    def _save_all_changes(self):
        res = self.engine.save_changes(self.pending_updates)
        if res.get("success"):
            total_saved = sum(len(v) for v in self.pending_updates.values())
            self.pending_updates.clear()
            self.original_values.clear()
            self._update_pending_status()
            self._populate_file_tree()
            self._load_file(self.active_filename)
            messagebox.showinfo(
                "Success",
                f"Successfully saved {total_saved} configurations!\n\nBackup snapshot created in:\n{res['backup_folder']}",
            )
        else:
            messagebox.showerror("Error", f"Failed to save configurations: {res.get('error')}")

    def _show_build_modal(self):
        win = tk.Toplevel(self.root)
        win.title("Build Pokémon Confluence ROM")
        win.geometry("850x550")
        win.configure(bg=C_BG_BASE)

        header = tk.Frame(win, bg="#0f172a", padx=16, pady=12)
        header.pack(fill=tk.X)
        tk.Label(
            header,
            text="🔨 make -C pokeconfluence -j$(nproc)",
            font=("DejaVu Sans", 11, "bold"),
            fg="#ffffff",
            bg="#0f172a",
        ).pack(side=tk.LEFT)

        status_lbl = tk.Label(
            header, text="Compiling in background...", font=("DejaVu Sans", 9, "bold"), fg=C_ACCENT, bg="#0f172a"
        )
        status_lbl.pack(side=tk.RIGHT)

        txt = scrolledtext.ScrolledText(win, bg="#030712", fg="#e2e8f0", font=("Courier", 9), padx=10, pady=10)
        txt.pack(fill=tk.BOTH, expand=True, padx=12, pady=8)

        def run_make():
            cmd = ["make", "-C", str(ROM_DIR), f"-j{os.cpu_count() or 4}"]
            proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            for line in proc.stdout:
                txt.insert(tk.END, line)
                txt.see(tk.END)
            proc.wait()
            if proc.returncode == 0:
                status_lbl.config(text="✓ BUILD SUCCESSFUL", fg=C_EMERALD)
                txt.insert(
                    tk.END,
                    "\n============================================\n>>> ROM COMPILATION COMPLETE (pokeconfluence.gba) <<<\n============================================\n",
                )
            else:
                status_lbl.config(text="✕ BUILD FAILED", fg=C_RUBY)
                txt.insert(tk.END, f"\n>>> BUILD FAILED WITH EXIT CODE {proc.returncode} <<<\n")

        threading.Thread(target=run_make, daemon=True).start()

    def _add_placeholder(self, entry, text):
        entry.insert(0, text)
        entry.config(fg=C_TEXT_SUB)

        def on_focus_in(event):
            if entry.get() == text:
                entry.delete(0, tk.END)
                entry.config(fg=C_TEXT_MAIN)

        def on_focus_out(event):
            if not entry.get():
                entry.insert(0, text)
                entry.config(fg=C_TEXT_SUB)

        entry.bind("<FocusIn>", on_focus_in)
        entry.bind("<FocusOut>", on_focus_out)


def run_desktop():
    root = tk.Tk()
    app = ConfigStudioTkApp(root)
    root.mainloop()


if __name__ == "__main__":
    run_desktop()
