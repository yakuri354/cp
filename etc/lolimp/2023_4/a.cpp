// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <deque>
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
using pll = pair<ll, ll>;

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    vector<bool> ok(n, true);
    for (ll &i: a) cin >> i;

    sort(a.begin(), a.end());

    ll ans = 0;

    ll l = 0;

    for (ll i = 0; i < n; i++) {
        while (l < n && a[i] - a[l] > k) l++;

        ans = max(ans, i - l + 1);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

