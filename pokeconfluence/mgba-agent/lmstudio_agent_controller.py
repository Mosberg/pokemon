"""Local vision-model control loop through LM Studio's OpenAI-compatible server (http://localhost:1234/v1).

Beyond the reference version this also asks the pathfinder for a route when the model emits a
"goto": {"x": .., "y": ..} target, then walks it step by step.
"""
import base64
import json
import time

from agent_common import SYSTEM_PROMPT, dispatch, extract_json, observe
from mgba_client import Bridge
from openai import OpenAI  # type: ignore
from pathfinding import a_star_search, read_collision_map

LM_STUDIO_URL = "http://localhost:1234/v1"
client = OpenAI(base_url=LM_STUDIO_URL, api_key="lm-studio")

PROMPT = SYSTEM_PROMPT + ' Optionally add "goto": {"x": int, "y": int} (map coordinates) to be walked there automatically.'


def walk_to(bridge: Bridge, target: tuple, max_steps: int = 60) -> bool:
    for _ in range(max_steps):
        x, y, *_ = bridge.player_position()
        if (x, y) == target:
            return True
        blocked, bounds = read_collision_map(bridge.read)
        path = a_star_search((x, y), target, blocked, bounds)
        if not path:
            return False
        bridge.press(path[0], 8)
        bridge.step(22)
    return False


def run_cycle(bridge: Bridge) -> None:
    path, state = observe(bridge)
    with open(path, "rb") as f:
        image = base64.b64encode(f.read()).decode()
    response = client.chat.completions.create(
        model="local-model",
        temperature=0.1,
        messages=[
            {"role": "system", "content": PROMPT},
            {"role": "user", "content": [
                {"type": "text", "text": f"Telemetry: {json.dumps(state)}\nDecide the next step."},
                {"type": "image_url", "image_url": {"url": f"data:image/png;base64,{image}"}},
            ]},
        ],
    )
    decision = extract_json(response.choices[0].message.content or "")
    if not decision:
        print("unparseable model output:", response.choices[0].message.content)
        return
    print("[thought]", decision.get("reasoning"))
    goto = decision.get("goto")
    if isinstance(goto, dict) and "x" in goto and "y" in goto and not state["in_battle"]:
        print("[goto]", goto, "->", "arrived" if walk_to(bridge, (int(goto["x"]), int(goto["y"]))) else "no path")
    else:
        dispatch(bridge, decision)


if __name__ == "__main__":
    bridge = Bridge()
    print("[*] LM Studio controller active (start the LM Studio server on :1234 first). Ctrl+C to stop.")
    while True:
        try:
            run_cycle(bridge)
            time.sleep(0.5)
        except KeyboardInterrupt:
            break
        except Exception as exc:
            print(f"loop warning: {exc}")
            time.sleep(2)
