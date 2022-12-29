n = int(input())

if n <= 3 or n * (n + 1) % 3 != 0:
    print(-1)
    exit()

a = (n * (n + 1)) // 6

fst = []
snd = []

free = [True for _ in range(n+1)]
lst = n

rem = a
while rem >= lst:
    fst.append(lst)
    rem -= lst
    free[lst] = False
    lst -= 1

if rem != 0:
    fst.append(rem)
    free[rem] = False


rem = a
while rem >= lst:
    if not free[lst]:
        lst -= 1
        continue
    snd.append(lst)
    rem -= lst
    free[lst] = False
    lst -= 1

if rem != 0:
    if not free[rem]:
        snd.append(1)
        snd.append(rem - 1)
        free[1] = False
        free[rem-1] = False
    else:
        snd.append(rem)
        free[rem] = False

print(len(fst))
print(" ".join((str(x) for x in fst)))
print(len(snd))
print(" ".join((str(x) for x in snd)))

trd = [x for x in range(1, n + 1) if free[x]]

print(len(trd))
print(" ".join((str(x) for x in trd)))
