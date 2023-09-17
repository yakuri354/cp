// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 5e5;

struct node {
    ll l_e, r_e;
    fl max2;
};

fl avg(ll a, ll b) {
    return (fl(a) + fl(b)) / 2.0;
}

node op(node a, node b) {
    return {
        a.l_e, b.r_e, max(avg(a.r_e, b.l_e), max(a.max2, b.max2))
    };
}

const node n_id = node{-inf, 0};

node t[maxn * 4];
ll mod[maxn * 4];

ll a[maxn];

void build(ll n, ll nl, ll nr) {
    if (nr - nl <= 1) {
        t[n] = {a[nl], a[nl], fl(-inf)};
        return;
    }

    ll m = (nl + nr) / 2;
    build(n * 2 + 1, nl, m);
    build(n * 2 + 2, m, nr);

    t[n] = op(t[n * 2 + 1], t[n * 2 + 2]);
}

void push(ll n, ll nl, ll nr) {
    if (nr - nl > 1) {
        mod[n * 2 + 1] += mod[n];
        mod[n * 2 + 2] += mod[n];
    }

    t[n].max2 += mod[n];
    t[n].max2 += mod[n];
    mod[n] = 0;
}

node query(ll n, ll nl, ll nr, ll ql, ll qr) {
    push(n, nl , nr);

    if (ql <= nl && nr <= qr) {
        return t[n];
    }

    if (qr <= nl || ql >= nr) {
        return n_id;
    }

    ll m = (nl + nr) / 2;
    return op(
        query(n * 2 + 1, nl, m, ql, qr),
        query(n * 2 + 2, m, nr, ql, qr)
    );
}

void add_mut(ll n, ll nl, ll nr, ll ql, ll qr, ll x) {
    push(n, nl , nr);

    if (ql <= nl && nr <= qr) {
        mod[n] += x;
        push(n, nl, nr);
        return;
    }

    if (qr <= nl || ql >= nr) {
        return;
    }

    ll m = (nl + nr) / 2;

    add_mut(n * 2 + 1, nl, m, ql, qr, x);
    add_mut(n * 2 + 2, m, nr, ql, qr, x);

    t[n] = op(t[n * 2 + 1], t[n * 2 + 2]);
}

struct ev {
    ll ty, x, ly, ry;
};

void solve() {
    ll n, q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(0, 0, n);

    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            add_mut(0, 0, n, l - 1, r, x);
        } else if (qt == 2) {
            ll l, r;
            cin >> l >> r;
            auto res = query(0, 0, n, l - 1, r);
            cout << (fl(res.max1) + fl(res.max2)) / 2.0 << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
