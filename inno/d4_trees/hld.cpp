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
vector<ll> head, sz, tin, tout, parent;
ll t = 0;


using el = ll;
el el_id = 0;

el op(el a, el b) {
    return a + b;
}

vector<el> st;
ll n;

void build() {
    for (ll i = n - 1; i > 0; i--) {
        st[i] = op(st[i*2], st[i*2+1]);
    }
}

el query(ll l, ll r) {
    el res_l = el_id, res_r = el_id;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res_l = op(res_l, st[l++]);
        if (r & 1) res_r = op(st[--r], res_r);
    }
    return op(res_l, res_r);
}

void set_el(ll i, el x) {
    for (st[i += n] = x, i >>= 1; i > 0; i >>= 1) {
        st[i] = op(st[i*2], st[i*2+1]);
    }
}

void comp_sz(ll v, ll p) {
    sz[v] = 1;
    for (ll &u : adj[v]) {
        if (u == p) continue;
        comp_sz(u, v);
        sz[v] += sz[u];
        if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
    }
}

void hld(ll v, ll p) {
    parent[v] = p;
    tin[v] = t;
    for (ll u : adj[v]) {
        if (u == p) continue;

        head[u] = (u == adj[v][0] ? head[v] : u);
        
        t++;
        hld(u, v);
    }
    tout[v] = t;
}

bool ancestor(ll v, ll u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

void decompose(ll &v, ll u, el &ans) {
    while (!ancestor(head[v], u)) {
        ans = op(ans, query(tin[head[v]] + 1, tin[v] + 1));
        v = parent[v];
    }
}

el sum_path(ll v, ll u) {
    el ans = el_id;
    decompose(v, u, ans);
    decompose(u, v, ans);
    if (!ancestor(v, u)) swap(v, u);
    ans = op(ans, query(tin[v] + 1, tin[u] + 1)); // or tin[v] for vertices
    return ans;
}

void set_val(ll v, el x) {
    set_el(tin[v], x);
}

void solve() {
    ll root = 0;
    comp_sz(root, -1);
    head[root] = root;
    hld(root, -1);

    for (ll i = 0; i < n; i++) {
        cin >> st[n + i];
    }
    
    build();
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
