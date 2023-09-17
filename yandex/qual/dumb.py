#!/usr/bin/env python3.11
n = int(input())
s = input()

def z(n):
    if n == 0:
        return 0
    return 1 + z(n % n.bit_count())

def b2d(s):
    ans = 0
    pw = 1
    for c in s[::-1]:
        if c == '1':
            ans += pw
        pw *= 2
    return ans

for i in range(n):
    s2 = list(s)
    s2[i] = str(int(s2[i]) ^ 1)
    print(z(b2d("".join(s2))))
