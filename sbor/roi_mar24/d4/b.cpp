// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

vector<vector<ll>> g;

struct res {
    ll ld1 = -1, ld2 = -1, cost = 0;
};

res dfs_solve(ll v, ll p, ll d) {
    ll cost = 0, down = 0;
    vector<ll> leaves;

    for (ll u: g[v]) {
        if (u == p) continue;

        down++;
        auto r = dfs_solve(u, v, d + 1);
        cost += r.cost;

        if (r.ld1 != -1) {
            leaves.push_back(r.ld1);
        }
        if (r.ld2 != -1) {
            leaves.push_back(r.ld2);
        }
    }

    if (down == 0) {
        return {d, -1, 0};
    }

    ll sum = accumulate(leaves.begin(), leaves.end(), 0ll) - d * ll(leaves.size());
    sort(leaves.begin(), leaves.end());

    if (p == v) {
        if (g[v].size() == 1) {
            // leaf at 0
            if (leaves.size() == 1) {
                return {-1, -1, cost + leaves[0]};
            } else {
                return {-1, -1, -1};
            }
        } else {
            if (leaves.size() % 2 == 1) {
                return {-1, -1, -1};
            } else {
                return {-1, -1, cost + sum};
            }
        }
    }

    if (leaves.size() % 2 == 1) {
        return {leaves[0], -1, sum - leaves[0] + d + cost};
    } else {
        return {leaves[0], leaves[1], sum - leaves[0] - leaves[1] + 2 * d + cost};
    }
}

res dfs_solve2(ll v, ll p, ll d) {
    ll cost = 0, down = 0;
    vector<ll> leaves;

    for (ll u: g[v]) {
        if (u == p) continue;

        down++;
        auto r = dfs_solve(u, v, d + 1);
        cost += r.cost;

        if (r.ld1 != -1) {
            leaves.push_back(r.ld1);
        }
        if (r.ld2 != -1) {
            leaves.push_back(r.ld2);
        }
    }

    if (down == 0) {
        return {d, -1, 0};
    }

    ll sum = accumulate(leaves.begin(), leaves.end(), 0ll) - d * ll(leaves.size());
    sort(leaves.begin(), leaves.end());

    if (p == v) {
        if (g[v].size() == 1) {
            // leaf at 0
            if (leaves.size() == 1) {
                return {-1, -1, cost + leaves[0]};
            } else {
                return {-1, -1, -1};
            }
        } else {
            if (leaves.size() % 2 == 1) {
                return {-1, -1, -1};
            } else {
                return {-1, -1, cost + sum};
            }
        }
    }

    if (leaves.size() % 2 == 1) {
        return {leaves[0], -1, sum - leaves[0] + d + cost};
    } else {
        return {leaves[0], leaves[1], sum - leaves[0] - leaves[1] + 2 * d + cost};
    }
}

void solve() {
    ll n, q;
    cin >> n >> q;

    g.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }

    auto g0 = g;
    
    for (ll i = 0; i < q; i++) {
        ll D;
        cin >> D;
        g.resize(n + D);
        for (ll j = 0; j < D; j++) {
            ll x;
            cin >> x;
            g[x - 1].push_back(n + j);
            g[n + j].push_back(x - 1);
        }

        auto res = dfs_solve(0, 0, 0);

        cout << res.cost << '\n';

        g = g0;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
