// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 129;
ll n;

ll t[maxn][maxn][maxn];

ll query(ll x, ll y, ll z) {
    ll res = 0;

    for (; x > 0; x -= x & -x) {
        for (; y > 0; y -= y & -y) {
            for (; z > 0; z -= z & -z) {
                res += t[x][y][z];
            }
        }
    }

    return res;
}

void add(ll x, ll y, ll z, ll v) {
    for (; x <= n; x += x & -x) {
        for (; y <= n; y += y & -y) {
            for (; z <= n; z += z & -z) {
                t[x][y][z] += v;
            }
        }
    }
}

ll seg(ll x1, ll x2, ll y1, ll y2, ll z1, ll z2) {
    ll ans = query(x2, y2, z2);
    ans -= query(x2, y1, z2);
    ans -= query(x1, y2, z2);
    ans += query(x1, y1, z2);

    ll lower = query(x2, y2, z1);
    lower -= query(x2, y1, z1);
    lower -= query(x1, y2, z1);
    lower += query(x1, y1, z1);

    return ans - lower;
}


void solve() {
    cin >> n;

    for (;;) {
        ll qt;
        cin >> qt;

        if (qt == 1) {
            ll x, y, z, k;
            cin >> x >> y >> z >> k;

            add(x + 1, y + 1, z + 1, k);
        } else if (qt == 2) {
            ll x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

            cout << seg(x1, x2 + 1, y1, y2 + 1, z1, z2 + 1) << '\n';
        } else if (qt == 3) {
            return;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
