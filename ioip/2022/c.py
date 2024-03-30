k, m = map(int, input().split())

def ord64(c):
    x = ord(c)

    if x >= 97:
        return x - 97 + 38

    if x >= 65:
        return x - 65 + 12

    if x >= 48:
        return x - 48 + 2

    if x >= 35:
        return x - 35

    if x in [35, 36]:
        return x - 35
    
    exit(-1)

def unb64(s):
    ans = 0
    for i in range(len(s)):
        ans += ord64(s[i]) * int(64 ** (len(s) - i - 1))
    return ans

def bn(x, l):
    return "".join(['1' if (x & (1 << i)) > 0 else '0' for i in range(l)])

for _ in range(m):
    s0, s1 = input().split()
    p0, p1 = unb64(s0), unb64(s1)
    b0, b1 = bn(p0, 6 * k), bn(p1, 6 * k)

    if not b0 in (b1 + b1):
        print(-1)
        continue

    x = (b1 + b1).find(b0)

    print(x)