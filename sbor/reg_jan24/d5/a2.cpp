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
    ll l, r;
    cin >> l >> r;
    
    ll l1 = 0, r1 = 0;

    while 
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

