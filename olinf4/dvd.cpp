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

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}


void solve() {
    ll w, h;
    cin >> w >> h;

    ll x1 = (w * h) / gcd(w, h) ;
    ll hi = x1 / w - 1;
    ll vi = x1 / h - 1;
    bool right = hi % 2 == 0, down = vi % 2 == 0;
    if (!right) {
        if (down)
            cout << 3;
        else 
            cout << 1;
    } else {
        if (down)
            cout << 4;
        else
            cout << 2;
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
