"""Answer the ROM's AI-bridge requests from Python: a stand-in for the VS Code extension / an LLM.

    python ai_bridge_demo.py [--slot N] [--seconds 60]

Enables gAiBridgeMailbox and, whenever the opponent AI asks (status == REQUEST), answers with a fixed move slot
(or the built-in choice when --slot is omitted) and prints what it saw. Needs the bridge and a battle.
"""
import argparse
import struct
import time

from addresses import SYMBOLS
from mgba_client import Bridge

ap = argparse.ArgumentParser()
ap.add_argument("--slot", type=int, default=None)
ap.add_argument("--seconds", type=int, default=60)
a = ap.parse_args()
b = Bridge()
mb = SYMBOLS["gAiBridgeMailbox"]
b.w8(mb + 0x18, 1)          # enabled
b.w8(mb + 0x19, 15)         # wait up to 15 x 8 = 120 frames for an answer
end = time.time() + a.seconds
while time.time() < end:
    if b.u8(mb) == 1:       # REQUEST
        raw = b.read(mb, 0x27)
        _st, ps, ais, php, ahp = struct.unpack_from("<BHHBB", raw, 0)
        pm = struct.unpack_from("<4H", raw, 7)
        am = struct.unpack_from("<4H", raw, 15)
        built_in = raw[0x1A]
        slot = built_in if a.slot is None else a.slot
        print(f"request: player #{ps} {php}% moves {pm} | AI #{ais} {ahp}% moves {am} | built-in slot {built_in} -> answering {slot}")
        b.w8(mb + 0x17, slot)
        b.w8(mb, 2)         # READY
    time.sleep(0.02)
raw = b.read(mb, 0x27)
print("answered", struct.unpack_from("<H", raw, 0x23)[0], "timed out", struct.unpack_from("<H", raw, 0x25)[0])
