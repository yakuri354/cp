// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll d[101][10];
ll lb[101], hb[101];

ll mod(ll x) {
    return x % ll(1e9+7);
}

void solve() {
    string l, r;
    cin >> l >> r;
    for (ll i = 0; i < l.size(); i++) {
        lb[i] = l[l.size() - i - 1] - '0';
    }

    for (ll i = 0; i < 100; i++) {
        hb[i] = 9;
    }
    
    for (ll i = 0; i < r.size(); i++) {
        hb[i] = r[r.size() - i - 1] - '0';
    }

    for (ll i = 1; i < r.size(); i++) {
        for (ll j = hb[i]; j >= lb[i]; j--) {
            d[i][j] = d[i][j+1] + d[i-1][j];
        }
    }

    cout << d[r.size() - 1][lb[r.size() - 1]] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
