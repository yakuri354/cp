// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <map>

using namespace std;
using ll = long long;
// using li = __int128;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

struct pt {
    ll i, j;

    bool operator<(const pt &o) const {
        return make_tuple(i, j) < make_tuple(o.i, o.j);
    }

    bool operator==(const pt &o) const {
        return make_tuple(i, j) == make_tuple(o.i, o.j);
    }
};

struct dsu {
    // vector<ll> par, sz;

    // unordered_map<ll, ll> par, sz;
    map<pt, ll> sz;
    map<pt, pt> par;
    
    // dsu(ll n): par(n), sz(n, 1) {
    //     iota(par.begin(), par.end(), 0);
    // }

    void add(pt x) {
        sz[x] = 1;
        par[x] = x;
    }

    pt leader(pt v) {
        if (!par.count(v)) {
            par[v] = v;
            return v;
        }
        return v == par[v] ? v : (par[v] = leader(par[v]));
    }

    void unite(pt a, pt b) {
        if (par.count(a) == 0 || par.count(b) == 0) return;

        a = leader(a), b = leader(b);

        if (a == b) return;

        if (!sz.count(a)) {
            sz[a] = 1;
        }
        if (!sz.count(b)) {
            sz[b] = 1;
        }

        if (sz[a] < sz[b]) swap(a, b);

        par[b] = a;
        sz[a] += sz[b];
    }
};

ll enc(ll x, ll y) {
    return x * ll(1e10) + y;
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    dsu d;

    pt DOWN = {0, ll(1e12)}, RIGHT = {ll(1e12), 0};

    d.add(DOWN);
    d.add(RIGHT);

    bool def = false;

    for (ll i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;
        x--, y--;

        pt p = {x, y};       

        d.add(p);

        if (def) {
            cout << "Defeat!\n";
            continue;
        }

        if (p.j == m - 1 || p.i == 0) {
            d.unite(p, RIGHT);
        }

        if (p.i == n - 1 || p.j == 0) {
            d.unite(p, DOWN);
        }

        d.unite(p, {p.i, p.j + 1});
        d.unite(p, {p.i, p.j - 1});

        d.unite(p, {p.i + 1, p.j});
        d.unite(p, {p.i - 1, p.j});

        d.unite(p, {p.i + 1, p.j + 1});
        d.unite(p, {p.i - 1, p.j - 1});

        d.unite(p, {p.i - 1, p.j + 1});
        d.unite(p, {p.i + 1, p.j - 1});

        if (d.leader(DOWN) == d.leader(RIGHT)) {
            def = true;
            cout << "Defeat!\n";
        } else {
            cout << "Success!\n";
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

