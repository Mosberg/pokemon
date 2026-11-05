"""Multimodal control loop driven by Gemini (google-genai). Needs GEMINI_API_KEY (or GOOGLE_API_KEY) set."""
import time
from typing import Literal

from agent_common import SYSTEM_PROMPT, dispatch, observe
from google import genai  # type: ignore
from google.genai import types  # type: ignore
from mgba_client import Bridge
from PIL import Image
from pydantic import BaseModel, Field


class AgentAction(BaseModel):
    reasoning: str = Field(description="What is on screen and why this move was chosen.")
    button: Literal["A", "B", "START", "SELECT", "UP", "DOWN", "LEFT", "RIGHT", "NONE"]
    hold_frames: int = Field(default=8, description="Frames to hold the button.")


def run_turn(client: genai.Client, bridge: Bridge, model: str = "gemini-2.5-flash") -> None:
    path, state = observe(bridge)
    prompt = f"{SYSTEM_PROMPT}\nTelemetry: {state}\nChoose the next action."
    response = client.models.generate_content(
        model=model,
        contents=[Image.open(path), prompt],
        config=types.GenerateContentConfig(response_mime_type="application/json",
                                           response_schema=AgentAction, temperature=0.2),
    )
    action: AgentAction = response.parsed or AgentAction.model_validate_json(response.text)
    print(f"[thought] {action.reasoning}\n[action] {action.button} x{action.hold_frames}")
    dispatch(bridge, action.model_dump())


def main() -> None:
    client = genai.Client()
    bridge = Bridge()
    print("[*] Gemini control loop running. Ctrl+C to stop.")
    while True:
        try:
            run_turn(client, bridge)
            time.sleep(0.5)
        except KeyboardInterrupt:
            break
        except Exception as exc:  # keep going through transient API or socket errors
            print(f"turn failed: {exc}")
            time.sleep(2)


if __name__ == "__main__":
    main()
