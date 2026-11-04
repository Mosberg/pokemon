"""Emulator backend that drives a running mGBA through lua/mgba_agent_bridge.lua.

Same interface as HeadlessEnv, so mgba_gym_env.PokemonMultiRegionEnv(backend="bridge") works without the
`mgba` Python bindings. It runs at emulator speed (no unthrottled stepping), so it suits evaluation,
debugging and small experiments; use the headless core for large training runs.
"""
import os
import tempfile
from typing import Optional

import numpy as np
from PIL import Image

from mgba_client import Bridge

_SHOT = os.path.join(tempfile.gettempdir(), "mgba_bridge_frame.png")


class BridgeEnv:
    def __init__(self, rom_path: str = "", host: str = "127.0.0.1", port: int = 8888):
        self.bridge = Bridge(host, port)          # rom_path is unused: the emulator already has the ROM loaded

    def set_keys(self, mask: int):
        self.bridge.send(f"SETKEYS {mask}")

    def step(self, key_mask: int = 0, frame_skip: int = 4, render: bool = True) -> Optional[np.ndarray]:
        self.set_keys(key_mask)
        self.bridge.step(frame_skip)
        return self.frame() if render else None

    def frame(self) -> np.ndarray:
        self.bridge.screenshot(_SHOT)
        with Image.open(_SHOT) as im:
            return np.asarray(im.convert("RGB"), dtype=np.uint8)

    def read_u8(self, addr: int) -> int: return self.bridge.u8(addr)
    def read_u16(self, addr: int) -> int: return self.bridge.u16(addr)
    def read_u32(self, addr: int) -> int: return self.bridge.u32(addr)
    def write_u8(self, addr: int, v: int): self.bridge.w8(addr, v)
    def write_u16(self, addr: int, v: int): self.bridge.w16(addr, v)
    def write_u32(self, addr: int, v: int): self.bridge.w32(addr, v)
    def read(self, addr: int, length: int) -> bytes: return self.bridge.read(addr, length)

    def reset(self):
        pass        # there is no hard reset over the bridge; the Gym env reloads its savestate instead

    def load_state_file(self, path: str):
        self.bridge.send(f"LOADFILE {os.path.abspath(path)}")

    def close(self):
        self.set_keys(0)
        self.bridge.close()
