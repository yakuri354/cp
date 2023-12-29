import math
t = int(input())

for iii in range(t):
    x = int(input())
    if x % 2 == 1:
        print(0)
    else:
        print((math.factorial(x / 2) ^ 2) % 998244353)