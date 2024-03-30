#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <array>
#include <iostream>
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

ll k, n, m, q;

const ll maxv = 50000ll * 5;
const ll maxk = 5;
const ll inf = 1e15;
const ll sq = 100;

vector<pll> g[maxv];

// ll dp[maxv]; // todo optimize

ll dfs_dist(ll v, ll bound, unordered_map<ll, ll> &dp) {
    if (v > bound) return inf;
    if (dp.count(v)) return dp[v];

    dp[v] = inf;

    for (auto [u, w]: g[v]) {
        dp[v] = min(ll(dp[v]), dfs_dist(u, bound, dp) + w);
    }

    return dp[v];
}

ll next_bl[maxv][maxk];

void answer(ll a) {
    if (a >= inf) {
        cout << "-1\n";
    } else {
        cout << a << '\n';
    }
}

void solve() {
    cin >> k >> n >> m >> q;

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
    
        g[a].push_back({b, c});
    }

    for (ll i = sq * k; i + k <= n; i += sq * k) {
        ll prev = i - sq * k;

        for (ll z = 0; z < k; z++) {
            unordered_map<ll, ll> dp;
            dp[i + z] = 0;

            for (ll j = 0; j < k; j++) {
                next_bl[prev + j][z] = dfs_dist(prev + j, i + k, dp);
            }
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        ll u, v;
        cin >> u >> v;

        if (v < u || v / k == u / k) {
            answer(inf);
            continue;
        }

        if (v / (k * sq) == u / (k * sq)) {
            unordered_map<ll, ll> dp;
            dp[v] = 0;
            answer(dfs_dist(u, v + k, dp));
            continue;
        }

        ll nx = (u / (k * sq) + 1) * k * sq;

        array<ll, maxk> dist0{};

        for (ll i = 0; i < k; i++) {
            unordered_map<ll, ll> dp;
            dp[nx + i] = 0;
            dist0[i] = dfs_dist(u, nx + k + i, dp);
        }

        while (nx + (k * sq) < v) {
            array<ll, maxk> dist1;
            dist1.fill(inf);
            for (ll i = 0; i < k; i++) {
                for (ll j = 0; j < k; j++) {
                    dist1[i] = min(ll(dist1[i]), dist0[j] + next_bl[nx + j][i]);
                }
            }
            dist0 = dist1;
            nx += k * sq;
        }

        unordered_map<ll, ll> dp;
        dp[v] = 0;
        ll ans = inf;
        for (ll i = 0; i < k; i++) {
            ans = min(ans, dist0[i] + dfs_dist(nx + i, v + k, dp));
        }

        answer(ans);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
