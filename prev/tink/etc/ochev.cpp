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

vector<set<ll>> adj;
bool used[10001];
ll n, m;

void dfs(ll v, ll p) {
    used[v] = true;

    for (ll u : adj[v]) {
        if (used[u]) {
            cout << 1 << endl;
            exit(0);
        }
        dfs(u, v);
    }
}

void solve() {
    cin >> n >> m;
    adj.resize(n + 1);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].insert(v);
    }

    for (ll i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }

    cout << 0 << endl;
}
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
