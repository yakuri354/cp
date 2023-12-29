import random

n = int(1e5)
l = n
w = int(1e9)

print(n, l, w)

for i in range(n - 1):
    print(i + 1, random.randint(0, int(1e4)))