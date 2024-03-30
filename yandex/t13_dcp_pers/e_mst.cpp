#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
using uint = unsigned int;
using fl = long double;

const ll N = 1 << 17;

const ll LGA = 24;

uint A, B, cur = 0;

uint nextRand17() {
    cur = cur * A + B; // вычисляется с переполнениями 
    return cur >> 15; // число от 0 до 2^{17}-1.
}

uint nextRand24() {
    cur = cur * A + B; // вычисляется с переполнениями
    return cur >> 8; // число от 0 до 2^{24}-1.
}

struct node {
    node *l = 0, *r = 0;
    ll x = 0;
};

// node narr[1 << 21];
node narr[100];
ll last = 0;

node *alloc() {
    return narr + last++;
}

node *clone(node *x) {
    node *y = alloc();
    y = x;
    return y;
}

node *add(node *t, ll nl, ll nr, ll p, ll x) {
    if (!t) t = alloc();
    else t = clone(t);

    if (nr - nl < 2) {
        t->x += x;
        return t;
    }

    ll m = (nl + nr) / 2;

    if (p < m) {
        t->l = add(t->l, nl, m, p, x);
    } else {
        t->r = add(t->r, m, nr, p, x);
    }

    return t;
}

ll sum(node *t, ll nl, ll nr, ll ql, ll qr) {
    if (!t) return 0;

    if (ql <= nl && nr <= qr) {
        return t->x;
    }

    if (ql >= nr || qr <= nl) {
        return 0;
    }

    ll m = (nl + nr) / 2;

    return sum(t->l, nl, m, ql, qr) + sum(t->r, m, nr, ql, qr);
}

void solve() {
    ll q;
    cin >> q >> A >> B;

    node *t = nullptr;

    vector<node*> hist;

    for (ll i = 0; i < N; i++) {
        ll x = nextRand24();
        hist.push_back(add(t, 0, N, x, 1));
    }

    for (ll qi = 0; qi < q; qi++) {
        ll l = nextRand17(), r = nextRand17();
        if (l > r) swap(l, r);

        ll x = nextRand24(), y = nextRand24();
        if (x > y) swap(x, y);

        ll res = sum(hist[r]

        B += res;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

