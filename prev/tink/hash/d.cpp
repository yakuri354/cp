// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;
using ull = unsigned long long;

const ll inf = INT32_MAX;
const ull P = 307;
const ull maxn = 2e5;

ull p[maxn], h[maxn], hr[maxn];
ull n;

ull hsr(ull l, ull r) {
    ll lb = 0;
    if (l > 0) lb = hr[l-1];
    return (hr[r] - lb) * p[n - 1 - r];
}

ull hs(ull l, ull r) {
    if (l == 0) return h[r];
    return (h[r] - h[l - 1]) * p[l];
}

void solve() {
    string s1;
    cin >> s1;

    string s;

    for (char i : s1) {
        s.push_back(i);
        s.push_back('#');
    }

    s.erase(s.end() - 1);

    n = s.length();

    p[0] = 1;
    for (ull i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = p[n-1] * s[0];
    for (ull i = 1; i < n; i++) {
        h[i] = h[i-1] + s[i] * p[n-i-1];
    }

    hr[0] = s[0];
    for (ull i = 1; i < n; i++) {
        hr[i] = hr[i-1] + s[i] * p[i];
    }

    ull ans = 0;
    for (ull i = 0; i < n; i++) {
        ll lo = 0, hi = min(i, n - i - 1) + 1;
        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;
            if (hs(i - m, i + m) == hsr(i - m, i + m))
                lo = m;
            else
                hi = m;
        }

        ll q = lo + 1;
        if (s[i] == '#') {
            if (s[i+lo] == '#') q--;
        } else {
            if (s[i+lo] != '#') q++;
        }
        ans += q / 2;
    }

    cout << ans << endl;
}
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
