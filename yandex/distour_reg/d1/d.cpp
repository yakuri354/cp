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
    for (ll &i: a) cin >> i;

    ll maxn = *max_element(a.begin(), a.end()) + 2;

    vector<int> idx(maxn, -1);
    for (ll i = 0; i < n; i++) idx[a[i]] = i;

    vector<vector<pair<ll, ll>>> divs(n);

    vector<bool> sieve(maxn);
    for (ll k = 2; k < maxn; k++) {
        if (sieve[k]) continue;
        for (ll i = k; i < maxn; i += k) {
            sieve[i] = true;
            if (idx[i] != -1) {
                ll x = i, alpha = 0;
                while (x % k == 0) {
                    x /= k;
                    alpha++;
                }
                divs[idx[i]].push_back({k, alpha});
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        ll ans = -1, mdist = INT32_MAX;
        for (ll j = 0; j < n; j++) {
            if (i == j) continue;

            ll x = a[i], y = a[j], dist = 0;

            for (auto [d1, alpha1]: divs[i]) {
                for (ll z = 0; z < alpha1; z++) {
                    if (y % d1 == 0) {
                        y /= d1;
                    } else {
                        dist += alpha1 - z;
                        break;
                    }
                }
            }

            for (auto [d1, alpha1]: divs[j]) {
                for (ll z = 0; z < alpha1; z++) {
                    if (x % d1 == 0) {
                        x /= d1;
                    } else {
                        dist += alpha1 - z;
                        break;
                    }
                }
            }

            if (dist < mdist) {
                mdist = dist;
                ans = j;
            }
        }

        cout << ans + 1 << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

