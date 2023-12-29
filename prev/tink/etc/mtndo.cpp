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

ll t[200000];
ll n;

void add(ll l, ll r, ll v) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) t[l++] += v;
        if (r & 1) t[--r] += v;
    }
}

void pusha() {
    for (ll i = 1; i < n; ++i) {
        t[i * 2] += t[i];
        t[i * 2 + 1] += t[i];
        t[i] = 0;
    }
}

void solve() {
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> t[n+i];
    }
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll k, x;
        cin >> k >> x;
        add(n - k, n, x);
    }
    pusha();
    for (ll i = 0; i < n; i++) {
        cout << t[n+i] << ' ';
    }
    cout << '\n';
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
