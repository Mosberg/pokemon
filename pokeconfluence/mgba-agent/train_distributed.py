"""Parallel PPO training: one headless mGBA core per worker process (SubprocVecEnv).

    python train_distributed.py --rom ../pokemultiregion/pokemultiregion.gba --steps 10000000 [--impala] [--curriculum]

--impala   uses the residual CNN extractor with a 4-frame stack on the screen only
--curriculum  moves workers through the stages in curriculum_engine.py (needs savestates in states/)
Tuned values follow the reference document: gamma 0.995, 3-4 epochs, batch 256, annealed lr/clip/entropy.
"""
import argparse
import multiprocessing as mp
import os
from typing import Callable

import torch
from stable_baselines3 import PPO
from stable_baselines3.common.callbacks import BaseCallback, CheckpointCallback
from stable_baselines3.common.vec_env import SubprocVecEnv, VecMonitor

from vec_wrappers import ScreenFrameStack

from mgba_gym_env import PokemonMultiRegionEnv


def linear_schedule(initial: float, final: float = 0.0) -> Callable[[float], float]:
    """SB3 passes progress_remaining going 1.0 -> 0.0."""
    return lambda progress_remaining: final + (initial - final) * progress_remaining


class EntropyAnneal(BaseCallback):
    def __init__(self, start: float, end: float):
        super().__init__()
        self.schedule = linear_schedule(start, end)

    def _on_step(self) -> bool:
        self.model.ent_coef = self.schedule(self.model._current_progress_remaining)
        return True


def make_env(rom_path: str, rank: int, state_path: str = None, frame_skip: int = 6):
    def _init():
        os.environ["OMP_NUM_THREADS"] = "1"
        os.environ["MKL_NUM_THREADS"] = "1"
        env = PokemonMultiRegionEnv(rom_path, state_path=state_path, frame_skip=frame_skip)
        env.reset(seed=1000 + rank)
        return env
    return _init


def build_vec_env(rom: str, num_envs: int, frame_skip: int = 6, stack: int = 1, state_path: str = None):
    vec = SubprocVecEnv([make_env(rom, i, state_path, frame_skip) for i in range(num_envs)], start_method="spawn")
    vec = VecMonitor(vec, filename="runs/monitor_logs")
    if stack > 1:
        vec = ScreenFrameStack(vec, n_stack=stack)    # screen only; telemetry stays a single 9-vector (matches the ONNX export)
    return vec


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", default="../pokemultiregion/pokemultiregion.gba")
    ap.add_argument("--envs", type=int, default=max(1, mp.cpu_count() - 1))
    ap.add_argument("--steps", type=int, default=10_000_000)
    ap.add_argument("--impala", action="store_true")
    ap.add_argument("--curriculum", action="store_true")
    ap.add_argument("--state", default=None, help="savestate every episode starts from")
    ap.add_argument("--out", default="ppo_pokemon_impala.zip")
    args = ap.parse_args()

    os.makedirs("runs", exist_ok=True)
    stack = 4 if args.impala else 1
    vec = build_vec_env(args.rom, args.envs, stack=stack, state_path=args.state)

    policy_kwargs = dict(net_arch=dict(pi=[256, 128], vf=[256, 128]), activation_fn=torch.nn.ReLU)
    if args.impala:
        from custom_policy import GbaMultiInputExtractor
        policy_kwargs = dict(features_extractor_class=GbaMultiInputExtractor,
                             features_extractor_kwargs=dict(features_dim=512), net_arch=dict(pi=[128, 64], vf=[128, 64]))

    model = PPO(
        "MultiInputPolicy", vec,
        learning_rate=linear_schedule(3e-4, 2e-5),
        n_steps=max(256, 2048 // max(1, args.envs // 4)),
        batch_size=256, n_epochs=4, gamma=0.995, gae_lambda=0.95,
        clip_range=linear_schedule(0.15, 0.05),
        ent_coef=0.01, vf_coef=0.5, max_grad_norm=0.5,
        tensorboard_log="runs/tb_logs", policy_kwargs=policy_kwargs, verbose=1,
        device="cuda" if torch.cuda.is_available() else "cpu",
    )
    # SB3 takes a plain float for ent_coef, so the 0.04 -> 0.002 schedule is applied by a callback
    callbacks = [EntropyAnneal(0.04, 0.002), CheckpointCallback(save_freq=max(10_000 // args.envs, 1), save_path="runs/checkpoints", name_prefix="mgba_ppo")]
    if args.curriculum:
        from curriculum_engine import CurriculumCallback
        callbacks.append(CurriculumCallback())

    try:
        model.learn(total_timesteps=args.steps, callback=callbacks, progress_bar=True)
        model.save(args.out)
    finally:
        vec.close()


if __name__ == "__main__":
    mp.set_start_method("spawn", force=True)
    main()
