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
    ll n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (((i + 1) * (n - i)) % 2 == 1) {
            ans ^= a[i];
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        ll p, x;
        cin >> p >> x;
        p--;

        if (((p + 1) * (n - p)) % 2 == 1) {
            ans ^= a[p];
        }

        a[p] = x;

        if (((p + 1) * (n - p)) % 2 == 1) {
            ans ^= a[p];
        }

        cout << ans << '\n';
    }
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

