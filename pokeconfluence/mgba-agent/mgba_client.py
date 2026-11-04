"""Tiny client for lua/mgba_agent_bridge.lua. Shared by the MCP server, the agents and the tools."""
import os
import socket
import threading

from addresses import MAIN_IN_BATTLE_BIT, MAIN_IN_BATTLE_BYTE, SB1, SYMBOLS

HOST, PORT = "127.0.0.1", int(os.environ.get("MGBA_BRIDGE_PORT", "8888"))


class Bridge:
    def __init__(self, host: str = HOST, port: int = PORT, timeout: float = 30.0):
        self.sock = socket.create_connection((host, port), timeout=timeout)
        self.file = self.sock.makefile("rwb", buffering=0)
        self.lock = threading.Lock()

    def send(self, cmd: str) -> str:
        with self.lock:
            self.file.write((cmd.strip() + "\n").encode())
            line = self.file.readline().decode().strip()
        if line.startswith("ERR"):
            raise RuntimeError(f"{cmd!r} -> {line}")
        return line[2:].strip() if line.startswith("OK") else line

    # -- memory -------------------------------------------------------------------------
    def u8(self, a): return int(self.send(f"READ8 {a:#x}"))
    def u16(self, a): return int(self.send(f"READ16 {a:#x}"))
    def u32(self, a): return int(self.send(f"READ32 {a:#x}"))

    def s16(self, a):
        v = self.u16(a)
        return v - 0x10000 if v & 0x8000 else v

    def w8(self, a, v): self.send(f"WRITE8 {a:#x} {v}")
    def w16(self, a, v): self.send(f"WRITE16 {a:#x} {v}")
    def w32(self, a, v): self.send(f"WRITE32 {a:#x} {v}")

    def read(self, addr: int, length: int) -> bytes:
        out = bytearray()
        while length > 0:
            n = min(length, 2048)
            out += bytes.fromhex(self.send(f"READBLOCK {addr:#x} {n}"))
            addr, length = addr + n, length - n
        return bytes(out)

    def write(self, addr: int, data: bytes):
        for i in range(0, len(data), 1024):
            self.send(f"WRITEBLOCK {addr + i:#x} {data[i:i + 1024].hex()}")

    # -- control ------------------------------------------------------------------------
    def press(self, button: str, frames: int = 6): self.send(f"PRESS {button} {frames}")
    def step(self, frames: int = 1): self.send(f"STEP {frames}")
    def screenshot(self, path: str): self.send(f"SCREENSHOT {path}")

    def close(self):
        try:
            self.sock.close()
        except OSError:
            pass

    # -- game helpers -------------------------------------------------------------------
    def sb1(self) -> int: return self.u32(SYMBOLS["gSaveBlock1Ptr"])
    def sb2(self) -> int: return self.u32(SYMBOLS["gSaveBlock2Ptr"])

    def player_position(self):
        """(x, y, map_group, map_num) from SaveBlock1."""
        base = self.sb1()
        return (self.s16(base + SB1["pos_x"]), self.s16(base + SB1["pos_y"]),
                self.u8(base + SB1["map_group"]), self.u8(base + SB1["map_num"]))

    def flag(self, flag_id: int) -> bool:
        return bool((self.u8(self.sb1() + SB1["flags"] + flag_id // 8) >> (flag_id % 8)) & 1)

    def in_battle(self) -> bool:
        return bool((self.u8(SYMBOLS["gMain"] + MAIN_IN_BATTLE_BYTE) >> MAIN_IN_BATTLE_BIT) & 1)
