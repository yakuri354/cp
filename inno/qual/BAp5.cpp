// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 100;

ll a[maxn], n;

bool f(ll m) {
    bool flag = false;
    for (ll i = 0; i < n; i++) {
        if (a[i] > m) {
            if (flag) return false;
            else flag = true;
        } else flag = false;
    }
    return true;
}

void solve() {
    cin >> n;

    for (ll i = 0; i < n; i++) {
        string x;
        cin >> x;
        a[i] = x.length();
    }

    ll l = 0, r = 101;
    while (r - l >= 2) {
        ll m = (l + r) / 2;

        if (f(m)) r = m;
        else l = m;
    }

    cout << l + 1 << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
