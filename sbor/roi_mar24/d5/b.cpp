#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ull P = 307;
const ll maxn = 5e5 + 1;

ull p[maxn], h[maxn];

vector<ll> divisors[maxn];
vector<ull> sums[maxn];

inline ull hs1(ll l, ll r) {
    ull z = h[r - 1];
    if (l > 0) z -= h[l - 1];
    return z;
}

void calc_divs(ll x) {
    vector<ll> dd = {1, x};
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            dd.push_back(i);
            if (x / i != i) dd.push_back(x / i);
        }
    }
    sort(dd.begin(), dd.end());
    divisors[x] = dd;
}

void solve() {
    ll n;
    cin >> n;
    
    p[0] = 1;
    for (ll i = 1; i <= n; i++) {
        p[i] = p[i - 1] * P;
    }

    string s;
    cin >> s;

    h[0] = s[0] * p[n-1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + ull(s[i]) * p[n - i - 1];
    }

    for (ll i = 1; i <= n; i++) {
        sums[i] = {1};
        for (ll j = 1; j * i <= n; j++) {
            sums[i].push_back(sums[i][j-1] + p[i * j]);
        }
    }

    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;

        ull h0 = hs1(l, r);

        if (divisors[r - l].empty()) calc_divs(r - l);

        for (ll x: divisors[r - l]) {
            if (h0 == sums[x][(r - l) / x - 1] * hs1(r - x, r)) {
                cout << x << '\n';
                break;
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

