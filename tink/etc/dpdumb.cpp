// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

ll a[1000];
ll ss[1000];
ll d[1000][1000];

void solve() {
    ll n, a1, k, b, m;
    cin >> n >> a1 >> k >> b >> m;

    a[0] = a1;
    ss[0] = a1;
    for (ll i = 1; i < n; i++) {
        a[i] = (k * a[i-1] + b) % m;
        ss[i] = a[i];
    }

    sort(ss, ss + n);
    m = unique(ss, ss + n) - ss;
    
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            if (a[i-1] == ss[j-1])
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
