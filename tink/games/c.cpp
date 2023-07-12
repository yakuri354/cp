#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

ll d[5000];

ll cldiv(ll a, ll b) {
    if (a == 1) return 0;
    if (a % b == 0) {
        return a / b;
    } else {
        return a / b + 1;
    }
}

void solve() {
    ull a, b, c;
    cin >> a >> b >> c;
    a--, b--, c--;

    bitset<5001> mex;
    d[1] = 1;
    for (ll i = 2; i < 1 << (max(a, max(b, c))); i++) {
        mex.set();
        for (ll j = cldiv(i, 2); j < i; j++) {
            mex[d[j]] = false;
        }
        d[i] = mex._Find_first();
    }

    ll xs = d[a] ^ d[b] ^ d[c];

    if (xs == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        ull a_p = a, b_p = b, c_p = c;

        for (ll i = cldiv(a, 2); i < a; i++) {
            if ((d[i] ^ d[b] ^ d[c]) == 0) {
                a_p = i;
                goto ans;
            }
        }


        for (ll i = cldiv(b, 2); i < b; i++) {
            if ((d[a] ^ d[i] ^ d[c]) == 0) {
                b_p = i;
                goto ans;
            }
        }

        for (ll i = cldiv(c, 2); i < c; i++) {
            if ((d[a] ^ d[b] ^ d[i]) == 0) {
                c_p = i;
                goto ans;
            }
        }
    ans: cout << a_p + 1 << ' ' << b_p + 1 << ' ' << c_p + 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
