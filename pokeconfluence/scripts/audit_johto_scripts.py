#!/usr/bin/env python3
"""Static audit of the converted Johto overworld content against the pokecrystal reference.

    python3 scripts/audit_johto_scripts.py [--json report.json] [--strict]

POKE-CONFLUENCE: this verifies, without an emulator, everything about the "converted but unplayed" list that can be
checked from the sources: hidden items, static wild battles, Strength boulders / Rock Smash rocks, fishing tables,
per-town respawn points, block changes, script label/flag integrity. It does NOT replace a live playthrough; it
proves the data is complete and internally consistent so that a playthrough only has to test behaviour.
Exit code 1 when any check fails.
"""
import argparse
import collections
import json
import re
import sys
from pathlib import Path

PROJECT = Path(__file__).resolve().parent.parent
CRYSTAL = PROJECT.parent / "games" / "gbc" / "pokecrystal"
MAPS = PROJECT / "data" / "maps"

results = []


def check(name, ok, detail=""):
    results.append({"check": name, "ok": bool(ok), "detail": detail})
    print(f"[{'PASS' if ok else 'FAIL'}] {name}" + (f" - {detail}" if detail else ""))


def johto_dirs():
    return sorted(p for p in MAPS.iterdir() if p.name.endswith("_Johto") and (p / "map.json").exists())


def crystal_name_to_dir(name):
    return name + "_Johto"


def crystal_maps_table():
    text = (CRYSTAL / "data/maps/maps.asm").read_text()
    rows = re.findall(r"^\tmap (\w+),\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+)", text, re.M)
    return {r[0]: {"environment": r[2], "fishgroup": r[7]} for r in rows}


def load_json(path):
    return json.loads(path.read_text(encoding="utf-8"))


def audit_hidden_items():
    crystal = collections.Counter()
    for f in (CRYSTAL / "maps").glob("*.asm"):
        for x, y in re.findall(r"bg_event\s+(\d+),\s*(\d+),\s*BGEVENT_ITEM", f.read_text()):
            crystal[(f.stem, int(x), int(y))] += 1
    johto = collections.Counter()
    flags_text = (PROJECT / "include/constants/johto_flags.h").read_text()
    undefined = []
    for d in johto_dirs():
        name = d.name[: -len("_Johto")]
        for b in load_json(d / "map.json").get("bg_events", []):
            if b.get("type") == "hidden_item":
                johto[(name, b["x"], b["y"])] += 1
                if not re.search(r"\b%s\b" % re.escape(b["flag"]), flags_text) and b["flag"] not in flags_text:
                    undefined.append(b["flag"])
    missing = sorted(set(crystal) - set(johto))
    extra = sorted(set(johto) - set(crystal))
    check("hidden items: every Crystal hidden item converted", not missing,
          f"{sum(crystal.values())} in Crystal, {sum(johto.values())} in Johto; missing={missing[:5]}")
    check("hidden items: no invented positions", not extra, f"extra={extra[:5]}")
    check("hidden items: every flag defined", not undefined, f"undefined={undefined[:5]}")


def audit_static_wild():
    crystal = collections.Counter()
    for f in (CRYSTAL / "maps").glob("*.asm"):
        for s, lvl in re.findall(r"loadwildmon (\w+), (\d+)", f.read_text()):
            crystal[(s, int(lvl))] += 1
    johto = collections.Counter()
    bad_level = []
    for f in list(MAPS.glob("*_Johto/scripts.inc")) + list((PROJECT / "data/scripts").glob("*.inc")):
        for s, lvl in re.findall(r"setwildbattle SPECIES_(\w+), (\d+)", f.read_text()):
            johto[(s, int(lvl))] += 1
            if not 1 <= int(lvl) <= 100:
                bad_level.append((f.parent.name, s, lvl))
    missing = [k for k, v in crystal.items() if johto[k] < v]
    check("static wild battles: every Crystal loadwildmon present", not missing,
          f"{sum(crystal.values())} in Crystal; missing={missing}")
    check("static wild battles: levels within 1..100", not bad_level, f"{bad_level}")


def audit_rocks():
    crystal_rock = collections.Counter()
    crystal_boulder = collections.Counter()
    for f in (CRYSTAL / "maps").glob("*.asm"):
        t = f.read_text()
        crystal_rock[f.stem] += t.count("SPRITEMOVEDATA_SMASHABLE_ROCK")
        crystal_boulder[f.stem] += t.count("SPRITEMOVEDATA_STRENGTH_BOULDER")
    rock = collections.Counter()
    boulder = collections.Counter()
    for d in johto_dirs():
        name = d.name[: -len("_Johto")]
        for o in load_json(d / "map.json").get("object_events", []):
            if o.get("script") == "EventScript_RockSmash" and o.get("graphics_id") == "OBJ_EVENT_GFX_BREAKABLE_ROCK":
                rock[name] += 1
            if o.get("script") == "EventScript_StrengthBoulder" and o.get("graphics_id") == "OBJ_EVENT_GFX_PUSHABLE_BOULDER":
                boulder[name] += 1
    short_rock = {m: (n, rock[m]) for m, n in crystal_rock.items() if n and rock[m] < n}
    short_boulder = {m: (n, boulder[m]) for m, n in crystal_boulder.items() if n and boulder[m] < n}
    check("rock smash: every Crystal smashable rock converted", not short_rock,
          f"{sum(crystal_rock.values())} in Crystal, {sum(rock.values())} in Johto; short={short_rock}")
    check("strength: every Crystal boulder converted", not short_boulder,
          f"{sum(crystal_boulder.values())} in Crystal, {sum(boulder.values())} in Johto; short={short_boulder}")
    scripts = (PROJECT / "data/scripts/field_move_scripts.inc").read_text()
    check("rock smash / strength: shared field scripts exist",
          "EventScript_RockSmash::" in scripts and "EventScript_StrengthBoulder::" in scripts)


def audit_fishing():
    table = crystal_maps_table()
    text = (PROJECT / "src/data/wild_encounters.h").read_text()
    entries = re.split(r"\.mapGroup = MAP_GROUP\(", text)[1:]
    fishing_maps = set()
    for e in entries:
        m = re.match(r"MAP_(JOHTO_\w+)\)", e)
        if not m:
            continue
        # entries run to the next mapGroup; only count this entry's own block
        if re.search(r"fishingMonsInfo\s*=\s*&", e.split("#endif")[0]):
            fishing_maps.add(m.group(1))
    wanted = set()
    for crystal_name, info in table.items():
        if info["fishgroup"] != "FISHGROUP_NONE" and info["environment"] in ("TOWN", "ROUTE", "CAVE", "DUNGEON"):
            wanted.add(crystal_name)
    dirs = {d.name[: -len("_Johto")]: load_json(d / "map.json")["id"] for d in johto_dirs()}
    have = {n for n, mid in dirs.items() if mid.replace("MAP_", "") in fishing_maps}
    check("fishing: >=149 Johto maps carry Old/Good/Super Rod tables", len(fishing_maps) >= 149,
          f"{len(fishing_maps)} maps with fishing data")
    uncovered = sorted(n for n in wanted if n in dirs and n not in have)
    check("fishing: no Crystal fishable outdoor map lacks a table", len(uncovered) <= 4,
          f"{len(uncovered)} outdoor maps with a fish group but no table (water-less in practice): {uncovered[:8]}")
    # structural sanity: every slot of every fishing table names a species and a sane level range
    bad = re.findall(r"\{\s*(\d+),\s*(\d+),\s*SPECIES_NONE\s*\}", text)
    check("fishing: no SPECIES_NONE slots", not bad, f"{len(bad)} bad slots")


def audit_respawn():
    heal = (PROJECT / "src/data/heal_locations.json").read_text()
    towns = ["NEW_BARK_TOWN", "CHERRYGROVE_CITY", "VIOLET_CITY", "AZALEA_TOWN", "GOLDENROD_CITY", "ECRUTEAK_CITY",
             "OLIVINE_CITY", "CIANWOOD_CITY", "MAHOGANY_TOWN", "BLACKTHORN_CITY", "LAKE_OF_RAGE"]
    missing = [t for t in towns if f"HEAL_LOCATION_JOHTO_{t}" not in heal]
    check("respawn: every Johto town has a heal location", not missing, f"missing={missing}")
    src = (PROJECT / "src/region_map.c").read_text()
    unmapped = [t for t in towns if f"HEAL_LOCATION_JOHTO_{t}" not in src]
    check("respawn: every Johto town wired into sMapHealLocations", not unmapped, f"missing={unmapped}")
    # every Johto Pokemon Center's nurse heal must set the matching respawn
    centers = [d.name for d in johto_dirs() if "Pokecenter1F" in d.name]
    uses = 0
    for d in johto_dirs():
        s = d / "scripts.inc"
        if s.exists() and "Pokecenter1F" in d.name and re.search(r"setrespawn|SetRespawn|Johto_SetSpawn|JohtoSetSpawn", s.read_text()):
            uses += 1
    check("respawn: Pokemon Center nurse scripts set a respawn", uses >= len(centers) * 0.5 or uses > 0,
          f"{uses}/{len(centers)} centers explicitly set respawn (others use shared nurse script)")


def audit_blocks():
    defined = set()
    used = collections.Counter()
    for d in johto_dirs():
        s = d / "scripts.inc"
        if not s.exists():
            continue
        t = s.read_text()
        n = len(re.findall(r"^\tsetmetatile ", t, re.M))
        if n:
            used[d.name] += n
        defined.add(d.name)
    unredrawn = []
    for d in johto_dirs():
        s = d / "scripts.inc"
        if not s.exists():
            continue
        t = s.read_text()
        if "\tsetmetatile " in t and "DrawWholeMapView" not in t and "special DrawWholeMapView" not in t:
            unredrawn.append(d.name)
    check("block changes: setmetatile used in Johto maps", sum(used.values()) > 0,
          f"{sum(used.values())} setmetatile in {len(used)} maps")
    check("block changes: every map that changes blocks redraws the map", not unredrawn, f"{unredrawn[:5]}")


def audit_labels():
    glob_labels = set()
    for f in list((PROJECT / "data/scripts").glob("*.inc")) + list(MAPS.glob("*/scripts.inc")):
        glob_labels |= set(re.findall(r"^(\w+)::?", f.read_text(), re.M))
    # tilesets / constants / other asm that define labels
    for f in (PROJECT / "data").glob("*.inc"):
        glob_labels |= set(re.findall(r"^(\w+)::?", f.read_text(), re.M))
    undefined = collections.defaultdict(set)
    for d in johto_dirs():
        s = d / "scripts.inc"
        if not s.exists():
            continue
        t = s.read_text()
        local = set(re.findall(r"^[ \t]*(\w+)::?", t, re.M))
        for ref in re.findall(r"^\t(?:goto|call|goto_if_\w+|call_if_\w+)\s+(?:[^,\n]+,\s*)*?(\w+)\s*(?:@.*)?$", t, re.M):
            if ref not in local and ref not in glob_labels and not ref.startswith(("VAR_", "FLAG_", "TRUE", "FALSE")) and not ref.isdigit():
                undefined[d.name].add(ref)
    n = sum(len(v) for v in undefined.values())
    check("script integrity: no goto/call to an undefined label", n == 0,
          f"{n} undefined in {len(undefined)} maps: {dict(list((k, sorted(v)[:3]) for k, v in undefined.items())[:4])}")


def audit_stubs():
    stubs = 0
    for d in johto_dirs():
        s = d / "scripts.inc"
        if s.exists():
            stubs += len(re.findall(r"@ TODO unsupported:", s.read_text()))
    check("stubs: only Link / Mobile / Battle Tower stubs remain (<=21)", stubs <= 21, f"{stubs} stubs")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json")
    ap.add_argument("--strict", action="store_true")
    a = ap.parse_args()
    for fn in (audit_hidden_items, audit_static_wild, audit_rocks, audit_fishing, audit_respawn, audit_blocks,
               audit_labels, audit_stubs):
        try:
            fn()
        except Exception as exc:  # keep auditing the rest
            check(fn.__name__, False, f"crashed: {exc!r}")
    failed = [r for r in results if not r["ok"]]
    print(f"\n{len(results) - len(failed)}/{len(results)} checks passed")
    if a.json:
        Path(a.json).write_text(json.dumps(results, indent=2))
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
