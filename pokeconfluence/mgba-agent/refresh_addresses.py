"""Refresh addresses.json from a freshly built ELF.  usage: python refresh_addresses.py [path/to/pokeconfluence.elf]
Runs arm-none-eabi-nm inside WSL when it is not on PATH (the toolchain lives in WSL here)."""
import json
import shutil
import subprocess
import sys
from pathlib import Path
from addresses import SYMBOLS

ELF = Path(sys.argv[1] if len(sys.argv) > 1 else "../pokeconfluence.elf").resolve()
# names in addresses.py -> real symbol names (the party/enemy symbols are named differently)
ALIAS = {"gPlayerParty": "gPlayerPartyPtr", "gEnemyParty": "gEnemyPartyPtr",
         "gPlayerPartyCount": "gPlayerPartyCountPtr", "gEnemyPartyCount": "gEnemyPartyCountPtr"}


def nm():
    if shutil.which("arm-none-eabi-nm"):
        cmd = ["arm-none-eabi-nm", str(ELF)]
    else:
        wsl_path = "/mnt/" + ELF.drive[0].lower() + ELF.as_posix()[2:]
        cmd = ["wsl", "-d", "Ubuntu", "-e", "arm-none-eabi-nm", wsl_path]
    return subprocess.run(cmd, capture_output=True, text=True, check=True).stdout


table = {}
for line in nm().splitlines():
    parts = line.split()
    if len(parts) == 3:
        table[parts[2]] = int(parts[0], 16)

out = {}
for name in SYMBOLS:
    real = ALIAS.get(name, name)
    if real not in table:
        print("missing symbol:", real)
        continue
    addr = table[real]
    if real != name:  # these are const pointers in ROM: follow them
        data = ELF.with_suffix(".gba").read_bytes()
        addr = int.from_bytes(data[addr - 0x08000000:addr - 0x08000000 + 4], "little")
    out[name] = addr
Path(__file__).with_name("addresses.json").write_text(json.dumps({"symbols": out}, indent=2))
print(f"wrote addresses.json with {len(out)} symbols")
