// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll force[maxn];
ll nxt[maxn];
ll pln[maxn];
ll ble[maxn];

void solve() {
    ll n, m;

    cin >> n >> m;
    ll bs = sqrt(n) + 1;

    for (ll i = 0; i < n; i++) {
        cin >> force[i];
    }

    for (ll i = n-1; i >= 0; i--) {
        ll nn = i + force[i];
        pln[i] = 1;
        ble[i] = i;
        if (nn >= n) {
            nxt[i] = inf;
        } else if (nn / bs == i / bs) {
            pln[i] = 1 + pln[nn];
            nxt[i] = nxt[nn];
            ble[i] = ble[nn];
        } else {
            nxt[i] = nn;
        }
    }

    for (ll i = 0; i < m; i++) {
        ll qt;
        cin >> qt;
        if (qt == 0) {
            ll a, b;
            cin >> a >> b;
            a--;

            force[a] = b;
            for (ll j = a; j >= (a / bs) * bs; j--) {
                pln[j] = 1;
                ll np = j + force[j];
                if (np >= n) {
                    nxt[j] = inf;
                    ble[j] = j;
                } else if (np / bs != a / bs) {
                    nxt[j] = np;
                    ble[j] = j;
                } else {
                    nxt[j] = nxt[np];
                    pln[j] += pln[np];
                    ble[j] = ble[np];
                }
            }
        }
        if (qt == 1) {
            ll a, pl = 0, cntr = 0;
            cin >> a;
            a--;

            while (nxt[a] != inf) {
                if (cntr > 10 * (n / bs)) assert(0);
                pl += pln[a];
                a = nxt[a];
                cntr++;
            }

            pl += pln[a];

            cout << ble[a] + 1 << ' ' << pl << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
