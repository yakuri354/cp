// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
#include <cmath>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const fl pi = 3.14159265359;

void solve() {
    fl a, b;
    cin >> a >> b;

    if (b < a) swap(a, b);

    fl mmax = 1;
    fl mmin = sqrtl(3) / 2;

    while (abs(mmin - mmax) > 1e-10) {
        fl mid = (mmin + mmax) / 2;

        fl minb = cosl(pi / 6.0 - acosl(mid)) * (a / mid);

        if (minb <= b) mmax = mid;
        else mmin = mid;
    }

    cout << fixed << setprecision(10) << a / mmax << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
