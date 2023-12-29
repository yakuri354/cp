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

ll a[100000];
ll n, k;

bool check(ll d) {
    ll last = a[0], placed = 1;
    for (ll i = 1; i < n; i++) {
        if (placed >= k) return true;
        if (a[i] - last < d) continue;

        placed++;
        last = a[i];
    }

    // cerr << "d " << d << "; placed " << placed << endl;

    return placed >= k;
}

void solve() {
    cin >> n >> k;

    for (ll i = 0; i < n; i++) cin >> a[i];

    sort(a, a + n);

    ll lo = 0, hi = 1000000000;
    while (lo + 1 < hi) {
        ll m = (lo + hi) / 2;
        if (check(m))
            lo = m;
        else
            hi = m;
    }

    cout << lo << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
