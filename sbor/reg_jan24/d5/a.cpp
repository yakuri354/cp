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

ll inc(ll x) {
    return (x * (x + 1)) / 2;
}

ll before_full(ll x) {
    ll lo = 0, hi = x + 1;

    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (inc(m) < x) lo = m;
        else hi = m;
    }

    return lo;
}

ll between_full(ll x) {
    ll lo = 0, hi = x + 1;

    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if ((m * (m + 1)) / 2 < x) lo = m;
        else hi = m;
    }

    return lo;
}

void solve() {
    l1 _l, _r;
    cin >> _l >> _r;

    ll l = _l, r = _r;

    ll l_b = before_full(l);
    ll lx = inc(l_b) + 1;

    ll r_b = before_full(r);
    ll rx = inc(r_b) + 1;

    ll l_sub = inc(l - lx);
    ll r_add = inc(r - rx + 1);

    ll ans = 0;
    for (ll i = l_b + 1; i <= r_b; i++) {
        ans += inc(i);
    }
    ans -= l_sub;
    ans += r_add;

    cout << l1(ans) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

