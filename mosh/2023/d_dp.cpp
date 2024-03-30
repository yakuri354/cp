// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <string_view>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll inf = 1e12;


template<typename It1, typename It2>
ll levenstein(It1 l1, It1 r1, It2 l2, It2 r2) {
    ll n = r1 - l1, m = r2 - l2;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
    for (ll i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (ll i = 0; i <= m; i++) {
        dp[0][i] = i;
    }
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
            if (*(l1 + i - 1) == *(l2 + j - 1)) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            }
        }
    }

    return dp[n][m];
}

struct lvns {
    ll n, m = 0;
    vector<ll> dp0, dp1;
    string base;

    lvns(string &s): n(s.size()), dp0(vector<ll>(n + 1, 0)), base(s) {
        iota(dp0.begin(), dp0.end(), 0);
    }

    void add_char(char c) {
        m++;
        dp1 = vector<ll>(n + 1, 0);

        dp1[0] = m;

        for (ll i = 1; i <= n; i++) {
            dp1[i] = min(min(dp0[i], dp1[i-1]), dp0[i-1]) + 1;
            if (c == base[i-1]) {
                dp1[i] = min(dp1[i], dp0[i-1]);
            }
        }

        dp0 = dp1;
    }

    ll get_dist() {
        return dp0.back();
    }
};

void solve() {
    string SS, A;
    vector<pll> words, segs;
    ll M, n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        string w;
        cin >> w;
        ll l = SS.size();
        if (!SS.empty()) {
            SS.push_back(' ');
            l++;
        }
        SS += w;
        words.push_back({l, SS.size()});
    }

    cin >> M;
    for (ll i = 0; i < M; i++) {
        ll k;
        cin >> k;

        ll l = A.size();
        if (!A.empty()) {
            A.push_back(' ');
            l++;
        }

        for (ll i = 0; i < k; i++) {
            string s;
            cin >> s;
            A += s;
            if (i != k - 1) A.push_back(' ');
        }

        segs.push_back({l, A.size()});
    }

    vector<vector<ll>> dp(M + 1, vector<ll>(n + 1, inf));
    vector<vector<ll>> par(M + 1, vector<ll>(n + 1, -1));
    // dp[0].assign(n + 1, 0);
    dp[0][0] = 0;

    for (ll i = 1; i <= M; i++) { // split into i segments
        cout << "\33[2K\r";
        cout << "segment " << i << "/" << M << " word " << 0 << "/" << n << flush;
        auto [sl, sr] = segs[i-1];
        auto sg = A.substr(sl, sr - sl);
        auto sgr = sg;
        ll words_in_seg = count(sg.begin(), sg.end(), ' ') + 1;
        reverse(sgr.begin(), sgr.end());
        for (ll j = 1; j <= n; j++) { // first j words
            lvns dist(sgr);
            for (ll k = j - 1; k >= max(0ll, j - 2 * words_in_seg - 1); k--) { // using words (k, j] in 1-idx
                // if (dp[i-1][k] == inf && i != 1) break;
                for (ll x = words[k].second - 1; x >= words[k].first; x--) {
                    dist.add_char(SS[x]);
                }
                ll relax = dp[i-1][k] + dist.get_dist();

                if (relax < dp[i][j]) {
                    dp[i][j] = relax;
                    par[i][j] = k;
                }
            }
        }
    }

    vector<ll> ans;

    ll ii = M, jj = n;
    while (par[ii][jj] != -1) {
        ll k = par[ii][jj];
        ans.push_back(jj - k);
        jj = k;
        ii--;
    }

    reverse(ans.begin(), ans.end());

    for (ll &i: ans) cerr << i << ' ';
    cerr << endl << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

