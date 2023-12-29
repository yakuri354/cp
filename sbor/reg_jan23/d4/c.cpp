#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 5*1e5;
const ll tsz = 1 << 20;

ll a[maxn], N;

struct ent {
    ll v1, v2, v3;
    ll l = 0, r = 0;

    ll sz() {
        return this->r - this->l;
    }

    ent(ll x1, ll x2, ll x3, ll l, ll r) : l(l), r(r), v1(x1), v2(x2), v3(x3) {}
    ent(ll x, ll l, ll r) : l(l), r(r), v1(x), v2(x), v3(x) {}
    ent() : v1(0), v2(0), v3(0) {}
};

struct segt {
    vector<ent> t;
    vector<ll> m;

    ent(*op)(ent, ent);
    ent(*full)(ll, ll, ll);

    segt(ent(*op)(ent, ent), ent(*full)(ll, ll, ll)) : op(op), full(full) {
        t.resize(maxn * 4);
        m.resize(maxn * 4);
    }
};

void build(segt& t, ll n, ll nl, ll nr) {
    t.m[n] = -1;
    if (nr - nl <= 1) {
        t.t[n] = ent(a[nl], nl, nr);
        return;
    }

    ll m = (nl + nr) / 2;
    build(t, n * 2 + 1, nl, m);
    build(t, n * 2 + 2, m, nr);
    t.t[n] = t.op(t.t[n*2 + 1], t.t[n*2 + 2]);
}

void push(segt& t, ll n, ll nl, ll nr) {
    if (t.m[n] == -1) return;

    if (nr - nl > 1) {
        ll m = (nl + nr) / 2;
        t.m[n*2 + 1] = t.m[n];
        t.m[n*2 + 2] = t.m[n];
    }

    t.t[n] = t.full(t.m[n], nl, nr);
    t.m[n] = -1;
}

ent query(segt& t, ll n, ll nl, ll nr, ll ql, ll qr) {
    push(t, n, nl, nr);
    if (ql <= nl && nr <= qr) {
        return t.t[n];
    }
    if (nl >= qr || nr <= ql) {
        return ent(0, 0, 0);
    }

    ll m = (nl + nr) / 2;
    return t.op(query(t, n*2 + 1, nl, m, ql, qr), query(t, n*2 + 2, m, nr, ql, qr));
}


void modify(segt& t, ll n, ll nl, ll nr, ll ql, ll qr, ll v) {
    push(t, n, nl, nr);
    if (ql <= nl && nr <= qr) {
        t.m[n] = v;
        push(t, n, nl, nr);
        return;
    }
    if (nl >= qr || nr <= ql) {
        return;
    }

    ll m = (nl + nr) / 2;
    modify(t, n*2 + 1, nl, m, ql, qr, v);
    modify(t, n*2 + 2, m, nr, ql, qr, v);
    t.t[n] = t.op(t.t[n*2 + 1], t.t[n*2 + 2]);
}

ll mod(ll x) {
    return x % ll(1e9 + 7);
}

ll sum_int(ll l, ll r) {
    return ((r - l + 1) * (l + r)) / 2;
}

ll sum_sq(ll l, ll r) {
    ll n = r - l + 1;
    return mod((l - 1) * (l - 1) * n) + mod((n * (n + 1) * (2*n + 1)) / 6);
}

ent cmbf(ent a, ent b) {
    if (a.sz() == 0) return b;
    if (b.sz() == 0) return a;
    ll v1 = a.v1 + b.v1;
    ll v2 = a.v2 + b.v2 + mod(b.v1 * a.sz());
    ll v3 = a.v3 + b.v3 + mod(2 * a.sz() * b.v2) + mod(a.sz() * a.sz() * b.v1);

    return ent(mod(v1), mod(v2), mod(v3), a.l, b.r);
}

ent fullf(ll v, ll l, ll r) {
    return ent(
        mod(v) * (r - l),
        mod(sum_int(1, r - l)) * v,
        mod(sum_sq(1, r - l)) * v,
        l, r
    );
}

segt tr(cmbf, fullf);

void solve() {
    ll n, q;
    cin >> n >> q;
    N = n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(tr, 0, 0, n);

    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;

        if (qt == 1) {
            ll l, r, x;
            cin >> l >> r >> x;

            modify(tr, 0, 0, n, l - 1, r, x);
        } else if (qt == 2) {
            ll l, r;
            cin >> l >> r;

            cout << mod(query(tr, 0, 0, n, l - 1, r).v3) << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
