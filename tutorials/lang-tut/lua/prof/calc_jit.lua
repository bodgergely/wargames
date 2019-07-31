require("jit.p").start("4fGi10", "calc.prof")
iter = 20000

fib_cache = {}

function fib(n)
    if n == 0 or n == 1 then
        return 1
    end
    if not fib_cache[n-1] then
        fib_cache[n-1] = fib(n-1)
    end
    if not fib_cache[n-2] then
        fib_cache[n-2] = fib(n-2)
    end

    return fib_cache[n-1] + fib_cache[n-2]
end

function calculate(x, y, z)
    local x = x + (y % fib(z))
    return x
end

function main(iter)
    local res = 0
    for i=1,iter do
        local v = fib(i)
        for j=1,iter do
            res = calculate(res, v, j)
        end
    end
    return res
end

print(fib(100))

res = main(iter)
print(res)
require("jit.p").stop()
