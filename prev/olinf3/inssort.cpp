#include "bits/stdc++.h"
#include <stdint.h>

using namespace std;
using ll = long long;

ll a[100000];
ll b[100000];

ll ins = 0;

void mergesort(ll l, ll r) {
    if (l + 1 == r) return;
    if (l + 2 == r) {
        if (a[l] > a[r-1]) {
            swap(a[l], a[r-1]);
            ins++;
        }
        return;
    }

    ll mid = (l + r) / 2;
    mergesort(l, mid);
    mergesort(mid, r);

    ll lp = l, rp = mid, op = l;

    while (lp != mid || rp != r) {
        if (rp == r || (lp != mid && a[lp] < a[rp])) {
            b[op++] = a[lp++];
            ins += rp - mid;
        } else {
            b[op++] = a[rp++];
        }
    }

    for (ll i = l; i < r; i++) {
        a[i] = b[i];
    }
}

int main() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    mergesort(0, n);

    // for (ll i = 0; i < n; i++) {
        // cout << a[i] << ' ';
    // }

    cout << ins << endl;

    // cout << endl;
}
