#!/usr/bin/env python3.11
from random import *

n = randint(1, 50)

a = [str(randint(1, 50)) for i in range(n)]
b = [str(randint(1, 50)) for i in range(n)]

print(n)
print(" ".join(a))
print(" ".join(b))