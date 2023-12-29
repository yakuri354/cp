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

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    ll q = lcm(b, d), p = a * (q / b) + c * (q / d);
    ll dv = gcd(p, q), m = p / dv, n = q / dv;
    cout << m << ' ' << n << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
