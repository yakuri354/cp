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

bool imp(bool a, bool b) {
    return ~a|b;
}

bool bit(int mask, int pos) {
    return ((mask>>pos)&1) == 1;
}

void solve() {
    int mask = 0;

    for (int m = 0; m < 1 << 5; m++) {
        if (imp(bit(m, 0)))
            cout << bitset<32>(m) << endl;
            return;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
