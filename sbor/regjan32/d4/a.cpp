// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 3 * 1e5;

ll a[maxn];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<ll, vector<ll>> mp;

    for (ll i = 0; i < n; i++) {
        mp[a[i]].push_back(i);
    }

    ll ans = inf;
    for (auto &[ix, ent] : mp) {
        for (ll i = 1; i < ent.size(); i++) {
            ans = min(ans, ent[i] - ent[i-1]);
        }
    }

    if (ans == inf) {
        cout << -1 << endl;
        return;
    }

    cout << n - ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
