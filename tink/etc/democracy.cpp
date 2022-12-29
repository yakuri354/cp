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

struct pt {
    ll votes;
    ll bribe;

    bool operator<(const pt& other) {
        return this->votes < other.votes;
    }
    bool operator>(const pt& other) {
        return this->votes > other.votes;
    }
};

pt a[100000];

void solve() {
    ll n, people = 0;

    for (ll i = 0; i < n; i++) {
        cin >> a[i].votes >> a[i].bribe;
        people += a[i].votes;
    }

    sort(a, a + n, greater<>());

    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
