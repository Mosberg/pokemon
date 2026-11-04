"""Battle state extraction for pokemultiregion (pokeemerald-expansion layout)."""
import struct
from typing import Any, Callable, Dict

from addresses import BATTLE_MON, BATTLE_MON_SIZE, MAIN_IN_BATTLE_BIT, MAIN_IN_BATTLE_BYTE, SYMBOLS

OUTCOMES = {0: "ongoing", 1: "won", 2: "lost", 3: "drew", 4: "ran", 5: "teleported",
            6: "mon_fled", 7: "caught", 8: "no_safari_balls", 9: "forfeited", 10: "mon_teleported"}

STATUS1 = {"poison": 1 << 3, "burn": 1 << 4, "freeze": 1 << 5, "paralysis": 1 << 6,
           "toxic": 1 << 7, "frostbite": 1 << 12}

ReadFn = Callable[[int, int], bytes]


def parse_battle_mon(raw: bytes, slot: int) -> Dict[str, Any]:
    o = BATTLE_MON
    species = struct.unpack_from("<H", raw, o["species"])[0]
    moves = list(struct.unpack_from("<4H", raw, o["moves"]))
    stages = list(struct.unpack_from("<8b", raw, o["stat_stages"]))   # HP, Atk, Def, Spe, SpA, SpD, Acc, Eva; 6 = neutral
    pp = list(raw[o["pp"]:o["pp"] + 4])
    hp, = struct.unpack_from("<H", raw, o["hp"])
    level = raw[o["level"]]
    max_hp, = struct.unpack_from("<H", raw, o["max_hp"])
    status1, = struct.unpack_from("<I", raw, o["status1"])
    return {
        "slot": slot, "species": species, "level": level,
        "current_hp": hp, "max_hp": max_hp, "hp_fraction": hp / max_hp if max_hp else 0.0,
        "moves": moves, "pp": pp, "stages": stages,
        "status": {"sleep_turns": status1 & 7, **{k: bool(status1 & v) for k, v in STATUS1.items()}},
    }


def get_battle_engine_state(read: ReadFn) -> Dict[str, Any]:
    """`read(address, length) -> bytes`. Works with Bridge.read or the headless core."""
    in_battle = bool((read(SYMBOLS["gMain"] + MAIN_IN_BATTLE_BYTE, 1)[0] >> MAIN_IN_BATTLE_BIT) & 1)
    if not in_battle:
        return {"in_battle": False}
    mons = read(SYMBOLS["gBattleMons"], BATTLE_MON_SIZE * 2)
    outcome = read(SYMBOLS["gBattleOutcome"], 1)[0]
    flags = struct.unpack("<I", read(SYMBOLS["gBattleTypeFlags"], 4))[0]
    return {
        "in_battle": True, "outcome": outcome, "outcome_name": OUTCOMES.get(outcome & 0x7F, "unknown"),
        "battle_type_flags": flags,
        "player": parse_battle_mon(mons[:BATTLE_MON_SIZE], 0),
        "opponent": parse_battle_mon(mons[BATTLE_MON_SIZE:], 1),
    }
