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

ll n, x, c;

ll sg(ll z) {
    z = min(z, c);

    return (2 * c - z) * (z + 1) / 2;
}

bool check(ll k) {
    ll mx = 0;
    if (k >= n) {
        mx = n * c;
    } else if (k * c <= n) { // sus
        mx = k * (c + 1) * c / 2;
    } else {
        mx = k * sg(n / k - 1) + (n % k) * max(0ll, c - n / k);
    }

    return mx >= x;
}

void solve() {
    cin >> n >> x >> c;

    ll lo = -1, hi = n;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (check(m + 1)) hi = m;
        else lo = m;
    }

    if (check(hi + 1)) {
        cout << hi << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

