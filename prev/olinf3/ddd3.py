s = input()

s1 = s[0:len(s)//2]
diffs = []
if len(s) % 2 == 0:
    s2 = s[len(s)//2:][::-1]
    for i in range(len(s1)):
        if s1[i] != s2[i]:
            diffs.append([s1[i], s2[i]])
    if len(diffs) == 2 and (diffs[0] == diffs[1] or diffs[0] == diffs[1][::-1]):
        print("YES")
        exit()
else:
    s2 = s[len(s)//2+1:][::-1]
    mid = s[len(s)//2]
    # print(f"{s1=} {s2=}")
    for i in range(len(s1)):
        if s1[i] != s2[i]:
            diffs.append([s1[i], s2[i]])
    if (len(diffs) == 1 and mid in diffs[0]) or (len(diffs) == 2 and (diffs[0] == diffs[1] or diffs[0] == diffs[1][::-1])):
        print("YES")
        exit()

if len(diffs) == 0:
    print("YES")
else:
    print("NO")

