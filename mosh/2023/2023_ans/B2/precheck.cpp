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
        bool flag = true;
        int jlen = ans.readInt();
        int plen = ouf.readInt();
        vector <int> jdays(jlen);
        for (int i = 0; i < jlen; ++i) {
            jdays[i] = ans.readInt();
        }
		if (plen < 0) {
			quitf(_wa, "negative number of days");
		} 
        vector <int> pdays(plen);
        for (int i = 0; i < plen; ++i) {
            pdays[i] = ouf.readInt();			
			if (pdays[i] < 0) {
				quitf(_wa, "negative number of days");
			}

        }
        if (jlen != plen) {
            flag = false;
        } else {
            for (int i = 0; i < plen; ++i) {
                if (pdays[i] != jdays[i]) {
                    flag = false;
                }
            }

        }

        if (flag) {
            score += 10;
        }
    }
    //quitp(score, "participant's solution is ok");
	quitf(_ok, "accepted for testing");
    return 0;
}