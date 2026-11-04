"""Record a curriculum savestate through the bridge:  python record_state.py <stage-number|name>

Play the game to the milestone first (e.g. just before the Pewter gym), then run this. The state is written to
states/stage<N>_<name>.ss1 using the same file names curriculum_engine.py expects.
"""
import sys
from pathlib import Path

from curriculum_engine import STAGES
from mgba_client import Bridge

if len(sys.argv) != 2:
    sys.exit(__doc__)
key = sys.argv[1]
stage = next((s for s in STAGES if str(s["stage"]) == key or key.lower() in s["name"].lower()), None)
if stage is None:
    sys.exit("unknown stage; choose from: " + ", ".join(f"{s['stage']}={s['name']}" for s in STAGES))
path = (Path(__file__).parent / stage["savestate"]).resolve()
path.parent.mkdir(exist_ok=True)
Bridge().send(f"SAVEFILE {path}")
print(f"[+] saved {path}")
