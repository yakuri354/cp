#include <random>
#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

ll a[900][3000];
ll b[900][3000];


ll incm[3000];
pair<ll, ll> qs[900 * 3000];

ll solvebs(ll l, ll x, ll y) {
    auto op = [&](ll k) {
        return max(a[x][k], b[y][k]);
    };

    ll lo = 0, hi = l;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;
        ll pt = op(m);
        ll va = a[x][m];
        ll vb = b[y][m];

        ll lo2 = lower_bound(incm + m, incm + l, 0, [&](auto a1, auto b1) {
                                 if (va > vb)
                                     return a[x][a1] == va;
                                 else
                                     return b[y][a1] == vb;
                             }) - incm;
        ll lo1 = upper_bound(incm, incm + m, 0, [&](auto a1, auto b1) {
                                 if (va > vb)
                                     return a[x][b1] == va;
                                 else
                                     return b[y][b1] == vb;
                             }) - incm;

        // cerr << "lo1 " << lo1 << " m " << m << " lo2 " << lo2 << endl;

        if ((lo1 == 0 && lo2 == l) || (lo1 > 0 && op(lo1 - 1) > pt) && (lo2 < l && op(lo2) > pt)) {
            return m + 1;
        }
        if (lo2 == l || (lo1 > 0 && op(lo1 - 1) < pt) || (lo2 < l && op(lo2) > pt)) {
            hi = m;
        } else {
            lo = m;
        }
    }

    if (op(lo) < op(hi))
        return lo + 1;
    else
        return hi + 1;
}

ll solvedumb(ll l, ll qi, ll qj) {
    ll minv = INT32_MAX, mini = 0;
    for (ll i = 0; i < l; i++) {
        ll x = max(a[qi][i], b[qj][i]);
        if (x < minv) {
            minv = x;
            mini = i;
        }
    }
    return mini + 1;
}

void solve() {
    ll n, m, l, q;
    cin >> n >> m >> l;

    iota(incm, incm + l, 0);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < l; j++) {
            cin >> a[i][j];
        }
    }
    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j < l; j++) {
            cin >> b[i][j];
        }
    }
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll x, y;
        cin >> x >> y;
        x--;
        y--;

        auto op = [&](ll k) {
            return max(a[x][k], b[y][k]);
        };

        ll lo = 0, hi = l;
        while (hi - lo > 1) {
            ll m = (lo + hi) / 2;
            ll pt = op(m);
            ll va = a[x][m];
            ll vb = b[y][m];

            ll lo2 = lower_bound(incm + m, incm + l, 0, [&](auto a1, auto b1) {
                                     if (va > vb)
                                         return a[x][a1] == va;
                                     else
                                         return b[y][a1] == vb;
                                 }) - incm;
            ll lo1 = upper_bound(incm, incm + m, 0, [&](auto a1, auto b1) {
                                     if (va > vb)
                                         return a[x][b1] == va;
                                     else
                                         return b[y][b1] == vb;
                                 }) - incm;

            // cerr << "lo1 " << lo1 << " m " << m << " lo2 " << lo2 << endl;

            if ((lo1 == 0 && lo2 == l) || (lo1 > 0 && op(lo1 - 1) > pt) && (lo2 < l && op(lo2) > pt)) {
                cout << m + 1 << '\n';
                goto nxt;
            }
            if (lo2 == l || (lo1 > 0 && op(lo1 - 1) < pt) || (lo2 < l && op(lo2) > pt)) {
                hi = m;
            } else {
                lo = m;
            }
        }

        if (op(lo) < op(hi))
            cout << lo + 1 << '\n';
        else
            cout << hi + 1 << '\n';
    nxt: {}
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
