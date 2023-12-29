#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
    unordered_map<ll, ll> mp;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]] = i;
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    n = a.size();
    ll m = *max_element(a.begin(), a.end());

    vector<ll> v(m + 1);

    for (ll i: a) v[i]++;

    ll ans = -1, ansl = -1, ansr = -1;

    for (ll i = 0; i < n; i++) {
        for (ll j = 1; a[i] * j <= m; j++) {
            if (v[a[i] * j] > 0) {
                if (ans < a[i] * (j - 1)) {
                    ans = a[i] * (j - 1);
                    ansl = a[i];
                    ansr = a[i] * j;
                }
            }
        }
    }

    cout << mp[ansl] + 1 << ' ' << mp[ansr] + 1 << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0) solve();
}
