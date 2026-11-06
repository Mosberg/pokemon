# Pokémon Confluence Configuration Studio (`poke-config-gui`) v2.5 PRO

An interactive, visual configuration studio for all 23 C header files and 2,040+ game options in `/home/mosberg/wsl_projects/pokemon/pokeconfluence/include/config/`.

---

## What's New in v2.5 PRO

1. **Responsive 3-Pane Studio Architecture**:
   - **Left Pane**: File Explorer, Categories Accordion, Live Search across 2,040+ options, and status badges.
   - **Center Pane**: Responsive stream of cards with zero void / dead space. Setting cards dynamically scale to fit the viewport.
   - **Right Pane (Live Inspector & Companion)**:
     - Active Macro Name with 1-click **Copy Macro** and **Copy `#define`**.
     - Source file location and line number (`include/config/...:line`).
     - **Deep Engine Impact**: Explains engine functions (e.g. `ShouldSwitch()` in `src/battle_ai_switch_items.c`, `src/caps.c`), safe ranges, and default values.
     - **Presets Comparison Matrix**: Shows setting values across Vanilla Gen3, Modern Gen9, Hardcore Nuzlocke, Competitive Smogon, and Sandbox Dev.
     - **Project Hub**: Quick stats, 1-click preset triggers, Build ROM, Run Unit Tests, Limits Audit, and Web Studio launcher.
     - Toggleable with `[ Inspector ❯ ]` / `[ ❮ Inspector ]` to expand center stream full-width.

2. **Flawless Obsidian Pro Dark Theme & Clean Controls (No Stark White Boxes!)**:
   - Deep obsidian backgrounds (`#090d16` base, `#0f172a` panels, `#151f32` cards, `#0a1120` inputs).
   - High-contrast, crystal clear typography across Linux X11, WSLg, and Web.
   - **Booleans**: Smooth Canvas Pill Switch (rounded animated capsule: Emerald `#10b981` when ON, Slate `#334155` when OFF).
   - **Numbers**: Sleek Dark Steppers `[-10]` `[-]` `[ 100 ]` `[+]` `[+10]` with `#0a1120` background and cyan focus.
   - **Generations**: Generation selector with Gen 1-9 color badges.
   - **Enums**: Modern dark dropdowns.
   - **Families**: 3-way segmented pill buttons `[Inherit]` `[ON]` `[OFF]`.

3. **5 Game Presets**:
   - ⚡ **Modern Gen 9 Experience (Recommended)**: Reusable TMs, modern criticals, full Exp Share, running indoors, all Gen 1-9 Pokémon.
   - ☠ **Hardcore Nuzlocke Challenge**: Hard level caps (zero exp at cap), Rare Candy cap lock, overworld poison damage, Gen 3 battle rules.
   - 🌿 **Vanilla Generation 3 (RSE Purist)**: Authentic 2004 Emerald/FRLG mechanics: single-use TMs, 200% crit damage, no indoor running.
   - 🏆 **Competitive Smogon / Tournament Rules**: Smart AI dynamic switching, Gen 9 damage/burn formulas, team preview, soft level caps.
   - 🛠 **Developer & Sandbox Mode**: Overworld debug menus in start menu, battle debug menus, AI timer displays, lifted level caps.

4. **Safety, Profiles & Verification**:
   - **Live Unified Diff**: Syntax-highlighted code diff preview before writing.
   - **Automatic Timestamped Backups**: Saved to `include/config/.backups/`.
   - **JSON Configuration Profiles**: Export custom configuration snapshots (`.json`) and import them on any machine.
   - **Integrated ROM Compiler**: `make -C pokeconfluence -j$(nproc)` with real-time log output.
   - **Integrated C Test Suite Runner**: `bash pokeconfluence/scripts/test.sh`.
   - **Engine Limits Auditor**: `python3 .agents/scripts/check_limits.py`.

---

## How to Launch

### 1. Web Studio (Default)
In your terminal, run:
```bash
poke-config-gui
# Or directly:
python3 tools/config-editor/web_server.py
```
This automatically starts the local HTTP server and opens your browser at `http://localhost:8088`.

Options:
- `--port 8090`: Specify custom port.
- `--no-browser`: Start server without auto-opening the browser.

### 2. Native Desktop GUI (Tkinter)
For a native desktop window on Linux / WSLg:
```bash
poke-config-gui --desktop
# Or directly:
python3 tools/config-editor/desktop_gui.py
```

### Keyboard Shortcuts
- `Ctrl + S`: Save Changes (creates backup and writes headers)
- `Ctrl + D`: Diff Preview modal
- `Ctrl + B`: Build ROM modal
- `Ctrl + T`: Run C Unit Tests modal
