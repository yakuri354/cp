// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll gcd(ll a, ll b) {
    if (b == 0) return a;

    return gcd(b, a % b);
}

void solve() {
    ll m, n;
    cin >> m >> n;

    cout << gcd(m, n) << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
