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

const ll maxn = 1e5;
constexpr ll k = 300;

const ll inf = INT32_MAX;

struct dsu {
    ll n, comps;
    vector<ll> parent;
    vector<ll> sz;
    
    explicit dsu(ll n) : n(n), comps(n) {
        clear();
    }
    
    void clear() {
        comps = n;
        parent.resize(n);
        sz.resize(n);
        for (ll i = 0; i < n; i++) {
            sz[i] = 1;
            parent[i] = i;
        }
    }
    
    ll leader(ll v) {
        // return parent[v] == v ? v : (parent[v] = leader(parent[v]));
        return parent[v] == v ? v : leader(parent[v]);
    }
    
    void unite(ll v, ll u, vector<ll> *bcp) {
        v = leader(v), u = leader(u);
        if (v == u) return;
        
        if (sz[v] < sz[u]) swap(v, u);
        
        if (bcp) bcp->push_back(u);
        parent[u] = v;
        sz[v] += sz[u];
        comps--;
    }
    
    void rollback(vector<ll> &bcp) {
        for (ll i = bcp.size() - 1; i >= 0; i--) {
            ll x = bcp[i];
            sz[parent[x]] -= sz[x];
            parent[x] = x;
            comps++;
        }
    }
};

struct edge {
    ll u, v;
};

struct query {
    ll l, r, i;
};

vector<ll> ans;
vector<edge> el;
vector<query> qs;

void solve() {
    ll n, m;
    cin >> n >> m;

    el.resize(m);

    for (ll i = 0; i < m; i++) {
        cin >> el[i].u >> el[i].v;
        el[i].u--, el[i].v--;
    }
    
    ll q;
    cin >> q;

    ans.resize(q);
    qs.resize(q);

    for (ll i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--, qs[i].r--;
        qs[i].i = i;
    }
    
    sort(qs.begin(), qs.end(), [](query a, query b) {
        if (a.l / k == b.l / k) {
            return a.r < b.r;
        } else {
            return a.l / k < b.l / k;
        }
    });
    
    ll r = 0, bl = 0;
    dsu d(n);
    for (query q : qs) {
        if (bl != q.l / k) {
            d.clear();
            bl = q.l / k;
            r = 0;
        }
        
        ll border = (bl + 1) * k;

        if (q.r <= border) {
            d.clear();
            for (ll i = q.l; i <= q.r; i++) {
                d.unite(el[i].u, el[i].v, nullptr);
            }
            ans[q.i] = d.comps;
            d.clear();
            r = 0;
            continue;
        }

        for (ll i = border + r; i <= q.r; i++) {
            d.unite(el[i].u, el[i].v, nullptr);
            r++;
        }
        
        vector<ll> bcp;

        for (ll i = border - 1; i >= q.l; i--) {
            d.unite(el[i].u, el[i].v, &bcp);
        }
        
        ans[q.i] = d.comps;
        d.rollback(bcp);
    }
    
    for (ll x : ans) {
        cout << x << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
