// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> adj;
vector<vector<ll>> binup;
vector<vector<ll>> path_v;
vector<ll> tin;
vector<ll> tout;

ll t = 0;

ll lg;

void dfs(ll v, ll p = -1) {
    tin[v] = t;
    for (ll i = 1; i < lg; i++) {
        binup[v][i] = binup[binup[v][i-1]][i-1];
    }
    for (ll u : adj[v]) {
        if (u == p) continue;
        t++;
        binup[u][0] = v;
        dfs(u, v);
    }
    tout[v] = t;
}

bool ancestor(ll v, ll u) { // v == u ?
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

ll lca(ll v, ll u) {
    if (ancestor(v, u)) return v;
    if (ancestor(u, v)) return u;

    for (ll i = lg - 1; i >= 0; i--) {
        if (!ancestor(binup[v][i], u)) v = binup[v][i];
    }

    return binup[v][0];
}

void solve() {
    ll n;
    cin >> n;
    
    lg = 20;
    
    adj.resize(n);
    tin.resize(n);
    tout.resize(n);
    binup.resize(n, vector<ll>(lg));
    
    for (ll i = 0; i < n - 1; i++) {
        ll x;
        cin >> x;
        adj[x - 1].push_back(i + 1);
    }
    
    ll root = 0;
    
    for (ll i = 0; i < lg; i++) {
        binup[root][i] = root;
    }

    dfs(root, -1);
    
    ll m;
    cin >> m;
    
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        
        cout << lca(u, v) + 1 << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
