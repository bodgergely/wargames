a = {3,34,1,5,7}
v = 5
local i = 1
while a[i] do
    if a[i] == v then
        break
    end
    i = i + 1
end

print("Found at postion:", i)


