"""Export a trained PPO policy (actor head) to ONNX:  python export_onnx.py ppo_pokemon_impala.zip policy_pokemon.onnx [--stack 4]"""
import argparse

import torch
import torch.nn as nn
from stable_baselines3 import PPO

import custom_policy  # noqa: F401  (makes the custom extractor importable when unpickling)


class OnnxDeployablePolicy(nn.Module):
    """Feature extractor + actor head as one feed-forward graph."""

    def __init__(self, policy):
        super().__init__()
        self.policy = policy

    def forward(self, screen: torch.Tensor, telemetry: torch.Tensor):
        # public input is (B, H, W, C) uint8 like the env emits; the policy wants channels-first (SB3 normalises inside)
        features = self.policy.extract_features({"screen": screen.permute(0, 3, 1, 2), "telemetry": telemetry})
        if isinstance(features, tuple):               # separate pi/vf extractors
            features = features[0]
        latent_pi = self.policy.mlp_extractor.forward_actor(features)
        probs = torch.softmax(self.policy.action_net(latent_pi), dim=-1)
        return torch.argmax(probs, dim=-1), probs


def export_policy_to_onnx(model_path: str, output: str, stack: int = 4):
    model = PPO.load(model_path, device="cpu")
    model.policy.eval()
    wrapper = OnnxDeployablePolicy(model.policy)
    dummy = (torch.zeros((1, 80, 120, stack), dtype=torch.uint8), torch.zeros((1, 9), dtype=torch.float32))
    torch.onnx.export(
        wrapper, dummy, output, opset_version=17, dynamo=False,
        input_names=["screen", "telemetry"], output_names=["action", "action_probabilities"],
        dynamic_axes={n: {0: "batch_size"} for n in ("screen", "telemetry", "action", "action_probabilities")},
    )
    print(f"[+] exported {output}")


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("model")
    ap.add_argument("output")
    ap.add_argument("--stack", type=int, default=4)
    a = ap.parse_args()
    export_policy_to_onnx(a.model, a.output, a.stack)
