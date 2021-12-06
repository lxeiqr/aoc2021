local SIM_TIME = 80
local FISH_CYCLE = 7

local function parse_input(s)
    local elems = {}

    for elem in string.gmatch(s, '([^,]+)') do
        table.insert(elems, tonumber(elem))
    end

    return elems
end

local function sim_iteration(fishes)
    local new_fishes = {}

    for _, fish in pairs(fishes) do
        if fish == 0 then
            table.insert(new_fishes, FISH_CYCLE - 1)
            table.insert(new_fishes, FISH_CYCLE + 1)
        else
            table.insert(new_fishes, fish - 1)
        end
    end

    return new_fishes
end

local input_s = io.read("*line")
local fishes = parse_input(input_s)

for _=1,SIM_TIME do
    fishes = sim_iteration(fishes)
end

print(#fishes)
