-- Brute force approach O(n^2), could be done in O(n)

local function read_input(s)
    local elems = {}
    for elem in string.gmatch(s, '([^,]+)') do
        table.insert(elems, tonumber(elem))
    end
    return elems
end

local function transform_input(l)
    local elems = {}

    for _,e in ipairs(l) do
        if elems[e+1] == nil then elems[e+1] = 0 end
        elems[e+1] = elems[e+1] + 1
    end

    return elems
end

local function sum_of_progression(n)
    if n == 0 then
        return 0
    else
        return (2 + n - 1)/2 * n
    end
end

local function find_minimum(data, part)
    local minimum = math.huge

    for i,_ in pairs(data) do
        local sum = 0

        for j,w in pairs(data) do
            local dist = math.abs(j - i)
            if part == 2 then dist = sum_of_progression(dist) end

            sum = sum + dist * w
        end

        if sum < minimum then minimum = sum end
    end

    return minimum
end

local input = transform_input(read_input(io.read("*line")))
print('Part 1: '..find_minimum(input, 1))
print('Part 2: '..find_minimum(input, 2))
