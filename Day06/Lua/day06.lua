local inspect = require('inspect')

local SIM_TIME_A = 80
local SIM_TIME_B = 256
local FISH_CYCLE = 7

local function parse_input(s)
    local elems = {}

    for i=1, FISH_CYCLE + 2 do
        elems[i] = 0
    end

    for elem in string.gmatch(s, '([^,]+)') do
        local i = tonumber(elem)
        elems[i+2] = elems[i+2] + 1
    end

    return elems
end

local function sim_iteration(fishes)
    local new_fishes = {}

    for i = 1, FISH_CYCLE+1 do
        new_fishes[i] = fishes[i+1]
    end

    new_fishes[FISH_CYCLE+2] = fishes[1]
    new_fishes[FISH_CYCLE] = new_fishes[FISH_CYCLE] + fishes[1]

    return new_fishes
end

local function sum(l)
    local s = 0
    for _,f in ipairs(l) do
        s = s + f
    end
    return s
end

local input_s = io.read("*line")
local fishes = parse_input(input_s)

for _ = 0,SIM_TIME_A do fishes = sim_iteration(fishes) end
print('Part A: '..sum(fishes))
for _ = 0, SIM_TIME_B - SIM_TIME_A - 1 do fishes = sim_iteration(fishes) end
print('Part B: '..sum(fishes))
