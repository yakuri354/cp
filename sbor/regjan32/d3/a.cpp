// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 1e5;

void solve() {
    ll n, m, asum = 0, bsum = 0;
    cin >> n >> m;

    vector<ll> a(n), b(m);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        asum += a[i];
    }
    for (ll i = 0; i < m; i++) {
        cin >> b[i];
        bsum += b[i];
    }

    ll ap = 0, bp = 0, al = a[0], bl = b[0];

    if (asum > bsum) {
        ll diff = asum - bsum;

        while (diff > 0) {
            if (diff < al) {
                al -= diff;
                break;
            } else {
                diff -= al;
                al = a[++ap];
            }
        }
    }

    if (asum < bsum) {
        ll diff = bsum - asum;

        while (diff > 0) {
            if (diff < bl) {
                bl -= diff;
                break;
            } else {
                diff -= bl;
                bl = b[++bp];
            }
        }
    }

    if (al > bl) {
        al -= bl;
        if (++bp < m)
            bl = b[bp];
    } else {
        bl -= al;
        if (++ap < n)
            al = a[ap];
    }
    for (;;) {
        if (bp >= m || ap >= n) break;
        if (al > bl) {
            cout << bl << ' ';
            al -= bl;
            if (++bp >= m) break;
            bl = b[bp];
        } else {
            cout << al << ' ';
            bl -= al;
            if (++ap >= m) break;
            al = a[ap];
        }
    }
    
    if (ap >= n) {
        if (bl) cout << bl << ' ';
        for (bp++; bp < m; bp++) {
            cout << b[bp] << ' ';
        }
    } else {
        if (al) cout << al << ' ';
        for (ap++; ap < n; ap++) {
            cout << a[ap] << ' ';
        }
    }

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
