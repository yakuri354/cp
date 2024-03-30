from subprocess import Popen, PIPE
import sys
from random import randint as ri

n = 100
t = 10000
h = 10000000

def write(p, s):
    print("--> " + str(s))
    p.stdin.write(str(s) + '\n')
    p.stdin.flush()

def read(p):
    s = p.stdout.readline()
    print("<-- " + s)
    return s

while True:
    p = Popen(sys.argv[1], text=True, stdin=PIPE, stdout=PIPE)

    write(p, t)
    write(p, f"{n} {h} {10000}")
    for _ in range(t):
        a = [ri(0, h) for _ in range(n)]
        a0 = a.copy()
        while True:
            z = read(p).split()
            i = int(z[1]) - 1
            if z[0] == '!':
                if int(z[1]) == sum(a0):
                    write(p, "OK")
                    break
                else:
                    write(p, "-1")
                    print("array was: ", a0, "with sum", sum(a0))
                    exit(-1)
            if z[0] == '?':
                write(p, sum(1 for x in a if x >= a[i]))
            if z[0] == '-':
                x = int(z[2])
                if a[i] >= x:
                    a[i] -= x
                    write(p, "OK")
                else:
                    write(p, "FAIL")
    print("done", t)