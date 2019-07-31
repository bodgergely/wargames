a = {"one", "two", "three"}

function iter(a, i)
    i = i + 1
    local v = a[i]
    if v then
        return i, v
    end
end

function ipairs(a)
    return iter, a, 0
end

for i, v in ipairs(a) do
    print(i, v)
end

print("--------------------")

function ppairs(t)
    return next, t, nil
end

for k, v in ppairs(a) do
    print(k, v)
end

c = ""
for i= 1, 10 do
    c = c.."-"
end
print(c)

for i, k in next, a do
    print(i, k)
end


