// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, m;

    cin >> n >> m;

    if (n == 1) {
        cout << "yes" << endl;
        return;
    }

    if (m > n && n > 1) {
        cout << "no" << endl;
        return;
    }

    while (true) {
        m = n % m;
        if (m == 0) {
            cout << "NO" << endl;
            return;
        } else if (m == 1) {
            cout << "YES" << endl;
            return;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
