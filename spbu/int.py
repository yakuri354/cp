from random import shuffle
import subprocess
from sys import stderr

n = 5
print(n, flush=True)
p = list(range(n))
shuffle(p)
orig = p.copy()

while True:
    try:
        a, b = [int(x) - 1 for x in input().split()]
    except:
        break

    old = p
    p[a], p[b] = p[b], p[a]
    p = p[1:] + [p[0]]

    print('<' if p < old else '>', flush=True)
    print("now", p, file=stderr)

print(orig)
print(p)