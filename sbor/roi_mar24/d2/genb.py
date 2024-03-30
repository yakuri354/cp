import random

n = 50000
k = 1
m = 50000
q = 10000

print(k, n, m, q)

for i in range(n):
    print(i, i + 1, random.randint(0, 10000))

for i in range(q):
    # a = random.randint(0, n - 2)
    # b = random.randint(a + 1, n - 1);
    print(10, n - 1)