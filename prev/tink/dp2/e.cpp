// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll d[21][10];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < 10; i++) {
        d[1][i] = 1;
    }

    for (ll i = 2; i <= n; i++) {
        for (ll j = 0; j < 10; j++) {
            d[i][j] = d[i-1][j];
            if (j > 0) d[i][j] += d[i-1][j-1];
            if (j < 9) d[i][j] += d[i-1][j+1];
        }
    }

    ll ans = 0;
    for (ll i = 1; i < 10; i++) {
        ans += d[n][i];
    }
    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
