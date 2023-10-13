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

const ll inf = INT32_MAX;

void solve() {
    ll mx = 0, ans = 0;
    set<ll> z;
    for (ll x = 100; x <= 1e4; x++) {
        ll cnt = 0;
        for (ll n = x; n < 1e5 && cnt <= 110; ++n) {
            if (n != x && (x * n) % (n - x) == 0 && (x * n) / (n - x) >= n) {
                // cout << cnt << ' ' << n << ' ' << (x * n) / (n - x) << endl;
                cnt++;
            }

            // for (ll m = n; m <= 100000; ++m) {
            //     if (x * (n + m) == n * m) {
            //         ++cnt;
            //         cout << x << ' ' << n << ' ' << m << endl;
            //     }
            // }
        }
        
        cout << x << " -> " << cnt << endl;
        
        if (cnt > 110) {
            z.insert(x);
        }

        if (mx < cnt) {
            mx = cnt;
            ans = x;
        }
    }
    
    for (ll i : z) {
        cout << i << endl;
    }

    cout << mx << ' ' << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
