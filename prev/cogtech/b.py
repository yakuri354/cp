import functools

def fuck(n):
    if n == 0: return 1
    return functools.reduce(lambda a, b: a * b, [x ** x for x in range(1, n + 1)], 1)

sums = []

for i in range(100):
    for j in range(100):
        x = fuck(i) + fuck(j)
        if x > int(1e9):
            break
        sums.append(x)

print("YES" if int(input()) in sums else "NO")