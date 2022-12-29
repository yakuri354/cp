// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<pair<ll, ll>>> adj;
vector<ll> sz;
vector<ll> ans;
vector<ll> paths;
vector<bool> used;

void dfs1(ll v, ll p) {
    if (used[v]) return;
    used[v] = true;
    sz[v] = 1;
    for (auto [u, x] : adj[v]) {
        if (u == p) continue;
        dfs1(u, v);
        sz[v] += sz[u];
    }
}

void dfs2(ll v, ll p, ll ps) {
    if (used[v]) return;
    used[v] = true;
    for (auto [u, x] : adj[v]) {
        if (u == p) continue;
        ll back = ps + sz[v] - sz[u];
        ans[x] = back * sz[u];
        dfs2(u, v, back);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    adj.resize(n);
    sz.resize(n);
    paths.resize(n);
    ans.resize(m);
    used.resize(n);

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }

    for (ll i = 0; i < n; i++) dfs1(i, -1);
    used.assign(n, false);
    for (ll i = 0; i < n; i++) dfs2(i, -1, 0);

    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll e;
        cin >> e;
        cout << ans[e-1] << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
