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

vector<ll> a;

void solve() {
    ll m;
    cin >> m;

    for (ll i = 0; i < m; ++i) {
        ll n;
        cin >> n;
        for (ll j = 0; j < n; ++j) {
            ll x;
            cin >> x;
            a.push_back(x);
        }
    }

    // sort(a.rbegin(), a.rend());
    sort(a.begin(), a.end());

    float ans = 0;

    for (ll i = a.size() - 1; i >= 2 * (m - 1); --i) {
        ans = ans + float(a[i]) / float(a.size() - (m - 1) * 2);
    }


    for (ll i = 2 * (m - 1) - 2; i >= 0; i -= 2) {
        ans += float(a[i] + a[i+1]) / 2;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

