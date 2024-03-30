import os, sys, math, random

_, f1 = sys.argv

def prime(a):
     return not (a < 2 or any(a % x == 0 for x in range(2, int(a ** 0.5) + 1)))

for i in range(int(1000000)):
    if i % 1000 == 0:
        print('Test', i + 1)

    n = random.randint(1, 1000)
    k = random.randint(1, n)
    m = 4
    while not prime(m):
        m = random.randint(1, 10000)

    ans = 0 if n - k + 1 < k else (math.comb(n - k + 1, k) % m)

    os.popen(f"echo {n} {k} {m} > test.txt")

    v1 = int(os.popen(f'./{f1} < test.txt').read().strip())
    if v1 != ans:
        print("Failed test:")
        print(open("test.txt").read())
        print(f'Output of {f1}:')
        print(v1)
        print(f'Ans:')
        print(ans)
        break
