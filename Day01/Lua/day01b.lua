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

for i=4, #data do
    if data[i-3] < data[i] then
        larger = larger + 1
    end
end

print(larger)
