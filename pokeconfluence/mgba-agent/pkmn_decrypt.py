"""Decode a 100-byte struct Pokemon as laid out by pokeemerald-expansion (the pokemultiregion ROM).

Differences from the vanilla layout the reference document assumed: species, moves, held item and
experience are bit-packed (11/11/10/21 bits), and the plaintext party stats start at byte 80 with a
padding byte after the level (status u32 @80, level @84, hp @86, maxHP @88, atk @90 ...).
"""
import struct

BLOCK_ORDERS = [
    "GAEM", "GAME", "GEAM", "GEMA", "GMAE", "GMEA",
    "AGEM", "AGME", "AEGM", "AEMG", "AMGE", "AMEG",
    "EGAM", "EGMA", "EAGM", "EAMG", "EMGA", "EMAG",
    "MGAE", "MGEA", "MAGE", "MAEG", "MEGA", "MEAG",
]


def split_blocks(raw: bytes) -> dict:
    """Decrypt the 48-byte secure area and return {'G','A','E','M'} -> 12 bytes."""
    pid, otid = struct.unpack_from("<II", raw, 0)
    key = pid ^ otid
    plain = bytearray()
    for i in range(32, 80, 4):
        plain += struct.pack("<I", struct.unpack_from("<I", raw, i)[0] ^ key)
    order = BLOCK_ORDERS[pid % 24]
    return {ch: bytes(plain[i * 12:(i + 1) * 12]) for i, ch in enumerate(order)}


def decrypt_pokemon_data(raw: bytes) -> dict:
    if len(raw) < 100:
        raise ValueError("needs the full 100-byte struct Pokemon")
    pid, otid = struct.unpack_from("<II", raw, 0)
    blocks = split_blocks(raw)

    g0, g1, g2 = struct.unpack_from("<HHI", blocks["G"], 0)
    species = g0 & 0x7FF
    held_item = g1 & 0x3FF
    experience = g2 & 0x1FFFFF

    moves = [v & 0x7FF for v in struct.unpack_from("<HHHH", blocks["A"], 0)]
    pps = [b & 0x7F for b in blocks["A"][8:12]]

    evs = list(blocks["E"][0:6])
    iv_word = struct.unpack_from("<I", blocks["M"], 4)[0]
    ivs = {n: (iv_word >> (5 * i)) & 0x1F for i, n in enumerate(("hp", "atk", "def", "spd", "spatk", "spdef"))}
    is_egg = bool((iv_word >> 30) & 1)

    status, level, _mail, cur_hp, max_hp, atk, dfn, spd, spatk, spdef = struct.unpack_from("<IBBHHHHHHH", raw, 80)
    return {
        "personality": pid, "otid": otid,
        "species_id": species, "held_item": held_item, "experience": experience,
        "level": level, "current_hp": cur_hp, "max_hp": max_hp, "status_condition": status,
        "moves": moves, "pps": pps, "evs": evs, "ivs": ivs, "is_egg": is_egg,
        "stats": {"atk": atk, "def": dfn, "spd": spd, "spatk": spatk, "spdef": spdef},
    }


def encrypt_for_tests(pid: int, otid: int, species: int, moves, level: int, hp: int, max_hp: int) -> bytes:
    """Builds a minimal valid struct Pokemon; only used by the unit tests."""
    g = struct.pack("<HHI", species & 0x7FF, 0, 100) + bytes(4)
    a = struct.pack("<HHHH", *moves) + bytes([35, 35, 35, 35])
    e = bytes(12)
    m = struct.pack("<BBHI", 0, 0, 0, (31 | 31 << 5 | 31 << 10 | 31 << 15 | 31 << 20 | 31 << 25)) + bytes(4)
    order = BLOCK_ORDERS[pid % 24]
    parts = {"G": g, "A": a, "E": e, "M": m}
    plain = b"".join(parts[c] for c in order)
    key = pid ^ otid
    secure = b"".join(struct.pack("<I", struct.unpack_from("<I", plain, i)[0] ^ key) for i in range(0, 48, 4))
    header = struct.pack("<II", pid, otid) + bytes(24)
    tail = struct.pack("<IBBHHHHHHH", 0, level, 0, hp, max_hp, 10, 11, 12, 13, 14)
    return header + secure + tail
