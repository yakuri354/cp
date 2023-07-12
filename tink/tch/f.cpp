// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, n1;
    cin >> n;

    unordered_map<ll, ll> divs;
    n1 = n;

    for (ll i = 2; i * i <= n1 && n > 1;) {
        if (n % i == 0) {
            n /= i;
            divs[i]++;
        } else {
            i++;
        }
    }

    if (n != 1) divs[n]++;

    ll ans = 1;
    for (auto [k, v] : divs) {
        ans *= v + 1;
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
