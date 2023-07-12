// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

mt19937_64 mt(random_device{}());
uniform_int_distribution<ll> id(INT64_MIN, INT64_MAX);

struct node {
    node *l = 0, *r = 0;
    ll v, s = 1, y;

    explicit node(ll v) : v(v), y(id(mt)) {}

    void upd() {
        s = 1;
        if (l) s += l->s;
        if (r) s += r->s;
    }
};

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }
}

pair<node*, node*> split(node* t, ll n) {
    if (!t) return {0, 0};

    ll ls = t->l ? t->l->s : 0;
    if (n > ls) { // ?
        auto [m, r] = split(t->r, n - ls - 1);
        t->r = m;
        t->upd();
        return {t, r};
    } else {
        auto [l, m] = split(t->l, ls);
        t->l = m;
        t->upd();
        return {l, t};
    }
}

void solve() {

}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
