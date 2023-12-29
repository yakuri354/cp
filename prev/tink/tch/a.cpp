// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, n1;
    cin >> n;
    n1 = n;

    for (ll i = 2; i * i <= n1 && n > 1;) {
        if (n % i == 0) {
            n /= i;
            cout << i << ' ';
        } else {
            i++;
        }
    }

    if (n > 1) {
        cout << n << ' ';
    }

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
