import random
import sys
n = int(sys.argv[1])
data = list(range(2 * n))
random.shuffle(data)
kind = [0] * (2 * n)
for i, e in enumerate(data):
    kind[e] = i // 2

print([x + 1 for x in data], file=sys.stderr)

random.shuffle(data)

inside = set()
ik = dict()
outside = set(data)

print(n, flush=True)
while True:
    s = input()

    if s[0] == '?':
        x = int(s.split()[1]) - 1
        if x in inside:
            inside.remove(x)
            ik[kind[x]] -= 1
            if ik[kind[x]] <= 0:
                del ik[kind[x]]
            outside.add(x)
        elif x in outside:
            outside.remove(x)
            if not kind[x] in ik:
                ik[kind[x]] = 0
            ik[kind[x]] += 1
            inside.add(x)
        print(len(ik), flush=True)

    if s[0] == '!':
        ans = s.split()[1:]
        assert len(set(ans)) == 2 * n

        error = False
        for i in range(0, 2 * n, 2):
            a = int(ans[i]) - 1
            b = int(ans[i+1]) - 1
            if ans[i] == ans[i+1]:
                print("eq")
                error = True
            if kind[a] != kind[b]:
                print(f"not equal k[{a + 1}] != k[{b + 1}] ({kind[a]} != {kind[b]})", file=sys.stderr)
                error = True

        if error:
            raise Exception()
        exit()