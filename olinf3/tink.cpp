//
// Created by lain on 9/11/22.
//

#include "bits/stdc++.h"

using namespace std;

using ll = long long;
const ll maxn = 1e5 + 1;

struct ent {
    ll yb;
    ll ix;
    ll pw;
};

ll p[maxn + 1];

ent a[maxn];

int main() {
    ll n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> a[i].yb;
        a[i].ix = i + 1;
    }

    sort(a, a + n, [](auto a, auto b) {return a.yb > b.yb;});

    ll lst = 0;

    for (int i = 1; i < n; ++i) {
        if (a[lst].yb < a[i].yb + k) {
            cout << "-1\n";
            return 0;
        }

        p[a[i].ix] = a[lst].ix;
        if (++a[lst].pw >= 2) lst++;
    }

    for (int i = 1; i <= n; ++i) {
        cout << p[i] << ' ';
    }
    cout << endl;
}