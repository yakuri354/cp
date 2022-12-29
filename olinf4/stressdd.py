import random
import os
import subprocess
cwdd = os.path.dirname(os.path.realpath(__file__)) 
l = 100
q = 100
mx = 100000
mxv = 100000

def gq():
    if random.choice([True, False]):
        return f"1 {random.randint(1, l)} {random.randint(0, mx)}"
    else:
        return f"2 {random.randint(1, mxv)}"

while True:
    d = [str(random.randint(0, mx)) for i in range(l)]
    qs = [gq() for i in range(q)]
    inp = "\n".join([f"{l} {q}", " ".join(d)] + qs)
    r1 = subprocess.Popen(["./dd4.cpp.out"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=cwdd)
    r2 = subprocess.Popen(["./dd4fuckingimbecile.cpp.out"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=cwdd)
    ress = [x.communicate(input=bytes(inp, 'utf-8')) for x in [r1, r2]]
    if ress[0] != ress[1]:
        print("ERR")
        print(inp)
        print("R1")
        print(ress[0][0].decode('utf-8'))
        print(ress[0][1].decode('utf-8'))
        print("R2")
        print(ress[1][0].decode('utf-8'))
        print(ress[1][1].decode('utf-8'))

