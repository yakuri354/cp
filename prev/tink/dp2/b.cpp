// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll d[11][82];

void solve() {
    ll s;
    cin >> s;

    if (s == 1) {
        cout << 10 << endl;
        return;
    }

    for (ll i = 0; i < 10; i++) {
        d[1][i] = 1;
    }
    for (ll i = 2; i < 10; i++) {
        for (ll z = 0; z <= s; z++) {
            for (ll j = max(z - 9, 0ll); j <= z; j++) {
                d[i][z] += d[i-1][j];
            }
        }
    }

    cout << d[9][s] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
