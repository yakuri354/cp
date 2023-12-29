#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

random_device rd{};
mt19937 mt(rd());
uniform_int_distribution<ll> dist(0, INT64_MAX);

struct node {
    ll s = 1, y, v, maxv, minv, area = 0;

    node *l = nullptr, *r = nullptr;

    node(ll v): y(dist(mt)), v(v), maxv(v), minv(v) {}

    void upd() {
        s = 1;
        if (l) {
            minv = l->minv;
            s += l->s;
        }
        if (r) {
            maxv = r->maxv;
            s += r->s;
        }

        area = 0;
        if (l) area += l->area + (v - l->maxv) * l->s;
        if (r) area += r->area + (maxv - v) * ((l ? l->s : 0) + 1);
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

pair<node*, node*> split(node *t, ll k) {
    if (!t) return {0, 0};

    ll ls = t->l ? t->l->s : 0;
    if (ls >= k) {
        auto [lt, rt] = split(t->l, k);
        t->l = rt;
        t->upd();
        return {lt, t};
    } else {
        auto [lt, rt] = split(t->r, k - ls - 1); 
        t->r = lt;
        t->upd();
        return {t, rt};
    }
}

pair<node*, node*> split_by(node *t, ll v) {
    if (!t) return {0, 0};

}

ll a[100000];

void solve() {
    ll n, q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) cin >> a[i];

    sort(a, a + n);

    node *dd = nullptr;
    
    for (ll i = 0; i < n; i++) dd = merge(dd, new node(a[i]));

    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;

        if (qt == 1) {
            ll p, x;
            cin >> p >> x;

            auto [l, rt] = split(dd, p - 1);
            auto [vert, r] = split(rt, 1);
            
            dd = merge(l, r);


        } else if (qt == 2) {
            ll v;
            cin >> v;


        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
