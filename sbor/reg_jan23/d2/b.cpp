// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

int a[10000000];

void solve() {
    ll n, k;
    cin >> n >> k;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (ll i = 1; i < k; i++) {
        for (ll j = 0; j < n; j++) {
            a[j+i*n] = a[i*n-j-1];
        }
    }

    vector<ll> end;
    ll sbl = 0;
    for (ll i = 0; i < n * k; i++) {
        auto x = lower_bound(end.begin(), end.end(), a[i]);

        if (x == end.end()) {
            sbl += 1;
            end.push_back(a[i]);
        } else {
            *x = a[i];
        }
    }

    cout << sbl << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
