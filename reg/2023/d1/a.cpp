// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const fl eps = 1e-6;

void solve() {
    ll a, b, k, m;
    cin >> a >> b >> k >> m;

    // x^2 - (k+2)x + m = 0
    
    fl d = (k+2)*(k+2) - 4 * m;
    if (d < 0) {
        cout << -1 << endl;
        return;
    }

    fl xl = (fl(k + 2) - sqrt(d)) / 2 - 1;
    fl xh = (fl(k + 2) + sqrt(d)) / 2 - 1;

    if (abs(xh - round(xh)) > eps || abs(xl - round(xl)) > eps || xl < 0) {
        cout << -1 << endl;
        return;
    }

    if (xh >= max(a, b) || xl >= min(a, b)) {
        cout << -1 << endl;
        return;
    }

    ll h = xl, v = xh;

    if (h >= a || v >= b) swap(h, v);

    cout << h << ' ' << v << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
