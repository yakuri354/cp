// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 5 * 1e5;

struct edge {
    ll u, v, w, d;
};

vector<edge> adj[maxn];

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        ll u, v, w, d;
        cin >> u >> v >> w >> d;
        u--, v--, d--;
        adj[u].emplace_back(u, v, w, d);
    }

    vector<ll> d(n);
    set<pair<ll, ll>> q;
    d[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [pl, u] = *q.begin();
        q.erase({pl, u});
        for (edge &e : adj[u]) {
            if (pl + e.w < d[e.v]) {
                q.erase({d[e.v], e.v});
                d[e.v] = pl + e.w;
                q.emplace(pl + e.w, e.v);
            }
        }

        while ()
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
