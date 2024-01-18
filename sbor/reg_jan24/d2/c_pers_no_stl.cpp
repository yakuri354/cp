#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = int;
using ull = unsigned long long;
using fl = long double;

const ll maxv = 1500001;
// const ll maxv = 100;
const ll maxn = 500000;
// const ll maxn = 100;

ll a[maxn], n, q;

ll from[maxv];

struct st {
    ll x = 0;
    st *l = 0, *r = 0;

    void add_pt(ll l, ll r, ll p, ll x);
    ll query_sum(ll l, ll r, ll ql, ll qr);
};

// const ll maxq = 500000;
const ll logv = 25;

// st st_ar[maxn * logv];
st *st_ar;
ll st_sz = 0;

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

st *history[maxn];

void solve() {
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    st_ar = (st*) malloc(sizeof(st) * max(n, 1000) * logv);

    for (ll i = 0; i < maxv; i++) {
        from[i] = i;
    }

    history[0] = new st();
    history[0]->add_pt(0, maxv, a[0], 1);
    for (ll i = 1; i < n; i++) {
        history[i] = clone(history[i-1]);
        history[i]->add_pt(0, maxv, a[i], 1);
    }

    for (ll qi = 0; qi < q; qi++) {
        ll ty;
        cin >> ty;

        if (ty == 1) {
            ll x;
            cin >> x;

            from[x+1] = from[x];
        } else if (ty == 2) {
            ll l, r, y;
            cin >> l >> r >> y;
            l--;

            ll bnd = from[y+1];

            ll ans = history[r - 1]->query_sum(0, maxv, 0, bnd);
            if (l > 0) ans -= history[l - 1]->query_sum(0, maxv, 0, bnd);

            cout << ans << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

