from random import *

n = 1000
t = 642
print(n, t)

def rp():
    return int(gauss(0, 100000)), int(gauss(0, 100000))

for i in range(n):
    print(*rp())