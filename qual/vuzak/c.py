n, k, a, b, c = [int(input()) for _ in range(5)]

ab = a + b <= k
bc = b + c <= k
ac = a + c <= k

abc = a + b + c <= k
p2 = [ab, bc, ac]

if abc:
    print(n)
elif ab and bc and ac:
    z = n % 3
    if z == 2:
        print((n // 3) * 2 + 1)
    else:
        print((n // 3) * 2)
elif p2.count(False) < 3:
    print(n // 2)
else:
    print(n // 3)
