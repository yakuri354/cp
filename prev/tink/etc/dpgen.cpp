// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

void solve() {
    random_device rd;
    mt19937_64 mt(rd());
    uniform_int_distribution<ll> dist1(1, 10);
    ll m = dist1(mt);
    uniform_int_distribution<ll> dist2(0, m);
    cout << dist1(mt) << ' ' << dist2(mt) << ' ' << dist2(mt) << ' ' << dist2(mt) << ' ' << m << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
