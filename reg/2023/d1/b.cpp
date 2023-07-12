// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll fib[92];

ll f(ll x, ll hb) {
    if (x == 1) return 1;
    ll ans = 0;
    for (ll i = 90; i > 1; i--) {
        if (fib[i] > hb) continue;
        if (x == fib[i]) {
            ans += 1;
        } else if (x % fib[i] == 0) {
            ans += f(x / fib[i], fib[i]);
        }
    }
    return ans;
}

void solve() {
    ll x;
    cin >> x;

    cout << f(x, fib[91]) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    fib[0] = 1;
    fib[1] = 1;
    for (ll i = 2; i < 92; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    ll t; cin >> t;
    while (t --> 0) solve();
}
