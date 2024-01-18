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

struct node {
    vector<int> ixs;
    ll val;
};

const ll maxv = 1500001;
// const ll maxv = 100;
const ll maxn = 500000;
// const ll maxn = 100;

node* n_now[maxv], *n_here[maxv];
node na[maxv];

ll a[maxn], n, q;

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
        na[i].val = i;
        na[i].ixs.push_back(i);
        n_now[i] = na + i;
        n_here[i] = na + i;
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

            if (n_now[x]->ixs.size() == 0) continue;

            auto from_n = n_here[x];
            auto to_n = n_here[x + 1];

            if (to_n->ixs.size() < from_n->ixs.size()) {
                swap(n_here[x], n_here[x+1]);
                swap(from_n, to_n);
                n_here[x]->val = x;
                n_here[x+1]->val = x + 1;
            }

            for (ll i: from_n->ixs) {
                n_now[i] = to_n;
                // to_n->ixs.push_back(i);
            }

            ll from_sz = from_n->ixs.size(), to_sz = to_n->ixs.size();
            to_n->ixs.resize(from_sz + to_sz, 0);
            copy(from_n->ixs.begin(), from_n->ixs.end(), to_n->ixs.begin() + to_sz);

            from_n->ixs.clear();
        } else if (ty == 2) {
            ll l, r, y;
            cin >> l >> r >> y;
            l--;

            ll lo = 0, hi = y + 1; // sus
            while (hi - lo > 1) {
                ll m = (lo + hi) / 2;

                if (n_now[m]->val > y) {
                    hi = m;
                } else {
                    lo = m;
                }
            }

            ll ans = history[r - 1]->query_sum(0, maxv, 0, hi);
            if (l > 0) ans -= history[l - 1]->query_sum(0, maxv, 0, hi);

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

