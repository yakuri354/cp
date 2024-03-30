from random import randint as ri
import sys

def test():
    n = ri(1, 500)
    # n = 500

    print(n)

    a = [[0] * n for _ in range(n)]

    for i in range(n):
        for j in range(i + 1, n):
            a[i][j] = ri(0, 1)
            a[j][i] = a[i][j] ^ 1

    good = [x for x in range(n) if sum(a[x][y] for y in range(n)) < 2]

    cntr = 0

    while True:
        s = input().split()
        
        if s[0] == '?':
            if s[1] == s[2]:
                print("BAD REQUEST")
                exit(-1)
            print('forward' if a[int(s[1]) - 1][int(s[2]) - 1] == 1 else 'backward')
            cntr += 1
            if cntr > n * 4:
                print("LIMIT")
                exit(-1)
        if s[0] == '!':
            if (s[1] == '-1' and len(good) == 0) or int(s[1]) - 1 in good:
                print("OK")
                #print(round(cntr / n, 2), file=sys.stderr)
                print(cntr, file=sys.stderr)
                return
            else:
                print("WRONG")
                print("right: " + " ".join(str(x + 1) for x in good))
                print("\n".join(
                    " ".join(str(x) for x in i) for i in a
                ))
                exit(-1)

t = 1000000

print(0, t)

for i in range(t):
    test()