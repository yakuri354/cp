from random import randint, shuffle

def rperm(n):
    l = list(range(n))
    shuffle(l)
    return l

def inv(p):
    return sum(x > p[i] for i in range(len(p)) for x in p[:i])

n = 10

while True:
    p = rperm(n)
    
    mp = min(p[i:] + p[:i] for i in range(len(p)))
    mi = min((p[i:] + p[:i] for i in range(len(p))), key=inv)

    if inv(mp) != inv(mi):
        print(p)
        print(mp, inv(mp))
        print(mi, inv(mi))
        exit(0)
        