import os, sys

_, gen, good, bad = sys.argv

while True:
    os.system(f"./{gen} > test.txt")
    os.system(f"./{good} < test.txt > goodans.txt")
    os.system(f"./{bad} < test.txt > badans.txt")
    if (goodans := open('goodans.txt').read()) != (badans := open('badans.txt').read()):
        print("ERR")
        print()
        print(open('test.txt').read())
        print()
        print(goodans)
        print()
        print(badans)
        print()
        exit(1)
