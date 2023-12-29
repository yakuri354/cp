// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll t[2*maxn], n;

ll query(ll l, ll r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += t[l++];
        if (r & 1) res += t[--r];
    }
    return res;
}

void modp(ll i, ll x) {
    for (t[i += n] = x; i > 1; i >>= 1) {
        t[i>>1] = t[i] + t[i ^ 1];
    }
}

void solve() {
    ll k;
    cin >> n >> k;

    for (ll i = 0; i < k; i++) {
        char qty;
        cin >> qty;
        if (qty == 'A') {
            ll i, x;
            cin >> i >> x;
            modp(i - 1, x);
        } else if (qty == 'Q') {
            ll l, r;
            cin >> l >> r;
            cout << query(l - 1, r) << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
