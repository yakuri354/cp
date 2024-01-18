// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <iterator>
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

const ull P = 1e9 + 7;

vector<ull> h, p;

string s, t;
ull ht;

mt19937_64 mt(0xab0ba);

bool check(ll l) {
    ull v = 0;
    ll r = l + t.size();
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    v *= p[l];

    if (v != ht) return false;
    else {
        uniform_int_distribution<ll> dd(0, t.size() - 1);
        for (ll i = 0; i < 100; i++) {
            ll x = dd(mt);
            if (s[l + x] != t[x]) return false;
        }

        return true;
    }
}

void solve() {
    cin >> s >> t;

    string s1 = s;

    ll n0 = s.size();
    ll m0 = t.size();

    s.reserve(n0 + m0 + 1);

    while (s.size() < n0 + m0 + 1) {
        s += s1;
    }

    ll n = s.size();

    p.resize(n);
    h.resize(n);

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i - 1] * P;
    }

    h[0] = p[n - 1] * s[0];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + s[i] * p[n - i - 1];
    }

    ht = t[0] * p[n-1];
    for (ll i = 1; i < t.size(); i++) {
        ht += t[i] * p[n - i - 1];
    }

    ll ans = 0;
    for (ll i = 0; i < n0; i++) {
        ans += check(i);
    }
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
