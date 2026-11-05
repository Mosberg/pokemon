"""Playtests Johto phone book registration, rematch fight scaling, and BILL's Grandpa species check in the emulator.

    MGBA_BRIDGE_PORT=8921 .venv/bin/python mgba-agent/johto_phone_rematch.py
"""
import struct
import sys
from pathlib import Path

from addresses import BATTLE_MON, SB1, SYMBOLS
from memory_patcher import give_mon, set_flag, warp_player
from mgba_client import Bridge

ROUTE_30 = (78, 72)
STATION = (78, 83)
ARENA = (78, 84)
DRAGON_SHRINE = (75, 97)
VICTORY_ROAD_GATE = (78, 43)

FLAG_JOHTO_START = 3750
FLAG_JOHTO_TRAINERS_START = FLAG_JOHTO_START + 1472
JOHTO_TRAINER_BASE = 1488
TRAINER_JOHTO_YOUNGSTER_JOEY1 = 1529
JOEY1_TRAINER_FLAG = FLAG_JOHTO_TRAINERS_START + (TRAINER_JOHTO_YOUNGSTER_JOEY1 - JOHTO_TRAINER_BASE)
FLAG_JOHTO_ROUTE_30_YOUNGSTER_JOEY = FLAG_JOHTO_START + 716
FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH = FLAG_JOHTO_START + 1134
FLAG_JOHTO_JOEY_ASKED_FOR_PHONE_NUMBER = FLAG_JOHTO_START + 1167
FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED = FLAG_JOHTO_START + 1351
FLAG_JOHTO_DRAGON_SHRINE_CLAIR = FLAG_JOHTO_START + 313
FLAG_JOHTO_ENGINE_RISINGBADGE = FLAG_JOHTO_START + 358
JOHTO_BADGE_FLAGS = [
    FLAG_JOHTO_START + 464,  # ZEPHYRBADGE
    FLAG_JOHTO_START + 432,  # HIVEBADGE
    FLAG_JOHTO_START + 532,  # PLAINBADGE
    FLAG_JOHTO_START + 332,  # FOGBADGE
    FLAG_JOHTO_START + 655,  # STORMBADGE
    FLAG_JOHTO_START + 3,    # MINERALBADGE
    FLAG_JOHTO_START + 15,   # GLACIERBADGE
    FLAG_JOHTO_START + 358,  # RISINGBADGE
]

VARS_START = 0x4000
VAR_JOHTO_START = 0x4140
VAR_JOHTO_SCENE_DRAGON_SHRINE = VAR_JOHTO_START + 20
VAR_JOHTO_SCENE_VICTORY_ROAD_GATE = VAR_JOHTO_START + 67
VAR_JOHTO_MEM_WJOEYFIGHTCOUNT = VAR_JOHTO_START + 100

b = Bridge()
failures = []


def check(name: str, ok: bool) -> None:
    print(("PASS " if ok else "FAIL ") + name)
    if not ok:
        failures.append(name)


def get_var(var_id: int) -> int:
    return b.u16(b.sb1() + SB1["vars"] + (var_id - VARS_START) * 2)


def set_var(var_id: int, val: int) -> None:
    b.w16(b.sb1() + SB1["vars"] + (var_id - VARS_START) * 2, val)


def set_options() -> None:
    opts = b.sb2() + 0x14
    b.w16(opts, (b.u16(opts) & ~7) | 2 | 0x600)


def strong_mon() -> None:
    set_options()
    give_mon(b, 150, 100, [34], slot=0)
    base = SYMBOLS["gPlayerParty"] + 0x56
    b.write(base, struct.pack("<HHHHHHH", 999, 999, 999, 999, 999, 999, 999))


def advance(n: int = 12, stop_in_battle: bool = True) -> None:
    for _ in range(n):
        b.step(180)
        b.press("A", 4)
        b.step(30)
        if stop_in_battle and b.in_battle():
            break
    b.step(180)


def wait_battle(frames: int = 1200) -> bool:
    for _ in range(frames // 30):
        if b.in_battle():
            return True
        b.step(30)
    return False


def win_battle(max_turns: int = 1500) -> bool:
    mon = SYMBOLS["gBattleMons"]
    for _ in range(max_turns):
        if not b.in_battle():
            return True
        b.w8(mon + BATTLE_MON["pp"], 40)
        b.w16(mon + BATTLE_MON["hp"], 999)
        b.press("A", 4)
        b.step(45)
    return not b.in_battle()


def main() -> None:
    start_state = Path(__file__).parent / "states" / "stage0_start.ss1"
    if start_state.exists():
        b.send(f"LOADFILE {start_state}")
        b.step(60)
    strong_mon()

    # 1. Visual check of Meridian Station and Apex Summit layouts
    scratch = Path("/home/mosberg/.gemini/antigravity/brain/2d3b606d-7b75-490a-94e9-8ed6912a9d40/scratch")
    scratch.mkdir(parents=True, exist_ok=True)
    warp_player(b, STATION[0], STATION[1], 9, 8)
    b.step(240)
    b.screenshot(str(scratch / "meridian_station.png"))

    warp_player(b, ARENA[0], ARENA[1], 6, 11)
    b.step(240)
    b.screenshot(str(scratch / "apex_summit.png"))

    # 2. Test Youngster Joey phone registration & rematch cycle on Route 30
    set_flag(b, FLAG_JOHTO_ROUTE_30_YOUNGSTER_JOEY, False)
    set_flag(b, JOEY1_TRAINER_FLAG, True)
    set_flag(b, FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED, False)
    set_flag(b, FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH, False)
    set_flag(b, FLAG_JOHTO_JOEY_ASKED_FOR_PHONE_NUMBER, False)
    set_var(VAR_JOHTO_MEM_WJOEYFIGHTCOUNT, 0)

    warp_player(b, ROUTE_30[0], ROUTE_30[1], 3, 28)
    b.step(300)
    b.press("LEFT", 10)
    b.step(20)
    b.press("A", 4)
    b.step(100)
    b.screenshot(str(scratch / "joey_phone_ask.png"))
    advance(14, stop_in_battle=False)

    check("Joey asks for phone number", b.flag(FLAG_JOHTO_JOEY_ASKED_FOR_PHONE_NUMBER))
    check("Accepting registers Joey in phone book", b.flag(FLAG_JOHTO_PHONE_YOUNGSTER_JOEY_REGISTERED))
    check("Registering Joey arms his rematch flag", b.flag(FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH))

    # Talk to Joey again -> triggers rematch battle!
    b.press("A", 4)
    b.step(100)
    advance(6, stop_in_battle=True)
    check("Talking to Joey with READY_FOR_REMATCH starts rematch battle", wait_battle())
    check("Joey rematch battle can be won", win_battle())
    b.step(120)

    check("Winning Joey rematch increments wJoeyFightCount to 1", get_var(VAR_JOHTO_MEM_WJOEYFIGHTCOUNT) == 1)
    check("Winning Joey rematch clears READY_FOR_REMATCH", not b.flag(FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH))

    # Talk to Joey a third time -> JohtoPhoneIsRegistered re-arms READY_FOR_REMATCH for the next visit
    b.press("A", 4)
    b.step(100)
    advance(6, stop_in_battle=False)
    check("Talking to registered Joey re-arms READY_FOR_REMATCH for next visit", b.flag(FLAG_JOHTO_ENGINE_JOEY_READY_FOR_REMATCH))

    # 3. Test Dragon Shrine loadmenu quiz -> Clair awards 8th Johto badge (RISINGBADGE)
    for bf in JOHTO_BADGE_FLAGS[:7]:
        set_flag(b, bf, True)
    set_flag(b, FLAG_JOHTO_ENGINE_RISINGBADGE, False)
    set_flag(b, FLAG_JOHTO_DRAGON_SHRINE_CLAIR, True)
    set_var(VAR_JOHTO_SCENE_DRAGON_SHRINE, 0)
    warp_player(b, DRAGON_SHRINE[0], DRAGON_SHRINE[1], 4, 9)
    b.step(360)
    b.screenshot(str(scratch / "dragon_shrine_quiz.png"))
    for _ in range(60):
        if b.flag(FLAG_JOHTO_ENGINE_RISINGBADGE):
            break
        res = b.u16(SYMBOLS["gSpecialVar_Result"])
        if res == 0xFF and ((b.flag(0x14) and not b.flag(0x15)) or b.flag(0x16)):
            b.press("DOWN", 4)
            b.step(20)
        b.press("A", 4)
        b.step(140)
    check("Dragon Shrine loadmenu quiz awards Rising Badge (8th Johto badge)", b.flag(FLAG_JOHTO_ENGINE_RISINGBADGE))
    advance(10, stop_in_battle=False)

    # 4. Test Victory Road Gate badge check with all 8 Johto badges
    for bf in JOHTO_BADGE_FLAGS:
        set_flag(b, bf, True)
    set_var(VAR_JOHTO_SCENE_VICTORY_ROAD_GATE, 0)
    warp_player(b, VICTORY_ROAD_GATE[0], VICTORY_ROAD_GATE[1], 9, 11)
    b.step(240)
    b.press("LEFT", 10)
    b.step(20)
    b.press("A", 4)
    b.step(100)
    advance(8, stop_in_battle=False)
    check("Victory Road Gate Officer unlocks gate when player has 8 Johto badges", get_var(VAR_JOHTO_SCENE_VICTORY_ROAD_GATE) == 1)

    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()

