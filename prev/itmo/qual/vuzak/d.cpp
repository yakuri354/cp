// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, t;
    cin >> n >> t;

    ll prev, vad = 0, val = 0;
    cin >> prev;

    for (ll i = 1; i < n; i++) {
        ll x;
        cin >> x;
        if (x <= prev) {
            ll k = 0;
            while (x + (1 << k) <= prev && k < 32) k++;
            vad++;
            val += k + 1;
            prev = x + (1 << k);
        } else {
            prev = x;
        }
    }

    if (t == 1) {
        cout << vad << endl;
    } else {
        cout << val << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
