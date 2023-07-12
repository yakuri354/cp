// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    cout << "ll facm[] = { ";
    ll fac = 1;
    for (ll i = 1; i <= ll(1e9); i++) {
        fac = (fac * i) % (ll(1e9) + 7);
        if (i % 1000 == 0) {
            cout << fac << ", ";
        }
    }
    cout << "};\n";
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
