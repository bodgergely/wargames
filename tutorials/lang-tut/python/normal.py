# Enter your code here. Read input from STDIN. Print output to STDOUT
import math

def normal(x, mean, var):
    stddev = pow(var, 0.5)
    term1 = 1 / (stddev * math.pow(2*math.pi, 0.5))
    term2 = pow(math.e, -1 * (pow((x-mean), 2) / (2* var) ))
    return term1 * term2

def integral(a, b, fun, granularity=1e5):
    total = 0.0
    a, b = float(a), float(b)
    if a == b:
        b += 1e-10
    step = abs(a - b)/granularity
    c = a
    while c <= b:
        total += fun(c) * step
        c+=step
    return total


def erf(x, z):
    """Error function"""
    term1 = 2 / pow(math.pi, 0.5)
    term2 = integral(0, z, lambda x: pow(math.e, pow(x, 2) ) )
    return term1 * term2

def cum_normal(x, mean, stddev): 
    v = (x - mean) / (stddev * pow(2, 0.5))
    return 0.5 * (1 + erf(x, v))

def normal_std(x, mean, var):
    def fi(x):
        return pow(math.e, -1 * (pow(x, 2) / 2) ) / pow(2 * math.pi ,0.5) 
    stddev = pow(var, 0.5)
    return 1/stddev * fi((x-mean)/stddev)


mean, stddev = [float(i) for i in input().split()]
q1 = float(input())
begin, end = [float(i) for i in input().split()]

a1 = cum_normal(q1, mean, stddev)
print("%.3f" % a1)
a2 = cum_normal(end, mean, stddev) - cum_normal(begin, mean, stddev)
print("%.3f" % a2)

