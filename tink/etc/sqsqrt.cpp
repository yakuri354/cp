#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

const fl eps = 1e-15;

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

fl f(fl c) {
    return c * c + sqrt(c);
}

void solve() {
    fl c;
    cin >> c;

    fl lo = 0.0, hi = 1e10;
    ll iters = 0;
    while (hi - lo > eps && iters < 1000000) {
        iters++;
        fl m = (hi - lo) / 2 + lo;

        if (f(m) < c)
            lo = m;
        else
            hi = m;
    }
    cout << fixed << setprecision(20) << lo << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
