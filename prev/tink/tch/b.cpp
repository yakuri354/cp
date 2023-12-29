// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct gcda {
    ll x, y, g;
};

gcda gcde(ll a, ll b) {
    if (b == 0) {
        return {1, 0, a};
    }

    auto nxt = gcde(b, a % b);
    return {
        .x = nxt.y,
        .y = nxt.x - nxt.y * (a / b),
        .g = nxt.g
    };
}

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;

    auto z1 = gcde(a, b);
    if (c % z1.g != 0) {
        cout << "Impossible" << endl;
        return;
    }

    auto cf = c / z1.g;
    auto z2 = gcde(a*cf, b*cf);
    ll a1 = cf * z2.x, a2 = cf * z2.y;

    if (a1 < 0) {
        ll qt = (-a1) / b;
        if ((-a1) % b != 0) qt++;

        a1 += b * qt;
        a2 -= a * qt;
    } else {
        ll qt = a1 / b;
        a1 -= b * qt;
        a2 += a * qt;
    }

    cout << a1 << ' ' << a2 << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
