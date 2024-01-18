from functools import cache

n, p, v = map(int, input().split())

@cache
def dp(n, x):
    if x <= 1:
        return n
    
    