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
    ll n;
    cin >> n;

    ll s = ll(sqrtl(n));

    ll pos = 0;
    for (ll i = 0; i <= 62; i++) {
        if (((n >> i) & 1) == 0) {
            pos++;
        }
    }

    ll cnt = 0, maxv = 0;
    for (ll i = 62; i >= 0; i--) {
        if (((n >> i) & 1) == 0) {
            pos--;
        }

        if (((n >> i) & 1) == 0 && maxv + (1ll << i) <= s) {
            cnt += 1ll << pos;
            maxv += 1ll << i;
        }
    }

    ll ans = 2 * cnt;

    if (s * s == n && (s & n) == 0) {
        ans -= 1;
    }
    
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

