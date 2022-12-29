#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

random_device rdd;
mt19937 mt(rdd());
uniform_int_distribution<ll> dist(0, INT64_MAX);

struct node {
    ll x, y;

    node *l = nullptr, *r = nullptr;

    node(ll x, ll y) : x(x), y(y) {}
    explicit node(ll x): x(x), y(dist(mt)) {}

    void killallmen() {
        if (l) {
            l->killallmen();
            delete l;
        }
        if (r) {
            r->killallmen();
            delete r;
        }
    }
    
    ~node() {
        killallmen();
    }
};

node* merge(node* l, node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(r->l, l);
        return r;
    }
}

pair<node*, node*> split(node* t, ll x) {
    if (t == nullptr) return make_pair(nullptr, nullptr);
    if (t->x < x) {
        auto [l, r] = split(t->r, x);
        t->r = l;
        return {t, r};
    } else {
        auto [l, r] = split(t->l, x);
        t->l = r;
        return {l, t};
    }
}

void insert(node* t, ll x, ll y) {
    auto [l, r] = split(t, x);

    l = merge(l, new node(x, y));
    
    t = merge(l, r);
}

node* find(node* t, ll x) {
    while (t != nullptr && t->x != x)
        if (x < t->x) t = t->l;
        else t = t->r;
    return t;
}

void remove(node* t, node* r) {
    node* p = nullptr;
    while (p != nullptr && p->l != r && p->r != r)
        if (r->x < p->x) p = p->l;
        else p = p->r;

    if (p == nullptr) return;

    auto n = merge(r->l, r->r);
    if (p->l == r) p->l = n;
    else p->r = n;

    r->l = r->r = nullptr;
    delete r;
}
