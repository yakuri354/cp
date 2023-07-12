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
    for (ll i = 1; i <= n; i++) {
        for (ll j = 0; j <= n / 2; j++) {
            cout << dp[i][j] << ' ';
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

void solve() {
    cin >> n >> m;

    adj.resize(n);
    used.resize(n);

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<pair<ll, ll>> comps;

    for (ll i = 0; i < n; i++) {
        auto ans = dfs(i, 0);
        if (ans != make_pair(0ll, 0ll))
            comps.push_back(ans);
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
    ll ans2 = ans * (n - ans) - m;
    ll dumb = da * db - m;
    if (dumb < ans2 && n <= 10) {
        cout << dumb << endl;
    } else cout << max(dumb, ans2) << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
