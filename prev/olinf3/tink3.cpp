//
// Created by lain on 9/11/22.
//

#include "bits/stdc++.h"

using namespace std;
using ll = long long;

bool a[100001 * 2];
ll n, q;

void build() {
    for (int i = n - 1; i > 0; --i) a[i] = a[i<<1]&a[i<<1|1];
}

bool query(int l, int r) {
    bool res = true;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res &= a[l++];
        if (r&1) res &= a[--r];
    }
    return res;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        a[n+i] = x == 1;
    }

    build();

    cin >> q;

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << (query(--l, r) ? 2 : 1) << endl;
    }
}