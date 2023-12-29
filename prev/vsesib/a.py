tab = [list(input().split()) for i in range(10)]
atw = list(input().split())
wat = list(input().split())

q = int(input())
for _ in range(q):
    a, b = input().split()
    if len(a) < len(b):
        a = '@' * (len(b) - len(a)) + a
    if len(b) < len(a):
        b = '@' * (len(a) - len(b)) + b
    
    ans = ''
    for (i, j) in zip(a, b):
        if i == '@':
            res = atw[int(j)]
        elif j == '@':
            res = wat[int(i)]
        else:
            res = tab[int(i)][int(j)]
        ans += res
    print(ans)
