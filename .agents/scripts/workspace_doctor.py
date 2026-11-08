#!/usr/bin/env python3
"""
workspace_doctor.py - Comprehensive workspace health inspector and diagnostics tool.
Audits toolchains, compilers, configurations, assets, and engine limits across the repository.
"""

import sys
import os
import shutil
import subprocess
from pathlib import Path

WORKSPACE = Path("/home/mosberg/wsl_projects/pokemon")
POKECONFLUENCE = WORKSPACE / "pokeconfluence"
TOOLS = WORKSPACE / "tools"

CYAN = "\033[1;36m"
GREEN = "\033[0;32m"
YELLOW = "\033[1;33m"
RED = "\033[0;31m"
BOLD = "\033[1m"
RESET = "\033[0m"


def check_toolchain():
    print(f"\n{BOLD}[1/5] Checking Toolchain & Compilers{RESET}")
    tools = [
        ("ARM GCC Compiler", "arm-none-eabi-gcc", "--version"),
        ("ARM Linker", "arm-none-eabi-ld", "--version"),
        ("Host C++ Compiler", "g++", "--version"),
        ("Host C Compiler", "gcc", "--version"),
        ("GNU Make", "make", "--version"),
        ("Python 3", sys.executable, "--version"),
        ("Qt6 QMake", "qmake6", "-v"),
        ("Porymap Map Editor", str(Path.home() / ".local/bin/porymap"), "--version"),
        ("Porytiles Compiler", str(TOOLS / "porytiles-linux-amd64/porytiles"), "--version"),
        ("Poryscript Compiler", str(Path.home() / ".local/bin/poryscript"), "-v"),
    ]

    all_ok = True
    for label, cmd, flag in tools:
        resolved = shutil.which(cmd) or (Path(cmd).is_file() and os.access(cmd, os.X_OK))
        if resolved:
            try:
                out = subprocess.check_output([cmd, flag], stderr=subprocess.STDOUT, text=True).splitlines()[0]
                print(f"  {GREEN}✓{RESET} {label:24} : {out[:50]}")
            except Exception:
                print(f"  {GREEN}✓{RESET} {label:24} : Available at {resolved}")
        else:
            print(f"  {YELLOW}⚠{RESET} {label:24} : Not found ({cmd})")
            all_ok = False
    return all_ok


def check_python_environment():
    print(f"\n{BOLD}[2/5] Checking Python Virtual Environment{RESET}")
    venv_py = POKECONFLUENCE / ".venv/bin/python"
    venv_pytest = POKECONFLUENCE / ".venv/bin/pytest"
    if venv_py.exists():
        print(f"  {GREEN}✓{RESET} pokeconfluence/.venv found ({venv_py})")
        packages = ["pytest", "PIL", "pydantic"]
        for pkg in packages:
            try:
                subprocess.check_output([str(venv_py), "-c", f"import {pkg}"], stderr=subprocess.DEVNULL)
                print(f"  {GREEN}✓{RESET} Python package: {pkg}")
            except Exception:
                print(f"  {YELLOW}⚠{RESET} Missing Python package in .venv: {pkg}")
    else:
        print(f"  {YELLOW}⚠{RESET} pokeconfluence/.venv not initialized (run pokeconfluence/scripts/setup.sh)")


def check_configs():
    print(f"\n{BOLD}[3/5] Checking Project Configurations & Data Schemas{RESET}")
    configs = [
        ("Porymap Project Config", POKECONFLUENCE / "porymap.project.cfg"),
        ("Porymap Region Maps JSON", POKECONFLUENCE / "src/data/region_map/porymap_config.json"),
        ("Map Groups JSON", POKECONFLUENCE / "data/maps/map_groups.json"),
        ("Layouts JSON", POKECONFLUENCE / "data/layouts/layouts.json"),
        ("Region Map Sections JSON", POKECONFLUENCE / "src/data/region_map/region_map_sections.json"),
        ("Trainers Party Data", POKECONFLUENCE / "src/data/trainers.party"),
        ("Limits Hook Configuration", WORKSPACE / ".agents/hooks.json"),
    ]

    for label, path in configs:
        if path.exists():
            size = path.stat().st_size
            print(f"  {GREEN}✓{RESET} {label:28} : Found ({size:,} bytes)")
        else:
            print(f"  {RED}✗{RESET} {label:28} : MISSING at {path}")


def check_script_permissions():
    print(f"\n{BOLD}[4/5] Checking Executable Permissions{RESET}")
    scripts = list(WORKSPACE.glob(".agents/scripts/*.sh")) + \
              list(WORKSPACE.glob(".agents/scripts/*.py")) + \
              list(POKECONFLUENCE.glob("scripts/*.sh")) + \
              list(POKECONFLUENCE.glob("scripts/*.py"))

    missing_exec = []
    for s in scripts:
        if not os.access(s, os.X_OK):
            missing_exec.append(s)

    if missing_exec:
        print(f"  {YELLOW}⚠{RESET} {len(missing_exec)} scripts lack executable bit (+x):")
        for m in missing_exec[:5]:
            print(f"    - {m.relative_to(WORKSPACE)}")
        if "--fix" in sys.argv:
            for m in missing_exec:
                m.chmod(m.stat().st_mode | 0o111)
            print(f"  {GREEN}✓{RESET} Fixed executable permissions for all {len(missing_exec)} scripts.")
    else:
        print(f"  {GREEN}✓{RESET} All {len(scripts)} scripts have proper executable permissions (+x).")


def check_engine_limits_summary():
    print(f"\n{BOLD}[5/5] Checking Hardware & Engine Limits{RESET}")
    res = subprocess.run([sys.executable, str(WORKSPACE / ".agents/scripts/check_limits.py")], capture_output=True, text=True)
    for line in res.stdout.splitlines():
        if line.startswith("["):
            print(f"  {line}")


def main():
    print(f"{CYAN}{BOLD}================================================================{RESET}")
    print(f"{CYAN}{BOLD} Pokémon Workspace Diagnostics & Health Doctor{RESET}")
    print(f"{CYAN}{BOLD}================================================================{RESET}")

    check_toolchain()
    check_python_environment()
    check_configs()
    check_script_permissions()
    check_engine_limits_summary()

    print(f"\n{CYAN}{BOLD}================================================================{RESET}")
    print(f"{GREEN}{BOLD} Workspace audit complete.{RESET}")
    print(f"{CYAN}{BOLD}================================================================{RESET}\n")


if __name__ == "__main__":
    main()
