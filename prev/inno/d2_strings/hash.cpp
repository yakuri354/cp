// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>

using namespace std;
using ll = long long;
using ull = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ull P = 307;

ull p[maxn], h[maxn];

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

void solve() {
    string s;
    cin >> s;
    ll n = s.size();

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = s[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + s[i] * p[n - i - 1];
    }

    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, c--;

        if (hs(a, b) == hs(c, d)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}