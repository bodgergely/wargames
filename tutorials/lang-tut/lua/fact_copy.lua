--[[
Factorial module by Greg
]]


-- defines a factorial function
function factorial(n)
    if n == 0 then
        return 1
    else
        return n * factorial(n-1)
    end
end



--print("Enter a number:")
--a = io.read("*number")
--print(fact(a))

--[[
This is a comment
]]
