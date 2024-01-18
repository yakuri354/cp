// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    ll half = (k - 1) / 2;

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        cout << i << ' ';
        for (ll j = 2; j <= k - 1; j += 2) {
            ll ctr = (i + (i + j)) / 2;
            if (i + j >= 0 && i + j < n && ctr >= half && ctr <= n - 1 - half) {
                cout << i + j << ' ';
                ans += a[i] != a[i+j];
            }
        }
        cout << endl;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

