#include <cmath>
#include <cstdint>
#include <math.h>
#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const fl eps = 1e-12;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

struct pt {
    fl x;
    fl y;
    fl w;
};

pt a[100];
ll n;

fl sq(fl x) {
    return x*x;
}

fl f(fl x, fl y) {
    fl ans = -INFINITY;
    for (ll i = 0; i < n; i++) {
        maxa(ans, a[i].w * sqrtl(sq(a[i].x - x) + sq(a[i].y - y)));
    }
    return ans;
}

fl bestat(fl ly, fl ry, fl x, fl& ans) {
    while (ry - ly > eps) {
        // cerr << "ly " << ly << "; ry " << ry << endl;
        fl u = (ry - ly) / 3;
        if (f(x, ly + u) < f(x, ry - u))
            ry = ry - u;
        else
            ly = ly + u;
    }
    ans = ly;
    // cerr << "ly " << ly << "; ry " << ry << " -> " << f(x,ly) << endl;
    return f(x, ly);
}

void solve() {
    cout << fixed << setprecision(10);
    // cerr << fixed << setprecision(20);
    for (cin >> n; n != 0; cin >> n) {
        fl lx = inf, rx = -inf, lyb = inf, ryb = -inf, ansy = 0.0;
        for (ll i = 0; i < n; i++) {
            cin >> a[i].x >> a[i].y >> a[i].w;
            mina(lx, a[i].x);
            mina(lyb, a[i].y);
            maxa(rx, a[i].x);
            maxa(ryb, a[i].y);
        }

        while (rx - lx > eps) {
            // cerr << "lx " << lx << "; rx " << rx << endl;
            fl u = (rx - lx) / 3;
            if (bestat(lyb, ryb, lx + u, ansy) < bestat(lyb, ryb, rx - u, ansy))
                rx = rx - u;
            else
                lx = lx + u;
        }
        cout << lx << ' ' << ansy << endl;

        // cerr << endl << endl << "ans " << f(1.0, 1.0) << " proposed " << f(lx, ansy) << endl << endl;
        // cerr << endl << endl << "ans " << f(2.4, 3.6) << " proposed " << f(lx, ansy) << endl << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
