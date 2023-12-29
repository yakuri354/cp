#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll a[maxn];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) cin >> a[i];

    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--, r--;

        ll sz = r - l + 1;

        ll ans = 0;
        ll b1 = inf;
        for (ll k = 0; k < n; k++) {
            if (k >= l && k <= r) continue;
            b1 = min(b1, a[k] + abs(k - l + 1));
        }
        ll b2 = inf;
        for (ll k = 0; k < n; k++) {
            if (k >= l && k <= r) continue;
            b2 = min(b2, a[k] + abs(k - r - 1));
        }
        for (ll j = l; j <= r; j++) {
            ll base = (a[j] * (a[j] - 1)) / 2;
            ll best = base + min(a[j] * abs(j - l + 1) + a[j] * b1, a[j] * abs(j - r - 1) + a[j] * b2);
            ans += best;
        }
        cout << ans << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
