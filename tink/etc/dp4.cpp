// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

ll d[5001][5001];

void solve() {
    ll n, k, ans = 0;
    cin >> n >> k;
    string a;
    cin >> a;

    for (ll s = 0; s < n - 1; s++) {
        if (a[s] == a[s+1]) d[2][s] = 0;
        else
            d[2][s] = 1;
        if (d[2][s] <= k) ans++;
    }

    for (ll l = 3; l <= n; l++) {
        for (ll s = 0; s < n - l + 1; s++) {
            d[l][s] = d[l-2][s + 1];
            if (a[s] != a[s+l-1]) d[l][s]++;
            if (d[l][s] <= k) ans++;
        }
    }

    cout << ans + n << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
