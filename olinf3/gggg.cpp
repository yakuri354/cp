//
// Created by lain on 9/1/22.
//

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll maxn = 3*1e5 + 1;

ll a[maxn];
ll m[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll l = 0;
    for (int i = 0; i < n; ++i) {
        auto nxt = lower_bound(m, m+l, a[i]);
        if (nxt == m+l) l++;
        *nxt = a[i];
    }

    cout << n - l << endl;
}