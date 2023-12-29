// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

ll a[1001], b[1001], d[1001][1001];

void solve() {
    ll n, m;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (ll i = 0; i < m; i++) {
        cin >> b[i];
    }

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1])
                d[i][j] = d[i-1][j-1] + 1;
            else
                d[i][j] = max(max(d[i][j-1], d[i-1][j]), d[i-1][j-1]);
        }
    }
    cout << d[n][m] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
