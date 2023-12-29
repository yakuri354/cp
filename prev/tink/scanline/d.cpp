// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<pair<ll, ll>> arr;

void solve() {
    ll n;
    cin >> n;

    arr.resize(n);

    for (ll i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
