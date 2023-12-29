// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
    if (p != -1) binup[v][0] = p;
    for (ll i = 1; i < lg; i++) {
        binup[v][i] = binup[binup[v][i-1]][i-1];
        path_v[v][i] = min(path_v[v][i-1], path_v[binup[v][i-1]][i-1]);
    }
    for (ll u : adj[v]) {
        if (u == p) continue;
        t++;
        dfs(u, v);
    }
    tout[v] = t;
}

bool ancestor(ll v, ll u) { // v == u ?
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

ll sum(ll v, ll u) {
    ll ans = inf;
    for (ll i = lg - 1; i >= 0; i--) {
        if (!ancestor(binup[v][i], u)) {
            ans = min(ans, path_v[v][i]);
            v = binup[v][i];
        }
    }

    for (ll i = lg - 1; i >= 0; i--) {
        if (!ancestor(binup[u][i], v)) {
            ans = min(ans, path_v[u][i]);
            u = binup[u][i];
        }
    }
    
    if (!ancestor(v, u)) ans = min(ans, path_v[v][0]);
    if (!ancestor(u, v)) ans = min(ans, path_v[u][0]);
    // if sum per vertex
    // ans += path_v[binup[v][0]][0];
    return ans;
}

ll lca(ll v, ll u) {
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
    path_v.resize(n, vector<ll>(lg));

    // for (ll i = 0; i < n - 1; i++) {
    //     ll u, v;
    //     u--, v--;
    //     adj[u].push_back(v);
    //     adj[v].push_back(u);
    // }

    for (ll i = 0; i < n - 1; i++) {
        ll x, y;
        cin >> x >> y;
        adj[x - 1].push_back(i + 1);
        path_v[i+1][0] = y;
    }
    
    ll root = 0;
    
    for (ll i = 0; i < lg; i++) {
        binup[root][i] = root;
        path_v[root][i] = inf;
    }
    
    dfs(root, -1);
    
    ll m;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        
        ll ans = sum(u - 1, v - 1);
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
