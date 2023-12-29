n, m, r = [int(x) for x in input().split()]
ans = input()
ar = [input() for _ in range(m)]

def lerr(s):
    ctr = 0
    mctr = 0
    for (i, j) in zip(ans, s):
        if i != j:
            ctr += 1
        else:
            ctr = 0
        mctr = max(ctr, mctr)
    return mctr

lerrs = [lerr(s) for s in ar]

print("\n".join([str(s) for s in lerrs]))

if max(lerrs) >= r:
    print("YES")
else:
    print("NO")
