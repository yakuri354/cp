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

void solve() {
    ll n, p, v;
    cin >> n >> p >> v;
    cout << dp(n, v, p) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

