#include <bits/stdc++.h>
#include"testlib.h"
using namespace std;
vector<vector<int>> a;

map<string, string> params;

long long get(string name, long long def = 0) {
    if (params.count(name)) {
        return stoll(params[name]);
    }
    else {
        return def;
    }
}
int tests;
vector<int> ns;
vector<vector<vector<int>>> as;
vector<long long> checkAns(InStream& stream)
{
    vector<long long> result;
    for (int testnum = 0; testnum < tests; ++testnum) {
        vector<vector<int>> triples;
        map<int, int> cnt;
        for (int i = 0; i < ns[testnum] / 3; ++i) {
            triples.push_back(vector<int>(3));
            for (int j = 0; j < 3; ++j) {
                triples[i][j] = stream.readInt(1, ns[testnum], "vertex");
            }
        }
        for (auto i : triples) for (int j : i) ++cnt[j];
		for (int i = 1; i <= ns[testnum]; ++i) {
			if (cnt.find(i) == cnt.end()) {
				quitf(_wa, "in testnum %d number %d is not used", testnum, i);
			}
			if (cnt[i] > 1) {
				quitf(_wa, "in testnum %d number %d used twice", testnum, i);
			}
		}

        long long sum = 0;
        for (auto i : triples) {
            long long prod = 1;
            for (int j = 0; j < 3; ++j) {
                prod *= as[testnum][i[j] - 1][i[(j + 1) % 3] - 1];
            }
            sum += prod;
        }
        result.push_back(sum);
    }
    return result;
}
double score(long long jury, long long participant) {
    if (participant > jury) {
        return 11;
    }
    double tmp = (double)participant / jury;
    return 10 * tmp * tmp * tmp;
}
int main(int argc, char* argv[]) {
    setName("checking optimal partition");

    registerTestlibCmd(argc, argv);
    tests = inf.readInt();
    ns.resize(tests);
    as.resize(tests);

    for (int i = 0; i < tests; ++i) {
        int n = inf.readInt();
        ns[i] = n;
        as[i].assign(n, vector<int>(n, 0));
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                as[i][x][y] = inf.readInt();
            }
        }
    }
    vector<long long> t_ans = checkAns(ans);
    vector<long long> t_out = checkAns(ouf);
    double sum = 0;
    for (int i = 0; i < tests; ++i) {
		double scr = score(t_ans[i], t_out[i]);
		sum += scr;
    }
    //quitp(sum);
	quitf(_ok, "accepted for testing");
}
