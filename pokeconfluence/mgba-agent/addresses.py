"""Memory map of pokemultiregion.gba (Emerald-based pokeemerald-expansion build, EMERALD mode).

The reference document used vanilla FireRed v1.0 offsets. Those do not match this ROM, so every
value below was taken from the real build: symbol addresses from `arm-none-eabi-nm pokemultiregion.elf`
and struct offsets from a probe compiled with the build's own flags. Re-run `refresh_addresses.py`
after rebuilding the ROM; it rewrites addresses.json, which overrides the defaults here.
"""
import json
from pathlib import Path

# --- Symbol addresses (EWRAM/IWRAM) -------------------------------------------------------
SYMBOLS = {
    "gMain": 0x030066D0,
    "gSaveBlock1Ptr": 0x030051D4,      # pointer: SaveBlock1 moves around, always dereference
    "gSaveBlock2Ptr": 0x030051D0,
    "gPlayerParty": 0x02031C40,        # 6 x struct Pokemon (100 bytes), decrypted view is in-place
    "gPlayerPartyCount": 0x02031C30,
    "gEnemyParty": 0x02031E98,
    "gEnemyPartyCount": 0x02031C31,
    "gBattleMons": 0x020004F0,         # 4 x struct BattlePokemon (140 bytes)
    "gBattleTypeFlags": 0x020000CC,    # u32
    "gBattleOutcome": 0x020000D8,      # u8
    "gBackupMapLayout": 0x03002510,    # {s32 width; s32 height; u16 *map}
    "sWarpDestination": 0x02031348,    # {s8 group; s8 num; s8 warpId; s16 x; s16 y}
    "gSpecialVar_Result": 0x0200156E,
    "gAiBridgeMailbox": 0x02000004,    # struct AiBridgeMailbox, see pokemultiregion/include/ai_bridge.h
    "CB2_LoadMap": 0x08190B38,
    "CB2_Overworld": 0x08193CD0,
}

# --- Struct offsets -----------------------------------------------------------------------
MAIN_IN_BATTLE_BYTE = 0x439            # gMain+0x439, bit 1 (oamLoadDisabled is bit 0)
MAIN_IN_BATTLE_BIT = 1
MAIN_CALLBACK2 = 0x004

SB1 = {
    "pos_x": 0x000, "pos_y": 0x002,    # s16 each
    "map_group": 0x004, "map_num": 0x005,
    "money": 0x490,                    # u32, XOR with SaveBlock2.encryptionKey
    "bag_items": 0x560, "bag_key_items": 0x5D8, "bag_poke_balls": 0x650,
    "bag_tms_hms": 0x690, "bag_berries": 0x790,
    "flags": 0x123C,                   # 723 bytes (300 original + Kanto band + 624 Kanto trainer flags + 1472 Johto event flags + 560 Johto trainer flags); FREE_* options moved it
    "vars": 0x1510,
}
SB2 = {"player_gender": 0x08, "encryption_key": 0xAC}

BAG_POCKETS = {            # name -> (offset in SaveBlock1, slot count)
    "items": (SB1["bag_items"], 30), "key_items": (SB1["bag_key_items"], 30),
    "poke_balls": (SB1["bag_poke_balls"], 16), "tms_hms": (SB1["bag_tms_hms"], 64),
    "berries": (SB1["bag_berries"], 46),
}

MON_SIZE = 100
BATTLE_MON_SIZE = 140
BATTLE_MON = {"species": 0, "moves": 12, "stat_stages": 24, "pp": 37, "hp": 42,
              "level": 44, "max_hp": 46, "status1": 80}

# --- Event flags (flag id -> byte SB1.flags + id//8, bit id%8) -----------------------------
SYSTEM_FLAGS = 0x860
KANTO_START = 0x960
FLAGS = {
    "POKEMON_GET": SYSTEM_FLAGS + 0x0,
    "POKEDEX_GET": SYSTEM_FLAGS + 0x1,
    **{f"BADGE{i:02d}_GET": SYSTEM_FLAGS + 0x6 + i for i in range(1, 9)},     # Hoenn badges 1-8
    **{f"BADGE{i:02d}_GET": KANTO_START + (i - 8) for i in range(9, 17)},    # Kanto badges 9-16
}

_override = Path(__file__).with_name("addresses.json")
if _override.exists():
    SYMBOLS.update({k: int(v) for k, v in json.loads(_override.read_text()).get("symbols", {}).items()})
