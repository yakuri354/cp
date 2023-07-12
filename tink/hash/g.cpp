// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;
using ull = unsigned long long;

const ll inf = INT32_MAX;
const ull P = 307;
const ull maxn = 2e6;

ull p[maxn], h[maxn];
ull n;

ull hs(ull l, ull r) {
    if (l == 0) return h[r];
    return (h[r] - h[l - 1]) * p[l];
}

void solve() {
    string s, t;
    cin >> s >> t;

    ll n1 = s.size();

    s += s;

    n = s.length();
    ull m = t.length();

    p[0] = 1;
    for (ull i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = p[n-1] * s[0];
    for (ull i = 1; i < n; i++) {
        h[i] = h[i-1] + s[i] * p[n-i-1];
    }

    ull ht = p[n-1] * t[0];
    for (ull i = 1; i < m; i++) ht += t[i] * p[n-i-1];

    ll ans = inf;
    for (ll i = 0; i + m <= n; i++) {
        if (hs(i, i + m - 1) == ht) {
            ans = min(ans, n1 - i);
        }
    }

    if (ans == inf)
        cout << -1 << endl;
    else
        cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
