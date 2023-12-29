// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct ev {
    ll ty;
    ll x;
    ll hi, lo;
};

vector<ev> evs;

struct node {
    int mel;
    ll mcnt;
    ll l, r;
};

vector<ll> ys;
unordered_map<ll, ll> compress;

node cmb(node a, node b) {
    if (a.mel == b.mel) {
        return node {
            a.mel,
            a.mcnt + b.mcnt,
            a.l, b.r
        };
    } else if (a.mel < b.mel) {
        return node {
            a.mel,
            a.mcnt,
            a.l, b.r
        };
    } else {
        return node {
            b.mel,
            b.mcnt,
            a.l, b.r
        };
    }
}

vector<node> t;
vector<ll> add;

void build(ll n, ll nl, ll nr) {
    if (nr - nl <= 1) {
        t[n] = node {
            .mel = 0,
            .l = ys[nl],
            .r = nl == ll(ys.size() - 1) ? ys[nl] + 1 : ys[nl+1],
        };
        t[n].mcnt = t[n].r - t[n].l;
        return;
    }

    ll m = (nl + nr) / 2;

    build(n*2+1, nl, m);
    build(n*2+2, m, nr);

    t[n] = cmb(t[n*2+1], t[n*2+2]);
}

void push(ll n, ll nl, ll nr) {
    t[n].mel += add[n];
    if (nr - nl > 1) {
        add[n*2+1] += add[n];
        add[n*2+2] += add[n];
    }
    add[n] = 0;
}

node query(ll n, ll nl, ll nr, ll ql, ll qr) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        return t[n];
    }
    if (ql >= nr || qr <= nl) {
        return node { inf, 0 };
    }

    ll m = (nl + nr) / 2;

    return cmb(
        query(n*2+1, nl, m, ql, qr),
        query(n*2+2, m, nr, ql, qr));
}

void add_segt(ll n, ll nl, ll nr, ll ql, ll qr, ll v) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        add[n] += v;
        push(n, nl, nr);
        return;
    }
    if (ql >= nr || qr <= nl) {
        return;
    }

    ll m = (nl + nr) / 2;

    add_segt(n*2+1, nl, m, ql, qr, v);
    add_segt(n*2+2, m, nr, ql, qr, v);

    t[n] = cmb(t[n*2+1], t[n*2+2]);
}

void solve() {
    ll n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return;
    }

    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        evs.push_back(ev {
                          .ty = 1,
                          .x = x1,
                          .hi = y2,
                          .lo = y1,
                      });

        evs.push_back(ev {
                          .ty = -1,
                          .x = x2,
                          .hi = y2,
                          .lo = y1,
                      });
    }

    sort(evs.begin(), evs.end(), [](ev a, ev b) {
             return a.x < b.x;
         });

    ll lx = -inf, state = 0, ans = 0;

    for (ev e : evs) {
        ys.push_back(e.hi);
        ys.push_back(e.lo);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    for (ll i = 0; i < ll(ys.size()); i++) {
        compress[ys[i]] = i;
    }

    t.assign(ys.size() * 4, node {});
    add.assign(ys.size() * 4, 0);

    build(0, 0, ys.size());

    for (ev e : evs) {
        ans += (e.x - lx) * state;

        add_segt(0, 0, ys.size(), compress[e.lo], compress[e.hi], e.ty);

        state = 1 + ys[ys.size() - 1] - ys[0] - t[0].mcnt;
        lx = e.x;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
