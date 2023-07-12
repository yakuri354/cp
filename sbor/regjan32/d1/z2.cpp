// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> adj;
vector<bool> used;

ll togcl(ll color) {
    if (color == 1) return 2;
    else return 1;
}

ll n, m;

const ll maxn = 10101;
const ll maxm = maxn/2 + 200;

void print_dp(vector<vector<ll>> &dp) {
    for (auto &i : dp) {
        for (auto &j : i) {
            cout << j << ' ';
        }
        cout << endl;
    }
}

pair<ll, ll> dfs(ll v, ll color) {
    if (used[v]) return {0, 0};
    used[v] = true;

    ll a = 0, b = 0;
    for (ll u : adj[v]) {
        auto [a1, b1] = dfs(u, color ^ 1);
        a += a1;
        b += b1;
    }

    if (color) b++;
    else a++;

    return {a, b};
}

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> nd(1, 10);

void solve() {
    ll n1 = nd(mt);

    vector<pair<ll, ll>> comps;
    n = 0;
    for (ll i = 0; i < n1; i++) {
        comps.emplace_back(nd(mt), nd(mt));
        n += comps[i].first + comps[i].second;
    }

    ll opt = n / 2;
    if (n & 1) opt++;

    vector<vector<ll>> dp(comps.size() + 1, vector<ll>(opt + 1));

    for (ll i = 1; i <= comps.size(); i++) {
        auto [xx, yy] = comps[i-1];
        for (ll c = 0; c <= opt; c++) {
            if (c < min(xx, yy))
                dp[i][c] = 0;
            else if (c >= max(xx, yy))
                dp[i][c] = max(dp[i-1][c-xx] + xx, dp[i-1][c-yy] + yy);
            else if (yy < xx)
                dp[i][c] = dp[i-1][c-yy] + yy;
            else
                dp[i][c] = dp[i-1][c-xx] + xx;
        }
    }

    ll da = 0, db = 0;

    for (ll i = 0; i < comps.size(); i++) {
        auto [ff, gg] = comps[i];
        if ((da + ff) * (db + gg) < (da + gg) * (db + ff)) swap(ff, gg);
        da += ff;
        db += gg;
    }

    ll ans = dp[comps.size()][opt];
    ll ans2 = ans * (n - ans);
    ll dumb = da * db;

    if (dumb > ans2) {
        cout << "ERRROROROROOROR " << endl;
        vector<vector<ll>> dp2(comps.size() + 1, vector<ll>(opt + 1));
        for (ll i = 1; i <= comps.size(); i++) {
            auto [xx, yy] = comps[i-1];
            for (ll c = 0; c <= opt; c++) {
                if (c < min(xx, yy))
                    dp2[i][c] = 0;
                else if (c >= max(xx, yy))
                    dp2[i][c] = max(dp2[i-1][c-xx] + xx, dp2[i-1][c-yy] + yy);
                else if (yy < xx)
                    dp2[i][c] = dp2[i-1][c-yy] + yy;
                else
                    dp2[i][c] = dp2[i-1][c-xx] + xx;
            }
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    while (1) solve();
}
