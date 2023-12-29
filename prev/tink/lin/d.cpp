// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll x;
    cin >> x;

    ll ai = 1, bi = 1, si = 1, last = 1;
    while (si < x) {
        ll na = (ai+1)*(ai+1), nb = (bi+1)*(bi+1)*(bi+1);
        if (na == nb) {
            ai++, bi++;
            last = na;
        } else if (na < nb) {
            ai++;
            last = na;
        } else {
            bi++;
            last = nb;
        }
        si++;
    }

    cout << last << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
