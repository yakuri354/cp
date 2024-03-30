from random import shuffle

n = int(input())

ok = [0] * n

def ask(a, b):
    print("?", a + 1, b + 1, flush=True)
    return int(input())

pos = [0, 1]
val = ask(0, 1)

order = list(range(2, n))
shuffle(order)

for i in order:
    res = ask(pos[-1], i)

    if res < val:
        ok[i] = res
    else:
        if res == val:
            ok[pos[-1]] = res
            pos.remove(pos[-1])
            val = ask(pos[0], i)
        else:
            ok[pos[-2]] = val
            pos.remove(pos[-2])

            val = res
        pos.append(i)

for i in pos:
    ok[i] = val

print("!", *ok, flush=True)