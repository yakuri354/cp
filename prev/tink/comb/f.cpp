// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll a[10];

void solve() {
    ll n, m;

    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        cin >> a[i];
    }

    bool gt = false, ansex = false;
    vector<ll> ans2;
    for (ll i = 0; i < 1 << (m * 2 + 1); i++) {
        vector<ll> ans;
        ll sum = 0;
        for (ll j = 0; j < m; j++) {
            if ((i & (1 << j)) > 0) {
                ans.push_back(j);
                sum += a[j];
            }
        }

        for (ll j = 0; j < m; j++) {
            if ((i & (1 << (j + m))) > 0) {
                ans.push_back(j);
                sum += a[j];
            }
        }
        if (sum > n) gt = true;
        if (sum == n) {
            if (!ansex || ans.size() < ans2.size()) {
                ans2 = ans;
                ansex = true;
            }
        }
    }

    if (ansex) {
        cout << ans2.size() << endl;
        for (ll i : ans2) {
            cout << a[i] << ' ';
        }
        cout << endl;
        return;
    }

    if (gt)
        cout << 0;
    else
        cout << -1;

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
