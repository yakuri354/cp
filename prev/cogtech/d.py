from math import hypot, sqrt
r, b, a = [float(input()) for _ in range(3)]

lo = float(0)
hi = r

def dst(x):
    z = sqrt(r * r - x * x)
    return a - z + hypot(z, b - x);

while hi - lo > 1e-7:
    m1 = lo + (hi - lo) / 3
    m2 = lo + 2 * (hi - lo) / 3

    if dst(m1) <= dst(m2):
        hi = m2
    else:
        lo = m1

print(dst(lo))