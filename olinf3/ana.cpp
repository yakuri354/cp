#include <random>
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

void solve() {
    string tmp;
    vector<string> s;

    while (getline(cin, tmp)) s.push_back(tmp);

    sort(s.begin(), s.end(), [](string &a, string &b) {
            auto y = a + b;
            auto x = b + a;
            return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
        });
    // sort(s.begin(), s.end(), greater<>());

    for (auto &x : s) {
        cout << x;
    }
    cout << endl;
}


int main() {
    // cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
    return 0;
}

