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

ll pref[1000001];

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        pref[i] = (pref[i-1] + x) % m;
    }

    if (n > m) {
        cout << "YES\n";
        return;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j <= n; j++) {
            if (pref[j] == pref[i]) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
