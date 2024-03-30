from random import randint
from sys import stderr

def test():
    n = 20
    print(n, flush=True)
    a = []

    for i in range(n):
        x = randint(0, 100)
        while x in a:
            x = randint(0, 100)
        a.append(x)

    # a = sorted(a)

    # for i in range(5):
    #     x = randint(0, n - 1)
    #     y = randint(0, n - 1)
    #     a[x], a[y] = a[y], a[x]

    while True:
        s = input().split()
        if s[0] == '?':
            print(min([a[int(x)] for x in s[1:3]]), flush=True)
        if s[0] == '!':
            sim = [a[i] == int(s[i+1]) for i in range(n)].count(True)
            if sim > 2:
                print("NO", file=stderr)
                print(a, file=stderr)
                print(s, file=stderr)
                exit(-1)
            print("OK", file=stderr)
        
test()