# Enter your code here. Read input from STDIN. Print output to STDOUT
import math

def normal_std(x, mean, stddev):
    def fi(x):
        return pow(math.e, -1 * (pow(x, 2) / 2) ) / pow(2 * math.pi ,0.5)
    return (1/stddev) * fi((x-mean)/stddev)


max_weight = int(input())
num_boxes = int(input())
mean_weight_cargo = int(input())
stddev = int(input())

# sample average = sum(xi) / n
# sample sum = 
# mean' = n * mean 
# sigma' = pow(n, 0.5) * sigma

f = 2 * stddev
curr = mean_weight_cargo - f
end = mean_weight_cargo + f
step = (end - curr) / 1e6

def cumulative(start, end, step):
    curr = start
    total = 0.0
    while curr <= end:
        total += normal_std(curr, mean_weight_cargo, stddev) * step
        curr += step
    return total


print("%.3f" % cumulative(curr, 200, step))
