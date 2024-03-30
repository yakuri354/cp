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

vector<vector<ll>> g, gT;

vector<ll> topo, comp, cs, dp;
vector<bool> used;
vector<set<ll>> cg;

ll n, m;

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
    if (comp[v] != c) {
        if (comp[v] != -1) cs[comp[v]]--;
        cs[c] += 1;
    }
    comp[v] = c;
    
    for (auto u: gT[v]) {
        if (comp[u] == -1) color(u, c);
    }
}

ll reach(ll v) {
    if (dp[v] != -1) return dp[v];

    ll res = cs[v];

    for (ll u: cg[v]) {
        res += reach(u);
    }

    dp[v] = res;
    return res;
}

void solve() {
    cin >> n >> m;
    g.assign(n, {});
    gT.assign(n, {});
    used.assign(n, false);
    comp.assign(n, -1);
    dp.assign(n, -1);
    cs.assign(n, 0);
    cg.assign(n, {});
    
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        
        g[a].push_back(b);
        gT[b].push_back(a);
    }
    
    for (ll i = 0; i < n; i++) {
        if (!used[i]) dfs1(i);
    }
    
    reverse(topo.begin(), topo.end());

    ll comps = 0;
    for (ll i : topo) {
        if (comp[i] == -1) color(i, comps++);
    }

    for (ll i = 0; i < n; i++) {
        for (ll u: g[i]) {
            if (comp[u] != comp[i]) {
                cg[comp[i]].insert(comp[u]);
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        cout << reach(comp[i]) - 1 << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
