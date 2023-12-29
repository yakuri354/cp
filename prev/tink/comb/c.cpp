// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll fac[13];
ll perm[12];
ll fin[12];

void solve() {
    ll n, k;
    cin >> n >> k;

    fac[0] = 1;
    for (ll i = 1; i <= n; i++) fac[i] = fac[i-1] * i;

    for (ll i = 0; i < n; i++) {
        perm[i] = k / fac[n - i - 1];
        k %= fac[n - i - 1];
    }

    for (ll i = n - 1; i > 0; i--) {
        for (ll j = i - 1; j >= 0; j--) {
            if (perm[j] <= perm[i]) perm[i]++;
        }
    }
    for (ll i = 0; i < n; i++) {
        cout << perm[i] + 1 << ' ';
    }
    cout << endl;
}

void str() {
    random_device rd;
    mt19937_64 mt(rd());
    ll n = 3;
    fac[0] = 1;
    for (ll i = 1; i <= n; i++) fac[i] = fac[i-1] * i;
    uniform_int_distribution<ll> id(1, fac[n]-1);

    while (true) {
        ll k = id(mt);

        vector<ll> ans1(n);
        iota(ans1.begin(), ans1.end(), 1);
        for (ll i = 0; i < k; i++) next_permutation(ans1.begin(), ans1.end());

        // solve(n, k);

        for (ll i = 0; i < n; i++) {
            if (fin[i] != ans1[i]) {
                cout << "ERR " << n << " " << k << endl;
                for (ll i = 0; i < n; i++) {
                    cout << fin[i] << ' ';
                }
                cout << endl;
                for (ll i : ans1) {
                    cout << i << ' ';
                }
                cout << endl;
                return;
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
