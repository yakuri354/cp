// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll t[maxn + 1], a[maxn], n;

ll ps(ll i) {
    ll ans = 0;
    for (; i > 0; i -= i & -i) {
        ans += t[i];
    }
    return ans;
}

ll sum(ll l, ll r) {
    return ps(r) - ps(l - 1);
}

void add(ll i, ll x) {
    for (; i <= n; i += i & -i) {
        t[i] += x;
    }
}

void solve() {
    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;

        add(i + 1, x);
    }

    ll m;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        string qt;
        cin >> qt;
        
        if (qt == "s") {
            ll l, r;
            cin >> l >> r;

            cout << sum(l, r) << ' ';
        } else if (qt == "u") {
            ll i, x;
            cin >> i >> x;

            add(i, x - sum(i, i));
        }
    }

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
