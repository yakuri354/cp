n, A = map(int, input().split())
a = list(zip(map(int, input().split()), range(n)))

a.sort()

ans = 0
al = 0
ar = 0

for i in range(n - 1):
    lo = i + 1
    hi = n

    while hi - lo > 1:
        m = (lo + hi) // 2
        if a[i][0] * a[m][0] <= A:
            lo = m
        else:
            hi = m
        
    if a[i][0] * a[lo][0] <= A and a[i][0] * a[lo][0] > ans:
        ans = a[i][0] * a[lo][0]
        al = a[i][1]
        ar = a[lo][1]

if ans == 0:
    print(0)
    exit(0)
else:
    print(ans)
    print(al + 1, ar + 1)