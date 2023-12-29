#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

ll prefv[100000];
pair<ll, ll> h[100000];
ll pos[100000];

ll n;

void calc() {
    sort(h, h + n);
    prefv[0] = 0;
    for (ll i = 1; i < n; i++) {
        prefv[i] = prefv[i-1] + (h[i].first - h[i-1].first) * i;
    }
    for (ll i = 0; i < n; i++) {
        pos[h[i].second] = i;
    }
}

void solve() {
    ll q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> h[i].first;
        h[i].second = i;
    }

    calc();

    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll p, x;
            cin >> p >> x;
            p--;

            h[pos[p]].first = x;
            calc();
        } else {
            ll v;
            cin >> v;

            ll pos = upper_bound(prefv, prefv + n, v) - prefv;
            cout << (fl(h[pos - 1].first) + fl(v - prefv[pos - 1]) / fl(pos)) << endl;
        }
    }
}


int main() {
    cin.tie(nullptr);
    cout << fixed << setprecision(6);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
