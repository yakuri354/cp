#include "bits/stdc++.h"

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
using ll = long long;
using fl = long double;

const ll maxn = 10;
ll r, c, q;

struct row {
    ll i;

    ll operator*(row &x) {
        ll bn1 = (min(r, c) * (min(r, c) + 1)) / 2;
        ll bn2 = bn1 + (max(r, c) - min(r, c)) * min(r, c);
        ll bn3 = bn2 + bn1;
        if (i <= min(r, c)) {
            return (i * (i + 1)) / 2;
        }
        else if (i <= max(r, c)) {
            return bn1 + (i - min(r, c)) * min(r, c);
        } else {
            return (bn2 + (2 * min(r, c) + max(r, c) - i - 1) * (i - max(r, c))) / 2;
        }
    }


};

ll rowen(ll i) {
    ll bn1 = (min(r, c) * (min(r, c) + 1)) / 2;
    ll bn2 = bn1 + (max(r, c) - min(r, c)) * min(r, c);
    ll bn3 = bn2 + bn1;
    if (i <= min(r, c)) {
        return (i * (i + 1)) / 2;
    }
    else if (i <= max(r, c)) {
        return bn1 + (i - min(r, c)) * min(r, c);
    } else {
        return (bn2 + (2 * min(r, c) + max(r, c) - i - 1) * (i - max(r, c))) / 2;
    }
}

int main() {
    cin >> r >> c >> q;

    for (int i = 0; i < q; ++i) {
        ll x;
        cin >> x;

        ll lo = 1, hi = r + c;
        while (lo + 1 < hi) {
            ll m = (lo + hi) / 2;
            if (rowen(m) > x) hi = m;
            else lo = m;
        }

        cout << (
    }
}