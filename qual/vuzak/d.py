# n, t = [int(x) for x in input().split()]
t = 2
# a = [int(x) for x in input().split()]
a = [int(1e9) for _ in range(int(1e5))]

prev = a[0]
val = 0
vad = 0
for i in a[1:]:
    if i <= prev:
        k = 0
        lo = -1
        hi = int(1e5)
        while hi - lo > 1:
            m = (lo + hi) // 2
            if i + (2 ** m) > prev:
                hi = m
            else:
                lo = m
        # print(f"{hi=} {lo=} {prev=} {i + (2 ** hi)=}")
        k = hi
        vad += 1
        val += k + 1
        prev = i + 2 ** k
    else:
        prev = i
if t == 1:
    print(vad)
else:
    print(val)

