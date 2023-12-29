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

    vector<ll> a(n);

    for (ll &i: a) {
        cin >> i;
    }

    ll sum_deg = accumulate(a.begin(), a.end(), 0ll);
    if (sum_deg / 2 < m) {
        cout << -1 << endl; // super sus
        return;
    }

    sort(a.begin(), a.end(), greater<>());

    ll ans = 1;
    for (ll i = 0; i < n && a[i] >= i; i++) {
        ans = i + 1;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

