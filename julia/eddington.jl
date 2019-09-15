#!/usr/bin/env julia

function E(rides)

  E = 0
  above = 0
  n = length(rides)
  H = zeros(Int64, n)

  for i=range(1, length=n)
    r = rides[i]
    if r > E
      above = above + 1
      if r < n
        H[r] = H[r] + 1
      end
    end

    if above > E
      E = E + 1
      if E > 0
        above = above - H[E]
      end
    end

  end

  E

end

rides = Int64[]

open(ARGS[1], "r") do f
  for ln in eachline(f)
    push!(rides, floor(Int64, parse(Float64, ln)))
  end
end

println(E(rides))

0

