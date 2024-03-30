// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll inf = 1e12;

struct segt_max {
    ll n;
    vector<ll> t;

    segt_max(ll n, ll v) : n(n), t(n * 2, v) {
    }

    void modify(ll i, ll x) {
        i += n;
        t[i] = x;

        for (i /= 2; i > 0; i /= 2)
            t[i] = max(t[i * 2], t[i * 2 + 1]);
    }

    ll getmax(ll l, ll r) {
        ll res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1)
                res = max(res, t[l++]);
            if (r & 1)
                res = max(res, t[--r]);
        }
        return res;
    }
};

void solve() {
    ll n;
    cin >> n;

    if (n > 10000) {
        cout << n << '\n';
        return;
    }

    vector<ll> a(n);
    for (ll& i : a)
        cin >> i;

    ll ans = 0;

    // vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, -inf));

    vector<segt_max> by_x(n + 2, segt_max(n + 2, -inf));
    vector<segt_max> by_y(n + 2, segt_max(n + 2, -inf));

    // dp[0][n+1] = 0;
    by_x[0].modify(n + 1, 0);

    for (ll i = 0; i < n; i++) {
        for (ll x = 0; x <= n + 1; x++) {
            if (x == a[i]) continue;
            // for (ll y = a[i] + 1; y <= n + 1; y++) {
                // dp[x][a[i]] = max(dp[x][a[i]], dp[x][y] + 1);
                ll nv = by_x[x].getmax(a[i] + 1, n + 2) + 1;
                nv = max(nv, by_x[x].t[n+2+a[i]]);

                by_x[x].modify(a[i], nv);
                by_y[a[i]].modify(x, nv);
                // by_x[x].modify(a[i], 
            // }
        }

        for (ll y = 0; y <= n + 1; y++) {
            if (y == a[i]) continue;
            // for (ll x = 0; x < a[i]; x++) {
                // dp[a[i]][y] = max(dp[a[i]][y], dp[x][y] + 1);
                ll nv = by_y[y].getmax(0, a[i]) + 1;
                nv = max(nv, by_x[a[i]].t[n + 2 + y]);

                by_x[a[i]].modify(y, nv);
                by_y[y].modify(a[i], nv);
            // }
        }

        for (ll x = 0; x <= n + 1; x++) {
            
        }
    
   		for (ll x = 0; x <= n + 1; x++) {
            for (ll y = 0; y <= n + 1; y++) {
                if (x < a[i] && y > a[i]) dp[x][y] = -inf;
            }
        }
    }

    for (ll x = 0; x <= n+1; x++) {
        for (ll y = 0; y <= n+1; y++) {
            ans = max(ans, dp[x][y]);
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t-- > 0)
        solve();
}
