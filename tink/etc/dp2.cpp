// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

ll d[1001][1001];

void solve() {
    string a, b;
    cin >> a >> b;

    ll n = a.length(), m = b.length();

    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= m; j++) {
            if (i == 0 && j == 0) continue;
            if (i == 0) {
                d[i][j] = d[i][j-1] + 1;
                continue;
            }

            if (j == 0) {
                d[i][j] = d[i-1][j] + 1;
                continue;
            }

            if (a[i-1] == b[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                d[i][j] = d[i-1][j];
                d[i][j] = min(d[i][j], d[i][j-1]);
                d[i][j] = min(d[i][j], d[i-1][j-1]);
                if (i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]) {
                    d[i][j] = min(d[i][j], d[i-2][j-2]);
                }

                d[i][j]++;
            }
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
