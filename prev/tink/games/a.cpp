// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> adj;
vector<ll> dp;
vector<bool> used;

void dfs(ll v) {
    if (used[v]) return;
    used[v] = true;
    for (ll u : adj[v]) {
        dfs(u);
    }

    dp[v] = 0;
    sort(adj[v].begin(), adj[v].end(), [](auto a, auto b) {
        return dp[a] < dp[b];
    });

    for (ll j : adj[v]) {
        if (dp[v] == dp[j]) {
            dp[v]++;
        } else if (dp[v] < dp[j]) {
            break;
        }
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    dp.resize(n);
    adj.resize(n);
    used.resize(n);

    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        adj[x-1].push_back(y-1);
    }

    for (ll i = 0; i < n; i++) {
        if (!used[i]) dfs(i);
        cout << dp[i] << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
