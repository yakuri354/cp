from dataclasses import dataclass
import re
t = int(input())

@dataclass
class Song:
    name: str
    author: str
    length: int

@dataclass
class Playlist:
    name: str
    songs: list[Song]
    length: int

@dataclass
class Query:
    typ: str
    plist: str
    time: int

def read_pl():
    namep, n = re.compile('\\"([a-zA-Z ]*)\\" ([0-9]*)').match(input()).groups()
    n = int(n)
    ln = 0

    songs = []
    r = re.compile('  \\"([a-zA-Z ]*)\\" song \\"([a-zA-Z ]*)\\" length ([0-9]{2}):([0-9]{2})')
    for _ in range(n):
        rr = r.match(input()).groups()
        timei = int(rr[2]) * 60 + int(rr[3])
        songs.append(Song(rr[1], rr[0], timei))
        ln += timei

    return Playlist(namep, songs, ln)

def read_qr():
    z = re.compile('(Restart|Play) \\"([a-zA-Z ]*)\\" for ([0-9]{2}):([0-9]{2})').match(input()).groups()
    timei = int(z[2]) * 60 + int(z[3])
    return Query(z[0], z[1], timei)

def getby(l, k):
    return [x for x in l if x[0] == k][0]

class K(tuple):
    def __lt__(self, other):
        if self[0] == other[0]:
            return self[1] < other[1]
        return self[0] > other[0]

for _ in range(t):
    input()
    try:
        pls = [read_pl() for _ in range(int(input()))]
        pls_by_name = {i.name: i for i in pls}
        next_song = {i.name: 0 for i in pls}
        pl_tst = {i.name: 0 for i in pls}
        song_st = {i: 0 for p in pls for i in p.songs}

        # print(f"{pls=}\n{pls_by_name=}\n{song_st=}")

        qs = [read_qr() for _ in range(int(input()))]
    except:
        exit()

    for i in qs:
        pl = pls_by_name[i.plist]
        if i.typ == "Restart":
            next_song[i.plist] = 0
        elapsed = 0
        while elapsed < i.time and next_song[i.plist] < len(pl.songs):
            nxt = pl.songs[next_song[i.plist]]
            song_st[nxt] += 1
            elapsed += nxt.length
            next_song[i.plist] += 1

    try:
        ans = []
        for k, v in song_st.items():
            if v > 0:
                ans.append((v, (k.author, k.name)))
        ans = sorted(ans, key=K)
        print(len(ans))
        ans = [f'"{x[1][0]}" song "{x[1][1]}" played {x[0]} times' for x in ans]
        print("\n".join(ans))
    except:
        exit()
