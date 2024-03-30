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
using pll = pair<ll, ll>;

const ll inf = 1e15;

void solve() {
    ll n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;
    sort(a.begin(), a.end());

    vector<ll> diff(n, 0);
    vector<ll> diffs = {0};
    vector<pll> diff_ixs;

    for (ll i = 1; i < n; i++) {
        diff[i] = a[i] - a[i-1];
        if (diff[i] != 0) {
            diffs.push_back(diff[i]);
        }
        diff_ixs.push_back({diff[i], i});
    }
    diff_ixs.push_back({0, n});

    sort(diff_ixs.begin(), diff_ixs.end());

    vector<ll> diff_pref_left(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        diff_pref_left[i] = diff_pref_left[i-1] + diff_ixs[i-1].first * diff_ixs[i-1].second;
    }

    vector<ll> diff_pref_right(n + 1, 0);
    for (ll i = n - 1; i >= 0; i--) {
        diff_pref_right[i] = diff_pref_right[i+1] + diff_ixs[i].second;
    }

    sort(diffs.begin(), diffs.end());
    // diffs.erase(unique(diffs.begin(), diffs.end()), diffs.end());

    for (ll qi = 0; qi < q; qi++) {
        ll qty, k;
        cin >> qty >> k;

        if (qty == 1) { // OK
            if (k == 0) cout << diffs.size() << '\n';
            else cout << diffs.end() - upper_bound(diffs.begin(), diffs.end(), k) + 1 << '\n';
        }

        if (qty == 2) {
            if (k == 0) {
                cout << 0 << '\n';
                continue;
            }

            auto bnd = upper_bound(diff_ixs.begin(), diff_ixs.end(), pll{k, inf}) - diff_ixs.begin();
            ll ans = diff_pref_left[bnd] + diff_pref_right[bnd] * k;
            cout << ans << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

