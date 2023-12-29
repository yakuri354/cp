//
// Created by lain on 9/11/22.
//

#include "bits/stdc++.h"
using namespace std;
using ll = long long;

const ll mod = 1e9+7;
ll ans = 1, n, s;

vector<vector<ll>> adj;

void dfs(ll i, ll cn, ll p, ll h) {
    ll c = 1;
    if (h > 1) cn++;
    ans *= max(0ll, s - cn);
    ans %= mod;

    cerr << "in " << i << " *= s - " << cn << endl;

    for (auto &u:adj[i]) {
        if (u == p) continue;
        dfs(u, c++, i, h + 1);
    }
}

int main() {
    cin >> n >> s;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0, 1, 0);

    cout << ans << endl;
}