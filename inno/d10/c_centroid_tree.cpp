#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ll lg = 19;

vector<vector<ll>> g;
vector<bool> used;
vector<ll> sz, tin, tout;
vector<vector<ll>> binup;
vector<ll> col;

vector<vector<ll>> ct_up;
vector<unordered_map<ll, ll>> ct_subtree_sum[2];
vector<ll> ct_sum[2];
vector<ll> ct_sz[2];

ll timer = 0;

void calc_euler(ll v, ll p) {
    tin[v] = timer++;
    
    for (ll u : g[v]) {
        if (u == p) continue;
        calc_euler(u, v);
    }
    
    tout[v] = timer;
}

bool is_ancestor(ll parent, ll child) {
    return tin[parent] <= tin[child] && tout[child] <= tout[parent];
}

void calc_binup(ll v, ll p) {
    binup[v][0] = p;
    
    for (ll i = 1; i < lg; i++) {
        binup[v][i] = binup[binup[v][i-1]][i-1];
    }
    
    for (ll u : g[v]) {
        if (u == p) continue;
        calc_binup(u, v);
    }
}

ll dist(ll v, ll u) {
    if (v == u) return 0;

    ll ans = 0;

    for (ll i = lg - 1; i >= 0; i--) {
        if (!is_ancestor(binup[v][i], u)) {
            ans += 1 << i;
            v = binup[v][i];
        }
    }

    for (ll i = lg - 1; i >= 0; i--) {
        if (!is_ancestor(binup[u][i], v)) {
            ans += 1 << i;
            u = binup[u][i];
        }
    }
    
    if (is_ancestor(v, u) || is_ancestor(u, v)) ans += 1;
    else ans += 2;
    
    return ans;
}


void sizes(ll v, ll p) {
    sz[v] = 1;
    for (ll u : g[v]) {
        if (used[u] || u == p) continue;
        sizes(u, v);
        sz[v] += sz[u];
    }
}

ll path_sum(ll v, ll p, ll h) {
    ll ans = h;
    
    for (ll u : g[v]) {
        if (used[u] || u == p) continue;
        ans += path_sum(u, v, h + 1);
    }
    
    return ans;
}

ll centroid(ll v, ll s, ll p) {
    for (ll u : g[v]) {
        if (sz[u] > s / 2 && u != p && !used[u]) {
            return centroid(u, s, v);
        }
    }
    
    return v;
}

void add_level(ll v, ll c, ll p, vector<bool> &used) {
    ct_up[v].push_back(c);
    for (ll u : g[v]) {
        if (used[u] || u == p) continue;
        add_level(u, c, v, used);
    }
}

ll decompose(ll v, ll s) {
    ll c = centroid(v, s, v);
    used[c] = true;
    auto prev_used = used; // super sus
    sizes(c, c);
    ct_sz[0][c] = sz[c];
    
    ll sum = 0;
    for (ll u : g[c]) {
        if (used[u]) continue;
        ll res = path_sum(u, u, 1);
        ll sc = decompose(u, sz[u]);
        ct_subtree_sum[0][c][sc] = res;
        sum += res;
    }
    ct_sum[0][c] = sum;
    
    add_level(c, c, c, prev_used);
    
    return c;
}

ll get_ans(ll v) {
    ll cl = col[v];
    ll ans = ct_sum[cl][v]; // ct_up[v][0] = v
    
    for (ll i = 1; i < ct_up[v].size(); i++) {
        ll ctr = ct_up[v][i], next = ct_up[v][i - 1];

        ll curr = ct_sum[cl][ctr] - ct_subtree_sum[cl][ctr][next];
        ll count = ct_sz[cl][ctr] - ct_sz[cl][next];
        ans += curr + count * dist(ctr, v);
    }

    return ans;
}

void upd_col(ll v) {
    ll cl = col[v];
    
    for (ll i = 1; i < ct_up[v].size(); i++) {
        ll ctr = ct_up[v][i], next = ct_up[v][i - 1];

        ll c_dist = dist(ctr, v);

        ct_sum[cl][ctr] -= c_dist;
        ct_subtree_sum[cl][ctr][next] -= c_dist;
        ct_sz[cl][ctr] -= 1;

        ct_sum[!cl][ctr] += c_dist;
        ct_subtree_sum[!cl][ctr][next] += c_dist;
        ct_sz[!cl][ctr] += 1;
    }
    
    ct_sz[cl][v] -= 1;
    ct_sz[!cl][v] += 1;

    col[v] ^= 1;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    g.resize(n);
    used.resize(n);
    sz.resize(n);
    tin.resize(n);
    tout.resize(n);
    col.resize(n);
    binup.resize(n, vector<ll>(lg));

    ct_up.resize(n);
    for (ll i = 0; i < n; i++) ct_up[i].reserve(lg);
    ct_subtree_sum[0].resize(n);
    ct_subtree_sum[1].resize(n);
    ct_sum[0].resize(n);
    ct_sum[1].resize(n);
    ct_sz[0].resize(n);
    ct_sz[1].resize(n);
    
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;

        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }

    calc_euler(0, 0);
    calc_binup(0, 0);
    sizes(0, 0);
    decompose(0, n);
    
    for (ll i = 0; i < m; i++) {
        ll qt, v;
        cin >> qt >> v;
        v--;
        
        if (qt == 1) {
            upd_col(v);
        }
        if (qt == 2) {
            cout << get_ans(v) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
