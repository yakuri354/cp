#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const ll inf = INT32_MAX;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

ll d[1001][1001];
ll n;

void floyd() {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            for (ll k = 0; k < n; k++) {
                d[j][k] = min(d[j][k], max(d[j][i], d[i][k]));
            }
        }
    }
}

void solve() {
    ifstream fs;
    fs.open("avia.in");
    fs >> n;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            fs >> d[i][j];
        }
    }
    floyd();

    ll maxl = INT32_MIN;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            maxl = max(maxl, d[i][j]);
        }
    }
    ofstream ofs;
    ofs.open("avia.out");
    ofs << maxl << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
