"""Curriculum learning keyed to pokeconfluence event flags.

The reference document used FireRed v1.0 flag ids and a fixed flag base address. In this ROM the flag
array lives inside SaveBlock1 (reached through gSaveBlock1Ptr, see addresses.py) and the Kanto badges are
FLAG_BADGE09_GET..FLAG_BADGE16_GET (Brock = BADGE09), separate from Hoenn's BADGE01..08.

Savestates are not shipped: record one per stage in the emulator (File > Save state file) into states/.
"""
import numpy as np
from stable_baselines3.common.callbacks import BaseCallback

from addresses import FLAGS

STAGES = [
    {"stage": 0, "name": "Receive the Pokedex", "savestate": "states/stage0_start.ss1",
     "target_flag": FLAGS["POKEDEX_GET"], "reward_bonus": 50.0, "max_steps": 15_000},
    {"stage": 1, "name": "Kanto: Brock - Boulder Badge", "savestate": "states/stage1_pewter.ss1",
     "target_flag": FLAGS["BADGE09_GET"], "reward_bonus": 200.0, "max_steps": 30_000},
    {"stage": 2, "name": "Kanto: Misty - Cascade Badge", "savestate": "states/stage2_cerulean.ss1",
     "target_flag": FLAGS["BADGE10_GET"], "reward_bonus": 300.0, "max_steps": 45_000},
    {"stage": 3, "name": "Kanto: Lt. Surge - Thunder Badge", "savestate": "states/stage3_vermilion.ss1",
     "target_flag": FLAGS["BADGE11_GET"], "reward_bonus": 400.0, "max_steps": 60_000},
    {"stage": 4, "name": "Hoenn: Roxanne - Stone Badge", "savestate": "states/stage4_rustboro.ss1",
     "target_flag": FLAGS["BADGE01_GET"], "reward_bonus": 200.0, "max_steps": 30_000},
]
CURRICULUM_STAGES = STAGES


class CurriculumCallback(BaseCallback):
    """Advances the stage when enough parallel workers reach the target flag, then retargets them all."""

    def __init__(self, check_freq: int = 5000, success_threshold: float = 0.5, confirmations: int = 2, verbose: int = 1):
        super().__init__(verbose)
        self.check_freq, self.success_threshold, self.confirmations = check_freq, success_threshold, confirmations
        self.idx = 0
        self.hits = 0

    def _on_training_start(self) -> None:
        self.training_env.env_method("set_curriculum_stage", STAGES[self.idx])

    def _on_step(self) -> bool:
        if self.n_calls % self.check_freq:
            return True
        stage = STAGES[self.idx]
        cleared = self.training_env.env_method("query_flag", stage["target_flag"])
        rate = float(np.mean(cleared))
        if self.verbose:
            print(f"[curriculum] {stage['name']}: {rate * 100:.0f}% of workers cleared it")
        if rate >= self.success_threshold:
            self.hits += 1
            if self.hits >= self.confirmations and self.idx < len(STAGES) - 1:
                self.idx += 1
                self.hits = 0
                print(f"[curriculum] advancing to: {STAGES[self.idx]['name']}")
                self.training_env.env_method("set_curriculum_stage", STAGES[self.idx])
        else:
            self.hits = 0
        return True
