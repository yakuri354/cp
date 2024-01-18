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
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    ll half = (k - 1) / 2;

    unordered_map<ll, ll> cnt;
    set<ll> added;
    ll total = 0;

    auto ix_ok = [&](ll i, ll x) {
        if (x <= i) return false;
        if (x - i > k - 1) return false;
        ll ctr = (i + x) / 2;
        return x >= 0 && x < n && ctr >= half && ctr <= n - 1 - half;
    };

    cnt.clear();
    total = 0;

    for (ll j = 2; j <= k - 1; j += 2) {
        if (ix_ok(0, j)) {
            cnt[a[j]]++;
            added.insert(j);
            total++;
        }
    }

    if (added.empty()) exit(-1);

    // ll ans = 0, l = *added.begin(), r = *added.rbegin();
    ll ans = 0;
    for (ll i = 0; i < n; i += 2) {
        if (added.empty()) break;
        while (*added.begin() - 2 >= 0 && ix_ok(i, *added.begin() - 2)) {
            ll l2 = *added.begin() - 2;
            cnt[a[l2]]++;
            added.insert(l2);
            total++;
        }

        while (*added.rbegin() + 2 < n && ix_ok(i, *added.rbegin() + 2)) {
            ll r = *added.rbegin();
            cnt[a[r+2]]++;
            added.insert(r + 2);
            total++;
        }

        while (!added.empty() && !ix_ok(i, *added.rbegin())) {
            ll r = *added.rbegin();
            cnt[a[r]]--;
            added.erase(r);
            total--;
        }

        while (!added.empty() && !ix_ok(i, *added.begin())) {
            ll l = *added.begin();
            cnt[a[l]]--;
            added.erase(l);
            total--;
        }

        // for (ll j = 2; j <= k - 1; j += 2) {
        //     ll ctr = (i + (i + j)) / 2;
        //     if (i + j >= 0 && i + j < n && ctr >= half && ctr <= n - 1 - half) {
        //         ans += a[i] != a[i+j];
        //     }
        // }

        ans += total - cnt[a[i]];

        // cout << i << ' ';
        // for (ll x: added) cout << x << ' ';
        // cout << endl;
    }

    cnt.clear();
    added.clear();
    total = 0;

    for (ll j = 2; j <= k - 1; j += 2) {
        if (ix_ok(1, 1 + j)) {
            cnt[a[1 + j]]++;
            added.insert(1 + j);
            total++;
        }
    }

    if (added.empty()) exit(-1);

    for (ll i = 1; i < n; i += 2) {
        if (added.empty()) break;
        while (*added.begin() - 2 >= 0 && ix_ok(i, *added.begin() - 2)) {
            ll l = *added.begin();
            cnt[a[l-2]]++;
            added.insert(l - 2);
            total++;
        }

        while (*added.rbegin() + 2 < n && ix_ok(i, *added.rbegin() + 2)) {
            ll r = *added.rbegin();
            cnt[a[r+2]]++;
            added.insert(r + 2);
            total++;
        }

        while (!added.empty() && !ix_ok(i, *added.rbegin())) {
            ll r = *added.rbegin();
            cnt[a[r]]--;
            added.erase(r);
            total--;
        }

        while (!added.empty() && !ix_ok(i, *added.begin())) {
            ll l = *added.begin();
            cnt[a[l]]--;
            added.erase(l);
            total--;
        }

        // for (ll j = 2; j <= k - 1; j += 2) {
        //     ll ctr = (i + (i + j)) / 2;
        //     if (i + j >= 0 && i + j < n && ctr >= half && ctr <= n - 1 - half) {
        //         ans += a[i] != a[i+j];
        //     }
        // }

        ans += total - cnt[a[i]];

        // cout << i << ' ';
        // for (ll x: added) cout << x << ' ';
        // cout << endl;
    }


    // for (ll i = 1; i < n; i += 2) {
    //     cout << i << ' ';
    //     for (ll j = 2; j <= k - 1; j += 2) {
    //         ll ctr = (i + (i + j)) / 2;
    //         if (i + j >= 0 && i + j < n && ctr >= half && ctr <= n - 1 - half) {
    //             cout << i + j << ' ';
    //             ans += a[i] != a[i+j];
    //         }
    //     }
    //     cout << endl;
    // }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

