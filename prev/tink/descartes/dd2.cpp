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

random_device rdd{};
mt19937 mt(rdd());
uniform_int_distribution<ll> dist(1, INT64_MAX);

struct node {
    node *l = nullptr, *r = nullptr;

    ll y, c, v;

    node(ll v): y(dist(mt)), c(1), v(v) {}

    void update() {
        this->c = 1;
        if (this->l) this->c += this->l->c;
        if (this->r) this->c += this->r->c;
    }
};

node* merge(node* l, node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->update();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->update();
        return r;
    }
}

pair<node*, node*> split(node *t, ll k) {
    if (t == nullptr) return {nullptr, nullptr};

    ll cl = t->l ? t->l->c : 0;
    if (cl > k) {
        auto [l1, r1] = split(t->l, k);
        t->l = r1;
        t->update();
        return {l1, t};
    } else {
        auto [l2, r2] = split(t->r, k - cl - 1);
        t->r = l2;
        t->update();
        return {t, r2};
    }
}

void dfsp(node* t) {
    if (!t) return;
    dfsp(t->l);
    cout << t->v << ' ';
    dfsp(t->r);
}

void solve() {
    ll n, m;
    cin >> n >> m;

    auto *dd = new node(1);
    
    for (ll i = 2; i <= n; i++) {
        dd = merge(dd, new node(i));
    }

    for (ll i = 0; i < m; i++) {
        ll li, ri;
        cin >> li >> ri;

        auto [l1, right] = split(dd, ri);
        auto [left, mid] = split(l1, li - 1);
        
        left = merge(mid, left);
        dd = merge(left, right);
    }

    dfsp(dd);
    cout << '\n';
}


int main() {
    // cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
