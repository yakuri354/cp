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

set<pair<ll, ll>> st;

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

using segt = map<ll, bool>;

segt tx, ty;

void push(segt &t, ll n, ll nl, ll nr) {
    if (nl + 1 >= nr) return;
    if (t.count(n * 2 + 1) == 0) t[n * 2 + 1] = false;
    if (t.count(n * 2 + 2) == 0) t[n * 2 + 2] = false;
    t[n*2+1] ^= t[n];
    t[n*2+2] ^= t[n];
    t[n] = false;
}

void modify(segt &t, ll n, ll nl, ll nr, ll ql, ll qr) {
    if (ql <= nl && nr <= qr) {
        t[n] ^= true;
        return;
    }
    if (ql >= nr || nl >= qr) {
        return;
    }
    push(t, n, nl, nr);
    ll m = (nl + nr) / 2;
    modify(t, n * 2 + 1, nl, m, ql, qr);
    modify(t, n * 2 + 2, m, nr, ql, qr);
}

bool query(segt &t, ll n, ll nl, ll nr, ll p) {
    if (nl + 1 >= nr) return t[n];

    auto cur = t.find(n);
    if (cur == t.end()) return false;
    
    ll m = (nl + nr) / 2;
    if (p < m) return query(t, n*2 + 1, nl, m, p) ^ t[n];
    return query(t, n*2 + 2, m, nr, p) ^ t[n];
}

ll n, m, k, q;

void solve() {
    cin >> n >> m >> k >> q;
    tx[0] = false;
    ty[0] = false;

    for (ll i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;
        st.emplace(x-1, y-1);
    }

    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;
            modify(tx, 0, 0, n, 0, x1 + 1);
            modify(tx, 0, 0, n, x2 + 1, n);
            modify(ty, 0, 0, m, y1 + 1, y2 + 1);
        } else {
            ll x, y;
            cin >> x >> y;
            x--;y--;
            bool ans = query(tx, 0, 0, n, x) ^ query(ty, 0, 0, m, y) ^ st.count({x, y});
            if (ans) cout << "YES";
            else cout << "NO";
            cout << '\n';
        }
    }
}

void stress() {
    ll n = 1e9, m = 1e9;

    random_device rd{};
    mt19937_64 mt(rd());
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
