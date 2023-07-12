// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2 * 1e5;

ll sum[maxn], a[maxn];

vector<vector<ll>> adj;

void dfs(ll v, ll par) {
    sum[v] = a[v] ^ sum[par];

    for (ll u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n - 1; i++) {
        ll p;
        cin >> p;

        adj[p].push_back(i);
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
