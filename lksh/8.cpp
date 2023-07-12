// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> adj;
vector<vector<ll>> children;
vector<pair<ll, ll>> edges;
vector<ll> bamboo;

void dfs(ll v, ll p) {
    for (ll u : adj[v]) {
        if (u == p) continue;
        children[v].push_back(u);
        dfs(u, v);

        if (adj[v].size() == 2) {
            bamboo[v] = bamboo[u] + 1;
            if (bamboo[v] >= 2) {
                edges.emplace_back(v, children[u][0]);
                bamboo[v] = 0;
            }
        }
    }
}

void solve() {
    ll n;
    cin >> n;

    adj.resize(n);
    children.resize(n);
    bamboo.resize(n);

    ll maxv = 0;
    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
        if (adj[a].size() > adj[maxv].size()) {
            maxv = a;
        }

        if (adj[b].size() > adj[maxv].size()) {
            maxv = b;
        }
    }

    dfs(maxv, -1);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < ll(children[i].size()) - 1; j += 2) {
            edges.emplace_back(children[i][j], children[i][j+1]);
        }
    }
    
    cout << edges.size() << '\n';
    for (auto e : edges) {
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
