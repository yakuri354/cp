// #pragma GCC optimize("Ofast")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll cnt[1 << 10];

void solve() {
    ll n, k;
    cin >> k >> n;

    for (ll i = 0; i < n; i++) {
        ll z;
        cin >> z;
        string x = to_string(z);

        ll mask = 0;

        bool kal = false;
        for (char y : x) {
            ll oldm = mask;
            mask |= 1 << (y - '0');
            if (mask == oldm) kal = true;
        }
        if (kal) continue;

        cnt[mask]++;
    }

    ll total = 0;
    for (ll m1 = 0; m1 < 1 << 10; m1++) {
        ll ans = 0;
        if (cnt[m1] == 0) continue;
        for (ll m2 = 0; m2 < 1 << 10; m2++) {
            if ((m1 & m2) == 0) ans += cnt[m1] * cnt[m2];
        }
        total += ans;
    }
    cout << total / 2 << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
    return 0;
}
