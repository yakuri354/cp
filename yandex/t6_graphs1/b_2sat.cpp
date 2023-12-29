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

vector<set<ll>> g, gT;

vector<ll> topo, comp;
vector<bool> used;

ll n, m;

ll ix(ll i, ll e) {
    return i + n * !e;
}

void dfs1(ll v) {
    if (used[v]) return;
    used[v] = true;
    
    for (auto u: g[v]) {
        if (!used[u]) dfs1(u);
    }
    
    topo.push_back(v);
}

void color(ll v, ll c) {
    if (comp[v] != -1) return;
    comp[v] = c;
    
    for (auto u: gT[v]) {
        if (comp[u] == -1) color(u, c);
    }
}

void solve() {
    g.assign(n * 2, {});
    gT.assign(n * 2, {});
    used.assign(n * 2, false);
    
    for (ll i = 0; i < m; i++) {
        ll i1, e1, i2, e2;
        cin >> i1 >> e1 >> i2 >> e2;
        
        g[ix(i1, !e1)].insert(ix(i2, e2));
        gT[ix(i2, e2)].insert(ix(i1, !e1));

        g[ix(i2, !e2)].insert(ix(i1, e1));
        gT[ix(i1, e1)].insert(ix(i2, !e2));
    }
    
    for (ll i = 0; i < n * 2; i++) {
        if (!used[i]) dfs1(i);
    }
    
    reverse(topo.begin(), topo.end());

    comp.assign(n * 2, -1);

    ll comps = 0;
    for (ll i : topo) {
        if (comp[i] == -1) color(i, comps++);
    }

    for (ll i = 0; i < n; i++) {
        if (comp[ix(i, 0)] > comp[ix(i, 1)]) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    while (cin >> n >> m) solve();
}
