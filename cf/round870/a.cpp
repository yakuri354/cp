// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll a[100000];

void solve() {
    ll n;
    cin >> n;
    ll maxc = -1;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        maxc = max(maxc, a[i]);
    }

    if (maxc == 0) {
        cout << 0 << endl;
        return;
    }

    sort(a, a + n);

    for (ll i = 0; i < n - 1; i++) {
        if (i < (n - a[i]) && i >= (n - a[i+1])) {
            cout << n - i - 1 << endl;
            return;
        }
    }

    cout << -1 << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
