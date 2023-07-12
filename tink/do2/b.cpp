// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll t[2*maxn], n;

void modify(ll l, ll r, ll x) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) t[l++] += x;
        if (r & 1) t[--r] += x;
    }
}

ll query(ll i) {
    ll res = 0;
    for (i += n; i > 0; i >>= 1) res += t[i];
    return res;
}

void solve() {
    ll k;
    cin >> n >> k;

    for (ll i = 0; i < k; i++) {
        char qty;
        cin >> qty;
        if (qty == '?') {
            ll i;
            cin >> i;
            cout << query(i - 1) << '\n';
        } else if (qty == '+') {
            ll l, r, x;
            cin >> l >> r >> x;
            modify(l - 1, r, x);
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
