// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll cc = 317;

ll a[cc + 2][cc + 2];
ll mx[cc + 2];
ll mxi[cc + 2];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i/cc][i%cc];
    }

    for (ll i = 0; i <= (n-1)/cc; i++) {
        mx[i] = -inf;
        for (ll j = 0; j < cc && i * cc + j < n; j++) {
            if (a[i][j] > mx[i]) {
                mx[i] = a[i][j];
                mxi[i] = i * cc + j;
            }
        }
    }

    ll k;
    cin >> k;

    for (ll i = 0; i < k; i++) {
        ll l, r, ans = -inf, ansi = 0;
        cin >> l >> r;
        l--;
        r--;

        while (l <= r) {
            if (l % cc == 0 && l + cc - 1 <= r) {
                if (ans < mx[l/cc]) {
                    ans = mx[l/cc];
                    ansi = mxi[l/cc];
                }
                l += cc;
                continue;
            }

            if (ans < a[l/cc][l%cc]) {
                ans = a[l/cc][l%cc];
                ansi = l;
            }

            l += 1;
        }

        cout << ans << ' ' << ansi + 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
