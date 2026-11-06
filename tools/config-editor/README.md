# Pokémon Confluence Configuration Studio (`poke-config-gui`)

An interactive, visual configuration editor for all 23 C header files and 2,040+ game options in `/home/mosberg/wsl_projects/pokemon/pokeconfluence/include/config/`.

---

## Features

1. **Full Coverage across all 23 Configuration Headers**:
   - `ai.h`: Battle AI switching chances, move scoring, damage thresholds.
   - `battle.h`: Battle calculation formulas, criticals, gimmicks, split exp, whiteout penalties.
   - `caps.h`: 24-badge multi-region level caps, soft/hard cap behavior, EV limits.
   - `item.h`: Reusable TMs, modern Exp. Share mode, Repel menus, bag healing values.
   - `overworld.h`: Indoor running, poison survival, PC deposit healing, Berry moisture and mutations.
   - `pokemon.h`: Shiny rates, trade evolutions, nature stat modifiers.
   - `species_enabled.h`: Toggle Generations 1-9, Regional forms, and individual Pokémon evolution families.
   - `summary_screen.h`, `name_box.h`, `map_preview_screen.h`, `debug.h`, `save.h`, `wild_encounter.h`, and more.

2. **Rich Information & Documentation on "What Everything Does"**:
   - Extracted directly from engine comments, documentation headers, and inline notes.
   - Highlights generational differences (`In Gen 4+...`, `In Gen 6+...`, `In Gen 9+...`).
   - Flags critical notices: `SAVE-BREAKING` alerts, `WIP / Experimental` notes, and `POKE-CONFLUENCE` custom mechanics.

3. **Smart Form Controls**:
   - **Booleans**: Instant Toggle Switches (`TRUE` / `FALSE`).
   - **Generations**: Pill selectors (`Gen 1` through `Gen 9` + `Latest`).
   - **Enums**: Dropdowns populated with valid constants (e.g. `EXP_CAP_SOFT`, `EXP_CAP_HARD`, `EXP_CAP_NONE`).
   - **Numbers & Percentages**: Steppers (`-10`, `-1`, `+1`, `+10`) with range sliders for percentage settings.
   - **Species Families**: 3-way toggle (`Inherit`, `ON`, `OFF`).

4. **Safety & Non-Destructive Editing**:
   - **Live Unified Diff**: Review every line of code that will change before saving.
   - **Automatic Backups**: Saves timestamped snapshots to `include/config/.backups/` before modifying any files.
   - **Formatting Preservation**: Preserves C indentation, comments, `#ifndef` guards, and `// POKE-CONFLUENCE` tags.
   - **One-Click Rebuild**: Trigger `make -C pokeconfluence -j$(nproc)` directly from the GUI with live terminal logs.

---

## How to Launch

### 1. Web GUI (Default)
In your terminal, simply run:
```bash
poke-config-gui
```
This starts the local web server (default port `8088` or next available) and automatically opens your browser.

Options:
- `--port 8090`: Specify a custom port.
- `--no-browser`: Start the server without auto-opening the browser.

### 2. Native Desktop GUI (Tkinter)
If you prefer a native desktop window over X11 / Wayland:
```bash
poke-config-gui --desktop
```
