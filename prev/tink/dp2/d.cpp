// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct evt {
    ll lo, hi, delta;
};

evt a[20];
ll d[1 << 20];
ll p[1 << 20];
ll n, k;

const ll UNDEF = 1e9 + 7; // :)

ll f(ll mask) {
    if (d[mask] != UNDEF) {
        return d[mask];
    }

    d[mask] = -inf;
    for (ll i = 0; i < n; i++) {
        ll elm = 1 << i;
        if ((mask & elm) > 0 && d[mask & ~elm] >= a[i].lo && d[mask & ~elm] <= a[i].hi) {
            ll res = d[mask & ~elm] + a[i].delta;
            if (d[mask] < res) {
                d[mask] = res;
                p[mask] = i;
            }
        }
    }

    return d[mask];
}

void solve() {
    cin >> n >> k;

    for (ll m = 0; m < 1 << n; m++) {
        d[m] = UNDEF;
    }

    d[0] = 0;
    p[0] = -1;

    for (ll i = 0; i < n; i++) {
        cin >> a[i].lo >> a[i].hi >> a[i].delta;
        if (k >= a[i].lo && k <= a[i].hi) {
            d[1 << i] = k + a[i].delta;
        } else {
            d[1 << i] = -inf;
        }
        p[1 << i] = i;
    }


    ll best_n = -inf, best_m = -inf, ans = 0;
    for (ll m = 0; m < 1 << n; m++) {
        ll sz = __builtin_popcountll(m);
        if (f(m) > -10000 && (sz > best_n || (sz >= best_n && f(m) > best_m))) {
            best_n = sz;
            best_m = f(m);
            ans = m;
        }
    }

    vector<ll> ansv;
    while (ans != 0) {
        ansv.push_back(p[ans]);
        ans &= ~(1 << p[ans]);
    }

    reverse(ansv.begin(), ansv.end());

    cout << ansv.size() << endl;

    for (ll i : ansv) {
        cout << i + 1 << ' ';
    }

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
