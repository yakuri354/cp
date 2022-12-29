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

ll part(ll l, ll r) {
    if (l < 0 || r < 0 || r <= l) return r;
    ll p = a[(l + r) / 2];
    ll lp = l - 1, rp = r + 1;

    for (;;) {
        do
            lp++;
        while
            (a[lp] < p);
        do
            rp--;
        while
            (a[rp] > p);
        if (lp >= rp) return rp;
        swap(a[lp], a[rp]);
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;

    k--;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll l = 0, r = n, m;
    for (;;) {
        m = part(l, r-1);

        if (m == k)
            break;
        else if (k < m)
            r = m;
        else
            l = m + 1;
    }

    cout << a[m] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
