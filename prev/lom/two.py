from functools import cmp_to_key

chars = dict()
chars['a'] = 1
chars['b'] = 5
chars['c'] = 10
chars['d'] = 50
chars['e'] = 100
chars['f'] = 200
chars['g'] = 500
chars['h'] = 1000
chars['i'] = 2500
chars['A'] = 500
chars['B'] = 1000
chars['C'] = 5000
chars['D'] = 10000
chars['E'] = 20000
chars['F'] = 50000
chars['G'] = 100000
chars['H'] = 200000
chars['I'] = 500000

n = int(input())

ar = []

for i in range(n):
    s = input()
    cur = 0
    for j in s:
        if ord(j) >= ord('0') and ord(j) <= ord('9'):
            cur *= 10
            cur += ord(j) - ord('0')
        else:
            ar.append(chars[j] * cur)
            cur = 0

difs = [(i, j, abs(ar[i] - ar[j])) for i in range(n) for j in range(n)]

def k(a):
    return (a[2], a[0] + a[1])

difs.sort(key=k)
difs.reverse()

difs = [(x[0] + 1, x[1] + 1, x[2]) for x in difs]

print(difs[0][0])
print(difs[0][1])