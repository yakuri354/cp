#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

vector<vector<ll>> adj;
ll comp[10001];
bool used[10001];
ll n, m, t;

void dfs(ll v, ll c) {
    comp[v] = c;
    used[v] = true;

    for (ll u : adj[v]) {
        if (!used[u] && u != t) dfs(u, c);
    }
}

void solve() {
    cin >> n >> m >> t;
    adj.resize(n + 1);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll c = 1;
    for (ll i = 1; i <= n; i++) {
        if (comp[i] != 0 || i == t) continue;
        dfs(i, ++c);
    }

    ll k;
    cin >> k;
    for (ll i = 0; i < k; i++) {
        ll u, v;
        cin >> u >> v;
        if (comp[u] == comp[v]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
