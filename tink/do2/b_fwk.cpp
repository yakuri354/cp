// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2 * 1e5;

ll t[maxn + 1], n;

ll sum_px(ll i) {
    ll res = 0;
    for (; i > 0; i -= i & -i) {
        res += t[i];
    }
    return res;
}

void add_pt(ll i, ll x) {
    for (; i <= n; i += i & -i) {
        t[i] += x;
    }
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
            cout << sum_px(i) << '\n';
        } else if (qty == '+') {
            ll l, r, x;
            cin >> l >> r >> x;
            add_pt(l, x);
            add_pt(r + 1, -x);
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
