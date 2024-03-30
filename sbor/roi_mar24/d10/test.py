import random
from random import randint
from subprocess import run, Popen, PIPE
from sys import argv, stderr
from io import TextIOWrapper

def rndexcl(a, b, *x):
    while (y := randint(a, b)) in x:
        continue
    return y

n = 20
tree = [randint(0, i) for i in range(n)]
if not 0 in tree:
    tree[0] = 0
w = [randint(1, 3) for i in range(n)]

p = Popen([argv[1]], stdin=PIPE, stdout=PIPE, stderr=PIPE)
tin, tout = TextIOWrapper(p.stdin), TextIOWrapper(p.stdout) # type: ignore
write = lambda *x: print(*x, file=tin, flush=True)
read = lambda: tout.readline()

write(n)
print(n)
write(*tree)
print(*tree)
write(*w)
print(*w)

ans = int(read())
perm = list(map(int, read().split()))
weights = list(map(int, read().split()))
comb = int(read())

print(ans)
print(perm)
print(weights)
print(comb)