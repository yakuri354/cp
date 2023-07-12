// #pragma GCC optimize("Ofast")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxm = 1e3;

ll mod(ll x) {
    return x % (ll(1e9) + 7);
}

ll C[maxm + 1][maxm + 1];

void solve() {
    for (ll n = 0; n <= maxm; n++) {
        C[n][0] = C[n][n] = 1;

        for (ll k = 1; k < n; k++) {
            C[n][k] = mod(C[n-1][k-1] + C[n-1][k]);
        }
    }

    ll n;
    cin >> n;
    ll ans = 1;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        ll zz = 0;
        for (ll j = 0; j < x; j++) {
            zz = mod(zz + C[x-1][j]);
        }
        ans = mod(ans * zz);
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
