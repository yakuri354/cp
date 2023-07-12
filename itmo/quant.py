l = 6
p1 = l
p2 = l
p3 = l
sq = [0]
while True:
    z1 = min(p1, 4)
    sq += [1] * z1
    p1 -= z1
    if p1 == 0:
        p1 = l

    z2 = min(p2, 4)
    sq += [2] * z2
    p2 -= z2
    if p2 == 0:
        p2 = l

    z3 = min(p3, 4)
    sq += [3] * z3
    p3 -= z3
    if p3 == 0:
        p3 = l

    if len(sq) > 1000:
        break
