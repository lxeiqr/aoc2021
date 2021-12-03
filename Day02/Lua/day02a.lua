local function words(s)
    local w = {}

    for word in s:gmatch("%w+") do
        table.insert(w, word)
    end

    return w
end

local function get_input()
    local data = {}

    while true do
        local line = io.read()
        if line == nil then break end

        local line_w = words(line)
        local p = {line_w[1], tonumber(line_w[2])}

        table.insert(data, p)
    end

    return data
end

local data = get_input()
local x = 0
local y = 0

for _, d in pairs(data) do
    if d[1] == 'forward' then
        x = x + d[2]
    elseif d[1] == 'down' then
        y = y + d[2]
    elseif d[1] == 'up' then
        y = y - d[2]
    end
end

print(x * y)
