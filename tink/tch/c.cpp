// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

bool x[1000001];

void solve() {
    ll a, b;
    cin >> a >> b;

    for (ll i = 2; i <= b; i++) {
        if (!x[i]) {
            if (i >= a) {
                cout << i << ' ';
            }
        }
        for (ll j = 1; i * j <= b; j++) {
            x[i*j] = true;
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
