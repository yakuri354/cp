// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX; // SUS

const ll maxn = 100;
const ll maxk = 1000;

ll buy[maxn][maxk];
ll sell[maxn][maxk];

ll cost[maxn][maxn];
ll dist[maxn][maxn];
fl profit[maxn][maxn];

ll n, m, k;

fl w(ll i, ll j, fl x) {
    return fl(dist[i][j]) * x - fl(cost[i][j]);
}

bool check(fl x) {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            profit[i][j] = INFINITY;
        }
        profit[i][i] = 0;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            for (ll k = 0; k < n; k++) {
                profit[j][k] = min(profit[j][k], w(j, i, x) + w(i, k, x));
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        if (profit[i][i] < 0) {
            return true;
        }
    }

    return false;
}

void solve() {
    cin >> n >> m >> k;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < k; j++) {
            cin >> buy[i][j] >> sell[i][j];
            if (buy[i][j] == -1) buy[i][j] = inf;
            if (sell[i][j] == -1) sell[i][j] = -inf;
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cost[i][j] = 0;
            for (ll l = 0; l < k; l++) {
                cost[i][j] = max(cost[i][j], sell[j][l] - buy[i][l]);
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            dist[i][j] = inf;
        }
        dist[i][i] = 0;
    }

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;

        a--, b--;
        dist[a][b] = c;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            for (ll k = 0; k < n; k++) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    if (!check(0)) {
        cout << 0 << endl;
        return;
    }

    fl lo = 0, hi = ll(1e9 + 1);

    while (hi - lo > 1.0 / 10.0) {
        fl m = (lo + hi) / 2;

        if (check(m)) lo = m;
        else hi = m;
    }

    cout << ll(floor(hi)) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
