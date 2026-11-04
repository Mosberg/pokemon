"""VecEnv wrapper that stacks only the screen across time (SB3's VecFrameStack insists on stacking every key)."""
import numpy as np
from gymnasium import spaces
from stable_baselines3.common.vec_env import VecEnvWrapper


class ScreenFrameStack(VecEnvWrapper):
    def __init__(self, venv, n_stack: int = 4):
        screen = venv.observation_space.spaces["screen"]
        h, w, c = screen.shape
        stacked = spaces.Box(0, 255, (h, w, c * n_stack), np.uint8)
        super().__init__(venv, observation_space=spaces.Dict({**venv.observation_space.spaces, "screen": stacked}))
        self.n_stack, self.c = n_stack, c
        self.buf = np.zeros((venv.num_envs, h, w, c * n_stack), np.uint8)

    def _push(self, obs):
        self.buf = np.roll(self.buf, -self.c, axis=-1)
        self.buf[..., -self.c:] = obs["screen"]
        return {**obs, "screen": self.buf.copy()}

    def reset(self):
        obs = self.venv.reset()
        self.buf[:] = 0
        for _ in range(self.n_stack):
            out = self._push(obs)
        return out

    def step_wait(self):
        obs, rewards, dones, infos = self.venv.step_wait()
        for i, done in enumerate(dones):
            if done:
                self.buf[i] = 0                      # new episode: clear that env's history
        out = self._push(obs)
        return out, rewards, dones, infos
