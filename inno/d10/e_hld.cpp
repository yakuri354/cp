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

ll n;
vector<ll> st;

void build() {
    for (ll i = n - 1; i > 0; i--) {
        st[i] = max(st[i*2], st[i*2 + 1]);
    }
}

ll query(ll l, ll r) {
    if (l > r) swap(l, r);
    ll res = -inf;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, st[l++]);
        if (r & 1) res = max(res, st[--r]);
    }
    return res;
}

void set_pt(ll i, ll x) {
    for (st[i += n] = x, i >>= 1; i > 0; i >>= 1) {
        st[i] = max(st[i * 2], st[i * 2 + 1]);
    }
}

vector<vector<ll>> g;
vector<ll> sz, head, tin, tout, parent, arr;

ll timer = 0;

bool is_parent(ll parent, ll child) {
    return tin[parent] <= tin[child] && tout[child] <= tout[parent]; // sus
}

void euler(ll v, ll p) {
    tin[v] = timer++;
    
    for (ll u : g[v]) {
        if (u == p) continue;
        euler(u, v);
    }
    
    tout[v] = timer;
}

void sizes(ll v, ll p) {
    sz[v] = 1;
    // sus: parent in adj list
    for (ll &u : g[v]) {
        if (u == p) continue;
        sizes(u, v);
        if (g[v][0] == p || sz[u] > sz[g[v][0]]) { // sus
            swap(u, g[v][0]);
        }
        sz[v] += sz[u];
    }
}

void hld(ll v, ll p) {
    for (ll u : g[v]) {
        if (u == p) continue;
        head[u] = u == g[v][0] ? head[v] : u;
        parent[u] = v;
        hld(u, v);
    }
}

void up(ll &v, ll &to, ll &ans) {
    while (!is_parent(head[v], to)) {
        ans = max(ans, query(tin[head[v]], tin[v] + 1));
        v = parent[head[v]];
    }
}

ll ans_query(ll v, ll u) {
    if (v == u) return st[tin[v] + n];

    ll ans = -inf;
    up(v, u, ans);
    up(u, v, ans);
    
    if (is_parent(u, v)) swap(u, v);
    
    ans = max(ans, query(tin[v], tin[u] + 1));

    return ans;
}


void solve() {
    cin >> n;
    
    arr.resize(n);
    g.resize(n);
    sz.resize(n);
    head.resize(n);
    tin.resize(n);
    tout.resize(n);
    parent.resize(n);
    st.resize(n * 2);

    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    sizes(0, 0);
    hld(0, 0);
    euler(0, 0);
    
    for (ll i = 0; i < n; i++) {
        st[n + tin[i]] = arr[i];
    }
    
    build();
    
    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        string qt;
        cin >> qt;

        if (qt == "!") {
            ll i, h;
            cin >> i >> h;

            set_pt(tin[i - 1], h);
        }
        
        if (qt == "?") {
            ll u, v;
            cin >> u >> v;

            cout << ans_query(u - 1, v - 1) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
