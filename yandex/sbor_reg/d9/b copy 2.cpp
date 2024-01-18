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

ll value(ll n, ll k, ll v, ll p) {
    ll rec = n / k;
    if (n % k != 0) rec++;

    return v + rec * p;
}

ll find_k(ll n, ll v, ll p) {
    ll lo = 1, hi = n - 1;
    while (hi - lo > 3) { // sus
        ll pt = (hi - lo) / 3;
        ll lb = lo + pt;
        ll hb = lb + pt;

        ll lv = value(n, lb, v, p);
        ll rv = value(n, hb, v, p);

        if (lv < rv) {
            hi = hb;
        } else {
            lo = lb;
        }
    }

    ll ans = -1;
    for (ll i = lo; i <= hi; i++) {
        if (ans == -1 || value(n, i, v, p) < value(n, ans, v, p)) {
            ans = i;
        }
    }

    return ans;
}

unordered_map<ll, ll> memo;

ll dp(ll n, ll v, ll p) {
    if (n == 1) return 0; // sus

    if (memo.count(n)) return memo[n];

    ll opt = find_k(n, v, p);

    ll val = value(n, opt, v, p) + dp(opt, v, p);

    memo[n] = val;
    return val;
}

ll cdiv(ll a, ll b) {
    ll r = a / b;
    if (a % b != 0) r++;
    return r;
}

ll dp_dumb(ll n, ll v, ll p) {
    if (n <= 1) return 0;
    if (memo.count(n)) return memo[n];

    ll opt = -1;
    for (ll i = 2; i <= 40; i++) {
        if (opt == -1 || dp_dumb(cdiv(n, i), v, p) + i * p < dp_dumb(cdiv(n, opt), v, p) + opt * p) {
            opt = i;
        }
    }

    memo[n] = dp_dumb(cdiv(n, opt), v, p) + opt * p + v;

    if (memo[n] > n * p + v) {
        memo[n] = n * p + v;
    }

    return memo[n];
}

void solve() {
    ll n, p, v;
    cin >> n >> p >> v;
    cout << dp_dumb(n, v, p) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}