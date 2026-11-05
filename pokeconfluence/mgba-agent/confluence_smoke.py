"""Plays the Confluence layer in the embedded emulator and asserts the outcomes from RAM.

    scripts/play.sh 8911 &          (or any emulator / mGBA with the bridge on that port)
    MGBA_BRIDGE_PORT=8911 .venv/bin/python mgba-agent/confluence_smoke.py [--only kit,enforcer,chairman,apex]

Needs a fresh game at the overworld (run new_game_kanto.py first). Flag ids come from the build (include/constants/flags.h):
FLAG_CONFLUENCE_* = 0x20..0x24, trainer flags = 0x500 + trainer id, badges as below.
"""
import argparse
import struct
import sys

from addresses import SYMBOLS
from memory_patcher import give_mon, set_flag, warp_player
from mgba_client import Bridge

HOENN_BADGES = list(range(2151, 2159))
KANTO_BADGES = list(range(2401, 2409))
JOHTO_BADGES = [4214, 4182, 4282, 4082, 4405, 3753, 3765, 4108]
FLAG_APEX_UNLOCKED, FLAG_APEX_CHAMPION, FLAG_MERIDIAN_USED, FLAG_CRISIS_RESOLVED, FLAG_FIELD_KIT = 32, 33, 34, 35, 36
TRAINER_FLAGS = 0x500
APEX = [855, 856, 857, 858]
SYNDICATE = {"kanto": 859, "johto": 860, "hoenn": 861, "chairman": 862}
OLIVINE = (75, 13)
SILVER_CAVE_OUTSIDE = (77, 80)

b = Bridge()
failures = []


def check(name: str, ok: bool) -> None:
    print(("PASS " if ok else "FAIL ") + name)
    if not ok:
        failures.append(name)


def badges(n: int) -> None:
    for f in (HOENN_BADGES + KANTO_BADGES + JOHTO_BADGES)[:n]:
        set_flag(b, f)


def clear_badges() -> None:
    for f in HOENN_BADGES + KANTO_BADGES + JOHTO_BADGES:
        set_flag(b, f, False)


def strong_mon() -> None:
    """A level 100 Mewtwo-like stat block with Psychic, so that scripted trainer fights can be won."""
    give_mon(b, 150, 100, [94], slot=0)
    base = SYMBOLS["gPlayerParty"] + 0x56
    b.write(base, struct.pack("<HHHHHHH", 999, 999, 999, 999, 999, 999, 999))


def talk(group_num, x: int, y: int, face: str) -> None:
    warp_player(b, group_num[0], group_num[1], x, y)
    b.step(300)
    b.press(face, 10)
    b.step(20)
    b.press("A", 4)
    b.step(100)


def advance(n: int = 8, stop_in_battle: bool = True) -> None:
    for _ in range(n):
        b.step(200)
        b.press("A", 4)
        b.step(30)
        if stop_in_battle and b.in_battle():
            break
    b.step(200)


def win_battle(max_turns: int = 400) -> bool:
    for _ in range(max_turns):
        if not b.in_battle():
            return True
        b.press("A", 4)
        b.step(45)
    return not b.in_battle()


def trainer_defeated(trainer_id: int) -> bool:
    return b.flag(TRAINER_FLAGS + trainer_id)


def test_kit() -> None:
    clear_badges()
    badges(2)
    talk(OLIVINE, 15, 22, "RIGHT")
    advance(10, stop_in_battle=False)
    check("conductor hands out the Field Kit with 2 badges", b.flag(FLAG_FIELD_KIT))


def test_enforcer() -> None:
    clear_badges()
    badges(2)
    strong_mon()
    talk(OLIVINE, 18, 23, "RIGHT")
    advance(4)
    check("enforcer ignores a player with 2 badges", not b.in_battle() and not trainer_defeated(SYNDICATE["johto"]))
    badges(6)
    talk(OLIVINE, 18, 23, "RIGHT")
    advance(8)
    check("enforcer battles a player with 6 badges", b.in_battle())
    check("enforcer fight can be won", win_battle())
    advance(4, stop_in_battle=False)
    check("enforcer defeat is recorded", trainer_defeated(SYNDICATE["johto"]))


def test_chairman() -> None:
    clear_badges()
    badges(12)
    strong_mon()
    for t in ("kanto", "johto", "hoenn"):
        set_flag(b, TRAINER_FLAGS + SYNDICATE[t])
    talk(OLIVINE, 15, 22, "RIGHT")
    advance(5, stop_in_battle=False)       # welcome, menu opens
    for _ in range(3):                     # Kanto, Hoenn, Circuit report, Crisis briefing
        b.press("DOWN", 4)
        b.step(15)
    b.press("A", 4)
    advance(8)
    check("chairman call starts a battle", b.in_battle())
    check("chairman fight can be won", win_battle())
    advance(8, stop_in_battle=False)
    check("beating the chairman resolves the crisis", b.flag(FLAG_CRISIS_RESOLVED))


def test_apex() -> None:
    clear_badges()
    badges(24)
    for t in APEX:
        set_flag(b, TRAINER_FLAGS + t)
    talk(SILVER_CAVE_OUTSIDE, 23, 21, "RIGHT")
    advance(10, stop_in_battle=False)
    b.step(600)
    check("Apex victory sets the champion flag", b.flag(FLAG_APEX_CHAMPION))
    print("position after the Apex ending:", b.player_position())


TESTS = {"kit": test_kit, "enforcer": test_enforcer, "chairman": test_chairman, "apex": test_apex}

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--only", default=",".join(TESTS))
    args = ap.parse_args()
    for name in args.only.split(","):
        print(f"== {name}")
        TESTS[name]()
    sys.exit(1 if failures else 0)
