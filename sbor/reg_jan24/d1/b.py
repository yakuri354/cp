import re

regex = re.compile(r'(?:(?<=^)|(?<=\s))(http\:\/\/[a-z0-9\/\:\.]{1,})(?=$|\s)')

l = int(input())
t = input()

sz = len(t)

def replace(m: re.Match):
    global sz

    link = m.group(1)

    shrink = min(sz - l, len(link) - 3)
    sz -= shrink

    if shrink > 0:
        return link[:-(shrink + 3)] + '...'
    else:
        return link

t2 = re.sub(regex, replace, t)

print(t2)
print(sz - l)