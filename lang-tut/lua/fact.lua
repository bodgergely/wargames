--[[
Factorial module by Greg
]]

local _M = {}

-- defines a factorial function
local function factorial(n)
    if n == 0 then
        return 1
    else
        return n * factorial(n-1)
    end
end

_M.factorial = factorial

return _M

--print("Enter a number:")
--a = io.read("*number")
--print(fact(a))

--[[
This is a comment
]]
