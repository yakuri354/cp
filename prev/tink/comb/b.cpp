// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<ll> ans;

void zz(ll n, ll k) {
    if (k == 0) {
        for (ll i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }

    for (ll i = k; i <= n; i++) {
        ans.push_back(i);
        zz(i - 1, k - 1);
        ans.pop_back();
    }
}

void solve() {
    ll k, n;
    cin >> k >> n;

    zz(n, k);
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
