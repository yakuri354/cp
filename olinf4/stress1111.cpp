#include <random>
#ifndef DBG
// #pragma GCC optimize("Ofast")
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

ll n, m, k, q;
bool d[100000];

struct tree {
    tree *l = 0, *r = 0;
    bool v = false;
    ll lb, rb;

    tree(ll l, ll r): lb(l), rb(r) {}

    void ext() {
        if (lb + 1 >= rb || l) return;
        ll m = (lb + rb) / 2;
        l = new tree(lb, m);
        r = new tree(m, rb);
    }

    void push() {
        if (lb + 1 >= rb) return;
        ext();
        l->v ^= v;
        r->v ^= v;
        v = false;
    }

    void setv(ll ql, ll qr) {
        if (ql <= lb && rb <= qr) {
            v ^= 1;
            return;
        }
        if (ql >= rb || lb >= qr) {
            return;
        }
        push();
        ll m = (lb + rb) / 2;
        l->setv(ql, qr);
        r->setv(ql, qr);
    }

    bool query(ll p) {
        if (lb + 1 >= rb) return v;
        if (l) push();
        ll m = (lb + rb) / 2;
        if (p < m) {
            if (l)
                return l->query(p) ^ v;
            return v;
        } else {
            if (r)
                return r->query(p) ^ v;
            return v;
        }
    }
};


void solve() {
    n = m = 10;
    tree t(0, n);
    random_device rd{};
    mt19937_64 mt(rd());
    uniform_int_distribution<ll> dist(0, n - 1);
    for (;;) {
        ll l = dist(mt);
        ll r = dist(mt);
        if (l > r) swap(l, r);
        t.setv(l, r + 1);
        for (ll i = l; i <= r; i++) {
            d[i] ^= true;
        }
        for (ll i = 0; i < n; i++) {
            if (t.query(i) != d[i]) {
                cout << "ERR" << endl;
                t.query(i);
                return;
            }
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
