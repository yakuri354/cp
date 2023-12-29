// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<pair<ll, ll>>> adj;
vector<ll> topo;
vector<bool> used;

void dfs_topo(ll v) {
    if (used[v]) return;
    used[v] = true;
    for (auto [u, w] : adj[v]) {
        dfs_topo(u);
    }
    topo.push_back(v);
}

void solve() {
    ll n, m, s, t;

    cin >> n >> m >> s >> t;
    s--, t--;

    used.resize(n);
    adj.resize(n);

    for (ll i = 0; i < m; i++) {
        ll a, b, w;
        cin >> a >> b >> w;

        adj[a-1].emplace_back(b-1, w);
    }

    dfs_topo(s);

    reverse(topo.begin(), topo.end());

    vector<ll> d(n, inf);

    d[s] = 0;

    for (ll u : topo) {
        for (auto [v, w] : adj[u]) {
            d[v] = min(d[v], d[u] + w);
        }
    }

    if (d[t] == inf) {
        cout << "Unreachable" << endl;
    } else {
        cout << d[t] << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
