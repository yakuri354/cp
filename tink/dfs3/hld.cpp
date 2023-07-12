// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

vector<ll> g[maxn];
ll head[maxn], sz[maxn], tin[maxn], tout[maxn], tmr = 0, t[maxn * 4], n, e[maxn], clr[maxn];

void dfs1(ll v, ll p) {
    sz[v] = 1;
    for (ll &u : g[v]) {
        if (u == v) continue;
        dfs1(u, v);
        sz[v] += sz[u];
        if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
    }
}

void dfs2(ll v, ll p) {
    e[tmr] = v;
    t[tmr + n] = clr[v];
    tin[v] = tmr++;

    for (ll u : g[v]) {
        if (u == v) continue;
        head[u] = u == g[v][0] ? head[v] : u;
        dfs2(u, v);
    }
    
    tout[v] = tmr;
}



void solve() {
    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
