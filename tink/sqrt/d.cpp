// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 3*1e5;

vector<ll> adj[maxn];

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto cmp = [](ll a, ll b) {
        if (adj[a].size() == adj[b].size()) return a < b;
        return adj[a].size() < adj[b].size();
    };

    vector<ll> perm(n);
    iota(perm.begin(), perm.end(), 0);

    sort(perm.begin(), perm.end(), cmp);

    for (ll i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end(), cmp);
    }

    ll full = 0;

    vector<bool> vis(n);

    for (ll v : perm) {
        for (ll u : adj[v]) {
            vis[u] = true;
        }

        for (ll u : adj[v]) {
            if (cmp(v, u)) break;
            for (ll w : adj[u]) {
                if (cmp(u, w)) break;
                if (vis[w]) full++;
            }
        }

        for (ll u : adj[v]) {
            vis[u] = false;
        }
    }

    cout << full << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
