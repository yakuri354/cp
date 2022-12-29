import sys

i = 1

while True:
    print(f"? {i} {i+1}")
    sys.stdout.flush()
    ans = int(input())
    if ans == -1:
        print(f"! {i}")
        exit()
    print(f"? {i+1} {i}")
    sys.stdout.flush()
    ans2 = int(input())

    if ans == ans2:
        i += 1
        continue

    print(f"! {ans + ans2}")
    exit()
