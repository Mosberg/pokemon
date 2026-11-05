"""Opens the party menu on the first Pokemon with the Field Kit and saves screenshots of the menu rows.

    scripts/play.sh 8921 &
    MGBA_BRIDGE_PORT=8921 .venv/bin/python mgba-agent/new_game_kanto.py
    MGBA_BRIDGE_PORT=8921 .venv/bin/python mgba-agent/confluence_smoke.py --only kit   (hands out the Field Kit)
    MGBA_BRIDGE_PORT=8921 .venv/bin/python mgba-agent/field_kit_menu.py [outdir]
"""
import sys
from pathlib import Path

from memory_patcher import give_mon, set_flag
from mgba_client import Bridge

b = Bridge()
out = Path(sys.argv[1] if len(sys.argv) > 1 else "/tmp/fieldkit")
out.mkdir(parents=True, exist_ok=True)


def shot(name: str) -> None:
    b.step(30)
    b.screenshot(str(out / f"{name}.png"))
    print("saved", out / f"{name}.png")


for _ in range(4):                  # leave any menu left open by an earlier run
    b.press("B", 6)
    b.step(40)
set_flag(b, 2144)                    # FLAG_SYS_POKEMON_GET: the start menu shows POKEMON
give_mon(b, 25, 20, [1], slot=0)   # a Pikachu that knows no field move
b.step(30)
b.press("START", 6)
b.step(40)
shot("1_start_menu")
b.press("UP", 6)                      # the cursor is remembered on BAG
b.step(10)
b.press("A", 6)                      # POKEMON is the first entry once there is a party
b.step(90)
shot("2_party")
b.press("A", 6)
b.step(40)
shot("3_mon_actions")
b.press("UP", 6)                     # wraps to Cancel; the FIELD KIT row sits just above SWITCH
b.step(5)
