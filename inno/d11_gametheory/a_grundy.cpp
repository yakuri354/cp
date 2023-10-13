// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> g;
vector<bool> used;
vector<ll> sg;
vector<ll> mex;
ll n, m;
ll t = 0;

void dfs(ll v) {
    if (used[v]) return;
    used[v] = true;

    for (ll u : g[v]) {
        dfs(u);
    }

    t++;

    for (ll u : g[v]) {
        mex[sg[u]] = t;
    }
    
    ll res = 0;
    for (ll i = 0; i < n; i++) {
        if (mex[i] == t) continue;
        res = i;
        break;
    }
    
    sg[v] = res;
}

void solve() {
    cin >> n >> m;
    
    g.resize(n);
    used.resize(n);
    sg.resize(n);
    mex.resize(n, -1);

    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        
        g[x - 1].push_back(y - 1);
    }
    
    for (ll i = 0; i < n; i++) {
        dfs(i);
        cout << sg[i] << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
