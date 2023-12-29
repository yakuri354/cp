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

    vector<ll> a(n);
    for (ll &i : a) cin >> i;

    sort(a.begin(), a.end());

    ll ans = 0;

    vector<pair<ll, ll>> rle;

    for (ll i = 0; i < n;) {
        ll el = a[i++];
        rle.push_back({el, 1});
        while (i < n && a[i] == el) {
            rle.back().second++;
            i++;
        }
    }

    for (ll i = 0; i < rle.size(); i++) {
        if (rle[i].second == 0) continue;

        if (i + 1 < rle.size() && rle[i].first == rle[i+1].first - 1) {
            ll match = min(rle[i].second, rle[i+1].second);
            ans += match;
            rle[i+1].second -= match;
            rle[i].second -= match;
        }

        ans += rle[i].second;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

