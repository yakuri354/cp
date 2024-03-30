import math

n, k, m = [int(x) for x in input().split()]

print(math.comb(n - k + 1, n) % m)