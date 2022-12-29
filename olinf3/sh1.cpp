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
    ll n, x, ans = 0;
    cin >> n >> x;

    if ((n + 1) * n / 2 < x) { cout << 0 << endl; }

    ll lo = 0, hi = n + 2;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if ((n - mid + 1) * (mid + n) / 2 > x) lo = mid;
        else hi = mid;
    }
    vector<ll> ans3{};
    ll ans2 = 0;
    for (ll ii = n; ans2 < x; ii--) {
        ans3.push_back(ii);
        ans2 += ii;
    }
    if (ans2 > x) {
        ans3[ans3.size() - 1] -= ans2 - x;
    }
    for (ll jj: ans3) {
        cout << jj << " ";
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
