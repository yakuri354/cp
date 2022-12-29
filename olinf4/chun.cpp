#include <algorithm>
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
    ll n, k;
    cin >> n >> k;
    string s, a;
    cin >> s;
    a = string(s, 0, k);

    for (ll i = 0; i < s.size(); i++) {
        rotate(s.begin(), s.begin() + 1, s.end());
        if (lexicographical_compare(s.begin(), s.begin() + k, a.begin(), a.end())) {
            a = string(s, 0, k);
        }
    }

    cout << a << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
