from random import randint as ri

n = 200000
q = 200000

print(n, q)

l = [ri(0, int(1e9)) for _ in range(n)]

print(*l)

for _ in range(q):
    l, r = ri(1, n), ri(1, n)
    if ri(0, 3) == 0:
        x = ri(0, int(1e9))

        print(2, l, r, x)
    else:
        print(1 + 2 * ri(0, 1), l, r)