#ifndef DBG
#pragma GCC optimize("Ofast")
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
ll comp[100001];
vector<set<ll>> compv;

void dfs(ll v, ll c) {
    comp[v] = c;
    compv[c].insert(v);
    for (auto u : adj[v]) {
        if (!comp[u]) dfs(u, c);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    compv.resize(n + 1);

    for (ll i = 0; i < m; i++) {
        ll v, u;
        cin >> v >> u;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    ll lastc = 1;
    for (ll i = 1; i <= n; i++) {
        if (comp[i] == 0) dfs(i, lastc++);
    }
    cout << lastc - 1 << '\n';
    for (auto &s : compv) {
        if (s.empty()) continue;
        cout << s.size() << '\n';
        for (auto v : s) {
            cout << v << ' ';
        }
        cout << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
