// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < 1 << n; i++) {
        if (!(i & (i >> 1))) {
            for (ll j = n - 1; j >= 0; j--)
                cout << (i >> j & 1) << ' ';
            cout << endl;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
