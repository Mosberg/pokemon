"""Low-latency inference without PyTorch:  python onnx_runner.py policy_pokemon.onnx   (benchmark)"""
import sys
import time

import numpy as np
import onnxruntime as ort  # type: ignore


class FastPolicyRunner:
    def __init__(self, onnx_file: str):
        available = ort.get_available_providers()
        providers = [p for p in ("CUDAExecutionProvider", "CPUExecutionProvider") if p in available]
        self.session = ort.InferenceSession(onnx_file, providers=providers)
        self.screen_name, self.telemetry_name = (i.name for i in self.session.get_inputs()[:2])

    def predict(self, screen_stack: np.ndarray, telemetry_vec: np.ndarray):
        """screen_stack: uint8 (80, 120, stack); telemetry_vec: float32 (9,). Returns (action, probabilities)."""
        outputs = self.session.run(None, {
            self.screen_name: np.expand_dims(screen_stack, 0),
            self.telemetry_name: np.expand_dims(telemetry_vec.astype(np.float32), 0),
        })
        return int(outputs[0][0]), outputs[1][0]


if __name__ == "__main__":
    runner = FastPolicyRunner(sys.argv[1] if len(sys.argv) > 1 else "policy_pokemon.onnx")
    stack = runner.session.get_inputs()[0].shape[-1]
    screen = np.random.randint(0, 255, (80, 120, stack), dtype=np.uint8)
    telem = np.random.randn(9).astype(np.float32)
    t0 = time.perf_counter()
    action, probs = 0, np.array([])
    for _ in range(1000):
        action, probs = runner.predict(screen, telem)
    print(f"[+] {(time.perf_counter() - t0):.3f} ms per step | action {action} | probs {np.round(probs, 3)}")
