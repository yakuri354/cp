// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

ll a[100000];

void solve() {
    ll n, cps = 0, cmi = 0, cpm = INT64_MAX, cai = 0, cav = INT64_MIN;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;

        cps += x;

        if (cps - cpm > cav) {
            cav = cps - cpm;
            cpi = i;
        }

        if (x < cpm) {
            cmi = i;
            cpm = x;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
