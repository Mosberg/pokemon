#!/usr/bin/env python3
"""
desktop_gui.py - World-class Native Desktop GUI for Pokémon Confluence Configuration Studio.
Crafted with high-contrast Obsidian dark styling, responsive 3-pane layout, live search,
interactive toggle switches, deep setting inspector, preset managers, diff inspector,
and integrated ROM build / test runners.
"""

import os
import subprocess
import sys
import threading
import tkinter as tk
from pathlib import Path
from tkinter import filedialog, messagebox, scrolledtext, ttk

# Ensure script dir in path
SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from config_engine import GEN_CHOICES, PRESETS, ConfigEngine

ROM_DIR = Path("/home/mosberg/wsl_projects/pokemon/pokeconfluence").resolve()

# OBSIDIAN PRO DARK PALETTE
C_BG_BASE = "#090d16"  # Deepest dark obsidian
C_BG_SIDEBAR = "#0f172a"  # Slate 900 panel background
C_BG_CARD = "#151f32"  # Card background
C_BG_CARD_HOVER = "#1c2b44"  # Card hover state
C_BG_CARD_ACTIVE = "#1e3a5f"  # Selected card state
C_BG_INPUT = "#0a1120"  # Dark input field background
C_BORDER = "#273549"  # Clean card border
C_BORDER_HI = "#38bdf8"  # Electric cyan focus border
C_TEXT_MAIN = "#f8fafc"  # Bright white/slate
C_TEXT_MUTED = "#94a3b8"  # Secondary gray
C_TEXT_SUB = "#64748b"  # Dim footnote gray
C_ACCENT = "#38bdf8"  # Electric sky blue
C_EMERALD = "#10b981"  # Success green
C_GOLD = "#f59e0b"  # Warning gold
C_RUBY = "#ef4444"  # Alert red
C_PURPLE = "#a855f7"  # Generational purple
C_BLUE = "#3b82f6"  # Interactive blue


class SmoothToggleSwitch(tk.Canvas):
    """Custom high-DPI Canvas Toggle Switch with rounded pill rendering."""

    def __init__(self, parent, is_on=False, command=None, width=46, height=22, bg=C_BG_CARD):
        super().__init__(parent, width=width, height=height, bg=bg, highlightthickness=0, cursor="hand2")
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
        bg_color = C_EMERALD if self.is_on else "#334155"
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
        self.root.title("Pokémon Confluence — Configuration Studio v2.5 PRO")
        self.root.geometry("1420x860")
        self.root.minsize(1050, 680)
        self.root.configure(bg=C_BG_BASE)

        self.engine = ConfigEngine()
        self.files = self.engine.list_files()
        self.active_filename = "caps.h"
        self.configs = []
        self.original_values = {}
        self.pending_updates = {}
        self.selected_setting_name = None
        self.card_widgets = {}
        self.current_filter = "all"
        self.current_sort = "file"
        self.canvas_window_id = None
        self.inspector_visible = True

        self._init_styles()
        self._build_header()
        self._build_body()
        self._setup_shortcuts()
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

        # Treeview styling with explicit high-contrast foreground
        self.style.configure(
            "Treeview",
            background=C_BG_SIDEBAR,
            fieldbackground=C_BG_SIDEBAR,
            foreground="#f8fafc",
            rowheight=32,
            font=("DejaVu Sans", 9),
            borderwidth=0,
        )
        self.style.map(
            "Treeview",
            background=[("selected", "#1e3a5f"), ("active", "#1e293b")],
            foreground=[("selected", "#38bdf8"), ("active", "#ffffff")],
        )
        self.style.configure(
            "Treeview.Heading",
            background="#1e293b",
            foreground="#cbd5e1",
            font=("DejaVu Sans", 8, "bold"),
            relief=tk.FLAT,
            padding=6,
        )
        self.style.map("Treeview.Heading", background=[("active", "#334155")])

        # Buttons
        self.style.configure(
            "TButton",
            background="#334155",
            foreground="#ffffff",
            padding=6,
            relief=tk.FLAT,
            font=("DejaVu Sans", 9, "bold"),
            borderwidth=0,
        )
        self.style.map(
            "TButton",
            background=[("active", "#475569"), ("disabled", "#1e293b")],
            foreground=[("disabled", "#64748b")],
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
            padding=4,
            relief=tk.FLAT,
            borderwidth=1,
            bordercolor=C_BORDER,
        )
        self.style.map(
            "TCombobox",
            fieldbackground=[("readonly", C_BG_INPUT)],
            selectbackground=[("readonly", "#1e40af")],
            selectforeground=[("readonly", "#ffffff")],
        )

        # Scrollbar
        self.style.configure(
            "Vertical.TScrollbar",
            background="#334155",
            troughcolor=C_BG_BASE,
            relief=tk.FLAT,
            borderwidth=0,
            arrowsize=11,
        )
        self.style.map("Vertical.TScrollbar", background=[("active", "#475569")])

    def _setup_shortcuts(self):
        self.root.bind("<Control-s>", lambda e: self._save_all_changes())
        self.root.bind("<Control-d>", lambda e: self._show_diff_modal())
        self.root.bind("<Control-b>", lambda e: self._show_build_modal())
        self.root.bind("<Control-t>", lambda e: self._show_test_modal())

    def _build_header(self):
        self.header_bar = tk.Frame(self.root, bg=C_BG_SIDEBAR, height=58, padx=16, pady=9)
        self.header_bar.pack(side=tk.TOP, fill=tk.X)

        # Logo / Brand
        brand_frame = tk.Frame(self.header_bar, bg=C_BG_SIDEBAR)
        brand_frame.pack(side=tk.LEFT)

        logo_lbl = tk.Label(
            brand_frame,
            text="⚡ Confluence Config Studio",
            font=("DejaVu Sans", 12, "bold"),
            fg=C_ACCENT,
            bg=C_BG_SIDEBAR,
            cursor="hand2",
        )
        logo_lbl.pack(side=tk.LEFT)
        logo_lbl.bind("<Button-1>", lambda e: self._select_setting(None))

        badge_lbl = tk.Label(
            brand_frame,
            text="v2.5 PRO",
            font=("DejaVu Sans", 7, "bold"),
            fg="#ffffff",
            bg="#8b5cf6",
            padx=6,
            pady=2,
        )
        badge_lbl.pack(side=tk.LEFT, padx=8)

        # Pending Changes Indicator
        self.pending_badge = tk.Label(
            self.header_bar,
            text="● 0 changes pending",
            font=("DejaVu Sans", 9, "bold"),
            fg=C_TEXT_SUB,
            bg=C_BG_SIDEBAR,
        )
        self.pending_badge.pack(side=tk.LEFT, padx=14)

        # Right Action Buttons
        actions_frame = tk.Frame(self.header_bar, bg=C_BG_SIDEBAR)
        actions_frame.pack(side=tk.RIGHT)

        # Presets Menu Button
        self.preset_btn = tk.Menubutton(
            actions_frame,
            text="⚡ Presets ▾",
            font=("DejaVu Sans", 9, "bold"),
            bg="#1e293b",
            fg="#f8fafc",
            activebackground="#334155",
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
            relief=tk.FLAT,
        )
        for key, p in PRESETS.items():
            self.preset_menu.add_command(label=f"{p['icon']} {p['title']}", command=lambda k=key: self._apply_preset(k))
        self.preset_btn.config(menu=self.preset_menu)
        self.preset_btn.pack(side=tk.LEFT, padx=3)

        # Batch Tools Menu Button
        self.batch_btn = tk.Menubutton(
            actions_frame,
            text="⚙ Batch Tools ▾",
            font=("DejaVu Sans", 9, "bold"),
            bg="#1e293b",
            fg="#f8fafc",
            activebackground="#334155",
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
            relief=tk.FLAT,
        )
        self.batch_menu.add_command(
            label="✓ Enable All Generations 1-9 in species_enabled.h", command=self._batch_enable_all_species
        )
        self.batch_menu.add_command(
            label="✓ Set All Battle Rules in battle.h to GEN_LATEST", command=self._batch_set_battle_latest
        )
        self.batch_menu.add_command(
            label="✓ Enable All Overworld & Battle Debug Menus", command=self._batch_enable_debug_menus
        )
        self.batch_menu.add_separator()
        self.batch_menu.add_command(label="↺ Reset Active File to Original Defaults", command=self._reset_current_file)
        self.batch_menu.add_command(label="✕ Discard All Pending Changes", command=self._discard_changes)
        self.batch_btn.config(menu=self.batch_menu)
        self.batch_btn.pack(side=tk.LEFT, padx=3)

        # Profile Export/Import Menu Button
        self.profile_btn = tk.Menubutton(
            actions_frame,
            text="📁 Profile ▾",
            font=("DejaVu Sans", 9, "bold"),
            bg="#1e293b",
            fg="#f8fafc",
            activebackground="#334155",
            activeforeground="#ffffff",
            relief=tk.FLAT,
            padx=10,
            pady=5,
        )
        self.profile_menu = tk.Menu(
            self.profile_btn,
            tearoff=0,
            bg=C_BG_CARD,
            fg=C_TEXT_MAIN,
            activebackground="#1e40af",
            activeforeground="#ffffff",
            relief=tk.FLAT,
        )
        self.profile_menu.add_command(label="💾 Export Configuration Profile (.json)...", command=self._export_profile)
        self.profile_menu.add_command(label="📂 Import Configuration Profile (.json)...", command=self._import_profile)
        self.profile_btn.config(menu=self.profile_menu)
        self.profile_btn.pack(side=tk.LEFT, padx=3)

        # Discard Button
        self.btn_discard = ttk.Button(
            actions_frame, text="↺ Discard", style="Danger.TButton", state=tk.DISABLED, command=self._discard_changes
        )
        self.btn_discard.pack(side=tk.LEFT, padx=3)

        # Diff Preview Button
        self.btn_diff = ttk.Button(
            actions_frame, text="👁 Diff Preview", style="TButton", state=tk.DISABLED, command=self._show_diff_modal
        )
        self.btn_diff.pack(side=tk.LEFT, padx=3)

        # Save All Button
        self.btn_save = ttk.Button(
            actions_frame,
            text="💾 Save Changes",
            style="Success.TButton",
            state=tk.DISABLED,
            command=self._save_all_changes,
        )
        self.btn_save.pack(side=tk.LEFT, padx=3)

        # Build ROM Button
        self.btn_build = ttk.Button(
            actions_frame, text="🔨 Build ROM", style="Accent.TButton", command=self._show_build_modal
        )
        self.btn_build.pack(side=tk.LEFT, padx=3)

        # Web Studio Button
        self.btn_web = tk.Button(
            actions_frame,
            text="🌐 Web Studio",
            font=("DejaVu Sans", 8, "bold"),
            bg="#312e81",
            fg="#c7d2fe",
            activebackground="#4338ca",
            activeforeground="#ffffff",
            relief=tk.FLAT,
            padx=8,
            pady=5,
            command=self._open_web_studio,
        )
        self.btn_web.pack(side=tk.LEFT, padx=3)

    def _build_body(self):
        self.paned = tk.PanedWindow(self.root, orient=tk.HORIZONTAL, bg=C_BORDER, sashwidth=5, bd=0)
        self.paned.pack(fill=tk.BOTH, expand=True)

        # ==================== PANE 1: LEFT SIDEBAR (File Explorer) ====================
        self.sidebar = tk.Frame(self.paned, bg=C_BG_SIDEBAR, width=290)
        self.paned.add(self.sidebar, minsize=240)

        # Global Search
        search_box_frame = tk.Frame(self.sidebar, bg=C_BG_SIDEBAR, padx=10, pady=8)
        search_box_frame.pack(fill=tk.X)

        search_row = tk.Frame(search_box_frame, bg=C_BG_INPUT, bd=1, relief=tk.SOLID)
        search_row.config(highlightbackground=C_BORDER, highlightthickness=1)
        search_row.pack(fill=tk.X)

        tk.Label(search_row, text="🔍", font=("DejaVu Sans", 9), fg=C_TEXT_SUB, bg=C_BG_INPUT).pack(
            side=tk.LEFT, padx=6
        )

        self.global_search_var = tk.StringVar()
        self.global_search_var.trace_add("write", lambda *args: self._on_global_search())
        self.search_entry = tk.Entry(
            search_row,
            textvariable=self.global_search_var,
            bg=C_BG_INPUT,
            fg=C_TEXT_MAIN,
            insertbackground=C_ACCENT,
            relief=tk.FLAT,
            font=("DejaVu Sans", 9),
            bd=3,
        )
        self.search_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)
        self._add_placeholder(self.search_entry, "Search 2,040+ settings...")

        # Treeview for 23 config files
        tree_container = tk.Frame(self.sidebar, bg=C_BG_SIDEBAR)
        tree_container.pack(fill=tk.BOTH, expand=True, padx=6, pady=2)

        self.file_tree = ttk.Treeview(tree_container, columns=("count",), show="tree headings", selectmode="browse")
        self.file_tree.heading("#0", text="  Configuration Categories & Files", anchor="w")
        self.file_tree.heading("count", text="Opts", anchor="center")
        self.file_tree.column("#0", width=205, anchor="w")
        self.file_tree.column("count", width=45, anchor="center")

        # Explicit tag colors to prevent invisible black text in clam theme
        self.file_tree.tag_configure(
            "cat_tag", foreground="#38bdf8", background="#152033", font=("DejaVu Sans", 9, "bold")
        )
        self.file_tree.tag_configure("file_clean", foreground="#f8fafc", background="#0f172a")
        self.file_tree.tag_configure(
            "file_dirty", foreground="#fbbf24", background="#1e293b", font=("DejaVu Sans", 9, "bold")
        )

        tree_scroll = ttk.Scrollbar(
            tree_container, orient=tk.VERTICAL, command=self.file_tree.yview, style="Vertical.TScrollbar"
        )
        self.file_tree.configure(yscrollcommand=tree_scroll.set)

        self.file_tree.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        tree_scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.file_tree.bind("<<TreeviewSelect>>", self._on_tree_select)

        self._populate_file_tree()

        # Sidebar footer
        sb_foot = tk.Frame(self.sidebar, bg="#0b1220", padx=10, pady=7)
        sb_foot.pack(fill=tk.X, side=tk.BOTTOM)
        tk.Label(
            sb_foot,
            text="23 C Header Files | pokeconfluence",
            font=("DejaVu Sans", 8),
            fg=C_TEXT_SUB,
            bg="#0b1220",
        ).pack(side=tk.LEFT)

        # ==================== PANE 2: CENTER PANEL (Settings Stream) ====================
        self.main_panel = tk.Frame(self.paned, bg=C_BG_BASE)
        self.paned.add(self.main_panel, minsize=520)

        # File Banner Header
        self.file_banner = tk.Frame(self.main_panel, bg="#0f172a", padx=18, pady=10, bd=1, relief=tk.FLAT)
        self.file_banner.pack(fill=tk.X)

        title_row = tk.Frame(self.file_banner, bg="#0f172a")
        title_row.pack(fill=tk.X)

        self.active_file_title_lbl = tk.Label(
            title_row, text="", font=("DejaVu Sans", 12, "bold"), fg="#ffffff", bg="#0f172a"
        )
        self.active_file_title_lbl.pack(side=tk.LEFT)

        self.active_file_tag_lbl = tk.Label(
            title_row, text="", font=("Courier", 8, "bold"), fg=C_ACCENT, bg="#1e293b", padx=7, pady=2
        )
        self.active_file_tag_lbl.pack(side=tk.LEFT, padx=8)

        # Toggle Inspector Button on file banner
        self.btn_toggle_inspector = tk.Button(
            title_row,
            text="Inspector ❯",
            font=("DejaVu Sans", 8, "bold"),
            bg="#1e293b",
            fg=C_TEXT_MUTED,
            activebackground="#334155",
            activeforeground="#ffffff",
            relief=tk.FLAT,
            padx=8,
            pady=2,
            command=self._toggle_inspector,
        )
        self.btn_toggle_inspector.pack(side=tk.RIGHT)

        self.active_file_desc_lbl = tk.Label(
            self.file_banner,
            text="",
            font=("DejaVu Sans", 8),
            fg=C_TEXT_MUTED,
            bg="#0f172a",
            wraplength=680,
            justify=tk.LEFT,
        )
        self.active_file_desc_lbl.pack(anchor="w", pady=(3, 0))

        # Filter Chips Toolbar
        filter_toolbar = tk.Frame(self.main_panel, bg="#121a2c", padx=14, pady=6)
        filter_toolbar.pack(fill=tk.X)

        filter_lbl = tk.Label(
            filter_toolbar, text="FILTER:", font=("DejaVu Sans", 7, "bold"), fg=C_TEXT_SUB, bg="#121a2c"
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
                activeforeground="#0f172a",
                relief=tk.FLAT,
                padx=7,
                pady=2,
                command=lambda k=fkey: self._set_filter(k),
            )
            btn.pack(side=tk.LEFT, padx=2)
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
            width=20,
            bd=3,
        )
        file_search_entry.pack(side=tk.RIGHT)
        self._add_placeholder(file_search_entry, "Filter active file...")

        # Responsive Scrollable Canvas for Settings Cards
        canvas_container = tk.Frame(self.main_panel, bg=C_BG_BASE)
        canvas_container.pack(fill=tk.BOTH, expand=True, padx=8, pady=6)

        self.canvas = tk.Canvas(canvas_container, bg=C_BG_BASE, highlightthickness=0)
        self.scrollbar = ttk.Scrollbar(
            canvas_container, orient=tk.VERTICAL, command=self.canvas.yview, style="Vertical.TScrollbar"
        )
        self.scrollable_inner = tk.Frame(self.canvas, bg=C_BG_BASE)

        self.canvas_window_id = self.canvas.create_window((0, 0), window=self.scrollable_inner, anchor="nw")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)

        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        # STRETCH INNER FRAME TO 100% CANVAS WIDTH (Permanently resolves right-side void!)
        self.canvas.bind("<Configure>", self._on_canvas_configure)
        self.scrollable_inner.bind("<Configure>", lambda e: self.canvas.configure(scrollregion=self.canvas.bbox("all")))
        self.canvas.bind_all("<MouseWheel>", self._on_mousewheel)

        # ==================== PANE 3: RIGHT PANEL (Setting Inspector & Companion) ====================
        self.inspector_panel = tk.Frame(self.paned, bg=C_BG_SIDEBAR, width=360)
        self.paned.add(self.inspector_panel, minsize=290)
        self._build_inspector()

    def _on_canvas_configure(self, event):
        # Dynamically set width of inner frame to match canvas viewport
        self.canvas.itemconfig(self.canvas_window_id, width=event.width)

    def _on_mousewheel(self, event):
        if event.num == 4 or event.delta > 0:
            self.canvas.yview_scroll(-2, "units")
        elif event.num == 5 or event.delta < 0:
            self.canvas.yview_scroll(2, "units")

    def _toggle_inspector(self):
        if self.inspector_visible:
            self.paned.remove(self.inspector_panel)
            self.btn_toggle_inspector.config(text="❮ Inspector")
            self.inspector_visible = False
        else:
            self.paned.add(self.inspector_panel, minsize=290)
            self.btn_toggle_inspector.config(text="Inspector ❯")
            self.inspector_visible = True

    # ==================== INSPECTOR PANEL LOGIC ====================
    def _build_inspector(self):
        # Header
        insp_header = tk.Frame(self.inspector_panel, bg="#111c30", padx=14, pady=10)
        insp_header.pack(fill=tk.X)

        self.insp_title_lbl = tk.Label(
            insp_header, text="🔍 Setting Inspector", font=("DejaVu Sans", 10, "bold"), fg=C_ACCENT, bg="#111c30"
        )
        self.insp_title_lbl.pack(side=tk.LEFT)

        # Scrollable inspector body
        insp_scroll_frame = tk.Frame(self.inspector_panel, bg=C_BG_SIDEBAR)
        insp_scroll_frame.pack(fill=tk.BOTH, expand=True, padx=12, pady=10)

        self.insp_canvas = tk.Canvas(insp_scroll_frame, bg=C_BG_SIDEBAR, highlightthickness=0)
        self.insp_scrollbar = ttk.Scrollbar(
            insp_scroll_frame, orient=tk.VERTICAL, command=self.insp_canvas.yview, style="Vertical.TScrollbar"
        )
        self.insp_inner = tk.Frame(self.insp_canvas, bg=C_BG_SIDEBAR)
        self.insp_window_id = self.insp_canvas.create_window((0, 0), window=self.insp_inner, anchor="nw")
        self.insp_canvas.configure(yscrollcommand=self.insp_scrollbar.set)

        self.insp_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.insp_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        self.insp_canvas.bind("<Configure>", lambda e: self.insp_canvas.itemconfig(self.insp_window_id, width=e.width))
        self.insp_inner.bind(
            "<Configure>", lambda e: self.insp_canvas.configure(scrollregion=self.insp_canvas.bbox("all"))
        )

        self._render_inspector_content()

    def _select_setting(self, setting_name):
        self.selected_setting_name = setting_name
        self._render_inspector_content()
        # Highlight card
        for name, widget in self.card_widgets.items():
            if name == setting_name:
                widget.config(highlightbackground=C_BORDER_HI, highlightthickness=2)
            else:
                is_mod = (
                    self.active_filename in self.pending_updates and name in self.pending_updates[self.active_filename]
                )
                border_col = C_GOLD if is_mod else C_BORDER
                widget.config(highlightbackground=border_col, highlightthickness=1)

    def _render_inspector_content(self):
        for w in self.insp_inner.winfo_children():
            w.destroy()

        if not self.selected_setting_name:
            # Show Studio Project Dashboard
            self.insp_title_lbl.config(text="📊 Project Status & Tools")

            # Stats Card
            stats_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
            stats_card.config(highlightbackground=C_BORDER, highlightthickness=1)
            stats_card.pack(fill=tk.X, pady=(0, 10))

            tk.Label(
                stats_card, text="CONFLUENCE ENGINE", font=("DejaVu Sans", 8, "bold"), fg=C_ACCENT, bg=C_BG_CARD
            ).pack(anchor="w")
            tk.Label(
                stats_card, text="23 C Header Files", font=("DejaVu Sans", 11, "bold"), fg="#ffffff", bg=C_BG_CARD
            ).pack(anchor="w", pady=(2, 0))
            tk.Label(
                stats_card,
                text="2,040+ Total Configuration Defines",
                font=("DejaVu Sans", 8),
                fg=C_TEXT_MUTED,
                bg=C_BG_CARD,
            ).pack(anchor="w")

            total_pending = sum(len(v) for v in self.pending_updates.values())
            pending_text = f"{total_pending} Pending Change(s)" if total_pending else "Clean / In Sync"
            pending_color = C_GOLD if total_pending else C_EMERALD
            tk.Label(
                stats_card,
                text=f"Status: {pending_text}",
                font=("DejaVu Sans", 9, "bold"),
                fg=pending_color,
                bg=C_BG_CARD,
            ).pack(anchor="w", pady=(6, 0))

            # Quick Presets
            presets_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
            presets_card.config(highlightbackground=C_BORDER, highlightthickness=1)
            presets_card.pack(fill=tk.X, pady=6)

            tk.Label(
                presets_card, text="QUICK PRESETS", font=("DejaVu Sans", 8, "bold"), fg=C_ACCENT, bg=C_BG_CARD
            ).pack(anchor="w", pady=(0, 6))
            for pkey, p in PRESETS.items():
                p_btn = tk.Button(
                    presets_card,
                    text=f"{p['icon']}  {p['title']}",
                    font=("DejaVu Sans", 8),
                    bg="#1e293b",
                    fg="#f8fafc",
                    activebackground="#334155",
                    activeforeground="#ffffff",
                    relief=tk.FLAT,
                    padx=8,
                    pady=5,
                    anchor="w",
                    command=lambda k=pkey: self._apply_preset(k),
                )
                p_btn.pack(fill=tk.X, pady=2)

            # Verification Hub
            tools_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
            tools_card.config(highlightbackground=C_BORDER, highlightthickness=1)
            tools_card.pack(fill=tk.X, pady=6)

            tk.Label(
                tools_card, text="DEVELOPER ACTIONS", font=("DejaVu Sans", 8, "bold"), fg=C_ACCENT, bg=C_BG_CARD
            ).pack(anchor="w", pady=(0, 6))

            ttk.Button(
                tools_card, text="🔨 Build ROM (make -j)", style="Accent.TButton", command=self._show_build_modal
            ).pack(fill=tk.X, pady=2)
            ttk.Button(
                tools_card, text="🧪 Run C Unit Tests (test.sh)", style="TButton", command=self._show_test_modal
            ).pack(fill=tk.X, pady=2)
            ttk.Button(
                tools_card, text="📊 Engine Limits Audit", style="TButton", command=self._show_limits_modal
            ).pack(fill=tk.X, pady=2)
            ttk.Button(tools_card, text="🌐 Launch Web Studio", style="TButton", command=self._open_web_studio).pack(
                fill=tk.X, pady=2
            )

            hint_lbl = tk.Label(
                self.insp_inner,
                text="💡 Tip: Click on any configuration card in the center list to view detailed engine documentation, C code impact, and preset values.",
                font=("DejaVu Sans", 8),
                fg=C_TEXT_SUB,
                bg=C_BG_SIDEBAR,
                wraplength=310,
                justify=tk.LEFT,
            )
            hint_lbl.pack(fill=tk.X, pady=14)
            return

        # Setting Details Mode
        self.insp_title_lbl.config(text="🔍 Setting Inspector")
        details = self.engine.get_setting_details(self.active_filename, self.selected_setting_name)
        if not details:
            return

        cfg = details["config"]
        name = cfg["name"]
        cur_val = self.pending_updates.get(self.active_filename, {}).get(name, cfg["value"])
        orig_val = self.original_values.get(self.active_filename, {}).get(name, cfg["value"])
        is_modified = cur_val != orig_val

        # Card 1: Identification
        id_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
        id_card.config(highlightbackground=C_BORDER, highlightthickness=1)
        id_card.pack(fill=tk.X, pady=(0, 8))

        tk.Label(id_card, text="DEFINE NAME", font=("DejaVu Sans", 7, "bold"), fg=C_TEXT_SUB, bg=C_BG_CARD).pack(
            anchor="w"
        )
        name_lbl = tk.Label(
            id_card,
            text=name,
            font=("Courier", 10, "bold"),
            fg="#ffffff",
            bg=C_BG_CARD,
            wraplength=310,
            justify=tk.LEFT,
        )
        name_lbl.pack(anchor="w", pady=(2, 4))

        meta_row = tk.Frame(id_card, bg=C_BG_CARD)
        meta_row.pack(fill=tk.X, pady=2)
        tk.Label(
            meta_row, text=f"File: {self.active_filename}:{cfg['line']}", font=("Courier", 8), fg=C_ACCENT, bg=C_BG_CARD
        ).pack(side=tk.LEFT)
        tk.Label(
            meta_row,
            text=f"Type: {cfg['type'].upper()}",
            font=("DejaVu Sans", 7, "bold"),
            fg=C_EMERALD,
            bg="#0f172a",
            padx=5,
            pady=1,
        ).pack(side=tk.RIGHT)

        # Action Buttons
        btn_row = tk.Frame(id_card, bg=C_BG_CARD)
        btn_row.pack(fill=tk.X, pady=(8, 0))
        tk.Button(
            btn_row,
            text="📋 Copy Macro",
            font=("DejaVu Sans", 7, "bold"),
            bg="#1e293b",
            fg=C_TEXT_MAIN,
            activebackground="#334155",
            relief=tk.FLAT,
            padx=6,
            pady=3,
            command=lambda: self._copy_to_clipboard(name),
        ).pack(side=tk.LEFT, padx=(0, 4))

        tk.Button(
            btn_row,
            text="📋 Copy #define",
            font=("DejaVu Sans", 7, "bold"),
            bg="#1e293b",
            fg=C_TEXT_MAIN,
            activebackground="#334155",
            relief=tk.FLAT,
            padx=6,
            pady=3,
            command=lambda: self._copy_to_clipboard(f"#define {name} {cur_val}"),
        ).pack(side=tk.LEFT)

        # Card 2: Current Value & Diff
        val_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
        val_card.config(highlightbackground=C_BORDER, highlightthickness=1)
        val_card.pack(fill=tk.X, pady=6)

        tk.Label(
            val_card, text="CURRENT CONFIGURATION", font=("DejaVu Sans", 7, "bold"), fg=C_TEXT_SUB, bg=C_BG_CARD
        ).pack(anchor="w")

        val_display_row = tk.Frame(val_card, bg=C_BG_CARD)
        val_display_row.pack(fill=tk.X, pady=(4, 0))
        val_color = C_GOLD if is_modified else C_EMERALD
        tk.Label(val_display_row, text=cur_val, font=("Courier", 11, "bold"), fg=val_color, bg=C_BG_CARD).pack(
            side=tk.LEFT
        )

        if is_modified:
            tk.Label(
                val_display_row, text=f"(Original: {orig_val})", font=("Courier", 8), fg=C_TEXT_SUB, bg=C_BG_CARD
            ).pack(side=tk.LEFT, padx=6)
            tk.Button(
                val_card,
                text="↺ Revert to Default Value",
                font=("DejaVu Sans", 7, "bold"),
                bg="#334155",
                fg="#f8fafc",
                activebackground="#475569",
                relief=tk.FLAT,
                padx=8,
                pady=3,
                command=lambda: self._undo_single_setting(name),
            ).pack(anchor="w", pady=(8, 0))

        # Card 3: Deep Technical Impact
        doc_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
        doc_card.config(highlightbackground=C_BORDER, highlightthickness=1)
        doc_card.pack(fill=tk.X, pady=6)

        tk.Label(
            doc_card, text="ENGINE IMPACT & DOCUMENTATION", font=("DejaVu Sans", 7, "bold"), fg=C_ACCENT, bg=C_BG_CARD
        ).pack(anchor="w")
        doc_body = cfg["description"] or "Standard pokeemerald-expansion configuration macro."
        tk.Label(
            doc_card,
            text=doc_body,
            font=("DejaVu Sans", 8),
            fg=C_TEXT_MUTED,
            bg=C_BG_CARD,
            wraplength=310,
            justify=tk.LEFT,
        ).pack(anchor="w", pady=(4, 6))

        if details.get("tech_note"):
            tk.Label(
                doc_card, text="💡 Technical Nuance:", font=("DejaVu Sans", 7, "bold"), fg=C_GOLD, bg=C_BG_CARD
            ).pack(anchor="w")
            tk.Label(
                doc_card,
                text=details["tech_note"],
                font=("DejaVu Sans", 8),
                fg="#cbd5e1",
                bg=C_BG_CARD,
                wraplength=310,
                justify=tk.LEFT,
            ).pack(anchor="w", pady=(2, 0))

        # Card 4: Presets Comparison Matrix
        preset_card = tk.Frame(self.insp_inner, bg=C_BG_CARD, padx=12, pady=12, bd=1, relief=tk.SOLID)
        preset_card.config(highlightbackground=C_BORDER, highlightthickness=1)
        preset_card.pack(fill=tk.X, pady=6)

        tk.Label(
            preset_card, text="PRESET VALUES MATRIX", font=("DejaVu Sans", 7, "bold"), fg=C_PURPLE, bg=C_BG_CARD
        ).pack(anchor="w", pady=(0, 6))
        for pkey, pinfo in details["presets"].items():
            p_row = tk.Frame(preset_card, bg="#0f172a", padx=8, pady=4)
            p_row.pack(fill=tk.X, pady=2)
            tk.Label(
                p_row,
                text=f"{pinfo['icon']} {pinfo['title'][:20]}...",
                font=("DejaVu Sans", 7),
                fg=C_TEXT_MUTED,
                bg="#0f172a",
            ).pack(side=tk.LEFT)
            tk.Label(p_row, text=pinfo["value"], font=("Courier", 8, "bold"), fg=C_ACCENT, bg="#0f172a").pack(
                side=tk.RIGHT
            )

    # ==================== FILE TREEVIEW LOGIC ====================
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
                self.file_tree.insert("", tk.END, iid=cat_id, text=f"📂 {cat}", open=True, tags=("cat_tag",))
                for f in filtered_files:
                    fname = f["filename"]
                    is_dirty = fname in self.pending_updates and len(self.pending_updates[fname]) > 0
                    dirty_marker = " ●" if is_dirty else ""
                    tag = "file_dirty" if is_dirty else "file_clean"
                    self.file_tree.insert(
                        cat_id,
                        tk.END,
                        iid=fname,
                        text=f"  {f['glyph']} {f['filename']}{dirty_marker}",
                        values=(f["config_count"],),
                        tags=(tag,),
                    )

    def _on_tree_select(self, event):
        selected = self.file_tree.selection()
        if selected:
            sel_id = selected[0]
            if sel_id.endswith(".h"):
                self._load_file(sel_id)

    def _load_file(self, filename):
        self.active_filename = filename
        self.selected_setting_name = None
        fmeta = next((f for f in self.files if f["filename"] == filename), None)
        if fmeta:
            self.active_file_title_lbl.config(text=f"{fmeta['glyph']} {fmeta['title']}")
            self.active_file_tag_lbl.config(text=filename)
            self.active_file_desc_lbl.config(text=fmeta["description"])

        self.configs = self.engine.parse_file(filename)
        if filename not in self.original_values:
            self.original_values[filename] = {c["name"]: c["value"] for c in self.configs}

        self._render_settings_list()
        self._render_inspector_content()

    def _set_filter(self, filter_key):
        self.current_filter = filter_key
        for k, btn in self.filter_buttons.items():
            if k == filter_key:
                btn.config(bg=C_ACCENT, fg="#0f172a")
            else:
                btn.config(bg="#1e293b", fg=C_TEXT_MUTED)
        self._render_settings_list()

    # ==================== SETTINGS CARDS RENDERING ====================
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

            # Apply search & type filters
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
                sec_bar.pack(fill=tk.X, pady=(12, 4))
                tk.Label(
                    sec_bar,
                    text=f"📁  {last_section.upper()}",
                    font=("DejaVu Sans", 8, "bold"),
                    fg="#38bdf8",
                    bg="#0d1527",
                ).pack(anchor="w")

            # Render Setting Card (100% full width responsive card)
            is_selected = name == self.selected_setting_name
            card_border = C_BORDER_HI if is_selected else (C_GOLD if is_modified else C_BORDER)
            card_bg = C_BG_CARD_ACTIVE if is_selected else ("#192538" if is_modified else C_BG_CARD)

            card = tk.Frame(self.scrollable_inner, bg=card_bg, bd=1, relief=tk.SOLID, padx=14, pady=10)
            card.pack(fill=tk.X, pady=3)
            card.config(highlightbackground=card_border, highlightthickness=2 if is_selected else 1)
            self.card_widgets[name] = card

            # Card Header: Name, Badges & Interactive Control
            top_row = tk.Frame(card, bg=card_bg)
            top_row.pack(fill=tk.X)

            # Left side: Name & Badges
            left_info = tk.Frame(top_row, bg=card_bg)
            left_info.pack(side=tk.LEFT, fill=tk.X, expand=True)

            name_lbl = tk.Label(
                left_info,
                text=name,
                font=("Courier", 10, "bold"),
                fg="#ffffff",
                bg=card_bg,
                cursor="hand2",
            )
            name_lbl.pack(side=tk.LEFT)
            name_lbl.bind("<Button-1>", lambda e, n=name: self._select_setting(n))

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
                bg="#0b1220",
                padx=4,
                pady=1,
            )
            type_badge.pack(side=tk.LEFT, padx=7)

            if is_modified:
                mod_lbl = tk.Label(left_info, text=f"(Was: {orig_val})", font=("Courier", 8), fg=C_GOLD, bg=card_bg)
                mod_lbl.pack(side=tk.LEFT, padx=5)
                undo_btn = tk.Button(
                    left_info,
                    text="↺ Revert",
                    font=("DejaVu Sans", 7, "bold"),
                    bg="#334155",
                    fg="#f8fafc",
                    activebackground="#475569",
                    relief=tk.FLAT,
                    padx=6,
                    pady=1,
                    command=lambda n=name: self._undo_single_setting(n),
                )
                undo_btn.pack(side=tk.LEFT, padx=3)

            # Right side: Interactive Form Controls (NO WHITE BOXES!)
            ctrl_box = tk.Frame(top_row, bg=card_bg)
            ctrl_box.pack(side=tk.RIGHT)

            self._build_card_control(ctrl_box, card_bg, cfg, val)

            # Card Body: Description
            if desc:
                desc_frame = tk.Frame(card, bg="#0d1424", padx=10, pady=7)
                desc_frame.pack(fill=tk.X, pady=(7, 0))

                desc_lbl = tk.Label(
                    desc_frame,
                    text=desc,
                    font=("DejaVu Sans", 8),
                    fg=C_TEXT_MUTED,
                    bg="#0d1424",
                    wraplength=640,
                    justify=tk.LEFT,
                    cursor="hand2",
                )
                desc_lbl.pack(anchor="w")
                desc_lbl.bind("<Button-1>", lambda e, n=name: self._select_setting(n))

                # Render Notice Badges
                if cfg["notices"]:
                    notice_row = tk.Frame(desc_frame, bg="#0d1424")
                    notice_row.pack(anchor="w", pady=(5, 0))
                    for n in cfg["notices"]:
                        n_color = C_RUBY if n["type"] == "danger" else (C_GOLD if n["type"] == "warning" else C_ACCENT)
                        n_tag = tk.Label(
                            notice_row,
                            text=f" ⚠ {n['text']} ",
                            font=("DejaVu Sans", 7, "bold"),
                            fg="#ffffff",
                            bg=n_color,
                            padx=5,
                            pady=1,
                        )
                        n_tag.pack(side=tk.LEFT, padx=(0, 6))

            # Bind entire card click to select setting
            card.bind("<Button-1>", lambda e, n=name: self._select_setting(n))
            top_row.bind("<Button-1>", lambda e, n=name: self._select_setting(n))
            left_info.bind("<Button-1>", lambda e, n=name: self._select_setting(n))

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
                text="Try clearing search or switching filter to 'All'",
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
                bg=bg_color,
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
            seg_frame = tk.Frame(parent, bg="#0b1220", padx=2, pady=2)
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
                padx=5,
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
                padx=5,
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
                padx=5,
                pady=2,
                command=lambda n=name: self._on_value_change(n, "FALSE"),
            )
            btn_off.pack(side=tk.LEFT, padx=1)

        elif cfg["type"] == "enum":
            opts = cfg.get("options", [current_val])
            box = ttk.Combobox(parent, values=opts, width=20, state="readonly", style="TCombobox")
            box.set(current_val)
            box.pack(side=tk.RIGHT)
            box.bind("<<ComboboxSelected>>", lambda e, n=name, b=box: self._on_value_change(n, b.get()))

        elif cfg["type"] == "number":
            # Sleek Dark Stepper: [-10] [-1] [Value] [+1] [+10] (NO WHITE BOXES!)
            stepper = tk.Frame(parent, bg=bg_color)
            stepper.pack(side=tk.RIGHT)

            btn_m10 = tk.Button(
                stepper,
                text="-10",
                font=("DejaVu Sans", 7, "bold"),
                bg="#1e293b",
                fg="#cbd5e1",
                activebackground="#334155",
                relief=tk.FLAT,
                padx=3,
                pady=2,
                command=lambda n=name: self._step_number(n, -10),
            )
            btn_m10.pack(side=tk.LEFT, padx=1)

            btn_m1 = tk.Button(
                stepper,
                text="-",
                font=("DejaVu Sans", 8, "bold"),
                bg="#1e293b",
                fg="#cbd5e1",
                activebackground="#334155",
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
            entry.pack(side=tk.LEFT, padx=2)
            entry.bind("<FocusOut>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))
            entry.bind("<Return>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))

            btn_p1 = tk.Button(
                stepper,
                text="+",
                font=("DejaVu Sans", 8, "bold"),
                bg="#1e293b",
                fg="#cbd5e1",
                activebackground="#334155",
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
                bg="#1e293b",
                fg="#cbd5e1",
                activebackground="#334155",
                relief=tk.FLAT,
                padx=3,
                pady=2,
                command=lambda n=name: self._step_number(n, 10),
            )
            btn_p10.pack(side=tk.LEFT, padx=1)

        else:
            # Code / Text entry with dark background
            entry = tk.Entry(
                parent,
                width=16,
                bg=C_BG_INPUT,
                fg="#ffffff",
                font=("Courier", 9),
                insertbackground=C_ACCENT,
                relief=tk.FLAT,
                bd=3,
            )
            entry.insert(0, current_val)
            entry.pack(side=tk.RIGHT)
            entry.bind("<FocusOut>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))
            entry.bind("<Return>", lambda e, n=name, ent=entry: self._on_value_change(n, ent.get()))

    # ==================== STATE & VALUE MANAGERS ====================
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
        if self.selected_setting_name == name:
            self._render_inspector_content()

    def _undo_single_setting(self, name):
        if self.active_filename in self.pending_updates and name in self.pending_updates[self.active_filename]:
            del self.pending_updates[self.active_filename][name]
            if not self.pending_updates[self.active_filename]:
                del self.pending_updates[self.active_filename]
            self._update_pending_status()
            self._populate_file_tree()
            self._render_settings_list()
            if self.selected_setting_name == name:
                self._render_inspector_content()

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
        messagebox.showinfo("Clipboard", f"Copied to clipboard:\n\n{text}")

    # ==================== PRESETS & BATCH MANAGERS ====================
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
                f"Preset '{p['title']}' loaded into pending changes.\nReview changes with 'Diff Preview' or save.",
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

    def _batch_enable_debug_menus(self):
        if messagebox.askyesno(
            "Enable Debug", "Enable overworld start menu debug options and battle debug menus in debug.h?"
        ):
            fname = "debug.h"
            if fname not in self.pending_updates:
                self.pending_updates[fname] = {}
            self.pending_updates[fname]["DEBUG_OVERWORLD_MENU"] = "TRUE"
            self.pending_updates[fname]["DEBUG_OVERWORLD_IN_MENU"] = "TRUE"
            self.pending_updates[fname]["DEBUG_BATTLE_MENU"] = "TRUE"
            self.pending_updates[fname]["DEBUG_AI_DELAY_TIMER"] = "TRUE"
            self.pending_updates[fname]["DEBUG_POKEMON_SPRITE_VISUALIZER"] = "TRUE"
            self._update_pending_status()
            self._populate_file_tree()
            if self.active_filename == fname:
                self._render_settings_list()
            messagebox.showinfo("Batch Updated", "All debug menus enabled in debug.h.")

    def _reset_current_file(self):
        if messagebox.askyesno("Reset File", f"Revert all pending changes in {self.active_filename}?"):
            if self.active_filename in self.pending_updates:
                del self.pending_updates[self.active_filename]
                self._update_pending_status()
                self._populate_file_tree()
                self._render_settings_list()
                self._render_inspector_content()

    def _discard_changes(self):
        if messagebox.askyesno("Discard All", "Discard ALL pending changes across all files?"):
            self.pending_updates.clear()
            self._update_pending_status()
            self._populate_file_tree()
            self._render_settings_list()
            self._render_inspector_content()

    # ==================== PROFILE EXPORT / IMPORT ====================
    def _export_profile(self):
        if not self.pending_updates:
            messagebox.showinfo("Export Profile", "No pending updates to export. Make changes or load a preset first!")
            return
        fpath = filedialog.asksaveasfilename(
            title="Export Configuration Profile",
            defaultextension=".json",
            filetypes=[("JSON Files", "*.json"), ("All Files", "*.*")],
            initialfile="confluence_profile.json",
        )
        if fpath:
            res = self.engine.export_profile(fpath, self.pending_updates)
            messagebox.showinfo("Export Successful", f"Exported {res['count']} settings to:\n{res['path']}")

    def _import_profile(self):
        fpath = filedialog.askopenfilename(
            title="Import Configuration Profile",
            filetypes=[("JSON Files", "*.json"), ("All Files", "*.*")],
        )
        if fpath:
            try:
                res = self.engine.import_profile(fpath)
                for fname, updates in res["updates"].items():
                    if fname not in self.pending_updates:
                        self.pending_updates[fname] = {}
                    for k, v in updates.items():
                        self.pending_updates[fname][k] = v
                self._update_pending_status()
                self._populate_file_tree()
                self._load_file(self.active_filename)
                messagebox.showinfo(
                    "Import Successful", f"Loaded profile '{res['name']}' with {res['count']} setting(s)."
                )
            except Exception as e:
                messagebox.showerror("Import Error", f"Failed to import profile:\n{e}")

    # ==================== MODALS: DIFF, BUILD, TEST, LIMITS ====================
    def _show_diff_modal(self):
        diffs = self.engine.compute_diff(self.pending_updates)
        if not diffs:
            messagebox.showinfo("Diff", "No differences found.")
            return

        win = tk.Toplevel(self.root)
        win.title("Unified Diff Preview — Review Code Changes")
        win.geometry("920x620")
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
        win.geometry("880x560")
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

    def _show_test_modal(self):
        win = tk.Toplevel(self.root)
        win.title("Run Pokémon Confluence C Unit Tests")
        win.geometry("880x560")
        win.configure(bg=C_BG_BASE)

        header = tk.Frame(win, bg="#0f172a", padx=16, pady=12)
        header.pack(fill=tk.X)
        tk.Label(
            header,
            text="🧪 bash pokeconfluence/scripts/test.sh",
            font=("DejaVu Sans", 11, "bold"),
            fg="#ffffff",
            bg="#0f172a",
        ).pack(side=tk.LEFT)

        status_lbl = tk.Label(
            header, text="Running tests...", font=("DejaVu Sans", 9, "bold"), fg=C_ACCENT, bg="#0f172a"
        )
        status_lbl.pack(side=tk.RIGHT)

        txt = scrolledtext.ScrolledText(win, bg="#030712", fg="#e2e8f0", font=("Courier", 9), padx=10, pady=10)
        txt.pack(fill=tk.BOTH, expand=True, padx=12, pady=8)

        def run_tests():
            test_script = ROM_DIR / "scripts" / "test.sh"
            cmd = ["bash", str(test_script)]
            proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            for line in proc.stdout:
                txt.insert(tk.END, line)
                txt.see(tk.END)
            proc.wait()
            if proc.returncode == 0:
                status_lbl.config(text="✓ ALL TESTS PASSED", fg=C_EMERALD)
            else:
                status_lbl.config(text="✕ TESTS FAILED", fg=C_RUBY)

        threading.Thread(target=run_tests, daemon=True).start()

    def _show_limits_modal(self):
        win = tk.Toplevel(self.root)
        win.title("Pokémon Confluence Engine Limits Audit")
        win.geometry("800x500")
        win.configure(bg=C_BG_BASE)

        header = tk.Frame(win, bg="#0f172a", padx=16, pady=12)
        header.pack(fill=tk.X)
        tk.Label(
            header,
            text="📊 python3 .agents/scripts/check_limits.py",
            font=("DejaVu Sans", 11, "bold"),
            fg="#ffffff",
            bg="#0f172a",
        ).pack(side=tk.LEFT)

        txt = scrolledtext.ScrolledText(win, bg="#030712", fg="#e2e8f0", font=("Courier", 9), padx=10, pady=10)
        txt.pack(fill=tk.BOTH, expand=True, padx=12, pady=8)

        def run_limits():
            script_path = Path("/home/mosberg/wsl_projects/pokemon/.agents/scripts/check_limits.py")
            cmd = ["python3", str(script_path)]
            proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            for line in proc.stdout:
                txt.insert(tk.END, line)
                txt.see(tk.END)
            proc.wait()

        threading.Thread(target=run_limits, daemon=True).start()

    def _open_web_studio(self):
        import webbrowser

        webbrowser.open("http://localhost:8996")
        messagebox.showinfo(
            "Web Studio",
            "Opened Web Studio at http://localhost:8996!\nIf server is not running, start it with:\n./tools/config-editor/poke-config-gui",
        )

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
