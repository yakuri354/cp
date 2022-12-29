#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

set<ll> adj[10001];
bool gray[10001];
bool black[10001];

void dfs(ll v) {
    if (gray[v]) {
        cout << 1 << endl;
        exit(0);
    }
    gray[v] = true;

    for (ll u : adj[v]) {
        dfs(u);
    }

    gray[v] = false;
    black[v] = true;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        adj[a].insert(b);
    }

    for (ll i = 0; i <= n; i++) {
        if (!black[i]) dfs(i);
    }
    cout << 0 << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
