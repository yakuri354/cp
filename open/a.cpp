// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2*1e5;

ll a[maxn];
bool was[maxn];

void solve() {
    ll n, k, full = 0;
    cin >> n >> k;

    vector<ll> block;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (k == 1) {
        cout << n << endl;
        return;
    }

    for (ll i = 0; i < n; i++) {
        was[a[i] - 1] = true;
        if (a[i] - 1 <= i) full++;
        if (was[i] && a[i] - 1 != i) full++;
        if (full == i + 1) block.push_back(i);
        if (block.size() + 1 == k) break;
    }

    if (block.size() + 1 < k || block.back() == n - 1) {
        cout << -1 << endl;
    } else {
        cout << block[0] + 1 << ' ';
        for (ll i = 1; i < block.size(); i++) {
            cout << block[i] - block[i-1] << ' ';
        }
        cout << n - block.back() - 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
