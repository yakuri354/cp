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


void solve() {
    ll n, m;
    cin >> n >> m;

    ll aans = 0;

    if (n < m) {
        ll x = m;
        m = n;
        n = x;
    }

    aans = n - (m / 2 + m % 2 - 1) * 2;
    if (!(m & 1)) aans *= 2;
    cout << aans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}



