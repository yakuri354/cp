from random import randint

n = 20
a = []

for i in range(n):
    x = randint(0, 100)
    while x in a:
        x = randint(0, 100)
    a.append(x)

a = sorted(a)

for i in range(5):
    x = randint(0, n - 1)
    y = randint(0, n - 1)
    a[x], a[y] = a[y], a[x]

print(*[f"{i:<2}" for i in a])

pos = [0, 1]
val = min(a[0], a[1])

print("start", pos, val)

ok = [0] * n
ok[pos[-1]] = val

for i in range(2, n):
    res = min(a[pos[-1]], a[i])

    if res < val:
        ok[i] = res
        print("ok", i, res)
    else: # res >= pos
        if res == val:
            print("mid", pos[-1], res)
            ok[pos[-1]] = res
            pos.remove(pos[-1])
            val = min(a[pos[-1]], a[i])
            
        else:
            print("lef", pos[-2], val)
            ok[pos[-2]] = val
            pos.remove(pos[-2])

            val = res
        pos.append(i)

        print(" -> ", pos, val)

for i in pos:
    ok[i] = val
