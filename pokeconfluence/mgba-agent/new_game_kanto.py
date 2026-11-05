"""Start a fresh game through the bridge and record states/stage0_start.ss1 (Kanto start, Red's house 2F).

    python new_game_kanto.py [--johto | --hoenn]

Needs mGBA on a title screen with a fresh/empty save and lua/mgba_agent_bridge.lua loaded. Savestates are tied to one
ROM build, so run this again after every rebuild of the ROM (refresh_addresses.py first).
"""
import sys
from pathlib import Path

from addresses import SYMBOLS
from mgba_client import Bridge

b = Bridge()
region = "hoenn" if "--hoenn" in sys.argv else "johto" if "--johto" in sys.argv else "kanto"
hoenn = region == "hoenn"


def cb2():
    return b.u32(SYMBOLS["gMain"] + 4) & ~1


def hold(mask, frames=40):
    b.send(f"SETKEYS {mask}")
    b.step(frames)
    b.send("SETKEYS 0")
    b.step(20)


b.press("START", 6)
b.step(30)
n = 0
while cb2() != SYMBOLS["CB2_Overworld"] and n < 900:      # title, menu and Birch's speech: mash A
    b.press("A", 4)
    b.step(14)
    n += 1
start = b.player_position()[2:]
for _ in range(10):                                       # the player starts facing a box: close its text, walk right
    hold(16, 24)
    if b.player_position()[0] != 2:
        break
    b.press("B", 5)
    b.step(60)
for _ in range(3):
    hold(16, 30)
# the region menu: Kanto / Johto / Hoenn, cursor starts on Hoenn. A dismisses the question text, then UP moves towards Kanto.
ups = {"kanto": 2, "johto": 1, "hoenn": 0}[region]
b.step(150)
b.press("A", 4)
b.step(90)
for _ in range(ups):
    hold(64, 5)
    b.step(20)
n = 0
while b.player_position()[2:] == start and n < 40:
    b.press("A", 4)
    b.step(30)
    n += 1
b.step(150)
path = Path(__file__).parent / "states" / "stage0_start.ss1"
path.parent.mkdir(exist_ok=True)
if not hoenn:
    b.send(f"SAVEFILE {path}")
    print("[+] recorded", path)
print("position:", b.player_position())
