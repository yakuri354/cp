#include <climits>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#include "testlib.h"

using ll = long long;
using ld = long double;

void LoadInitial(ll& n, ll &m, ll& empty, std::vector<std::vector<ll>>& stacks) {
    empty = 0;
    n = inf.readLong(0ll, 10000ll, "n");
    m = inf.readLong(0ll, 10000ll, "m");
    stacks.assign(n, std::vector<ll>());
    for (int i = 0; i < n; ++i) {
        ll cnt = inf.readLong(0ll, m, "length of a bucket");
        if (cnt != 0 && cnt != m) {
            quit(_fail, "Input file is incorrect : Got neither full nor empty bucket. m = " + std::to_string(m) + " cnt = " + std::to_string(cnt));
        }
        for (int j = 0; j < cnt; ++j) {
            stacks[i].push_back(inf.readLong(0, n, "bubble"));
        }
        empty += (cnt == 0);
    }
}

void LoadMovesParticipant(ll n, std::vector<std::pair<ll, ll>>& moves) {
    ll moves_cnt = ouf.readLong(0ll, 2000000000, "moves_cnt");
    moves.resize(moves_cnt);
    for (int i = 0; i < moves_cnt; ++i) {
        ll first = ouf.readLong(1, n, "from");
        ll second = ouf.readLong(1, n, "to");
        --first; --second;
        moves[i] = {first, second};
    }
}

void LoadMovesJury(ll n, std::vector<std::pair<ll, ll>>& moves) {
    ll moves_cnt = ans.readLong(0ll, 2000000000, "moves_cnt");
    moves.resize(moves_cnt);
    for (int i = 0; i < moves_cnt; ++i) {
        ll first = ans.readLong(1, n, "from");
        ll second = ans.readLong(1, n, "to");
        --first; --second;
        moves[i] = {first, second};
    }
}

void ApplyMovesToState(ll m, std::vector<std::vector<ll>>& initial, const std::vector<std::pair<ll, ll>>& moves) {
    for (auto &x : moves) {
        if (initial[x.first].empty() || initial[x.second].size() == m || initial[x.second].size() > 0 && initial[x.second].back() != initial[x.first].back()) {
            quitf(_wa, "Impossible move was found : %lld --> %lld", x.first, x.second);
        }
        initial[x.second].push_back(initial[x.first].back());
        initial[x.first].pop_back();
    }
}

ll CalculateSquareScore(ll n, ll m, ll empty, const std::vector<std::vector<ll>>& state) {
	ll res = 0;
	for (auto &x : state) {
		auto cur = x;
		std::sort(cur.begin(), cur.end());
		ll ccur = std::unique(cur.begin(), cur.end()) - cur.begin();
		res += ccur * ccur;
	}
	return res;
}

ld CalculateSquareScoreLd(ll n, ll m, ll empty, ll pscore, ll jscore) {
	ld pres = pscore; // CalculateSquareScore(n, m, empty, pstate);
	ld jres = jscore; // CalculateSquareScore(n, m, empty, jstate);

	auto g = [&](ld score) {
		return ((sqrt(n - empty) * m - sqrt(score - n + empty)) / (sqrt(n - empty) * m));
	};

	return std::pow(g(pres) / g(jres), 3);
}

int main(int argc, char * argv[])
{
    setName("compare files");
    registerTestlibCmd(argc, argv);

    ll t;
    t = inf.readLong(1ll, 7ll, "Number of test cases");
    ld total_score = 0;
    ll the_score = 10;
    ll n, m, empty = 0;
    std::vector<std::pair<ll, ll>> pmoves;
    std::vector<std::vector<ll>> initial;
    for (int i = 0; i < t; ++i) {
        setTestCase(i + 1);
        LoadInitial(n, m, empty, initial);

        auto participant = initial;
        auto jury = initial;

        LoadMovesParticipant(n, pmoves);
        ApplyMovesToState(m, participant, pmoves);
        LoadMovesJury(n, pmoves);
        ApplyMovesToState(m, jury, pmoves);
        ll pscore = CalculateSquareScore(n, m, empty, participant);
        ll jscore = CalculateSquareScore(n, m, empty, jury);
        if (pscore < jscore) {
            quitf(_fail, "Participant provided a better answer : %lld base score instead of %lld", pscore, jscore);
        }
        //std::cerr << "Particiant achieved base score of " << pscore << " min = " << n - empty << std::endl;
        if (pscore == n - empty) {
            total_score += the_score;
        }
        else {
            total_score += the_score * CalculateSquareScoreLd(n, m, empty, pscore, jscore);
        }
    }
    quitp(total_score, "Success");
}
