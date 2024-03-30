#pragma GCC optimize("Ofast")
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
using pll = pair<ll, ll>;

struct st {
    ll x = 0;
    st *l = 0, *r = 0;

    void add_pt(ll l, ll r, ll p, ll x);
    ll query_sum(ll l, ll r, ll ql, ll qr);
};

st *st_ar;
ll st_sz = 0;
ll n;

st *alloc() {
    return st_ar + (st_sz++);
}

st *clone(st *t) {
    auto p = alloc();
    if (t) *p = *t;
    else *p = st();
    return p;
}

void st::add_pt(ll nl, ll nr, ll p, ll v) {
    this->x += v;

    if (nr - nl > 1) {
        ll m = (nl + nr) / 2;

        if (p < m) {
            this->l = clone(this->l);
            this->l->add_pt(nl, m, p, v);
        } else {
            this->r = clone(this->r);
            this->r->add_pt(m, nr, p, v);
        }
    }
}

ll st::query_sum(ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) {
        return this->x;
    }

    if (l >= qr || r <= ql) {
        return 0;
    }

    ll m = (l + r) / 2;

    ll ans = 0;

    if (this->l) ans += this->l->query_sum(l, m, ql, qr);
    if (this->r) ans += this->r->query_sum(m, r, ql, qr);

    return ans;
}

vector<st*> history;

/// O(nlog^2n)
pll getseg(ll r, ll c) {
    ll lb, hb;
    { // lower bound
        ll lo = 0, hi = n + 1;
        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;

            if (history[m]->query_sum(0, n, 0, r) >= c) {
                hi = m;
            } else {
                lo = m;
            }
        }
        if (history[hi]->query_sum(0, n, 0, r) == c) lb = hi;
        else lb = lo;
    }

    { // upper bound
        ll lo = lb, hi = n + 1;
        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;

            if (history[m]->query_sum(0, n, 0, r) > c) {
                hi = m;
            } else {
                lo = m;
            }
        }
        hb = hi;
    }

    return {lb, hb};
}

pll getans(ll r1, ll c1, ll r2, ll c2) {
    auto s1 = getseg(r1, c1), s2 = getseg(r2, c2);

    // if (s1 > s2) {
    //     swap(s1, s2);
    //     swap(r1, r2);
    //     swap(c1, c2);
    // }

    if (s1 == s2) {
        if (r1 <= r2) {
            return {r1, c1};
        } else {
            return {r2, c2};
        }
    }

    if (s1.first <= s2.first && s2.second <= s1.second) {
        return {r1, c1};
    }

    if (s2.first <= s1.first && s1.second <= s2.second) {
        return {r2, c2};
    }

    ll lb = min(s1.first, s2.first), rb = max(s1.second, s2.second) - 1;

    ll lo = 0, hi = n + 1;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (history[lb]->query_sum(0, n, 0, m) == history[rb]->query_sum(0, n, 0, m)) {
            lo = m;
        } else {
            hi = m;
        }
    }

    return {lo, history[lb]->query_sum(0, n, 0, lo)};
}

void solve() {
    cin >> n;

    vector<ll> a(n);
    for (ll &i: a) cin >> i, i--;

    st_ar = new st[n * 20];
    history.push_back(new st());

    for (ll i = 0; i < n; i++) {
        history.push_back(clone(history.back()));
        history.back()->add_pt(0, n, a[i], 1);
    }

    ll q;
    cin >> q;

    for (ll qi = 0; qi < q; qi++) {
        ll r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        c1 = r1 - c1;
        c2 = r2 - c2;

        auto res = getans(r1, c1, r2, c2);

        res.second = res.first - res.second;

        cout << res.first << ' ' << res.second << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

