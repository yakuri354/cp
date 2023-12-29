#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iterator>
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2 * 1e5 + 1;
const ull P = 101;
const ull MOD = ~0ull;

ull p[maxn], h[maxn];

ull mod(ull x) {
    return (x + (x % MOD)) % MOD;
}

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0)
        v += h[r - 1];
    if (l > 0)
        v = mod(v - h[l - 1]);

    return mod(v * p[l]);
}

void solve() {
    ll k, n;
    cin >> k >> n;

    string s;
    cin >> s;

    vector<tuple<string, ull, ll>> arr;

    p[0] = 1;
    for (ll i = 1; i < maxn; i++) {
        p[i] = mod(p[i - 1] * P);
    }

    for (ll i = 0; i < k; i++) {
        string t;
        cin >> t;

        ull t_h = mod(t[0] * p[n - 1]);
        for (ll i = 1; i < t.size(); i++) {
            t_h += mod(t[i] * p[n - i - 1]);
        }

        arr.push_back({t, t_h, i});
    }

    h[0] = mod(s[0] * p[n - 1]);
    for (ll i = 1; i < n; i++) {
        h[i] = mod(h[i - 1] + mod(s[i] * p[n - i - 1]));
    }

    vector<vector<ll>> occ(k);

    for (ll x = 0; x < k; x++) {
        auto [s, s_h, si] = arr[x];
        ull sz = s.size();
        for (ll i = 0; i < n; i++) {
            if (i + sz > n) break;
            if (hs(i, i + sz) == s_h) {
                occ[si].push_back(i);
            }
        }
    }

    sort(arr.begin(), arr.end());
    ll ans = n;
    while (next_permutation(arr.begin(), arr.end())) {
        ll i = 0;
        for (ll x = 0; x < k; x++) {
            auto [s, hs, si] = arr[x];
            auto it = lower_bound(occ[si].begin(), occ[si].end(), i);
            if (it == occ[si].end()) goto next;
            else i = *it + s.size();

            if (i >= n && x != k - 1) goto next;
        }
        ans = min(ans, i);
        next:;
    }

    if (ans == n) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
