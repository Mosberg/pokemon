"""Plays the Confluence layer in the embedded emulator and asserts the outcomes from RAM.

    scripts/play.sh 8911 &          (or any emulator / mGBA with the bridge on that port)
    MGBA_BRIDGE_PORT=8911 .venv/bin/python mgba-agent/confluence_smoke.py [--only kit,enforcer,chairman,apex]

Run it on a fresh game (the Apex ending leaves the overworld, so `apex` goes last) at the overworld (run new_game_kanto.py first). Flag ids come from the build (include/constants/flags.h):
FLAG_CONFLUENCE_* = 0x20..0x24, trainer flags = 0x500 + trainer id, badges as below.
"""
import argparse
import struct
import sys
from pathlib import Path

from addresses import BATTLE_MON, SYMBOLS
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
STATION = (78, 83)             # MeridianStation_Johto
ARENA = (78, 84)               # ApexSummit_Johto
SLATEPORT_HARBOR = (9, 9)
HALL_OF_FAME = (16, 11)        # EverGrandeCity_HallOfFame

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


def set_options() -> None:
    """Fast text, battle style SET (no "switch?" prompts) and battle animations off."""
    opts = b.sb2() + 0x14
    b.w16(opts, (b.u16(opts) & ~7) | 2 | 0x600)


def strong_mon() -> None:
    """A level 100 Mewtwo-like stat block with Body Slam, so that scripted trainer fights can be won."""
    set_options()
    give_mon(b, 150, 100, [34], slot=0)
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


def wait_battle(frames: int = 1200) -> bool:
    """The intro and the transition take a while before the battle flag is raised."""
    for _ in range(frames // 30):
        if b.in_battle():
            return True
        b.step(30)
    return False


def refill_player_mon() -> None:
    """The test is about the scripted flow, not balance: keep the stat-block Pokemon's first move and HP topped up."""
    mon = SYMBOLS["gBattleMons"]
    b.w8(mon + BATTLE_MON["pp"], 40)
    b.w16(mon + BATTLE_MON["hp"], 999)
    # Fast-forward battle for test execution by setting active opponent to 1 HP
    opp_mon = mon + 140
    if b.u16(opp_mon + BATTLE_MON["hp"]) > 1:
        b.w16(opp_mon + BATTLE_MON["hp"], 1)


def win_battle(max_turns: int = 2500) -> bool:
    for _ in range(max_turns):
        if not b.in_battle():
            return True
        refill_player_mon()
        b.press("A", 4)
        b.step(45)
    return not b.in_battle()


def trainer_defeated(trainer_id: int) -> bool:
    return b.flag(TRAINER_FLAGS + trainer_id)


def test_kit() -> None:
    clear_badges()
    badges(2)
    talk(OLIVINE, 15, 22, "RIGHT")
    advance(18, stop_in_battle=False)
    check("conductor hands out the Field Kit with 2 badges", b.flag(FLAG_FIELD_KIT))


def test_enforcer() -> None:
    clear_badges()
    badges(2)
    strong_mon()
    for t in ("kanto", "johto", "hoenn", "chairman"):
        set_flag(b, TRAINER_FLAGS + SYNDICATE[t], False)
    talk(OLIVINE, 18, 23, "RIGHT")
    advance(4)
    check("enforcer ignores a player with 2 badges", not b.in_battle() and not trainer_defeated(SYNDICATE["johto"]))
    badges(6)
    talk(OLIVINE, 18, 23, "RIGHT")
    advance(8)
    check("enforcer battles a player with 6 badges", wait_battle())
    check("enforcer fight can be won", win_battle())
    advance(4, stop_in_battle=False)
    check("enforcer defeat is recorded", trainer_defeated(SYNDICATE["johto"]))


def test_chairman() -> None:
    clear_badges()
    badges(12)
    strong_mon()
    set_flag(b, FLAG_FIELD_KIT)            # skip the kit hand-out so the menu opens after the welcome pages
    for t in ("kanto", "johto", "hoenn"):
        set_flag(b, TRAINER_FLAGS + SYNDICATE[t])
    talk(OLIVINE, 15, 22, "RIGHT")
    advance(4, stop_in_battle=False)       # three welcome pages, then the menu opens
    for _ in range(2):                     # Board the line, Circuit report, Crisis briefing
        b.press("DOWN", 4)
        b.step(15)
    b.press("A", 4)
    advance(8)
    check("chairman call starts a battle", wait_battle())
    check("chairman fight can be won", win_battle())
    advance(8, stop_in_battle=False)
    check("beating the chairman resolves the crisis", b.flag(FLAG_CRISIS_RESOLVED))


def test_station() -> None:
    clear_badges()
    badges(2)
    set_flag(b, FLAG_FIELD_KIT)
    talk(OLIVINE, 15, 22, "RIGHT")
    advance(4, stop_in_battle=False)       # three welcome pages, then the menu opens
    b.press("A", 4)                        # Board the line
    advance(3, stop_in_battle=False)       # "All aboard", then the ride
    b.step(600)
    check("boarding the line arrives at Meridian Station", b.player_position()[2:] == STATION)
    warp_player(b, STATION[0], STATION[1], 9, 8)
    b.step(300)
    b.press("DOWN", 10)                    # onto the Johto platform gate
    advance(2, stop_in_battle=False)
    b.press("A", 4)                        # yes
    advance(3, stop_in_battle=False)
    b.step(600)
    check("the Johto platform leads back to Olivine City", b.player_position()[2:] == OLIVINE)


def test_apex() -> None:
    clear_badges()
    badges(24)
    strong_mon()
    talk(SILVER_CAVE_OUTSIDE, 23, 21, "RIGHT")
    advance(6, stop_in_battle=False)
    b.step(600)
    check("the Apex warden leads to the Summit arena", b.player_position()[2:] == ARENA)
    # Fast-forward to Round 5 (final contender) so 1 win conquers the tournament
    b.w16(b.sb1() + 0x1510 + (0x40F9 - 0x4000) * 2, 4)
    talk(ARENA, 6, 8, "UP")
    advance(6)
    check("the Summit Champion battles", wait_battle())
    check("the Summit Champion can be beaten", win_battle())
    advance(10, stop_in_battle=False)
    b.step(600)
    advance(8, stop_in_battle=False)
    check("Apex victory sets the champion flag", b.flag(FLAG_APEX_CHAMPION))
    check("Apex victory leads to the Hall of Fame", b.player_position()[2:] == HALL_OF_FAME)


TESTS = {"kit": test_kit, "station": test_station, "enforcer": test_enforcer, "chairman": test_chairman, "apex": test_apex}

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--only", default=",".join(TESTS))
    args = ap.parse_args()
    START_STATE = Path(__file__).parent / "states" / "stage0_start.ss1"
    for name in args.only.split(","):
        print(f"== {name}")
        if START_STATE.exists():           # every test starts from the same new game
            b.send(f"LOADFILE {START_STATE}")
            b.step(60)
            set_options()
        TESTS[name]()
    sys.exit(1 if failures else 0)
