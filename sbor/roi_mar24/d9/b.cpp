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

const ll maxn = 1e5 + 1;
const ll P = 307;

ull p[maxn], h[maxn];
ll b2l[maxn], b2r[maxn];

inline ull hs(ll l, ll r) {
    ull z = h[r - 1];
    if (l > 0) z -= h[l - 1];
    return z * p[l];
}

ll n;
string s;

bool check(ll l) {
    unordered_set<ull> prev;
    for (ll i = 0; i + l <= n; i++) {
        ull x = hs(i, i + l);
        if (prev.count(x)) {
            return true;
        }

        if (i >= l) {
            prev.insert(hs(i - l, i));
        }
    }
    return false;
}

void solve() {
    cin >> s;

    n = s.size();

    p[0] = 1;
    for (ll i = 1; i <= n; i++) {
        p[i] = p[i - 1] * P;
    }

    h[0] = s[0] * p[n-1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + ull(s[i]) * p[n - i - 1];
    }

    ll ans = 0;

    {
        ll lo = 1, hi = n;
        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;

            if (check(m)) lo = m;
            else hi = m;
        }

        ans = max(ans, lo);
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = i + 2; j <= n; j += 2) {
            ll m = (i + j) / 2;
            if (hs(i, m) == hs(m, j)) {
                b2r[i] = max(b2r[i], (j - i) / 2);
                b2l[j - 1] = max(b2l[j - 1], (j - i) / 2);
            }
        }
    }

    for (ll i = 0; i < n - 1; i++) {
        ans = max(ans, b2l[i] + b2r[i + 1]);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

