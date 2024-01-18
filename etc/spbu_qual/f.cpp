// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cstdint>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

mt19937_64 mt(0xab0ba);
uniform_int_distribution<ll> yd(INT64_MIN, INT64_MAX);

struct node {
    char c;
    ll sz = 1, ix;
    bool rev = false;
    node *l = 0, *r = 0;

    ll y;

    node(char c, ll ix): c(c), ix(ix), y(yd(mt)) {}

    void upd() {
        sz = 1;
        if (l) sz += l->sz;
        if (r) sz += r->sz;
    }

    void push() {
        if (rev) {
            swap(l, r);
            if (l) l->rev ^= 1;
            if (r) r->rev ^= 1;
            rev = false;
        }

        upd();
    }
};

node *merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;

    if (l->y > r->y) {
        l->push();
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else {
        r->push();
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }
}

pair<node*, node*> split_n(node *t, ll n) {
    if (!t) return {0, 0};
    t->push();

    ll ls = t->l ? t->l->sz : 0;
    if (ls >= n) {
        auto [l1, r1] = split_n(t->l, n);
        t->l = r1;
        t->upd();
        return {l1, t};
    } else {
        auto [l1, r1] = split_n(t->r, n - ls - 1);
        t->r = l1;
        t->upd();
        return {t, r1};
    }
}

void dfs(node *t) {
    if (!t) return;
    t->push();
    dfs(t->l);
    cout << t->c;
    dfs(t->r);
}

void solve() {
    ll n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    node *t = nullptr;
    for (ll i = 0; i < n; i++) {
        t = merge(t, new node(s[i], i));
    }

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--, r--;

        if (l == r) continue;

        if (l < r) {
            auto [lt, tmp] = split_n(t, l);
            auto [m, rt] = split_n(tmp, r - l + 1);

            m->rev ^= 1;

            t = merge(merge(lt, m), rt);
        } else {
            auto [lt, tmp] = split_n(t, r + 1);
            auto [m, rt] = split_n(tmp, l - r - 1);

            auto sg = merge(rt, lt);

            sg->rev ^= 1;

            auto [nr, nl] = split_n(sg, n - l);

            t = merge(merge(nl, m), nr);
        }
    }

    dfs(t);
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

