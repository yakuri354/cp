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

    if (k == 1) {
        cout << 0 << endl;
        return;
    }

    const ll half = (k - 1) / 2;

    unordered_map<ll, ll> cnt;
    set<ll> added;
    ll total = 0;

    auto ix_ok = [&](ll i, ll j) {
        ll ctr = (i + (i + j)) / 2;
        return i + j >= 0 && i + j < n && ctr >= half && ctr <= n - 1 - half;
    };

    for (ll j = 2; j <= k - 1; j += 2) {
        if (ix_ok(0, j)) {
            cnt[a[j]]++;
            added.insert(j);
            total++;
        }
    }

    ll ans = 0; // even idx
    for (ll i = 0; i < n; i += 2) {
        while (!added.empty() && !ix_ok(i, *added.rbegin() - i)) {
            ll x = *added.rbegin();
            cnt[a[x]]--;
            total--;
            added.erase(x);
        }

        ans += total - cnt[a[i]];

        if (added.count(i)) {
            cnt[a[i]]--;
            added.erase(i);
            total--;
        }

        if (ix_ok(i + 2, k - 1)) {
            cnt[a[i+k+1]]++;
            added.insert(i+k+1);
            total++;
        }
    }

    total = 0;
    cnt.clear();

    for (ll j = 2; j <= k - 1; j += 2) {
        if (ix_ok(1, j)) {
            cnt[a[1 + j]]++;
            added.insert(1 + j);
            total++;
        }
    }

    for (ll i = 1; i < n; i += 2) {
        while (!added.empty() && !ix_ok(i, *added.rbegin() - i)) {
            ll x = *added.rbegin();
            cnt[a[x]]--;
            total--;
            added.erase(x);
        }

        ans += total - cnt[a[i]];

        if (added.count(i)) {
            cnt[a[i]]--;
            added.erase(i);
            total--;
        }

        if (ix_ok(i + 2, k - 1)) {
            cnt[a[i+k+1]]++;
            added.insert(i+k+1);
            total++;
        }
    }
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

