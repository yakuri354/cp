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
#include <chrono>

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

// ll dumb(vector<ll> &a) {
//     const ll n = a.size();
//     ll ans = 0;
//     for (ll m = 0; m < 1 << n; m++) {

//     }
// }

ll dumb(const vector<ll> &a) {
    const ll n = a.size();
    ll ans = 0;
    for (ll m = 0; m < 1 << n; m++) {
        ll score = 0;
        ll up = 0, down = n + 1;
        for (ll i = 0; i < n; i++) {
            if ((m >> i) & 1) {
                if (a[i] > up) {
                    up = a[i];
                    score++;
                }
            } else {
                if (a[i] < down) {
                    down = a[i];
                    score++;
                }
            }
        }
        ans = max(ans, score);
    }
    return ans;
}

ll solve(const vector<ll> &a) {
    const ll n = a.size();
    if (n > 10000) {
        return n;
    }

    // vector<ll> a(n);
    // for (ll& i : a)
    //     cin >> i;

    ll ans = 0;

    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, -inf));

    // dp[0][n+1] = 0;

    dp[a[0]][n+1] = 1;
    dp[0][a[0]] = 1;

    for (ll i = 1; i < n; i++) {
        for (ll x = 0; x <= n + 1; x++) {
            if (x == a[i]) continue;
            for (ll y = a[i] + 1; y <= n + 1; y++) {
                dp[x][a[i]] = max(dp[x][a[i]], dp[x][y] + 1);
            }
        }

        // for (ll x = 0; x <= n + 1; x++) {
        //     for (ll y = 0; y <= n + 1; y++) {
        //         cout << (dp[x][y] < 0 ? "_" : to_string(dp[x][y])) << ' ';
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        for (ll y = 0; y <= n + 1; y++) {
            if (y == a[i]) continue;
            for (ll x = 0; x < a[i]; x++) {
                dp[a[i]][y] = max(dp[a[i]][y], dp[x][y] + 1);
            }
        }

        for (ll x = 0; x <= n + 1; x++) {
            for (ll y = 0; y <= n + 1; y++) {
                if (x < a[i] && y > a[i]) dp[x][y] = -inf;
            }
        }

        for (ll x = 0; x <= n + 1; x++) {
            for (ll y = 0; y <= n + 1; y++) {
                cout << (dp[x][y] < 0 ? "_" : to_string(dp[x][y])) << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    for (ll x = 0; x <= n + 1; x++) {
        for (ll y = 0; y <= n + 1; y++) {
            ans = max(ans, dp[x][y]);
        }
    }

    return ans;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    cout << solve(a) << endl;
}
