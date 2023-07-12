// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 102;

ll a[maxn], d[maxn][maxn];

void solve() {
    ll l, n;
    cin >> l >> n;

    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    a[n + 1] = l;
    for (ll l = 2; l <= n + 1; l++) {
        for (ll i = 0; i + l <= n + 1; i++) {
            d[i][i+l] = inf;
            for (ll j = i + 1; j < i + l; j++) {
                d[i][i + l] = min(d[i][i+l], d[i][j] + d[j][i+l] + a[i+l] - a[i]);
            }
        }
    }

    cout << d[0][n+1] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
