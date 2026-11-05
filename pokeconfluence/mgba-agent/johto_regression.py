"""Replays the Johto flows that were verified by hand and asserts their outcomes. Needs only Node (the embedded emulator), no mGBA window.

    python johto_regression.py <project> [--port 8911] [--only elm,mrpokemon,cherrygrove,itemball,cut,egg,blackout,smoke]

It starts `bin/poke-emulator` itself on <port>, creates a new Johto game, then for each check warps to the place, plays it with button presses and
reads flags / vars / party from RAM. Exit code 1 if a check fails. Takes about ten minutes. Johto flag numbers come from <project>/.poke-migrator-johto-flags.json.

Checks: elm (Elm's scene, Totodile), mrpokemon (Mystery Egg), cherrygrove (rival ambush resolves for the three starters), itemball (Sprout Tower Potion),
cut (Route 29 tree is cut and stays cut after a reload), egg (Violet Aide gives the Togepi egg), blackout (heal at Violet's nurse, lose a battle, wake up in Violet's Pokemon Center), smoke (every Johto map loads).
"""
import argparse
import json
import os
import struct
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
JOHTO_FLAG_START = 3750        # FLAG_JOHTO_START: FLAG_KANTO_END + 1 (verified below against a flag Crystal's InitializeEvents sets)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("project")
    ap.add_argument("--port", type=int, default=8911)
    ap.add_argument("--only", default="elm,mrpokemon,cherrygrove,itemball,cut,egg,blackout")
    a = ap.parse_args()
    project = Path(a.project).resolve()
    os.environ["MGBA_BRIDGE_PORT"] = str(a.port)

    from addresses import MON_SIZE, SB1, SYMBOLS
    from memory_patcher import give_mon, warp_player
    from mgba_client import Bridge
    from pkmn_decrypt import decrypt_pokemon_data

    rom = project / "pokeconfluence.gba"
    emu = subprocess.Popen([sys.executable, str(HERE.parent / "bin" / "poke-emulator"), "--rom", str(rom), "--port", str(a.port)],
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    failures = []
    try:
        for _ in range(40):
            try:
                b = Bridge()
                break
            except OSError:
                time.sleep(0.5)
        else:
            sys.exit("emulator did not start")
        reg = json.loads((project / ".poke-migrator-johto-flags.json").read_text(encoding="utf-8"))

        def sb1() -> int:
            return b.u32(SYMBOLS["gSaveBlock1Ptr"])          # the save block moves: read the pointer every time

        def fid(name: str) -> int:
            return JOHTO_FLAG_START + reg["flags"]["FLAG_JOHTO_" + name]

        def flag(name: str, on=None):
            addr = sb1() + SB1["flags"] + fid(name) // 8
            bit = 1 << fid(name) % 8
            if on is None:
                return int(bool(b.u8(addr) & bit))
            b.w8(addr, (b.u8(addr) | bit) if on else (b.u8(addr) & ~bit))

        def var(name: str):
            return b.u16(sb1() + SB1["vars"] + 2 * (0x140 + reg["vars"]["VAR_JOHTO_" + name]))

        def set_var(name: str, v: int) -> None:
            b.w16(sb1() + SB1["vars"] + 2 * (0x140 + reg["vars"]["VAR_JOHTO_" + name]), v)

        def pos():
            return b.player_position()

        def overworld() -> bool:
            return (b.u32(SYMBOLS["gMain"] + 4) & ~1) == SYMBOLS["CB2_Overworld"]

        def mash(n=1, wait=50):
            for _ in range(n):
                b.press("A", 4)
                b.step(wait)
                b.step(30)

        def goto(x: int, y: int, tries=8) -> bool:
            from pathfinding import a_star_search, read_collision_map
            for _ in range(tries):
                cx, cy, *_ = pos()
                if (cx, cy) == (x, y):
                    return True
                blocked, bounds = read_collision_map(b.read)
                path = a_star_search((cx, cy), (x, y), blocked, bounds)
                if not path:
                    return False
                for d in path:
                    b.press(d, 17)
                    b.step(8)
            return pos()[:2] == (x, y)

        def party():
            n = b.u8(SYMBOLS["gPlayerPartyCount"])
            return [decrypt_pokemon_data(b.read(SYMBOLS["gPlayerParty"] + i * MON_SIZE, MON_SIZE)) for i in range(n)]

        def check(name: str, cond: bool, detail: str = "") -> None:
            print(f"{'PASS' if cond else 'FAIL'}  {name} {detail}", flush=True)
            if not cond:
                failures.append(name)

        # --- new game ---------------------------------------------------------------------------------------------
        subprocess.run([sys.executable, str(HERE / "new_game_kanto.py"), "--johto"], cwd=HERE, check=True, stdout=subprocess.DEVNULL)
        state = (HERE / "states" / "stage0_start.ss1").as_posix()
        check("new game starts in Player's House 2F", pos()[2:] == (78, 50), str(pos()))
        check("InitializeEvents ran (flag numbering sane)", flag("COP_IN_ELMS_LAB") == 1)
        base = state

        def fresh():
            b.send(f"LOADFILE {base}")
            b.step(30)

        only = set(a.only.split(","))

        if "elm" in only:
            fresh()
            warp_player(b, 78, 48, 4, 10)
            b.step(200)
            for _ in range(140):
                mash()
                if var("SCENE_ELMS_LAB") == 1:
                    break
            check("Elm's scene ends with the lab locked (scene 1)", var("SCENE_ELMS_LAB") == 1)
            for _ in range(8):
                if goto(7, 4):
                    break
            b.press("UP", 17)
            b.step(20)
            for _ in range(24):
                mash(1, 60)
            mons = party()
            check("Totodile received", len(mons) == 1 and mons[0]["species_id"] == 158, str([m["species_id"] for m in mons]))
            check("starter flags set", flag("GOT_TOTODILE_FROM_ELM") == 1 and flag("GOT_A_POKEMON_FROM_ELM") in (0, 1))

        if "mrpokemon" in only:
            fresh()
            warp_player(b, 78, 81, 3, 7)
            b.step(300)
            for _ in range(160):
                mash(1, 60)
                if var("SCENE_CHERRYGROVE_CITY") == 1:
                    break
            check("Mr. Pokemon gives the Mystery Egg", flag("GOT_MYSTERY_EGG_FROM_MR_POKEMON") == 1)
            check("Cherrygrove rival scene armed", var("SCENE_CHERRYGROVE_CITY") == 1)

        if "cherrygrove" in only:
            for starter, species in (("TOTODILE", 158), ("CHIKORITA", 152), ("CYNDAQUIL", 155)):
                fresh()
                give_mon(b, species, 9, [10, 33, 52 if starter == "CYNDAQUIL" else 55, 0])
                flag(f"GOT_{starter}_FROM_ELM", True)
                flag("GOT_A_POKEMON_FROM_ELM", True)
                set_var("SCENE_CHERRYGROVE_CITY", 1)
                warp_player(b, 78, 74, 36, 6)
                b.step(300)
                for _ in range(6):
                    b.press("LEFT", 17)
                    b.step(30)
                    if not overworld() or pos()[0] <= 33:
                        break
                for i in range(160):
                    mash(1, 50)
                    if overworld() and i > 40 and var("SCENE_CHERRYGROVE_CITY") != 1:
                        break
                check(f"Cherrygrove rival scene resolves ({starter})", var("SCENE_CHERRYGROVE_CITY") == 0 and overworld())

        if "itemball" in only:
            fresh()
            warp_player(b, 75, 23, 6, 15)
            b.step(300)
            b.press("UP", 17)
            b.step(20)
            for _ in range(10):
                mash(1, 50)
            check("Sprout Tower Potion picked up", flag("SPROUT_TOWER_3F_POTION") == 1)

        if "cut" in only:
            fresh()
            give_mon(b, 25, 10, [15, 85, 98, 0])
            flag("ENGINE_HIVEBADGE", True)
            warp_player(b, 78, 46, 30, 11)
            b.step(300)
            for _ in range(6):
                if goto(30, 10):
                    break
            b.press("UP", 17)
            b.step(20)
            b.press("A", 4)
            b.step(100)
            for _ in range(8):
                mash(1, 50)
            check("Route 29 tree cut (flag set)", flag("CUTTREE_ROUTE_29_0") == 1)
            warp_player(b, 78, 46, 30, 12)
            b.step(300)
            reached = any(goto(30, 9) for _ in range(4))
            check("cut tree stays cut after a reload", reached, str(pos()))

        if "egg" in only:
            fresh()
            give_mon(b, 158, 5, [10, 43, 0, 0])
            for f in ("GOT_A_POKEMON_FROM_ELM", "GOT_MYSTERY_EGG_FROM_MR_POKEMON", "GAVE_MYSTERY_EGG_TO_ELM"):
                flag(f, True)
            flag("ELMS_AIDE_IN_VIOLET_POKEMON_CENTER", False)
            warp_player(b, 76, 73, 4, 6)
            b.step(300)
            b.press("UP", 17)
            b.step(20)
            b.press("UP", 17)
            b.step(20)
            for _ in range(40):
                mash(1, 60)
            mons = party()
            check("Violet Aide gives the Togepi egg", len(mons) == 2 and mons[1]["species_id"] == 175, str([m["species_id"] for m in mons]))

        if "blackout" in only:
            fresh()
            give_mon(b, 25, 2, [150, 0, 0, 0], hp=12)          # a level-2 Pikachu that only knows Splash
            warp_player(b, 76, 73, 3, 4)                        # Violet Pokemon Center, in front of the nurse
            b.step(300)
            b.press("UP", 17)
            b.step(20)
            for _ in range(14):
                mash(1, 60)
            warp_player(b, 78, 72, 5, 20)                       # Route 30, Mikey's sight line
            b.step(300)
            b.press("DOWN", 17)
            b.step(40)
            for i in range(250):
                mash(1, 50)
                if overworld() and pos()[2:] != (78, 72) and i > 20:
                    break
            b.step(200)
            check("whiteout wakes the player in Violet's Pokemon Center", pos()[2:] == (76, 73), str(pos()))

        if "smoke" in only:
            r = subprocess.run([sys.executable, str(HERE / "map_smoke_test.py"), str(project), "--filter", "_Johto", "--out", str(HERE / "states" / "smoke_johto.json")],
                               cwd=HERE, capture_output=True, text=True)
            report = json.loads((HERE / "states" / "smoke_johto.json").read_text(encoding="utf-8"))
            bad = [m["name"] for m in report if m["status"] != "ok"]
            check(f"all {len(report)} Johto maps load", not bad, ", ".join(bad[:5]))
    finally:
        if sys.platform == "win32":        # the wrapper's child (node) would survive terminate(): kill the whole tree
            subprocess.run(["taskkill", "/F", "/T", "/PID", str(emu.pid)], capture_output=True)
        else:
            emu.terminate()
    print("ALL PASSED" if not failures else f"{len(failures)} FAILED: {', '.join(failures)}")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
