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
const ll maxn = 1; // todo

vector<vector<ll>> g;
vector<ll> sz, c_par;
vector<bool> del;

void sizes(ll v, ll p) {
    sz[v] = 1;
    for (ll u : g[v]) {
        if (u == p || del[u]) continue;
        sizes(u, v);
        sz[v] += sz[u];
    }
}

ll find_centroid(ll v, ll s, ll p) {
    for (ll u : g[v]) {
        if (sz[u] > s / 2 && u != p && !del[u]) {
            return find_centroid(u, s, v);
        }
    }
    return v;
}

void decompose(ll v, ll s, ll p) {
    if (s == 1) {
        c_par[v] = p;
        return;
    }

    ll cc = find_centroid(v, s, p);
    del[cc] = true;
    c_par[cc] = p;
    sizes(cc, -1);
    
    for (ll u : g[cc]) {
        if (del[u]) continue;
        decompose(u, sz[u], cc);
    }
}

void solve() {
    ll n;
    cin >> n;
    
    g.resize(n);
    sz.resize(n);
    c_par.resize(n);
    del.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    
    sizes(0, -1);
    
    decompose(0, n, -1);
    
    for (ll i = 0; i < n; i++) {
        cout << c_par[i] + 1 << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
