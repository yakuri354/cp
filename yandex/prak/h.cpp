// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <utility>
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

    ll ans = (n - 2) * (n - 2);
    
    set<pair<ll, ll>> s[2];

    for (ll i = 0; i < q; i++) {
        ll ty, x;
        cin >> ty >> x;
        ty--;

        auto nxt = s[ty].upper_bound({x, 0});

        ll h = n - 1;
        if (nxt == s[ty].begin() || s[ty].empty()) {
            if (!s[ty^1].empty()) {
                h = s[ty^1].begin()->first - 1;
            }
        } else if (nxt == s[ty].end()) {
            h = s[ty].rbegin()->second;
        } else {
            h = (--nxt)->second;
        }
        s[ty].insert({x, h});
        ans -= h - 1;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

