// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n;
    cin >> n;

    if (n <= 6) {
        cout << 1 << endl;
        return;
    }

    if (n <= 10) {
        cout << 2 << endl;
        return;
    }

    n -= 7;
    ll ans = 2 + n / 4;
    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
