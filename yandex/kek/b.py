from math import comb

n = int(input())

print(comb(n, 4) + comb(n, 2) + 1)