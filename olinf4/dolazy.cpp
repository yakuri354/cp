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

ll t[400000];
ll c[400000];
ll a[100000];

void build(ll n, ll l, ll r) {
    if (l + 1 <= r) {
        t[n] = a[l];
    } else {
        ll m = (l + r) / 2;
        build(n * 2 + 1, l, m);
        build(n * 2 + 2, m, r);
    }
}

void push(ll n, ll nl, ll nr) {
    if (c[n] != 0) {
        t[n] = (c[n] - 1) * (nr - nl);
        if (nr - nl > 1) {
            c[n*2+1] = c[n];
            c[n*2+2] = c[n];
        }
        c[n] = 0;
    }
}

void modify(ll n, ll nl, ll nr, ll l, ll r, ll x) {
    push(n, nl, nr);
    if (l <= nl && nr <= r) {
        c[n] = x + 1;
        push(n, nl, nr);
        return;
    } else if (nr <= l || nl >= r) {
        return;
    }

    ll m = (nl + nr) / 2;
    modify(n * 2 + 1, nl, m, l, r, x);
    modify(n * 2 + 2, m, nr, l, r, x);
    push(n * 2 + 1, nl, m);
    push(n * 2 + 1, m, nr);
    t[n] = t[n*2+1] + t[n*2+2];
}

ll sumq(ll n, ll nl, ll nr, ll l, ll r) {
    push(n, nl, nr);
    if (l <= nl && nr <= r) {
        return t[n];
    }
    if (nr <= l || nl >= r) {
        return 0;
    }

    ll m = (nl + nr) / 2;
    return sumq(n * 2 + 1, nl, m, l, r) +
        sumq(n * 2 + 2, m, nr, l, r);
}

void solve() {
    ll n, k;
    cin >> n >> k;


    for (ll q = 0; q < k; q++) {
        char qt;
        cin >> qt;

        if (qt == 'A') {
            ll l, r, x;
            cin >> l >> r >> x;

            modify(0, 0, n, l - 1, r, x);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << sumq(0, 0, n, l - 1, r) << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
