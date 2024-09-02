#!/usr/bin/env lua
function eddington (file)
    local e, above = 0, 0
    local dist_table = {}

    for line in io.lines(file) do
        local ride = math.floor(line)

        if ride > e then
            above = above + 1
            dist_table[ride] = (dist_table[ride] or 0) + 1
        end

        if above > e then
            e = e + 1
            if dist_table[e] ~= nil then
                above = above - dist_table[e]
                dist_table[e] = nil
            end
        end

    end

    return e
end

function main ()
    local file = arg[1]
    print(eddington(file))
end

if not package.loaded['eddington'] then
    main()
end
