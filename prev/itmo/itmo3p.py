fail = [64, 116, 337]
sz = 384

def chkr(totr, t, n):
    if totr <= 0:
        return (t, n)
    bt = min(n, totr) + 1
    if any(x in range(t, t + bt) for x in fail):
        return chkr(totr, t + bt, n)
    else:
        return chkr(totr - bt + 1, t + bt, n)

print(min(chkr(sz, 0, n) for n in range(1, sz)))
