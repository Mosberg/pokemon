"""MCP server exposing mGBA (via lua/mgba_agent_bridge.lua) as tools for Claude Code, Gemini CLI, Copilot...

Register it with:  claude mcp add mgba -- python C:/Projects/Games/Poke-Migrator/mgba-agent/mgba_mcp_server.py
Requires `pip install mcp` (works with mcp 1.x and 2.x).
"""
import os
import tempfile

try:                                           # mcp 2.x renamed FastMCP to MCPServer
    from mcp.server.mcpserver import MCPServer as FastMCP
except ImportError:                            # mcp 1.x
    from mcp.server.fastmcp import FastMCP

from addresses import FLAGS
from battle_engine import get_battle_engine_state
from mgba_client import Bridge
from pkmn_decrypt import decrypt_pokemon_data
from addresses import MON_SIZE, SYMBOLS

mcp = FastMCP("mGBA Controller")
_bridge = None


def bridge() -> Bridge:
    global _bridge
    if _bridge is None:
        _bridge = Bridge()
    return _bridge


def call(fn):
    """Reconnects once if the emulator or the script was restarted."""
    global _bridge
    try:
        return fn(bridge())
    except (OSError, ConnectionError):
        _bridge = None
        return fn(bridge())


@mcp.tool()
def read_memory(address: str, size: int = 8) -> str:
    """Read an 8, 16 or 32 bit value from GBA memory, e.g. address '0x02000000'."""
    return str(call(lambda b: b.send(f"READ{size} {address}")))


@mcp.tool()
def read_bytes(address: str, length: int = 16) -> str:
    """Read raw bytes as hex (for structs)."""
    return call(lambda b: b.read(int(address, 0), length).hex())


@mcp.tool()
def write_memory(address: str, value: int, size: int = 8) -> str:
    """Write an 8, 16 or 32 bit value into GBA memory."""
    return call(lambda b: b.send(f"WRITE{size} {address} {value}")) or "OK"


@mcp.tool()
def send_button_input(button: str, hold_frames: int = 6) -> str:
    """Press A, B, SELECT, START, UP, DOWN, LEFT, RIGHT, L or R for hold_frames frames."""
    call(lambda b: b.press(button, hold_frames))
    return "OK"


@mcp.tool()
def advance_frames(count: int = 1) -> str:
    """Wait until the emulator has run N more frames."""
    return call(lambda b: b.send(f"STEP {count}"))


@mcp.tool()
def capture_frame(output_path: str = "") -> str:
    """Save a screenshot and return its path (open it to look at the game)."""
    path = output_path or os.path.join(tempfile.gettempdir(), "mgba_agent_view.png")
    call(lambda b: b.screenshot(path))
    return path


@mcp.tool()
def manage_savestate(action: str, slot: int = 1) -> str:
    """Save or load an emulator state slot. action is 'SAVE' or 'LOAD'."""
    cmd = "SAVESTATE" if action.upper() == "SAVE" else "LOADSTATE"
    return call(lambda b: b.send(f"{cmd} {slot}")) or "OK"


@mcp.tool()
def game_state() -> dict:
    """Player position and map, battle flag and badge flags for this ROM."""
    def f(b: Bridge):
        x, y, group, num = b.player_position()
        return {"x": x, "y": y, "map_group": group, "map_num": num, "in_battle": b.in_battle(),
                "badges": {k: b.flag(v) for k, v in FLAGS.items() if k.startswith("BADGE")}}
    return call(f)


@mcp.tool()
def party() -> list:
    """Decoded party (species id, level, HP, moves, IVs...)."""
    def f(b: Bridge):
        count = b.u8(SYMBOLS["gPlayerPartyCount"])
        raw = b.read(SYMBOLS["gPlayerParty"], MON_SIZE * min(count, 6))
        return [decrypt_pokemon_data(raw[i * MON_SIZE:(i + 1) * MON_SIZE]) for i in range(min(count, 6))]
    return call(f)


@mcp.tool()
def battle_state() -> dict:
    """Active battle: both front battlers, outcome and battle type flags."""
    return call(lambda b: get_battle_engine_state(b.read))


if __name__ == "__main__":
    mcp.run()
