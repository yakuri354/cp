// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1;  // todo

vector<vector<ll>> g;
vector<ll> d, col;
vector<unordered_set<ll>> ts;

void dfs(ll v, ll p) {
    ll heavy_u = -1;
    
    for (ll u : g[v]) {
        if (u == p) continue;
        dfs(u, v);
        if (heavy_u == -1 || ts[u].size() > ts[heavy_u].size()) {
            heavy_u = u;
        }
    }
    
    if (heavy_u == -1) {
        ts[v].insert(col[v]);
        d[v] = ts[v].size();
        return;
    }
    
    ts[v].swap(ts[heavy_u]);
    
    for (ll u : g[v]) {
        if (u == p || u == heavy_u) continue;
        
        ts[v].insert(ts[u].begin(), ts[u].end());
        ts[u].clear();
    }
    
    ts[v].insert(col[v]);
    d[v] = ts[v].size();
}

void solve() {
    ll n;
    cin >> n;
    
    g.resize(n);
    col.resize(n);
    d.resize(n);
    ts.resize(n);
    
    ll root = 0;

    for (ll i = 0; i < n; i++) {
        ll par, c;
        cin >> par >> c;
        
        if (par == 0) {
            root = i;
        } else {
            g[par - 1].push_back(i);
        }

        col[i] = c;
    }
    
    dfs(root, -1);
    
    for (ll i = 0; i < n; i++) {
        cout << d[i] << ' ';
    }
    
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
