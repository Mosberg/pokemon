-- mgba_agent_bridge.lua
-- Local TCP control server for AI agents. Load it in mGBA with Tools -> Scripting -> File -> Load script.
-- Protocol: one text command per line, one text reply per line ("OK ..." or "ERR ...").
--   READ8|READ16|READ32 addr          WRITE8|WRITE16|WRITE32 addr value
--   READBLOCK addr length             -> OK <hex bytes>          (up to 4096 bytes)
--   WRITEBLOCK addr hexbytes
--   PRESS button [frames]             SETKEYS mask               (A B SELECT START RIGHT LEFT UP DOWN R L)
--   STEP frames                       -> replies when that many frames have run
--   SCREENSHOT path                   SAVESTATE slot | LOADSTATE slot
--   SAVEFILE path | LOADFILE path     FRAME | TITLE
-- Notes: mGBA's scripting API has no synchronous runFrame, so STEP is a deferred reply driven by the
-- frame callback and the emulator keeps its normal pacing.

local PORT = 8888

local KEYS = { A = 1, B = 2, SELECT = 4, START = 8, RIGHT = 16, LEFT = 32, UP = 64, DOWN = 128, R = 256, L = 512 }

local server = nil
local clients = {}        -- id -> {sock=, buf=}
local nextId = 1
local releases = {}       -- {frame=, mask=}
local waits = {}          -- {frame=, client=}

local function num(s)
  if not s then return nil end
  return tonumber(s)      -- understands 0x... as well as decimal
end

local function unhex(s)
  local out = {}
  for h in s:gmatch("%x%x") do out[#out + 1] = string.char(tonumber(h, 16)) end
  return table.concat(out)
end

local function handle(client, line)
  local p = {}
  for w in line:gmatch("%S+") do p[#p + 1] = w end
  local cmd = (p[1] or ""):upper()

  if cmd == "READ8" or cmd == "READ16" or cmd == "READ32" then
    local a = num(p[2]); if not a then return "ERR BAD_ADDRESS" end
    local v
    if cmd == "READ8" then v = emu:read8(a) elseif cmd == "READ16" then v = emu:read16(a) else v = emu:read32(a) end
    return "OK " .. v
  elseif cmd == "WRITE8" or cmd == "WRITE16" or cmd == "WRITE32" then
    local a, v = num(p[2]), num(p[3]); if not (a and v) then return "ERR BAD_ARGS" end
    if cmd == "WRITE8" then emu:write8(a, v) elseif cmd == "WRITE16" then emu:write16(a, v) else emu:write32(a, v) end
    return "OK"
  elseif cmd == "READBLOCK" then
    local a, n = num(p[2]), num(p[3]); if not (a and n) or n > 4096 then return "ERR BAD_ARGS" end
    local t = {}
    for i = 0, n - 1 do t[#t + 1] = string.format("%02x", emu:read8(a + i)) end
    return "OK " .. table.concat(t)
  elseif cmd == "WRITEBLOCK" then
    local a = num(p[2]); if not (a and p[3]) then return "ERR BAD_ARGS" end
    local data = unhex(p[3])
    for i = 1, #data do emu:write8(a + i - 1, data:byte(i)) end
    return "OK " .. #data
  elseif cmd == "PRESS" then
    local mask = KEYS[(p[2] or ""):upper()]
    if not mask then return "ERR INVALID_KEY" end
    local frames = num(p[3]) or 6
    emu:addKeys(mask)
    releases[#releases + 1] = { frame = emu:currentFrame() + frames, mask = mask }
    return "OK"
  elseif cmd == "SETKEYS" then
    emu:setKeys(num(p[2]) or 0); return "OK"
  elseif cmd == "STEP" then
    waits[#waits + 1] = { frame = emu:currentFrame() + (num(p[2]) or 1), client = client }
    return nil            -- the reply is sent from the frame callback
  elseif cmd == "SCREENSHOT" then
    if not p[2] then return "ERR BAD_ARGS" end
    emu:screenshot(p[2]); return "OK " .. p[2]
  elseif cmd == "SAVESTATE" then
    emu:saveStateSlot(num(p[2]) or 1); return "OK"
  elseif cmd == "LOADSTATE" then
    emu:loadStateSlot(num(p[2]) or 1); return "OK"
  elseif cmd == "SAVEFILE" then
    if not p[2] then return "ERR BAD_ARGS" end
    return emu:saveStateFile(p[2]) and "OK" or "ERR SAVE_FAILED"
  elseif cmd == "LOADFILE" then
    if not p[2] then return "ERR BAD_ARGS" end
    return emu:loadStateFile(p[2]) and "OK" or "ERR LOAD_FAILED"
  elseif cmd == "FRAME" then
    return "OK " .. emu:currentFrame()
  elseif cmd == "TITLE" then
    return "OK " .. emu:getGameTitle()
  end
  return "ERR UNKNOWN_CMD"
end

local function reply(client, text)
  if client and client.sock then client.sock:send(text .. "\n") end
end

local function onReceived(id)
  local client = clients[id]
  if not client then return end
  local chunk, err = client.sock:receive(4096)
  if not chunk then
    if err and err ~= socket.ERRORS.AGAIN and err ~= socket.ERRORS.NO_DATA then clients[id] = nil end
    return
  end
  client.buf = client.buf .. chunk
  while true do
    local nl = client.buf:find("\n", 1, true)
    if not nl then break end
    local line = client.buf:sub(1, nl - 1):gsub("\r", "")
    client.buf = client.buf:sub(nl + 1)
    if #line > 0 then
      local ok, res = pcall(handle, client, line)
      if not ok then res = "ERR " .. tostring(res) end
      if res then reply(client, res) end
    end
  end
end

local function onAccept()
  local sock = server:accept()
  if not sock then return end
  local id = nextId; nextId = nextId + 1
  clients[id] = { sock = sock, buf = "" }
  sock:add("received", function() onReceived(id) end)
  sock:add("error", function() clients[id] = nil end)
  console:log("[agent bridge] client " .. id .. " connected")
end

local function onFrame()
  local now = emu:currentFrame()
  for i = #releases, 1, -1 do
    if now >= releases[i].frame then emu:clearKeys(releases[i].mask); table.remove(releases, i) end
  end
  for i = #waits, 1, -1 do
    if now >= waits[i].frame then reply(waits[i].client, "OK " .. now); table.remove(waits, i) end
  end
end

local err
server, err = socket.bind("127.0.0.1", PORT)   -- loopback only: this bridge can write RAM
if not server then
  console:error("[agent bridge] cannot bind port " .. PORT .. ": " .. tostring(err))
else
  server:add("received", onAccept)
  server:listen(4)
  callbacks:add("frame", onFrame)
  console:log("[agent bridge] listening on port " .. PORT)
end
