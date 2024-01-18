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
using l1 = long long;
using ll = __int128;
using ull = unsigned long long;
using fl = long double;

void solve() {
    l1 n, All;
    cin >> n >> All;

    ll A = All;

    vector<pair<ll, ll>> a(n);
    for (ll i = 0; i < n; i++) {
        l1 x;
        cin >> x;
        a[i].first = x;
        a[i].second = i;
    }

    sort(a.begin(), a.end());

    ll ans = 0;

    ll la = -1, lb = -1;
    for (ll i = 0; i < n - 1; i++) {
        ll lo = i + 1, hi = n;

        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;

            if (a[i].first * a[m].first <= A) {
                lo = m;
            } else {
                hi = m;
            }
        }

        ll val = a[i].first * a[lo].first;
        if (val <= A && val > ans) {
            ans = val;
            la = a[i].second;
            lb = a[lo].second;
        }
    }

    if (ans == 0) {
        cout << 0 << endl;
        return;
    } else {
        cout << l1(ans) << '\n';
        cout << l1(la + 1) << ' ' << l1(lb + 1) << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
