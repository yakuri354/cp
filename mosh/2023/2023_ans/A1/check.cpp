#include "testlib.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int t;
    t = inf.readInt();
    int score = 0;
    for (int testcase = 0; testcase < t; ++testcase) {
        int jans = ans.readInt();
        int pans = ouf.readInt();
        if (pans == jans) {
            score += 10;
        }
    }
    quitp(score, "participant's solution is ok");
    return 0;
}