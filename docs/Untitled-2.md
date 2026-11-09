### 1. Setup Git Fork / Branch (Industry Standard Workflow)

This approach isolates custom features while continuously tracking upstream changes. It can be configured using existing repositories such as `Mosberg/poke-multiregion` (forked from `rh-hideout/pokeemerald-expansion`) or a new fork on GitHub.

```
                 [upstream] (rh-hideout/pokeemerald-expansion:master)
                                    │
                                    ▼ (git fetch upstream)
[origin] (Mosberg/poke-multiregion) ──► [local: master] (100% untouched mirror)
                                           │
                                           ▼ (git checkout -b / rebase)
                                    [local: my-game-dev] (Your custom maps, C code, scripts)

```

Run these commands inside your WSL2 terminal (`/home/mosberg/workspace`):

```bash
cd ~/workspace

# 1. Clone your personal fork
git clone https://github.com/Mosberg/poke-multiregion.git engine/pokeemerald-expansion
cd engine/pokeemerald-expansion

# 2. Add the official upstream repository
git remote add upstream https://github.com/rh-hideout/pokeemerald-expansion.git
git fetch upstream

# 3. Create your dedicated development branch from clean upstream
git checkout -b my-game-dev upstream/master

# 4. Push your working branch to your GitHub fork
git push -u origin my-game-dev

```

#### How to Sync Upstream Updates Cleanly Without Conflicts

When the `rh-hideout` team releases new mechanics, engine bug fixes, or battle engine updates:

```bash
cd ~/workspace/engine/pokeemerald-expansion

# 1. Update your local master to match upstream 100%
git checkout master
git pull upstream master
git push origin master

# 2. Rebase or merge upstream improvements into your custom game branch
git checkout my-game-dev
git merge master
# (Resolve any merge conflicts in VS Code, then test build)
make -j$(nproc)
git push origin my-game-dev

```

---

### 2. Build Overlay Pipeline (`build_overlay.py`)

This pipeline preserves the decomp repository as a completely untouched dependency in an `/external/` directory. Edits remain in an external `/mods/` directory, and the script temporarily stages the modifications before executing compilation.

#### Directory Structure

```text
/home/mosberg/workspace/
├── external/
│   └── pokeemerald-expansion/   <-- Untouched upstream clone
├── mods/                        <-- Your files ONLY
│   ├── src/                     <-- Custom C functions
│   ├── data/maps/               <-- Custom Porymap layouts
│   ├── data/scripts/            <-- Custom .pory / .inc scripts
│   └── graphics/                <-- Custom sprites and tilesets
├── build_overlay.py             <-- Execution script
└── builds/                      <-- Destination for compiled ROMs

```

Save the script below to `/home/mosberg/workspace/build_overlay.py`:

```python
#!/usr/bin/env python3
import os
import sys
import shutil
import subprocess
from pathlib import Path

# Paths relative to the workspace root
BASE_DIR = Path(__file__).resolve().parent
EXTERNAL_DIR = BASE_DIR / "external" / "pokeemerald-expansion"
MODS_DIR = BASE_DIR / "mods"
BUILDS_DIR = BASE_DIR / "builds"
ROM_NAME = "pokeemerald.gba"
ELF_NAME = "pokeemerald.elf"

def setup_dirs():
    MODS_DIR.mkdir(parents=True, exist_ok=True)
    BUILDS_DIR.mkdir(parents=True, exist_ok=True)
    if not (EXTERNAL_DIR / "Makefile").exists():
        print(f"[ERROR] Untouched decomp not found at: {EXTERNAL_DIR}")
        print("Please clone it first via:")
        print(f"  git clone https://github.com/rh-hideout/pokeemerald-expansion.git {EXTERNAL_DIR}")
        sys.exit(1)

def apply_overlay():
    """Copies all files from mods/ into external/ preserving backups of replaced files."""
    staged_backups = {}
    copied_files = []

    print("[1/4] Staging mods into clean decompilation engine...")
    for src_path in MODS_DIR.rglob("*"):
        if src_path.is_file():
            rel_path = src_path.relative_to(MODS_DIR)
            dest_path = EXTERNAL_DIR / rel_path

            # Create backup if destination file exists
            if dest_path.exists():
                bak_path = dest_path.with_suffix(dest_path.suffix + ".orig_bak")
                shutil.copy2(dest_path, bak_path)
                staged_backups[dest_path] = bak_path
            else:
                copied_files.append(dest_path)

            dest_path.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src_path, dest_path)
            print(f"  -> Injected: {rel_path}")

    return staged_backups, copied_files

def revert_overlay(staged_backups, copied_files):
    """Restores all original files and removes newly copied files, returning the repo to a clean state."""
    print("[3/4] Reverting overlay (Restoring clean engine state)...")
    # Remove newly created files
    for new_file in copied_files:
        if new_file.exists():
            new_file.unlink()

    # Restore backups
    for orig_dest, bak_path in staged_backups.items():
        if bak_path.exists():
            shutil.move(str(bak_path), str(orig_dest))

    print("[OK] Decompilation engine restored to 100% clean state.")

def compile_rom(clean_first=False):
    cpu_count = os.cpu_count() or 4
    cmd = ["make", f"-j{cpu_count}", "MODERN=1"]
    
    if clean_first:
        print("  -> Cleaning previous build...")
        subprocess.run(["make", "clean"], cwd=EXTERNAL_DIR, check=True)

    print(f"[2/4] Compiling ROM via 'make -j{cpu_count} MODERN=1'...")
    res = subprocess.run(cmd, cwd=EXTERNAL_DIR)
    return res.returncode == 0

def export_binaries():
    print("[4/4] Exporting final binaries...")
    src_rom = EXTERNAL_DIR / ROM_NAME
    src_elf = EXTERNAL_DIR / ELF_NAME

    if src_rom.exists():
        shutil.copy2(src_rom, BUILDS_DIR / ROM_NAME)
        print(f"[SUCCESS] ROM built and saved to: {BUILDS_DIR / ROM_NAME}")
    else:
        print("[FAIL] Output ROM was not produced.")

    if src_elf.exists():
        shutil.copy2(src_elf, BUILDS_DIR / ELF_NAME)

def main():
    setup_dirs()
    clean_build = "--clean" in sys.argv
    staged_backups, copied_files = apply_overlay()
    build_success = False

    try:
        build_success = compile_rom(clean_first=clean_build)
    finally:
        revert_overlay(staged_backups, copied_files)

    if build_success:
        export_binaries()
    else:
        print("[ERROR] Build failed. Review compiler diagnostics above.")
        sys.exit(1)

if __name__ == "__main__":
    main()

```

#### How to Use It

1. Keep `external/pokeemerald-expansion/` untouched.
2. Place custom files inside `mods/` (for example, `mods/src/battle_main.c` or `mods/graphics/pokemon/pikachu/front.png`).
3. Run the overlay build in your terminal:
```bash
python3 /home/mosberg/workspace/build_overlay.py

```


4. The output ROM is deposited in `/home/mosberg/workspace/builds/pokeemerald.gba`, while `external/pokeemerald-expansion/` remains completely clean.

---

### 3. Export & Apply Modular Git Patches (`.patch`)

Git patches allow sharing modifications as lightweight text files containing map, logic, and visual diffs without redistributing original copyrighted source files.

#### Step 1: Exporting Changes as a Patch

From your development repo (`poke-multiregion` on your `my-game-dev` branch):

```bash
cd ~/workspace/engine/pokeemerald-expansion

# Ensure all your custom files and changes are committed
git add .
git commit -m "Add custom maps, story events, and balance updates"

# Option A: Create a unified diff against upstream master (Recommended)
git diff upstream/master HEAD > ~/workspace/my_expansion_mod.patch

# Option B: Create a formal Git formatted patch set (includes commit author & logs)
git format-patch upstream/master --stdout > ~/workspace/Mosberg_Custom_Update.patch

```

#### Step 2: Validating and Applying the Patch on a Clean Repo

When another developer or a clean clone applies the patch:

```bash
cd ~/workspace/engine/pokeemerald-expansion

# 1. Do a dry-run check to verify there are no merge conflicts
git apply --check ~/workspace/my_expansion_mod.patch

# 2. Apply the patch cleanly
git apply ~/workspace/my_expansion_mod.patch

# 3. Build the patched game
make -j$(nproc)

```

#### Step 3: Reversing the Patch

To remove the patch and return the directory to an untouched state:

```bash
git apply -R ~/workspace/my_expansion_mod.patch

```
