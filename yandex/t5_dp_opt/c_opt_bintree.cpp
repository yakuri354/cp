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
using ll = int;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

ll n;

void solve() {
    vector<ll> a(n);
    vector<ll> p(n + 1);
    vector<vector<ll>> d(n, vector<ll>(n)), opt(n, vector<ll>(n));

    for (ll &i: a) cin >> i;

    if (n < 2) {
        cout << 0 << '\n';
        return;
    }

    partial_sum(a.begin(), a.end(), p.begin() + 1);

    // sus init opt
    for (ll i = 0; i < n; i++) {
        opt[i][i] = i;
        d[i][i] = a[i];
    }

    for (ll r = 1; r < n; r++) {
        for (ll l = r - 1; l >= 0; l--) {
            ll from = opt[l][r-1], to = opt[l+1][r];

            d[l][r] = inf;
            for (ll i = max(from, l); i <= min(r, to); i++) {
                ll v = (i - 1 >= l ? d[l][i-1] : 0) + (i + 1 <= r ? d[i+1][r] : 0) + p[r + 1] - p[l];
                if (d[l][r] > v) {
                    d[l][r] = v;
                    opt[l][r] = i;
                }
            }
        }
    }

    cout << d[0][n-1] - p[n] << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    while (cin >> n) solve();
}
