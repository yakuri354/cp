#include "bits/stdc++.h"
#include <cstdint>
#include <random>

using namespace std;
using ll = long long;

ll a[100000];

void qsort(ll l, ll r) {
    if (l < 0 || r < 0 || r <= l) return;
    ll p = a[(l + r) / 2];
    ll lp = l - 1, rp = r + 1;

    for (;;) {
        do
            lp++;
        while
            (a[lp] < p);
        do
            rp--;
        while
            (a[rp] > p);
        if (lp >= rp) break;
        swap(a[lp], a[rp]);
    }

    qsort(l, rp);
    qsort(rp + 1, r);
}

int main() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) cin >> a[i];
    qsort(0, n - 1);
    for (ll i = 0; i < n; i++) cout << a[i] << ' ';
    return 0;
}

