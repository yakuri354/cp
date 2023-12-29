// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;
using ull = unsigned long long;

const ll inf = INT32_MAX;
const ull P = 307;
const ull maxn = 1e5;

ull p[maxn], h[maxn];
ull n;

ull hs(ull l, ull r) {
    if (l == 0) return h[r];
    return (h[r] - h[l - 1]) * p[l];
}

void solve() {
    string s;
    cin >> s;

    n = s.length();

    p[0] = 1;
    for (ull i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = p[n-1] * s[0];
    for (ull i = 1; i < n; i++) {
        h[i] = h[i-1] + s[i] * p[n-i-1];
    }

    ull m;
    cin >> m;
    for (ull i = 0; i < m; i++) {
        ull a, b, c, d;
        cin >> a >> b >> c >> d;

        if (hs(a - 1, b - 1) == hs(c - 1, d - 1)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
