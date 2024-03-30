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

const ll M = 998244353; 

ll mod(ll x) {
    return x % M;
}

ll binexp(ll b, ll e) {
    if (e == 0) return 1;
    
    if (e % 2 == 0) {
        ll x = binexp(b, e / 2);
        return mod(x * x);
    } else {
        return mod(b * binexp(b, e-1));
    }
}

vector<ll> fact, facti;

ll cnk(ll n, ll k) {
    return mod(mod(fact[n] * facti[n-k]) * facti[k]);
}

ll n, q;

void solve_dumb() {
    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    vector<ll> p0 = a, p1(n, 0);

    for (ll i = 0; i <= q; i++) {
        p1[0] = p0[0];
        for (ll j = 1; j < n; j++) {
            p1[j] = mod(p0[j] + p1[j-1]);
        }
        p0 = p1;
    }

    for (ll &i: p0) {
        cout << mod(i) << ' ';
    }
    cout << '\n';
}

void solve() {
    cin >> n >> q;
    q--;

    if (q < 200) {
        solve_dumb();
        return;
    }

    fact.resize(n + q + 1);
    facti.resize(n + q + 1);

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    fact[0] = 1;
    facti[0] = 1;
    for (ll i = 1; i <= n + q; i++) {
        fact[i] = mod(fact[i-1] * i);
        facti[i] = binexp(fact[i], M - 2);
    }

    vector<ll> ans(n);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j <= i; j++) {
            ans[i] = mod(ans[i] + mod(a[j] * cnk(q + i - j, i - j)));
        }
    }

    for (ll &i: ans) {
        cout << mod(i) << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

