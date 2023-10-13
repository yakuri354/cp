#include <cstdint>
#include <tuple>
#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

unordered_map<ll, ll> comp_y;

struct pt {
    ll x, y;
};

struct qr {
    pt a, b;
};

struct event {
    ll ix, ty, x, lo, hi;

    auto t() -> decltype(make_tuple(x, ty, lo, hi, ix)) {
        return make_tuple(x, ty, lo, hi, ix);
    }
};

vector<ll> t;
ll tn = 0;

void add(ll i, ll x) {
    t[i += tn] += x;
    for (i >>= 1; i > 0; i >>= 1) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += tn, r += tn; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res += t[l++];
        }
        if (r & 1) {
            res += t[--r];
        }
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;

    vector<event> evs;

    set<ll> cs;
    vector<pt> pts(n);

    for (auto& [x, y] : pts) {
        cin >> x >> y;
        cs.insert(y);
    }

    ll m;
    cin >> m;

    vector<qr> qs(m);

    for (auto& [a, b] : qs) {
        cin >> a.x >> a.y >> b.x >> b.y;
        cs.insert(a.y);
        cs.insert(b.y);
    }

    cerr << "cs " << cs.size() << " -> " << log10l(cs.size()) << endl;

    t.resize(cs.size() * 2 + 1);
    tn = cs.size();

    vector<ll> uncomp_y(cs.begin(), cs.end());

    for (ll i = 0; i < uncomp_y.size(); i++) {
        comp_y[uncomp_y[i]] = i;
    }

    for (ll i = 0; i < n; i++) {
        auto& [x, y] = pts[i];
        evs.push_back({.ix = 0, .ty = -inf, .x = x, .lo = comp_y[y]});
    }

    for (ll i = 0; i < m; i++) {
        auto& [a, b] = qs[i];
        evs.push_back({.ix = i,
                       .ty = -1,
                       .x = a.x - 1,
                       .lo = comp_y[a.y],
                       .hi = comp_y[b.y]});
        evs.push_back(
            {.ix = i, .ty = 1, .x = b.x, .lo = comp_y[a.y], .hi = comp_y[b.y]});
    }

    cerr << "evs " << evs.size() << " -> " << log10l(evs.size()) << endl;

    sort(evs.begin(), evs.end(),
         [](auto& a, auto& b) { return a.t() < b.t(); });

    cerr << "sorted" << endl;

    vector<ll> qa(m);

    for (auto& e : evs) {
        if (e.ty == -inf) {
            add(e.lo, 1);
            continue;
        }

        qa[e.ix] += query(e.lo, e.hi + 1) * e.ty;
    }

    for (ll i = 0; i < m; i++) {
        cout << qa[i] << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
