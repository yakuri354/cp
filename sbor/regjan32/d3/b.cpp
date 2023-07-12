// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll a[maxn], d[maxn + 1], fst[101], lst[101], cnt[101];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        fst[i] = -1;
        lst[i] = -1;
    }

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        lst[a[i]] = i;
        if (fst[a[i]] == -1)
            fst[a[i]] = i;
    }

    d[0] = 0;

    for (ll i = 1; i <= n; i++) {
        d[i] = d[i-1];

        if (lst[a[i-1]] == i - 1) {
            d[i] = max(d[i], d[fst[a[i-1]]] + cnt[a[i-1]]);
        }
    }

    cout << d[n] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
