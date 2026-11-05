-- watcher.lua: on-screen RAM overlay for pokeconfluence.gba (load via Tools -> Scripting).
-- Shows map, player tile, battle flag and the lead Pokemon's HP, using this ROM's real addresses
-- (see ../addresses.py; regenerate them with refresh_addresses.py after rebuilding the ROM).
local GMAIN, SB1PTR, PARTY = 0x030066D0, 0x030051D4, 0x02031C40
local painter, canvas = nil, nil

local function overlay()
  local sb1 = emu:read32(SB1PTR)
  if sb1 < 0x02000000 or sb1 >= 0x02040000 then return end
  local x, y = emu:read16(sb1), emu:read16(sb1 + 2)
  local group, num = emu:read8(sb1 + 4), emu:read8(sb1 + 5)
  local inBattle = (emu:read8(GMAIN + 0x439) >> 1) & 1
  console:log(string.format("map %d/%d  tile (%d,%d)  battle=%d  lead HP %d/%d",
    group, num, x, y, inBattle, emu:read16(PARTY + 86), emu:read16(PARTY + 88)))
end

local frames = 0
callbacks:add("frame", function()
  frames = frames + 1
  if frames % 60 == 0 then overlay() end
end)
console:log("[watcher] logging position once per second")
