"""Gymnasium environment over the headless mGBA core, targeting pokemultiregion.gba (Hoenn + Kanto)."""
from typing import Any, Dict, Optional, Tuple

import gymnasium as gym
import numpy as np
from gymnasium import spaces
from PIL import Image

from addresses import FLAGS, SB1, SYMBOLS
from battle_engine import get_battle_engine_state

# 9 discrete actions -> GBA key masks
GBA_KEYS = {0: 0, 1: 1, 2: 2, 3: 4, 4: 8, 5: 16, 6: 32, 7: 64, 8: 128}
SCREEN_SHAPE = (80, 120, 1)


class PokemonMultiRegionEnv(gym.Env):
    metadata = {"render_modes": ["rgb_array"], "render_fps": 60}

    def __init__(self, rom_path: str = "", state_path: Optional[str] = None, frame_skip: int = 6,
                 max_episode_steps: int = 20_000, backend: str = "headless"):
        super().__init__()
        self.rom_path, self.state_path = rom_path, state_path
        self.frame_skip, self.max_episode_steps = frame_skip, max_episode_steps
        if backend == "bridge":                      # a running mGBA with lua/mgba_agent_bridge.lua loaded
            from bridge_backend import BridgeEnv
            self.core = BridgeEnv(rom_path)
        else:                                       # needs the `mgba` Python bindings
            from headless_mgba import HeadlessEnv
            self.core = HeadlessEnv(rom_path)
        self.action_space = spaces.Discrete(9)
        self.observation_space = spaces.Dict({
            "screen": spaces.Box(0, 255, SCREEN_SHAPE, np.uint8),
            "telemetry": spaces.Box(-np.inf, np.inf, (9,), np.float32),
        })
        self.visited: set = set()
        self.prev_player_hp = self.prev_opp_hp = 1.0
        self.target_flag: Optional[int] = None
        self.curriculum_reward = 0.0
        self.steps = 0
        self._last_frame = np.zeros((160, 240, 3), np.uint8)

    # -- RAM helpers ----------------------------------------------------------------------
    def _sb1(self) -> int:
        return self.core.read_u32(SYMBOLS["gSaveBlock1Ptr"])

    def _position(self) -> Tuple[int, int, int, int]:
        base = self._sb1()
        if not (0x02000000 <= base < 0x02040000):
            return 0, 0, 0, 0
        x, y = np.frombuffer(self.core.read(base + SB1["pos_x"], 4), np.int16)
        return int(x), int(y), self.core.read_u8(base + SB1["map_group"]), self.core.read_u8(base + SB1["map_num"])

    def query_flag(self, flag_id: int) -> bool:
        """Called through SubprocVecEnv.env_method by the curriculum callback."""
        base = self._sb1()
        if not (0x02000000 <= base < 0x02040000):
            return False
        return bool((self.core.read_u8(base + SB1["flags"] + flag_id // 8) >> (flag_id % 8)) & 1)

    def set_curriculum_stage(self, stage: dict):
        self.state_path = stage.get("savestate")
        self.target_flag = stage.get("target_flag")
        self.curriculum_reward = float(stage.get("reward_bonus", 0.0))

    # -- gym API --------------------------------------------------------------------------
    def _obs(self, frame: np.ndarray) -> Dict[str, np.ndarray]:
        self._last_frame = frame
        gray = Image.fromarray(frame).convert("L").resize((120, 80), Image.BILINEAR)
        screen = np.asarray(gray, np.uint8)[..., None]
        x, y, group, num = self._position()
        battle = get_battle_engine_state(self.core.read)
        if battle["in_battle"]:
            p, o = battle["player"], battle["opponent"]
            vals = (1.0, p["hp_fraction"], o["hp_fraction"], p["level"], o["level"], float(battle["outcome"] & 0x7F))
        else:
            vals = (0.0, 1.0, 0.0, 0.0, 0.0, 0.0)
        telemetry = np.array([x, y, group * 256 + num, *vals[:5], len(self.visited)], np.float32)
        self._outcome = int(vals[5])
        return {"screen": screen, "telemetry": telemetry}

    def reset(self, seed: Optional[int] = None, options: Optional[dict] = None):
        super().reset(seed=seed)
        self.core.reset()
        if self.state_path:
            self.core.load_state_file(self.state_path)
        self.visited.clear()
        self.prev_player_hp = self.prev_opp_hp = 1.0
        self.steps = 0
        return self._obs(self.core.step(0, 10)), {}

    def step(self, action: int):
        self.core.step(GBA_KEYS.get(int(action), 0), self.frame_skip, render=False)
        frame = self.core.step(0, 2)
        self.steps += 1
        obs = self._obs(frame)

        reward, terminated = -0.01, False
        x, y, group, num = self._position()
        tile = (group, num, x, y)
        if tile not in self.visited:
            self.visited.add(tile)
            reward += 1.0

        in_battle = bool(obs["telemetry"][3])
        if in_battle:
            p_hp, o_hp = float(obs["telemetry"][4]), float(obs["telemetry"][5])
            if o_hp < self.prev_opp_hp:
                reward += (self.prev_opp_hp - o_hp) * 5.0
            if p_hp < self.prev_player_hp:
                reward -= (self.prev_player_hp - p_hp) * 3.0
            if self._outcome == 1:
                reward += 10.0
            elif self._outcome == 2:
                reward -= 10.0
                terminated = True
            self.prev_player_hp, self.prev_opp_hp = p_hp, o_hp
        else:
            self.prev_player_hp, self.prev_opp_hp = 1.0, 1.0

        if self.target_flag is not None and self.query_flag(self.target_flag):
            reward += self.curriculum_reward
            terminated = True

        truncated = self.steps >= self.max_episode_steps
        return obs, reward, terminated, truncated, {"visited_count": len(self.visited), "in_battle": in_battle}

    def render(self):
        return self._last_frame

    def close(self):
        self.core.close()


PokemonFireRedEnv = PokemonMultiRegionEnv   # name used by the reference document
