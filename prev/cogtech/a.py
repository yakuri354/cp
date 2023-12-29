a = ["OK", "WA", "PE", "RE", "ML", "TL"]

n = int(input())
z = [input().strip() for _ in range(n)]

print("\n".join([x for x in a if not x in z]))