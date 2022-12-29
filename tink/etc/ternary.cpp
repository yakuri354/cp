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

pair<ll, ll> a[100000];
ll x[100000];

void solve() {
    ll n, m;
    cin >> n >> m;
    for (ll i = 0; i < n; i++) cin >> a[i].first, a[i].second = i;
    for (ll i = 0; i < m; i++) cin >> x[i];

    sort(a, a + n);

    for (ll i = 0; i < m; i++) {
        
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
