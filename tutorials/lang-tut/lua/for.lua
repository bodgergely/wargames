-- numeric for and generic for

-- numeric for

f = function(x)
        return x * 2
    end

for i=1,f(3) do
    print(i)
end

print("==============")

for i=10,1,-1 do print(i) end

print("==============")

print("generic for:")

a = {6,4,2,7,9}
for i,v in ipairs(a) do print(v) end

days = {"Sunday", "Monday", "Tuesday", "Wednesday",
            "Thursday", "Friday", "Saturday"}

revDays = {}
for i, v in ipairs(days) do
    revDays[v] = i
end

print("Days:")

for day, i in pairs(revDays) do
    print(day, i)
end


