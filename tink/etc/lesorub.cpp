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


void solve() {
    ll a, k, b, m, x;
    cin >> a >> k >> b >> m >> x;
    __int128 al = a, kl = k, bl = b, ml = m, xl = x;

    __int128 lo = 0, hi = 2 * x;
    while (hi - lo > 1) {
        __int128 mid = lo + (hi - lo) / 2;
        if (al * mid + bl * mid - al * (mid / kl) - bl * (mid / ml) >= xl)
            hi = mid;
        else
            lo = mid;
    }

    cout << ll(lo + 1) << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
