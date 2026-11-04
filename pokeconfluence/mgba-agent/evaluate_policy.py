"""Live evaluation window: runs a trained PPO policy at 60 FPS and overlays V(s) and pi(a|s).

    python evaluate_policy.py ppo_pokemon_impala.zip ../pokemultiregion/pokemultiregion.gba [state.ss1] [--stack 4]
"""
import argparse
import time

import cv2
import numpy as np
import torch
from stable_baselines3 import PPO

from mgba_gym_env import PokemonMultiRegionEnv

ACTION_NAMES = ["NOOP", "A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN"]


def render_hud(frame_bgr, action, probs, value, fps):
    display = cv2.resize(frame_bgr, (720, 480), interpolation=cv2.INTER_NEAREST)
    h, w, _ = display.shape
    overlay = display.copy()
    cv2.rectangle(overlay, (w - 230, 0), (w, h), (20, 20, 20), -1)
    display = cv2.addWeighted(overlay, 0.75, display, 0.25, 0)
    put = lambda text, y, color=(255, 255, 255), s=0.55: cv2.putText(display, text, (w - 215, y), cv2.FONT_HERSHEY_SIMPLEX, s, color, 1)
    put(f"FPS: {fps:.1f}", 30, (0, 255, 0))
    put(f"Critic V(s): {value:+.2f}", 60, (0, 220, 255))
    put(f"Selected: {ACTION_NAMES[action]}", 90)
    put("Action dist:", 125, (180, 180, 180), 0.5)
    y = 150
    for i, (name, p) in enumerate(zip(ACTION_NAMES, probs)):
        put(f"{name:<6}", y + 10, (220, 220, 220), 0.38)
        cv2.rectangle(display, (w - 145, y), (w - 145 + int(p * 100), y + 10), (0, 255, 128) if i == action else (120, 120, 120), -1)
        y += 24
    return display


class FrameStack:
    """Mirror of VecFrameStack for a single env (screen only)."""
    def __init__(self, n):
        self.n, self.buf = n, None

    def __call__(self, obs):
        screen = obs["screen"]
        if self.buf is None or self.n == 1:
            self.buf = np.concatenate([screen] * self.n, axis=-1)
        else:
            self.buf = np.concatenate([self.buf[..., 1:], screen], axis=-1)
        return {"screen": self.buf, "telemetry": obs["telemetry"]}


def run(model_path, rom_path, state_path=None, stack=1):
    model = PPO.load(model_path, device="cpu")
    env = PokemonMultiRegionEnv(rom_path, state_path=state_path, frame_skip=4)
    stacker = FrameStack(stack)
    obs, _ = env.reset()
    obs = stacker(obs)
    try:
        while True:
            t0 = time.perf_counter()
            tensor, _ = model.policy.obs_to_tensor(obs)
            with torch.no_grad():
                dist = model.policy.get_distribution(tensor)
                action = int(dist.get_actions(deterministic=False).item())
                probs = dist.distribution.probs.squeeze().cpu().numpy()
                value = float(model.policy.predict_values(tensor).item())
            obs, _, terminated, truncated, _ = env.step(action)
            obs = stacker(obs)
            frame_bgr = cv2.cvtColor(env.render(), cv2.COLOR_RGB2BGR)
            dt = time.perf_counter() - t0
            cv2.imshow("pokemultiregion policy", render_hud(frame_bgr, action, probs, value, 1 / dt if dt else 60))
            if cv2.waitKey(max(1, int((1 / 60 - dt) * 1000))) & 0xFF in (ord("q"), 27):
                break
            if terminated or truncated:
                obs, _ = env.reset()
                obs = stacker(obs)
    finally:
        cv2.destroyAllWindows()
        env.close()


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("model")
    ap.add_argument("rom")
    ap.add_argument("state", nargs="?")
    ap.add_argument("--stack", type=int, default=1)
    a = ap.parse_args()
    run(a.model, a.rom, a.state, a.stack)
