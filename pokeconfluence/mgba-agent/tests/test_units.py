"""Offline tests (stdlib only):  python -m unittest discover -s tests -v   (run from mgba-agent/)"""
import os
import struct
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from addresses import BATTLE_MON, BATTLE_MON_SIZE, FLAGS, KANTO_START, SYMBOLS  # noqa: E402
from battle_engine import get_battle_engine_state, parse_battle_mon  # noqa: E402
from pathfinding import MAP_OFFSET, a_star_search, read_collision_map  # noqa: E402
from pkmn_decrypt import BLOCK_ORDERS, decrypt_pokemon_data, encrypt_for_tests  # noqa: E402


class DecryptTests(unittest.TestCase):
    def test_roundtrip_all_24_block_orders(self):
        for pid in range(24):                        # pid % 24 selects the block order
            raw = encrypt_for_tests(pid + 24 * 1000, 0x12345678, 252, (33, 45, 98, 0), 17, 40, 55)
            mon = decrypt_pokemon_data(raw)
            self.assertEqual(mon["species_id"], 252, BLOCK_ORDERS[pid])
            self.assertEqual(mon["moves"], [33, 45, 98, 0])
            self.assertEqual((mon["level"], mon["current_hp"], mon["max_hp"]), (17, 40, 55))
            self.assertEqual(mon["ivs"]["hp"], 31)
            self.assertEqual(mon["stats"]["atk"], 10)

    def test_short_input_rejected(self):
        with self.assertRaises(ValueError):
            decrypt_pokemon_data(b"\0" * 99)


class BattleTests(unittest.TestCase):
    def _mon(self, species, hp, max_hp, level, status=0):
        raw = bytearray(BATTLE_MON_SIZE)
        struct.pack_into("<H", raw, BATTLE_MON["species"], species)
        struct.pack_into("<4H", raw, BATTLE_MON["moves"], 33, 0, 0, 0)
        struct.pack_into("<8b", raw, BATTLE_MON["stat_stages"], 6, 6, 6, 6, 6, 6, 6, 6)
        struct.pack_into("<H", raw, BATTLE_MON["hp"], hp)
        raw[BATTLE_MON["level"]] = level
        struct.pack_into("<H", raw, BATTLE_MON["max_hp"], max_hp)
        struct.pack_into("<I", raw, BATTLE_MON["status1"], status)
        return bytes(raw)

    def test_parse(self):
        m = parse_battle_mon(self._mon(25, 20, 40, 12, status=1 << 6), 0)
        self.assertEqual((m["species"], m["level"], m["hp_fraction"]), (25, 12, 0.5))
        self.assertTrue(m["status"]["paralysis"])
        self.assertFalse(m["status"]["burn"])

    def test_state_via_fake_memory(self):
        mem = {SYMBOLS["gMain"] + 0x439: bytes([2]),                       # inBattle bit set
               SYMBOLS["gBattleMons"]: self._mon(25, 20, 40, 12) + self._mon(19, 5, 10, 3),
               SYMBOLS["gBattleOutcome"]: bytes([0]), SYMBOLS["gBattleTypeFlags"]: struct.pack("<I", 8)}

        def read(addr, n):
            for base, data in mem.items():
                if base <= addr < base + len(data):
                    return (data[addr - base:] + b"\0" * n)[:n]
            return b"\0" * n
        state = get_battle_engine_state(read)
        self.assertTrue(state["in_battle"])
        self.assertEqual(state["opponent"]["species"], 19)
        self.assertEqual(state["outcome_name"], "ongoing")


class PathTests(unittest.TestCase):
    def test_straight_and_detour(self):
        self.assertEqual(a_star_search((0, 0), (3, 0), set(), (5, 5)), ["RIGHT"] * 3)
        path = a_star_search((0, 0), (2, 0), {(1, 0)}, (5, 5))
        self.assertEqual(len(path), 4)
        self.assertIsNone(a_star_search((0, 0), (2, 0), {(1, 0), (1, 1), (1, 2), (1, 3), (1, 4)}, (3, 5)))

    def test_goal_may_be_blocked(self):
        self.assertEqual(a_star_search((0, 0), (1, 0), {(1, 0)}, (3, 3)), ["RIGHT"])

    def test_collision_map(self):
        width, height = 4 + 2 * MAP_OFFSET, 3 + 2 * MAP_OFFSET
        cells = [0] * (width * height)
        cells[(1 + MAP_OFFSET) * width + (2 + MAP_OFFSET)] = 0x0400 | 0x123   # collision bit set at map (2, 1)
        ptr = 0x02030000
        layout = struct.pack("<iiI", width, height, ptr)
        blob = struct.pack(f"<{len(cells)}H", *cells)

        def read(addr, n):
            if addr == SYMBOLS["gBackupMapLayout"]:
                return layout
            return blob[addr - ptr:addr - ptr + n]
        blocked, bounds = read_collision_map(read)
        self.assertEqual(bounds, (4, 3))
        self.assertIn((2, 1), blocked)
        self.assertEqual(len(blocked), 1)


class FlagTests(unittest.TestCase):
    def test_flag_ids(self):
        self.assertEqual(FLAGS["BADGE01_GET"], 0x867)
        self.assertEqual(FLAGS["BADGE08_GET"], 0x86E)
        self.assertEqual(FLAGS["BADGE09_GET"], KANTO_START + 1)
        self.assertEqual(FLAGS["BADGE16_GET"], KANTO_START + 8)
        self.assertLess(FLAGS["BADGE16_GET"] // 8, 300 + 92)      # inside the enlarged flag array


if __name__ == "__main__":
    unittest.main()
