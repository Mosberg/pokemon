"""Impala-style residual CNN + telemetry MLP feature extractor for the dict observation.

The reference version assumed channels-last raw pixels and permuted them itself. Inside SB3 the screen already
arrives as (B, C, H, W) floats in [0, 1], so that permute silently built a nonsense network (120 input channels).
"""
import torch
import torch.nn as nn
from gymnasium import spaces
from stable_baselines3.common.torch_layers import BaseFeaturesExtractor


class ResidualBlock(nn.Module):
    def __init__(self, channels: int):
        super().__init__()
        self.conv0 = nn.Conv2d(channels, channels, 3, padding=1)
        self.conv1 = nn.Conv2d(channels, channels, 3, padding=1)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        out = self.conv0(torch.relu(x))
        out = self.conv1(torch.relu(out))
        return out + x


class ImpalaBlock(nn.Module):
    def __init__(self, cin: int, cout: int):
        super().__init__()
        self.conv = nn.Conv2d(cin, cout, 3, padding=1)
        self.pool = nn.MaxPool2d(3, stride=2, padding=1)
        self.res0, self.res1 = ResidualBlock(cout), ResidualBlock(cout)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.res1(self.res0(self.pool(self.conv(x))))


class GbaMultiInputExtractor(BaseFeaturesExtractor):
    """screen (H, W, stacked) -> Impala blocks;  telemetry -> MLP;  fused to features_dim."""

    def __init__(self, observation_space: spaces.Dict, features_dim: int = 512):
        super().__init__(observation_space, features_dim)
        # SB3 hands the policy channels-first, already /255-normalised images (VecTransposeImage + preprocess_obs)
        channels, h, w = observation_space.spaces["screen"].shape
        self.visual = nn.Sequential(ImpalaBlock(channels, 16), ImpalaBlock(16, 32), ImpalaBlock(32, 32),
                                    nn.ReLU(), nn.Flatten())
        with torch.no_grad():
            flat = self.visual(torch.zeros(1, channels, h, w)).shape[1]
        self.visual_fc = nn.Sequential(nn.Linear(flat, 256), nn.ReLU())
        tdim = observation_space.spaces["telemetry"].shape[0]
        self.telemetry = nn.Sequential(nn.Linear(tdim, 64), nn.ReLU(), nn.Linear(64, 64), nn.ReLU())
        self.fuse = nn.Sequential(nn.Linear(256 + 64, features_dim), nn.ReLU())

    def forward(self, obs: dict) -> torch.Tensor:
        return self.fuse(torch.cat([self.visual_fc(self.visual(obs["screen"])), self.telemetry(obs["telemetry"].float())], dim=1))
