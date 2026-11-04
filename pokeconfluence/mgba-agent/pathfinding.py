"""Collision extraction from gBackupMapLayout and A* pathfinding over it."""
import heapq
import struct
from typing import Callable, Dict, List, Optional, Set, Tuple

from addresses import SYMBOLS

MAP_OFFSET = 7            # the backup layout has a 7-tile border on every side
MAPGRID_COLLISION_MASK = 0x0C00
MAPGRID_METATILE_MASK = 0x03FF

ReadFn = Callable[[int, int], bytes]
Tile = Tuple[int, int]


def read_collision_map(read: ReadFn) -> Tuple[Set[Tile], Tuple[int, int]]:
    """Returns (blocked tiles in map coordinates, (width, height)).

    struct BackupMapLayout { s32 width; s32 height; u16 *map; } -- width/height already include the
    border (map size + 15 x map size + 14), each cell is a u16 with metatile id in bits 0-9,
    collision in bits 10-11 and elevation in bits 12-15. Any non-zero collision value blocks walking;
    ledges and water are handled separately by the game, so this is an approximation.
    """
    width, height, ptr = struct.unpack("<iiI", read(SYMBOLS["gBackupMapLayout"], 12))
    if not (0 < width <= 256 and 0 < height <= 256 and 0x02000000 <= ptr < 0x03000000):
        raise RuntimeError("map layout not loaded (title screen or a transition)")
    raw = read(ptr, width * height * 2)
    cells = struct.unpack(f"<{width * height}H", raw)
    blocked = {(x - MAP_OFFSET, y - MAP_OFFSET)
               for y in range(height) for x in range(width) if cells[y * width + x] & MAPGRID_COLLISION_MASK}
    return blocked, (width - 2 * MAP_OFFSET, height - 2 * MAP_OFFSET)


class PriorityQueue:
    def __init__(self):
        self.elements: list = []
        self._n = 0

    def empty(self) -> bool:
        return not self.elements

    def put(self, item, priority):
        self._n += 1
        heapq.heappush(self.elements, (priority, self._n, item))   # counter keeps ties from comparing items

    def get(self):
        return heapq.heappop(self.elements)[2]


def heuristic(a: Tile, b: Tile) -> int:
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def a_star_search(start: Tile, goal: Tile, blocked_tiles: Set[Tile], map_bounds: Tuple[int, int]) -> Optional[List[str]]:
    """Shortest 4-connected path as a list of 'UP'/'DOWN'/'LEFT'/'RIGHT', or None. Coordinates are map
    coordinates (0..width-1). The goal is allowed to be a blocked tile (NPC, door, sign)."""
    max_x, max_y = map_bounds
    moves = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}
    frontier = PriorityQueue()
    frontier.put(start, 0)
    came_from: Dict[Tile, Optional[Tile]] = {start: None}
    cost: Dict[Tile, int] = {start: 0}
    action: Dict[Tile, str] = {}

    while not frontier.empty():
        current = frontier.get()
        if current == goal:
            break
        for name, (dx, dy) in moves.items():
            nxt = (current[0] + dx, current[1] + dy)
            if not (0 <= nxt[0] < max_x and 0 <= nxt[1] < max_y):
                continue
            if nxt in blocked_tiles and nxt != goal:
                continue
            new_cost = cost[current] + 1
            if nxt not in cost or new_cost < cost[nxt]:
                cost[nxt] = new_cost
                frontier.put(nxt, new_cost + heuristic(goal, nxt))
                came_from[nxt] = current
                action[nxt] = name

    if goal not in came_from:
        return None
    path, cur = [], goal
    while cur != start:
        path.append(action[cur])
        cur = came_from[cur]
    path.reverse()
    return path
