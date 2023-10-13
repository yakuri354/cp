// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ll inf = INT32_MAX;
const ll maxn = 1 << 18;

ll t[maxn * 2];

ll op(ll a, ll b, ll nl, ll nr) {
    ll sz = (nr - nl) / 2;

    if (b == sz) {
        return a + b;
    } else {
        return b;
    }
}

void modify(ll n, ll nl, ll nr, ll p, bool x) {
    ll m = (nl + nr) / 2;

    if (nr - nl < 2) {
        t[n] = x ? 1 : 0;
        return;
    }

    if (p < m) {
        modify(n * 2 + 1, nl, m, p, x);
    } else {
        modify(n * 2 + 2, m, nr, p, x);
    }

    t[n] = op(t[n * 2 + 1], t[n * 2 + 2], nl, nr);
}

ll ans(ll n, ll nl, ll nr, ll p) {
    ll m = (nl + nr) / 2;

    if (nr - nl < 2) {
        return nl;
    }

    if (p < m && t[n * 2 + 1] < min(m - p, (nr - nl) / 2)) {
        return ans(n * 2 + 1, nl, m, p);
    } else {
        return ans(n * 2 + 2, m, nr, p);
    }
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;

        if (x < 0) {
            modify(0, 0, maxn, -x, false);
        } else {
            ll p = ans(0, 0, maxn, x);
            cout << p << '\n';
            modify(0, 0, maxn, p, true);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
