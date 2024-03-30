from itertools import permutations, groupby
import sys
from math import factorial

def translate(p1: list[int]):
    n = len(p1) + 2
    p2 = [0] * n
    p2[0] = n - 1

    last = n - 1
    for i in range(0, n-2):
        p2[last] = p1.index(i) + 1
        last = p2[last]
    
    p2[last] = 0

    return p2

def gen(n):
    ps = list(permutations(range(0, n - 2)))
    ps2 = [translate(list(x)) for x in ps]
    ps2.sort()

    return [k for k, _ in groupby(ps2)]

def modify(l: list[int], i, x):
    l1 = l.copy()
    l1[i] = x
    return l1

def fin(l: list[int], i):
    if l[i] == i or l[i] == -1:
        return i
    else:
        return fin(l, l[i])

def zzz(n, free: set[int], to: list[int], p: int):
    if n == 0:
        return [[]]
    
    return [
        [x] + y
        for x in free
        for y in zzz(n - 1, free - {x}, modify(to, p, x), p + 1)
        if p != x and p != fin(to, x)
    ]

def z0(n):
    return zzz(n, set(range(n)), [-1] * (n + 1), 1)

def gk(n, k):
    free = set(range(n))
    to = [-1] * (n + 1)

    for i in range(1, n + 1):
        for x in free:
            if i != x and i != fin(to, x):
                cnt = factorial(max(n - i - 1, 0))
                if k < cnt:
                    to[i] = x
                    free.remove(x)
                    break
                else:
                    k -= cnt
        if to[i] == -1:
            return []
    
    to[0] = n
    return to

z0(5)

print(gk(6, 0))