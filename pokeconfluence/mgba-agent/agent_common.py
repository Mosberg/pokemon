"""Shared pieces of the screenshot + RAM telemetry agent loops (Gemini and LM Studio)."""
import json
import os
import tempfile
from typing import Optional

from addresses import MON_SIZE, SYMBOLS
from battle_engine import get_battle_engine_state
from mgba_client import Bridge
from pkmn_decrypt import decrypt_pokemon_data

SCREEN_PATH = os.path.join(tempfile.gettempdir(), "mgba_agent_view.png")
BUTTONS = ["A", "B", "START", "SELECT", "UP", "DOWN", "LEFT", "RIGHT", "L", "R", "NONE"]

SYSTEM_PROMPT = (
    "You are an agent playing a Pokemon game on a Game Boy Advance emulator. The ROM is a single cartridge "
    "that contains Kanto, Johto, and Hoenn regions. You see a screenshot plus RAM telemetry. Choose exactly one "
    "button. Advance text with A, leave menus with B, walk with the directions, and in battle pick moves with "
    "A and the directions. Reply only with JSON: "
    '{"reasoning": str, "button": one of ' + json.dumps(BUTTONS) + ', "hold_frames": int}'
)


def telemetry(b: Bridge) -> dict:
    x, y, group, num = b.player_position()
    state = {"x": x, "y": y, "map_group": group, "map_num": num, "in_battle": b.in_battle()}
    try:
        count = b.u8(SYMBOLS["gPlayerPartyCount"])
        if 0 < count <= 6:
            lead = decrypt_pokemon_data(b.read(SYMBOLS["gPlayerParty"], MON_SIZE))
            state["lead"] = {k: lead[k] for k in ("species_id", "level", "current_hp", "max_hp")}
    except Exception:
        pass
    if state["in_battle"]:
        state["battle"] = get_battle_engine_state(b.read)
    return state


def observe(b: Bridge) -> tuple:
    b.screenshot(SCREEN_PATH)
    return SCREEN_PATH, telemetry(b)


def dispatch(b: Bridge, decision: dict) -> None:
    button = str(decision.get("button", "NONE")).upper()
    frames = int(decision.get("hold_frames", 8) or 8)
    if button in BUTTONS and button != "NONE":
        b.press(button, frames)
        b.step(frames + 15)


def extract_json(text: str) -> Optional[dict]:
    start, end = text.find("{"), text.rfind("}") + 1
    if start < 0 or end <= start:
        return None
    try:
        return json.loads(text[start:end])
    except ValueError:
        return None
