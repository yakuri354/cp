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

#include "geom.hpp"

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

void solve() {
    ll n, m, k;

    cin >> n >> m >> k;

    vector<pt> pts(n);

    for (auto &i : pts) {
        cin >> i;
    }
    
    polygon p(pts);
    
    ll ans = 0;
    for (ll i = 0; i < m; i++) {
        pt x;
        cin >> x;

        ans += p.has(x);
    }
    
    if (ans >= k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
