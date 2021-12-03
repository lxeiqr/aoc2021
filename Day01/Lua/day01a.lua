local function get_input()
    local data = {}

    while true do
        local line = io.read()
        if line == nil then break end

        table.insert(data, tonumber(line))
    end

    return data
end

local data = get_input()
local larger = 0

for i=1, #data - 1 do
    if data[i] < data[i+1] then
        larger = larger + 1
    end
end

print(larger)
