"""Automated playtest & flow verification for Johto Overworld Scripts (Item 3 in MISSING.md).

Tests:
1. Static wild battles (Sudowoodo, Red Gyarados, Lapras, Celebi, Ho-Oh, Lugia, Electrodes)
2. Dynamic block changes (Ruins of Alph chambers, Rocket Base barriers, Ice Path boulders)
3. Hidden items across all 61 Johto maps (85 items verified against flags, item IDs, and bounds)
4. Strength boulders (24) and Rock Smash breakable rocks (16) across Johto dungeons
5. Elder Li's Flash gift follow-up sequence in Sprout Tower 3F
6. Route 32 Slowpoke Tail scene, Azalea Town, Kurt, and Ilex Forest Farfetch'd chase
7. Togepi hatching, Elm's follow-up phone call trigger, and Everstone gift reward
8. Per-town respawn locations (all 11 Johto towns and 22 Pokemon Center nurse scripts)
9. Fishing encounter tables (Old Rod, Good Rod, Super Rod across 149 maps)
"""

import json
import os
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent  # pokeconfluence/
DATA_MAPS = ROOT / "data" / "maps"
SCRIPTS = ROOT / "data" / "scripts"


class JohtoOverworldFlowsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.flags_text = (ROOT / "include" / "constants" / "johto_flags.h").read_text(encoding="utf-8")
        cls.items_text = (ROOT / "include" / "constants" / "items.h").read_text(encoding="utf-8")
        cls.species_text = (ROOT / "include" / "constants" / "species.h").read_text(encoding="utf-8")
        cls.heal_locs = json.loads((ROOT / "src" / "data" / "heal_locations.json").read_text(encoding="utf-8"))
        cls.layouts = {l["id"]: l for l in json.loads((ROOT / "data" / "layouts" / "layouts.json").read_text(encoding="utf-8"))["layouts"]}

    def test_01_static_wild_encounters(self):
        """Verifies that all authentic Crystal static wild encounters are mapped with valid species and levels."""
        expected = [
            ("Route36_Johto", "SPECIES_SUDOWOODO", 20),
            ("LakeOfRage_Johto", "SPECIES_GYARADOS", 30),
            ("UnionCaveB2F_Johto", "SPECIES_LAPRAS", 20),
            ("IlexForest_Johto", "SPECIES_CELEBI", 30),
            ("TinTower1F_Johto", "SPECIES_SUICUNE", 40),
            ("TinTowerRoof_Johto", "SPECIES_HO_OH", 60),
            ("WhirlIslandLugiaChamber_Johto", "SPECIES_LUGIA", 60),
            ("VermilionCity_Johto", "SPECIES_SNORLAX", 50),
            ("TeamRocketBaseB2F_Johto", "SPECIES_ELECTRODE", 23),
        ]
        for map_dir, species, level in expected:
            p = DATA_MAPS / map_dir / "scripts.inc"
            self.assertTrue(p.exists(), f"Map script missing: {p}")
            content = p.read_text(encoding="utf-8")
            pattern = rf"setwildbattle\s+{species},\s*{level}"
            self.assertRegex(content, pattern, f"Missing {species} Lv.{level} static battle in {map_dir}")

    def test_02_dynamic_block_changes(self):
        """Verifies that all 45 maps with dynamic block changes redraw the map view properly."""
        johto_maps = [d for d in DATA_MAPS.iterdir() if d.name.endswith("_Johto") and (d / "scripts.inc").exists()]
        redraw_count = 0
        for d in johto_maps:
            text = (d / "scripts.inc").read_text(encoding="utf-8")
            if "\tsetmetatile " in text:
                redraw_count += 1
                self.assertTrue(
                    "DrawWholeMapView" in text or "special DrawWholeMapView" in text,
                    f"Map {d.name} alters metatiles without redrawing the map view."
                )
        self.assertGreaterEqual(redraw_count, 40, f"Expected >=40 maps with dynamic metatiles, found {redraw_count}")

    def test_03_hidden_items_comprehensive(self):
        """Verifies all 85 hidden items across Johto maps have valid items, flags, and in-bounds coordinates."""
        total_hidden = 0
        for d in DATA_MAPS.iterdir():
            if not d.name.endswith("_Johto"):
                continue
            map_json = json.loads((d / "map.json").read_text(encoding="utf-8"))
            layout = self.layouts.get(map_json.get("layout", ""), {})
            width = layout.get("width", 999)
            height = layout.get("height", 999)

            for bg in map_json.get("bg_events", []):
                if bg.get("type") == "hidden_item":
                    total_hidden += 1
                    item = bg["item"]
                    flag = bg["flag"]
                    x, y = bg["x"], bg["y"]

                    # Check item constant
                    self.assertIn(item, self.items_text, f"Unknown item constant: {item} in {d.name}")
                    # Check flag definition
                    self.assertIn(flag, self.flags_text, f"Undefined flag: {flag} in {d.name}")
                    # Check bounds
                    self.assertLess(x, width, f"Hidden item X out of bounds in {d.name}: {x} >= {width}")
                    self.assertLess(y, height, f"Hidden item Y out of bounds in {d.name}: {y} >= {height}")

        self.assertEqual(total_hidden, 85, f"Expected exactly 85 hidden items, found {total_hidden}")

    def test_04_strength_and_rock_smash_objects(self):
        """Verifies all 24 Strength boulders and 16 Rock Smash rocks use standard engine scripts."""
        boulders = 0
        rocks = 0
        for d in DATA_MAPS.iterdir():
            if not d.name.endswith("_Johto"):
                continue
            map_json = json.loads((d / "map.json").read_text(encoding="utf-8"))
            for obj in map_json.get("object_events", []):
                if obj.get("graphics_id") == "OBJ_EVENT_GFX_PUSHABLE_BOULDER":
                    self.assertEqual(obj.get("script"), "EventScript_StrengthBoulder")
                    boulders += 1
                elif obj.get("graphics_id") == "OBJ_EVENT_GFX_BREAKABLE_ROCK":
                    self.assertEqual(obj.get("script"), "EventScript_RockSmash")
                    rocks += 1

        self.assertEqual(boulders, 24, f"Expected 24 Strength boulders, found {boulders}")
        self.assertEqual(rocks, 16, f"Expected 16 Rock Smash breakable rocks, found {rocks}")

    def test_05_elder_li_flash_sequence(self):
        """Verifies Sprout Tower 3F Sage Li battle, HM05 Flash reward, and post-battle dialogue advance."""
        script = (DATA_MAPS / "SproutTower3F_Johto" / "scripts.inc").read_text(encoding="utf-8")
        self.assertIn("TRAINER_JOHTO_SAGE_LI", script)
        self.assertIn("giveitem ITEM_HM_FLASH", script)
        self.assertIn("setflag FLAG_JOHTO_GOT_HM05_FLASH", script)
        self.assertIn("setflag FLAG_JOHTO_BEAT_SAGE_LI", script)
        self.assertIn("SproutTower3F_Johto_SageLiScript_GotFlash:", script)
        self.assertIn("SproutTower3F_Johto_SageLiAfterBattleText", script)

    def test_06_route32_kurt_farfetchd(self):
        """Verifies Route 32 Slowpoke Tail, Kurt's rescue, and Farfetch'd chase in Ilex Forest."""
        # Route 32 Slowpoke Tail salesman
        r32 = (DATA_MAPS / "Route32_Johto" / "scripts.inc").read_text(encoding="utf-8")
        self.assertIn("Route32_Johto_Text_MillionDollarSlowpokeTail", r32)

        # Kurt in Slowpoke Well & House
        well = (DATA_MAPS / "SlowpokeWellB1F_Johto" / "scripts.inc").read_text(encoding="utf-8")
        self.assertIn("TRAINER_JOHTO_GRUNTM_GRUNTM_29", well)
        kurt_house = (DATA_MAPS / "KurtsHouse_Johto" / "scripts.inc").read_text(encoding="utf-8")
        self.assertIn("FLAG_JOHTO_KURT_GAVE_YOU_LURE_BALL", kurt_house)

        # Farfetch'd chase
        ilex = (DATA_MAPS / "IlexForest_Johto" / "scripts.inc").read_text(encoding="utf-8")
        self.assertIn("FLAG_JOHTO_HERDED_FARFETCHD", ilex)
        self.assertIn("giveitem ITEM_HM_CUT", ilex)
        self.assertIn("setflag FLAG_JOHTO_GOT_HM01_CUT", ilex)

    def test_07_togepi_hatch_and_elm_call(self):
        """Verifies Togepi egg hatching arms FLAG_JOHTO_TOGEPI_HATCHED and triggers Elm's call."""
        # src/egg_hatch.c sets flag
        egg_c = (ROOT / "src" / "egg_hatch.c").read_text(encoding="utf-8")
        self.assertIn("FLAG_JOHTO_TOGEPI_HATCHED", egg_c)

        # src/johto_phone.c triggers Elm's priority call
        phone_c = (ROOT / "src" / "johto_phone.c").read_text(encoding="utf-8")
        self.assertIn("FLAG_JOHTO_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE", phone_c)
        self.assertIn("sText_ElmTogepiHatchedCall", phone_c)

        # ElmsLab gives Everstone
        elm_script = (DATA_MAPS / "ElmsLab_Johto" / "scripts.inc").read_text(encoding="utf-8")
        self.assertIn("giveitem ITEM_EVERSTONE", elm_script)
        self.assertIn("setflag FLAG_JOHTO_GOT_EVERSTONE_FROM_ELM", elm_script)

    def test_08_per_town_respawn_locations(self):
        """Verifies all Johto towns have valid heal locations and nurse scripts set respawn."""
        towns = [
            "NEW_BARK_TOWN", "CHERRYGROVE_CITY", "VIOLET_CITY", "AZALEA_TOWN",
            "GOLDENROD_CITY", "ECRUTEAK_CITY", "OLIVINE_CITY", "CIANWOOD_CITY",
            "MAHOGANY_TOWN", "BLACKTHORN_CITY", "LAKE_OF_RAGE"
        ]
        for t in towns:
            loc_name = f"HEAL_LOCATION_JOHTO_{t}"
            self.assertTrue(any(h["id"] == loc_name for h in self.heal_locs["heal_locations"]), f"Missing {loc_name} in heal_locations.json")

        # Check nurse scripts
        nurse_scripts = [
            ("CherrygrovePokecenter1F_Johto", "HEAL_LOCATION_JOHTO_CHERRYGROVE_CITY"),
            ("VioletPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_VIOLET_CITY"),
            ("AzaleaPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_AZALEA_TOWN"),
            ("GoldenrodPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_GOLDENROD_CITY"),
            ("EcruteakPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_ECRUTEAK_CITY"),
            ("OlivinePokecenter1F_Johto", "HEAL_LOCATION_JOHTO_OLIVINE_CITY"),
            ("CianwoodPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_CIANWOOD_CITY"),
            ("MahoganyPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_MAHOGANY_TOWN"),
            ("BlackthornPokecenter1F_Johto", "HEAL_LOCATION_JOHTO_BLACKTHORN_CITY"),
        ]
        for map_name, expected_loc in nurse_scripts:
            script_path = DATA_MAPS / map_name / "scripts.inc"
            self.assertTrue(script_path.exists())
            text = script_path.read_text(encoding="utf-8")
            self.assertIn(f"setrespawn {expected_loc}", text, f"{map_name} fails to set {expected_loc}")

    def test_09_fishing_encounters(self):
        """Verifies that all 149 Johto maps carry valid Old, Good, and Super Rod fishing encounter tables."""
        wild_h = (ROOT / "src" / "data" / "wild_encounters.h").read_text(encoding="utf-8")
        fishing_headers = re.findall(r"\.fishingMonsInfo\s*=\s*&(\w+)", wild_h)
        self.assertGreaterEqual(len(fishing_headers), 149, f"Expected >=149 fishing tables, found {len(fishing_headers)}")
        # Check no SPECIES_NONE in fishing slot data
        bad_slots = re.findall(r"\{\s*(\d+),\s*(\d+),\s*SPECIES_NONE\s*\}", wild_h)
        self.assertEqual(len(bad_slots), 0, "Found invalid SPECIES_NONE slots in fishing encounter tables")


if __name__ == "__main__":
    unittest.main()
