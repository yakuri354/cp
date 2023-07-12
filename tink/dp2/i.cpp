// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 17;

ll val[maxn];
ll dp[maxn][1 << maxn];
ll p[maxn][1 << maxn];
ll n;

bool in_mask(ll v, ll m) {
    return (m & (1 << v)) > 0;
}

void print_dp() {
    ll s = 0;
    for (ll v = 0; v < n; v++) {
        for (ll m = 0; m < 1 << n; m++) {
            string si = to_string(dp[v][m]);
            if (dp[v][m] == inf) si = "inf";
            s = max(ll(s), ll(si.size()));
        }
    }
    for (ll m = 0; m < 1 << n; m++) {
        cout << bitset<maxn>(m) << " -> ";
        for (ll v = 0; v < n; v++) {
            string si = to_string(dp[v][m]);
            if (dp[v][m] == inf) si = "inf";
            if (ll(si.size()) < s) si += string(s - si.size(), ' ');
            cout << si << ' ';
        }
        cout << endl;
    }
}

ll d(ll v, ll mask) {
    if (dp[v][mask] != -1) return dp[v][mask];

    if (!in_mask(v, mask)) {
        dp[v][mask] = inf;
    } else if (__builtin_popcountll(mask) == 1) {
        dp[v][mask] = val[__lg(mask)];
    } else {
        ll mask_p = mask & ~(1 << v);
        dp[v][mask] = inf;
        for (ll u = 0; u < n; u++) {
            ll ans = d(u, mask_p) + mat[u][v];
            if (ans < dp[v][mask]) {
                dp[v][mask] = ans;
                p[v][mask] = u;
            }
        }
    }

    return d(v, mask);
}

void solve() {
    cin >> n;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> mat[i][j];
            if (mat[i][j] == 0) mat[i][j] = inf;
        }
    }

    for (ll v = 0; v < n; v++) {
        for (ll m = 0; m < 1 << n; m++) {
            dp[v][m] = -1;
            p[v][m] = -1;
        }
    }

    ll be = -1, ans = inf;
    for (ll v = 0; v < n; v++) {
        ll a1 = d(v, (1 << n) - 1);
        if (a1 < ans) {
            ans = a1;
            be = v;
        }
    }

    if (ans == inf) {
        cout << -1 << endl;
    } else {
        cout << ans << '\n';

        vector<ll> path;
        ll v = be, m = (1 << n) - 1;
        while (v != -1) {
            path.push_back(v);
            ll pv = v;
            v = p[v][m];
            m &= ~(1 << pv);
        }

        reverse(path.begin(), path.end());
        for (ll v : path) {
            cout << v + 1 << ' ';
        }
        cout << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
