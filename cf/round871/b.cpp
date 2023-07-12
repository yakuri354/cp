// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll a[10100];
ll b[10100];

void solve() {
    ll n, m;
    cin >> n >> m;

    ll z = n*m;

    for (ll i = 0; i < z; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b, b + z);

    if (n > m) swap(n, m);

    ll ans = (m - 1) * n * (b[z-1] - b[0]);

    ans += max(b[z-1] - b[1], b[z-2] - b[0]) * (n - 1);

    cout << ans << '\n';
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
