from subprocess import Popen, PIPE
from random import randint as ri
import sys

# path = sys.argv[1]
path = "roi/2022/d2/build/b2.cpp.out"
n = 2
q = 1
c = 100

def calc(l, qs):
    ans = []
    for k, i in qs:
        l1 = l.copy()
        for _ in range(k):
            l2 = [l1[i] + len(set(x for x in l1 if x > l1[i])) for i in range(n - 1)] + [l1[-1]]
            l1 = l2
        ans.append(l1[i-1])
    return ans

its = 0
while True:
    # if its % 1000 == 0:
    #     print(its)
    proc = Popen(path, text=True, stdin=PIPE, stdout=PIPE)
    l = [ri(0, c) for _ in range(n)]
    qs = [(ri(0, c), ri(1, n)) for _ in range(q)]
    ans = calc(l, qs)

    qss = [f"3 {k} {i}" for k, i in qs]
    tst = "\n".join([f"{n} {q}", " ".join(str(x) for x in l)] + qss) + "\n"
    # print(tst)
    res = list(map(int, proc.communicate(tst)[0].split()))

    if res != ans:
        print("fail")
        print(tst)
        print()
        print("exp", ans)
        print()
        print("got", res)
        exit(-1)