An optimal VS Code configuration for developing Pokémon Generation 3 decompilation projects (`pokeemerald`, `pokefirered`, and `pokeemerald-expansion`) running inside WSL2 Ubuntu (`/home/mosberg/workspace`) requires coordinating cross-compilation toolchains and domain-specific languages:

1. **`arm-none-eabi` cross-compiler and GBA target defines** mapped so IntelliSense does not fail on Thumb assembly or GBA registers.


2. **Poryscript and ARM assembly associations** so `.pory`, `.inc`, and `.s` render with proper highlighting and compile hooks.


3. **mGBA source-level GDB debugging** to attach breakpoints to `.elf` files directly from VS Code.


4. **Custom workspace tasks** for parallel builds (`make -j12 MODERN=1`), SaveBlock RAM audits, Porytiles compilation, and Poryscript transpilation.



Place the following configuration files inside `/home/mosberg/workspace/engine/pokeemerald-expansion/.vscode/` (or your root project workspace).

---

### 1. `.vscode/extensions.json`

Ensures all required language servers, syntax linters, and emulator hooks are enabled inside the WSL remote environment:

```json
{
  "recommendations": [
    // Core C/C++ Engine & Build Systems
    "ms-vscode.cpptools",
    "ms-vscode.cpptools-extension-pack",
    "ms-vscode.makefile-tools",

    // ARM7TDMI Architecture & Assembly Syntax
    "dan-c-underwood.arm",
    "webfreak.debug",
    "marus25.cortex-debug",

    // Pokémon Decompilation DSLs & Formats
    "huderlem.poryscript",
    "tomek-k.gbapalette-vscode",
    "ms-vscode.hexeditor",

    // Scripting & Data Parsing
    "ms-python.python",
    "ms-python.vscode-pylance",
    "charliermarsh.ruff",
    "mechatroner.rainbow-csv",

    // Remote Architecture
    "ms-vscode-remote.remote-wsl"
  ]
}

```

---

### 2. `.vscode/settings.json`

Tuned for GBA hardware specs, your Ryzen 5 3600 (12 threads), and `pokeemerald-expansion` header structures:

```json
{
  // ── GBA Toolchain & IntelliSense Engine ──────────────────────────────────
  "C_Cpp.default.compilerPath": "/usr/bin/arm-none-eabi-gcc",
  "C_Cpp.default.cStandard": "gnu11",
  "C_Cpp.default.cppStandard": "gnu++14",
  "C_Cpp.default.intelliSenseMode": "linux-gcc-arm",
  "C_Cpp.default.includePath": [
    "${workspaceFolder}/include",
    "${workspaceFolder}/src",
    "${workspaceFolder}/tools/**",
    "/usr/lib/gcc/arm-none-eabi/**/include",
    "/usr/include/newlib"
  ],
  "C_Cpp.default.defines": [
    "MODERN=1",
    "ENGLISH=1",
    "EMERALD=1",
    "GEN_LATEST=1",
    "B_SAVE_EXPANSION=1",
    "DEBUG=1",
    "__GBA__=1",
    "ARM=1"
  ],
  "C_Cpp.errorSquiggles": "enabled",
  "C_Cpp.intelliSenseUpdateDelay": 500,

  // ── GBA & Decomp File Associations ──────────────────────────────────────
  "files.associations": {
    "*.pory": "poryscript",
    "*.inc": "arm",
    "*.s": "arm",
    "*.h": "c",
    "*.c": "c",
    "*.ld": "linkerscript",
    "*.gbapal": "hex",
    "*.pal": "plaintext",
    "*.4bpp": "hex",
    "*.8bpp": "hex",
    "*.bin": "hex",
    "*.party": "c"
  },

  // ── Source & Formatting Rules (Strict Decomp Parity) ─────────────────────
  // Decomp projects enforce 4-space tab indentation and LF line endings
  "editor.tabSize": 4,
  "editor.insertSpaces": false,
  "editor.detectIndentation": false,
  "editor.rulers": [80, 120],
  "files.eol": "\n",
  "files.encoding": "utf8",
  "files.trimTrailingWhitespace": true,
  "files.insertFinalNewline": true,

  // ── Poryscript Language Server Configuration ────────────────────────────
  "poryscript.commandPath": "${workspaceFolder}/../../tools/poryscript/poryscript",
  "poryscript.fontConfig": "pokeemerald",
  "poryscript.emitExpansionStringEncoding": true,

  // ── Makefile Automation ──────────────────────────────────────────────────
  "makefile.configureOnOpen": true,
  "makefile.makePath": "/usr/bin/make",

  // ── Performance: Exclude Massive Intermediate Build Trees ───────────────
  "files.watcherExclude": {
    "**/.git/objects/**": true,
    "**/.git/subtree-cache/**": true,
    "**/build/**": true,
    "**/*.gba": true,
    "**/*.elf": true,
    "**/*.4bpp": true,
    "**/*.8bpp": true
  },
  "search.exclude": {
    "**/build/**": true,
    "**/*.gba": true,
    "**/*.elf": true,
    "**/*.4bpp": true,
    "**/*.8bpp": true,
    "**/*.bin": true
  },

  // ── Integrated WSL2 Terminal Profile ─────────────────────────────────────
  "terminal.integrated.defaultProfile.linux": "bash",
  "terminal.integrated.scrollback": 15000,
  "terminal.integrated.env.linux": {
    "MAKEFLAGS": "-j12"
  }
}

```

---

### 3. `.vscode/tasks.json`

Provides one-key shortcuts (Ctrl+Shift+B) to compile with all 12 CPU cores, audit SaveBlock limits, and build tilesets:

```json
{
  "version": "2.0.0",
  "tasks": [
    // ── Primary Build: Parallel Modern GCC (Default Build Task) ────────────
    {
      "label": "Build ROM (Modern GCC - Parallel)",
      "type": "shell",
      "command": "make -j$(nproc) MODERN=1",
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"],
      "presentation": {
        "echo": true,
        "reveal": "always",
        "focus": false,
        "panel": "shared"
      }
    },

    // ── Debug Build with GDB Symbol Tables ─────────────────────────────────
    {
      "label": "Build ROM with Debug Symbols (ELF)",
      "type": "shell",
      "command": "make -j$(nproc) MODERN=1 DINFO=1",
      "group": "build",
      "problemMatcher": ["$gcc"]
    },

    // ── Matching Vanilla Byte Build (agbcc) ────────────────────────────────
    {
      "label": "Build Byte-Matching ROM (agbcc)",
      "type": "shell",
      "command": "make -j$(nproc) MODERN=0",
      "group": "build",
      "problemMatcher": ["$gcc"]
    },

    // ── Clean All Intermediate Objects ─────────────────────────────────────
    {
      "label": "Clean Workspace",
      "type": "shell",
      "command": "make clean",
      "problemMatcher": []
    },

    // ── Compile All Poryscript Files to .inc Assembly ──────────────────────
    {
      "label": "Compile Poryscripts",
      "type": "shell",
      "command": "find data/ -type f -name '*.pory' -exec poryscript -i {} -o {}.inc -fc tools/poryscript/font_config.json \\;",
      "problemMatcher": []
    },

    // ── Compile Overworld Tileset via Porytiles ────────────────────────────
    {
      "label": "Compile Primary Tileset (Porytiles)",
      "type": "shell",
      "command": "porytiles compile-primary -d data/tilesets/primary/default",
      "problemMatcher": []
    },

    // ── Automated Test Suite Execution ─────────────────────────────────────
    {
      "label": "Run Battle Engine Test Suite",
      "type": "shell",
      "command": "make -j$(nproc) check",
      "group": "test",
      "problemMatcher": ["$gcc"]
    }
  ]
}

```

---

### 4. `.vscode/launch.json`

Configured to attach directly to **mGBA's built-in GDB stub** (running on port `2345` with host loopback) for source-level debugging in C:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug ROM with mGBA (GDB Stub)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/pokeemerald.elf",
      "cwd": "${workspaceFolder}",
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/arm-none-eabi-gdb",
      "miDebuggerServerAddress": "localhost:2345",
      "setupCommands": [
        {
          "description": "Load ELF Symbols",
          "text": "file ${workspaceFolder}/pokeemerald.elf",
          "ignoreFailures": false
        },
        {
          "description": "Enable hardware watchpoints on GBA address ranges",
          "text": "set can-use-hw-watchpoints 1",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "Build ROM with Debug Symbols (ELF)"
    },
    {
      "name": "Attach to External GDB Server",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/pokeemerald.elf",
      "cwd": "${workspaceFolder}",
      "MIMode": "gdb",
      "miDebuggerPath": "/usr/bin/arm-none-eabi-gdb",
      "miDebuggerServerAddress": "127.0.0.1:2345",
      "setupCommands": [
        {
          "text": "target remote 127.0.0.1:2345"
        },
        {
          "text": "symbol-file ${workspaceFolder}/pokeemerald.elf"
        }
      ]
    }
  ]
}

```

---

### Quick Setup Steps

1. In your Ubuntu terminal, navigate to your repo and create the directory:
```bash
cd ~/workspace/engine/pokeemerald-expansion
mkdir -p .vscode

```


2. Save the four snippets above into `.vscode/extensions.json`, `.vscode/settings.json`, `.vscode/tasks.json`, and `.vscode/launch.json`.


3. Open the workspace from WSL by running `code .`.


4. Install recommended extensions when VS Code prompts in the bottom right corner.


5. Press Ctrl+Shift+B to execute a 12-thread parallel build directly to `pokeemerald.gba`.
