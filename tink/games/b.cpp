// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll d[100][100];

void solve() {
    ll n, m;
    cin >> n >> m;

    bitset<101> mex;

    cerr << setfill(' ');

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            mex.set();

            for (ll i2 = 0; i2 < i; i2++) {
                mex[d[i2][j]] = false;
            }

            for (ll j2 = 0; j2 < j; j2++) {
                mex[d[i][j2]] = false;
            }

            for (ll i2 = 1; i2 <= min(i, j); i2++) {
                mex[d[i - i2][j - i2]] = false;
            }

            d[i][j] = mex._Find_first();
            // cerr << setw(2) << d[i][j] << " ";
        }
        // cerr << '\n';
    }


    if (d[n-1][m-1] == 0) {
        cout << 2 << endl;
    } else {
        cout << 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
