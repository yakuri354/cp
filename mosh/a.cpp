// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll r, c, a, b;
    cin >> r >> c >> a >> b;

    for (ll rn = 0; rn < r; rn++) {
        for (ll hn = 0; hn < a; hn++) {
            for (ll cn = 0; cn < c; cn++) {
                for (ll ch = 0; ch < b; ch++) {
                    bool full = (rn & 1) == (cn & 1);
                    cout << (full ? 'X' : '.');
                }
            }
            cout << '\n';
        }
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
