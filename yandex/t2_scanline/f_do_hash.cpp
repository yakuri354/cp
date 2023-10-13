// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ull inf = INT64_MAX;
const ll maxn = 1e5;

struct node {
    ll l, r;
    ull hs;
};

const ull P = 1e9 + 7;

ull p[maxn + 1], ps[maxn + 1];

node merge(node l, node r) {
    return {
        l.l, r.r,
        l.hs * p[r.r - r.l] + r.hs
    };
}

vector<node> t;
vector<ull> m;

void push(ll n, ll nl, ll nr) {
    if (m[n] == inf) return;

    t[n].hs = ps[t[n].r - t[n].l - 1] * ull(m[n]);

    if (nr - nl > 1) {
        m[n * 2 + 1] = m[n];
        m[n * 2 + 2] = m[n];
    }

    m[n] = inf;
}

void modify(ll n, ll nl, ll nr, ll ql, ll qr, ll x) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        m[n] = x;
        push(n, nl, nr);
        return;
    }

    if (nl >= qr || nr <= ql) {
        return;
    }

    ll m = (nl + nr) / 2;

    modify(n * 2 + 1, nl, m, ql, qr, x);
    modify(n * 2 + 2, m, nr, ql, qr, x);

    t[n] = merge(t[n * 2 + 1], t[n * 2 + 2]);
}

node query(ll n, ll nl, ll nr, ll ql, ll qr) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        return t[n];
    }

    if (nl >= qr || nr <= ql) {
        return node{.l = nl, .r = nr, .hs = 0};
    } 

    ll m = (nl + nr) / 2;

    return merge(query(n * 2 + 1, nl, m, ql, qr), query(n * 2 + 2, m, nr, ql, qr));
}

ull a[maxn];

void build(ll n, ll nl, ll nr) {
    if (nr - nl < 2) {
        t[n] = {
            .l = nl,
            .r = nr,
            .hs = a[nl]
        };
        return;
    }

    ll m = (nl + nr) / 2;

    build(n * 2 + 1, nl, m);
    build(n * 2 + 2, m, nr);

    t[n] = merge(t[n * 2 + 1], t[n * 2 + 2]);
}

void solve() {
    ll n;
    cin >> n;
    
    p[0] = 1;
    ps[0] = 1;
    for (ll i = 1; i <= n; i++) {
        p[i] = p[i-1] * P;
        ps[i] = ps[i-1] + p[i];
    }

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    t.resize(n * 4);
    m.resize(n * 4, inf);

    build(0, 0, n);

    ll m;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        ll q, l, r, k;
        cin >> q >> l >> r >> k;
        l--, r--;

        if (q == 0) {
            modify(0, 0, n, l, r + 1, k);
        } else {
            if (p[l] * query(0, 0, n, l, l + k).hs == 
                p[r] * query(0, 0, n, r, r + k).hs) {
                cout << '+';
            } else {
                cout << '-';
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