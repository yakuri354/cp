#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char *argv[]) {
    setName("text-slicing-precheck");
    registerTestlibCmd(argc, argv);

    auto testCaseCount = inf.readInt();
    for (int testCase = 1; testCase <= testCaseCount; testCase++) {
        setTestCase(testCase);
        int n = inf.readInt();
        vector<string> words(n);
        for (auto &i: words) {
            i = inf.readToken();
        }

        int m = inf.readInt();
        vector<string> lines;
        for (int _ = 0; _ < m; _++) {
            int k = inf.readInt();
            lines.emplace_back("");

            for (int i = 0; i < k; i++) {
                string s = inf.readToken();
                lines.back() += s + " ";
            }
            lines.back().pop_back();
        }

        vector<int> cnt = ouf.readInts(lines.size(), 0, words.size(), "word counts");
        ouf.ensuref(accumulate(cnt.begin(), cnt.end(), 0) == words.size(), "Number of words in partition is not equal to original number of words in s");
    }
    quitf(_ok, "Output format is correct");
}
