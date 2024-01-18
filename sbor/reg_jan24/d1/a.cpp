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
    ll n, m;
    cin >> n >> m;

    ll i1 = -1, j1 = -1, i2, j2;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            ll x;
            cin >> x;

            if (x == 1) {
                if (i1 == -1) {
                    i1 = i, j1 = j;
                } else {
                    i2 = i, j2 = j;
                }
            }
        }
    }

    if (j1 > j2) {
        swap(i1, i2);
        swap(j1, j2);
    }

    ll ans = 0;
    
    if (j1 != j2) {
        ans = max(ans, n * (m - j1 - 1));
        ans = max(ans, n * (j1 + 1));

        ans = max(ans, n * (m - j2 - 1));
        ans = max(ans, n * j2);
    }

    if (i1 > i2) {
        swap(i1, i2);
        swap(j1, j2);
    }

    if (i1 != i2) {
        ans = max(ans, m * (n - i1 - 1));
        ans = max(ans, m * (i1 + 1));

        ans = max(ans, m * (n - i2 - 1));
        ans = max(ans, m * i2);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

