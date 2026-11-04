"""Warp into every map of a project and check the game survives it.

    python map_smoke_test.py ../pokemultiregion [--filter _Frlg] [--out report.json] [--state states/stage0_start.ss1]

Needs mGBA running the ROM with lua/mgba_agent_bridge.lua loaded. For each map it warps to the first warp tile
(or the map centre), runs 90 frames and records: whether the player really ended up on that map, whether the
main callback is still the overworld, and whether the screen is blank. Reloads the savestate when a map fails.
"""
import argparse
import hashlib
import json
import os
import sys
import tempfile
from pathlib import Path

from addresses import SYMBOLS
from memory_patcher import warp_player
from mgba_client import Bridge

SHOT = os.path.join(tempfile.gettempdir(), "mgba_smoke.png")


def load_maps(project: Path):
    groups = json.loads((project / "data/maps/map_groups.json").read_text(encoding="utf-8"))
    layouts = {l["id"]: l for l in json.loads((project / "data/layouts/layouts.json").read_text(encoding="utf-8"))["layouts"]}
    for gi, g in enumerate(groups["group_order"]):
        for ni, name in enumerate(groups[g]):
            meta = json.loads((project / "data/maps" / name / "map.json").read_text(encoding="utf-8"))
            lay = layouts.get(meta.get("layout"), {})
            w, h = lay.get("width", 8), lay.get("height", 8)
            warps = meta.get("warp_events") or []
            x, y = (warps[0]["x"], warps[0]["y"]) if warps else (w // 2, h // 2)
            yield {"name": name, "group": gi, "num": ni, "x": min(x, w - 1), "y": min(y, h - 1)}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("project")
    ap.add_argument("--filter", default="")
    ap.add_argument("--out", default="map_smoke_report.json")
    ap.add_argument("--state", default=str(Path(__file__).parent / "states/stage0_start.ss1"))
    ap.add_argument("--frames", type=int, default=90)
    ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args()

    b = Bridge()
    state = os.path.abspath(a.state)
    b.send(f"LOADFILE {state}")
    b.step(60)
    maps = [m for m in load_maps(Path(a.project)) if a.filter in m["name"]]
    if a.limit:
        maps = maps[:a.limit]
    results, bad = [], 0
    for i, m in enumerate(maps, 1):
        try:
            warp_player(b, m["group"], m["num"], m["x"], m["y"])
            b.step(a.frames)
            x, y, g, n = b.player_position()
            cb2 = b.u32(SYMBOLS["gMain"] + 4) & ~1
            b.screenshot(SHOT)
            digest = hashlib.md5(Path(SHOT).read_bytes()).hexdigest()
            size = Path(SHOT).stat().st_size
            ok_map = (g, n) == (m["group"], m["num"])
            ok_cb = cb2 == SYMBOLS["CB2_Overworld"]
            blank = size < 700
            status = "ok" if ok_map and ok_cb and not blank else "FAIL"
            m.update(status=status, at=[x, y, g, n], callback2=hex(cb2), png_bytes=size, md5=digest)
        except Exception as exc:  # bridge hiccup counts as a failure of that map
            m.update(status="FAIL", error=str(exc))
        if m["status"] != "ok":
            bad += 1
            print(f"[{i}/{len(maps)}] FAIL {m['name']}: {m.get('at')} cb2={m.get('callback2')} {m.get('error', '')}")
            try:
                b.send(f"LOADFILE {state}")
                b.step(60)
            except Exception:
                pass
        results.append(m)
        if i % 25 == 0:
            print(f"[{i}/{len(maps)}] {bad} failures so far", flush=True)
            Path(a.out).write_text(json.dumps(results, indent=1))
    Path(a.out).write_text(json.dumps(results, indent=1))
    print(f"[+] {len(maps) - bad}/{len(maps)} maps loaded cleanly; report in {a.out}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
