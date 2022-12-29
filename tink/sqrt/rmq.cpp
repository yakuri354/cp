// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2*1e5;
const ll cc = 640;

ll a[cc + 2][cc + 2];
ll mx[cc + 2];
ll zz[cc + 2];

void solve() {
    ll n, k, m;
    cin >> n >> k >> m;
    n += 1;

    for (ll i = 0; i < n; i++) {
        a[i/cc][i%cc] = k;
    }

    for (ll i = 0; i < cc + 2; i++) {
        mx[i] = k;
    }

    for (ll i = 0; i < m; i++) {
        ll l, l2, r, r2, ans = inf;
        cin >> l >> r;

        r--;

        l2 = l;
        r2 = r;

        while (l <= r) {
            if (l % cc == 0 && l + cc - 1 <= r) {
                ans = min(ans, mx[l/cc] + zz[l/cc]);
                l += cc;
                continue;
            }

            ans = min(ans, a[l/cc][l%cc] + zz[l/cc]);

            l += 1;
        }

        if (ans > 0) {
            cout << 1 << endl;
            l = l2;
            r = r2;
            while (l <= r) {
                if (l % cc == 0 && l + cc - 1 <= r) {
                    zz[l/cc] -= 1;
                    l += cc;
                    continue;
                }

                a[l/cc][l%cc] -= 1;

                l += 1;
            }
        } else {
            cout << 0 << endl;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
