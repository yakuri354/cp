// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

bool x[1000001], prime[1000001];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 2; i <= n; i++) {
        if (!x[i]) {
            prime[i] = true;
        }
        for (ll j = 1; i * j <= n; j++) {
            x[i*j] = true;
        }
    }

    for (ll i = 2; i < n; i++) {
        if (prime[i] && prime[n - i]) {
            cout << i << ' ' << n - i << endl;
            return;
        }
    }

    cout << "AAAA LJFSDJFLSJDFKJSDLFJSLFJLSDJFLSJDFLJSDLFJSLKDFJLSJFKSDFKSS" << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
