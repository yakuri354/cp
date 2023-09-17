// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 + 100;
const ull P = 1e5 + 3;

ull p[maxn], h[maxn], hr[maxn], a[maxn];
ll n, m;

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

ull hsr(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += hr[r-1];
    if (l > 0) v -= hr[l-1];

    return v * p[n - r];
}

bool compare(ll l, ll r) {
    if (hs(l, r) != hsr(l, r)) return false;

    for (ll i = 0; i < 100 && i < (l - r); i++) {
        if (a[l + i] != a[r - i - 1]) return false;
    }

    return true;
}

void solve() {
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    p[0] = 1;
    for (ll i = 1; i < maxn; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = a[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + a[i] * p[n - i - 1];
    }

    hr[0] = a[0];
    for (ll i = 1; i < n; i++) {
        hr[i] = hr[i-1] + a[i] * p[i];
    }

    cout << n << ' ';

    for (ll i = 1; i < n; i += 2) {
        if (compare(0, i + 1)) {
            cout << n - (i + 1) / 2 << ' ';
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
