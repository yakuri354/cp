#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdio>
#include <iostream>
#include <mutex>
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

const ll k = 500;

struct edge {
    ll i, x;
    ll from, to;
    
    bool up = false;
};

vector<ll> tin, tout;

struct query {
    ll a, b, i;
    
    inline ll _l() const {
        return tin[a] + 1;
    }
    
    inline ll _r() const {
        return tin[b];
    }

    pair<ll, ll> to_pair() const {
        ll l = _l(), r = _r();
        return {l / k, ((l / k) % 2 == 0) ? r : -r};
    }
};

struct sqrt_mex {
    ll n, k;
    
    vector<ll> a;
    vector<ll> bs;
    vector<ll> cnt;

    sqrt_mex(ll n): n(n), k(sqrt(n)), a(n), bs(k + 1), cnt(n) {}
    
    void resize(ll n) {
        this->n = n;
        k = sqrt(n);
        a.resize(n);
        bs.resize(k + 1);
        cnt.resize(n);
    }
    
    void add(ll x) {
        if (x >= n) return;
        if (cnt[x] > 0) {
            cnt[x]++;
            return;
        }
        
        a[x] = 1;
        bs[x / k]++;
        cnt[x] = 1;
    }
    
    void rm(ll x) {
        if (x >= n) return;
        if (cnt[x] > 1) {
            cnt[x]--;
            return;
        }
        
        a[x] = 0;
        bs[x / k]--;
        cnt[x] = 0;
    }
    
    ll mex() {
        ll i = 0;
        while (bs[i / k] >= min(k, n - k * (i / k))) i += k;
        while (a[i]) i++;
        
        return i;
    }
};

vector<vector<edge>> g;

vector<edge> ge;
vector<query> qs;

ll timer = 0;

void euler(ll v, ll p = -1) {
    for (auto e: g[v]) {
        if (e.to == p) continue;
        ge.push_back(e);

        tin[e.to] = timer++;
        euler(e.to, v);
        tout[e.to] = timer++;

        auto e2 = e;
        e2.up = true;
        swap(e2.from, e2.to);

        ge.push_back(e2);
    }
}

sqrt_mex mex(1);
vector<ll> edge_count;

ll answer() {
    return mex.mex();
}

void add_edge(ll t) {
    auto e = ge[t];
    if (e.i == -1) return;
    
    if (edge_count[e.i] == 0) {
        mex.add(e.x);
    } else if (edge_count[e.i] == 1) {
        mex.rm(e.x);
    }

    edge_count[e.i]++;
}

void remove_edge(ll t) {
    auto e = ge[t];
    if (e.i == -1) return;

    if (edge_count[e.i] == 2) {
        mex.add(e.x);
    } else if (edge_count[e.i] == 1) {
        mex.rm(e.x);        
    }

    edge_count[e.i]--;
}

void solve() {
    ll n, q;
    cin >> n >> q;
    
    g.resize(n, {});
    edge_count.resize(n);
    tin.resize(n);
    tout.resize(n);
    
    mex = sqrt_mex(n + 1);
    
    for (ll i = 0; i < n - 1; i++) {
        ll a, b, x;
        cin >> a >> b >> x;
        a--, b--;

        g[a].push_back({.i = i, .x = x, .from = a, .to = b});
        g[b].push_back({.i = i, .x = x, .from = b, .to = a});
    }
    
    ge.push_back({.i = -1, .x = inf});
    timer++;
    euler(0);
    ge.push_back({.i = -1, .x = inf});
    timer++;
    
    for (ll i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        
        if (tin[b] < tin[a]) swap(a, b);

        qs.push_back({.a = a, .b = b, .i = i});
    }
    
    vector<ll> qa(q);
    
    sort(qs.begin(), qs.end(), [](query a, query b) -> bool {
        return a.to_pair() < b.to_pair();
    });
    
    ll l = 0, r = 0;
    
    for (ll qi = 0; qi < q; qi++) {
        ll ql = qs[qi]._l(), qr = qs[qi]._r();
        
        while (r < qr) add_edge(++r);
        while (l > ql) add_edge(--l);
        
        while (r > qr) remove_edge(r--);
        while (l < ql) remove_edge(l++);
        
        qa[qs[qi].i] = answer();
    }
    
    for (ll i = 0; i < q; i++) {
        cout << qa[i] << '\n';
    }
    
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
