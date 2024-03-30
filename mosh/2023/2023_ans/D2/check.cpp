#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;


int dist(const string &a, const string &b) {
    vector<int> dp(a.size() + 1);
    iota(dp.begin(), dp.end(), 0);

    for (int i = 1; i <= b.size(); i++) {
        vector<int> nw(a.size() + 1);
        nw[0] = i;
        for (int j = 1; j <= a.size(); j++) {
            nw[j] = min({dp[j] + 1, nw[j - 1] + 1, dp[j - 1] + (a[j - 1] != b[i - 1])});
        }
        dp = nw;
    }
    return dp.back();
}


int count_score(const vector<string> &words, const vector<string> &lines, InStream &stream) {  // 0 if wrong format
    vector<int> cnt = stream.readInts(lines.size(), 1, words.size(), "word counts");
    stream.ensuref(accumulate(cnt.begin(), cnt.end(), 0) == words.size(),
                   "number of words in partition is not equal to original number of words in s");

    int pos = 0;
    int diff = 0;
    for (int line = 0; line < lines.size(); line++) {
        string now;
        for (int _ = 0; _ < cnt[line]; _++) {
            now += words[pos++] + " ";
        }
        now.pop_back();
        diff += dist(lines[line], now);
    }
    return diff;
}


int main(int argc, char *argv[]) {
    setName("text-slicing-check");
    registerTestlibCmd(argc, argv);

    double total_score = 0;
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

        int p_ans = count_score(words, lines, ouf);
        int j_ans = count_score(words, lines, ans);
        if (p_ans < j_ans) {
            quitf(_fail, "Participant's answer is better that jury's");
        }
        total_score += min(5., 5 * (double) j_ans / (double) p_ans);
    }
    quitp(total_score);
}
