"""Headless, unthrottled mGBA core for reinforcement learning.

The reference document drove libmgba through raw ctypes and an invented `mCore` struct. mCore is an
opaque C struct full of function pointers, so that cannot work. mGBA ships official Python (cffi)
bindings instead; build them from the mGBA source with -DBUILD_PYTHON=ON (Linux/WSL is easiest, the
Ubuntu libmgba-dev package does not include them) and `import mgba` works.

Frames are only rendered when asked for, so stepping runs as fast as the CPU allows.
"""
from typing import Any

import numpy as np

try:
    import mgba.core  # type: ignore
    import mgba.image  # type: ignore
    import mgba.log  # type: ignore
    mgba.log.silence()
except ImportError as exc:  # pragma: no cover - environment dependent
    raise ImportError("the `mgba` Python bindings are required (see module docstring)") from exc

SCREEN_W, SCREEN_H = 240, 160
KEY_MASK = {"A": 1, "B": 2, "SELECT": 4, "START": 8, "RIGHT": 16, "LEFT": 32, "UP": 64, "DOWN": 128, "R": 256, "L": 512}


class HeadlessEnv:
    def __init__(self, rom_path: str):
        core = mgba.core.load_path(rom_path)
        if core is None:
            raise RuntimeError(f"mGBA could not load {rom_path}")
        self.core: Any = core
        self.screen = mgba.image.Image(SCREEN_W, SCREEN_H)
        self.core.set_video_buffer(self.screen)
        self.core.reset()
        self._keys = 0

    # -- stepping -------------------------------------------------------------------------
    def set_keys(self, mask: int):
        self._keys = mask
        self.core._core.setKeys(self.core._core, mask)

    def step(self, key_mask: int = 0, frame_skip: int = 4, render: bool = True) -> np.ndarray | None:
        """Holds key_mask for frame_skip frames; returns the last frame as (160, 240, 3) uint8 RGB."""
        self.set_keys(key_mask)
        for _ in range(frame_skip):
            self.core.run_frame()
        return self.frame() if render else None

    def frame(self) -> np.ndarray:
        return np.asarray(self.screen.to_pil().convert("RGB"), dtype=np.uint8)

    # -- memory ---------------------------------------------------------------------------
    def read_u8(self, addr: int) -> int: return self.core.memory.u8[addr]
    def read_u16(self, addr: int) -> int: return self.core.memory.u16[addr]
    def read_u32(self, addr: int) -> int: return self.core.memory.u32[addr]
    def write_u8(self, addr: int, v: int): self.core.memory.u8[addr] = v
    def write_u16(self, addr: int, v: int): self.core.memory.u16[addr] = v
    def write_u32(self, addr: int, v: int): self.core.memory.u32[addr] = v

    def read(self, addr: int, length: int) -> bytes:
        mem = self.core.memory.u8
        try:
            return bytes(mem[addr:addr + length])
        except (TypeError, KeyError):   # older bindings do not slice
            return bytes(mem[addr + i] for i in range(length))

    # -- state ----------------------------------------------------------------------------
    def reset(self):
        self.core.reset()

    def save_state(self) -> bytes:
        return bytes(self.core.save_raw_state())

    def load_state(self, data: bytes):
        self.core.load_raw_state(data)

    def load_state_file(self, path: str):
        with open(path, "rb") as f:
            self.load_state(f.read())

    def close(self):
        self.core = None
