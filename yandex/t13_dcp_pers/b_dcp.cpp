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

enum class ty {
    add, rm, ask
};

struct query {
    ty t;
    ll u, v;

    ll edge_i() const {
        return u * 1000000 + v;
    }
};

struct dsu {
    ll n, comps;
    vector<ll> p, sz;

    dsu(ll n) : n(n), comps(n), p(n, 0), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    ll ldr(ll v) {
        return p[v] == v ? v : ldr(p[v]);
    }

    ll unite(ll a, ll b) {
        a = ldr(a), b = ldr(b);
        if (a == b) return -1;

        if (sz[a] < sz[b]) swap(a, b);

        p[b] = a;
        sz[a] += sz[b];
        comps--;

        return b;
    }

    void undo(ll x) {
        if (x < 0) return;

        sz[p[x]] -= sz[x];
        p[x] = x;
        comps++;
    }
};

vector<ll> qa;
vector<query> qs;

void dcp(ll l, ll r, dsu &d) {
    if (r - l <= 1) {
        if (qs[l].t == ty::ask) {
            qa[l] = d.comps;
        }
        return;
    }

    ll m = (l + r) / 2;

    vector<ll> hist;
    unordered_set<ll> used;

    for (ll i = l; i < m; i++) {
        if (qs[i].t != ty::ask) {
            used.insert(qs[i].edge_i());
        }
    }

    for (ll i = m; i < r; i++) {
        if (used.count(qs[i].edge_i())) continue;
        if (qs[i].t == ty::rm) {
            hist.push_back(d.unite(qs[i].u, qs[i].v));
        }
        used.insert(qs[i].edge_i());
    }

    dcp(l, m, d);

    for (; !hist.empty(); hist.pop_back()) {
        d.undo(hist.back());
    }

    used.clear();

    for (ll i = m; i < r; i++) {
        if (qs[i].t != ty::ask) {
            used.insert(qs[i].edge_i());
        }
    }

    for (ll i = m - 1; i >= l; i--) {
        if (used.count(qs[i].edge_i())) continue;
        if (qs[i].t == ty::add) {
            hist.push_back(d.unite(qs[i].u, qs[i].v));
        }
        used.insert(qs[i].edge_i());
    }

    dcp(m, r, d);

    for (; !hist.empty(); hist.pop_back()) {
        d.undo(hist.back());
    }
}

void solve() {
    ll n, q;
    cin >> n >> q;

    qa.resize(q);

    for (ll i = 0; i < q; i++) {
        string tt;
        cin >> tt;

        if (tt == "?") {
            qs.push_back({ty::ask, 0, 0});
            continue;
        }

        ll u, v;
        cin >> u >> v;

        if (u > v) swap(u, v);

        if (tt == "+") {
            qs.push_back({ty::add, u - 1, v - 1});
        }

        if (tt == "-") {
            qs.push_back({ty::rm, u - 1, v - 1});
        }
    }

    if (q == 0) return;

    dsu d(n);
    dcp(0, q, d);

    for (ll i = 0; i < q; i++) {
        if (qs[i].t == ty::ask) {
            cout << qa[i] << '\n';
        }
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

