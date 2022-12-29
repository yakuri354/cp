// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a == 0 || b == 0) {
        cout << 1 << ' ' << min(c, d) + 1 << endl;
        return;
    }

    if (c == 0 || d == 0) {
        cout << min(a, b) + 1 << ' ' << 1 << endl;
        return;
    }

    ll s1 = min(a + c, b + d) + 2;
    ll s2 = 1 + 1 + min(max(a, b), max(c, d));

    if (s1 <= s2) {
        if (a + c < b + d) {
            cout << a + 1 << ' ' << c + 1 << endl;
        } else {
            cout << b + 1 << ' ' << d + 1 << endl;
        }
    } else {
        if (max(a, b) < max(c, d)) {
            cout << max(a, b) + 1 << ' ' << 1 << endl;
        } else {
            cout << 1 << ' ' << max(c, d) + 1 << endl;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
