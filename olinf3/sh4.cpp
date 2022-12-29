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
    ll n, m, ans = n;
    cin >> n >> m;

    ll x = 0, y = 0;
    if (n != 1) {
        cout << ans << endl;
        return;
    }
    ans += m - 1;
    ans += n - 1;

    n -= 2;
    m -= 3;

    ll *zzz[2] = {&m, &n};

    ll i = 0;
    while (true) {
        if (*zzz[i%2] - i <= 0) break;
        ans += *zzz[i % 2] - i;
        i++;
    }
    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}



