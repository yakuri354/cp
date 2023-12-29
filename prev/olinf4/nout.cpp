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

template<typename T> T min(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

pair<ll, ll> a[100000];

void solve() {
    ll n;
    cin >> n;

    for (int i = 0; i < n; i++) { cin >> a[i].first >> a[i].second; }

    sort(a, a + n, [](auto a, auto b) {return a.first < b.first; });

    for (ll i = 1; i < n; i++) {
        if (a[i-1].first < a[i].first && a[i-1].second > a[i].second) {
            cout << "Happy Alex" << endl;
            return;
        }
    }
    cout << "Poor Alex" << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

