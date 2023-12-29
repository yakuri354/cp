// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll fld[10][10];
ll n, m, c;

ll f() {
    ll ans = 0;
    for (ll i1 = 0; i1 < n; i1++) {
        for (ll j1 = 0; j1 < m; j1++) {
            for (ll i2 = i1+1; i2 < n; i2++) {
                for (ll j2 = j1+1; j2 < m; j2++) {
                    if (fld[i1][j1] == fld[i1][j2]
                        && fld[i1][j1] == fld[i2][j1]
                        && fld[i1][j1] == fld[i2][j2]) {
                        ans++;
                    }
                }
            }
        }
    }
    return ans;
}

string ans10_10 = R"(2 2 1 2 1 3 1 3 1 3 
2 1 3 1 3 2 3 2 1 3 
2 3 1 3 3 3 2 1 2 1 
1 2 2 3 2 1 3 3 1 1 
2 3 2 1 1 1 3 1 3 2 
3 1 2 2 1 3 3 2 2 1 
3 1 1 3 2 1 2 2 3 3 
3 3 3 1 2 2 1 3 2 1 
1 2 1 1 3 2 2 3 3 2 
1 1 3 2 2 3 1 1 3 2)";

string ans10_9 = R"(2 2 1 1 2 2 3 3 3 
2 3 1 2 1 3 3 1 1 
1 2 3 2 3 3 1 1 2 
3 1 2 2 2 3 1 3 1 
1 2 2 3 3 1 2 3 1 
2 3 2 3 1 1 1 2 2 
1 3 3 1 1 2 2 3 2 
3 1 3 3 2 1 3 1 2 
1 1 1 3 2 3 2 2 3 
3 3 1 2 3 2 1 2 3)";

string ans9_10 = R"(3 1 3 2 2 1 3 2 3 1 
2 3 2 3 1 3 1 1 3 2 
3 3 1 1 3 2 1 3 2 2 
1 2 2 2 3 3 3 1 2 1 
3 1 2 1 2 3 2 1 1 3 
2 3 3 1 1 1 2 2 2 3 
1 1 1 2 1 2 2 3 3 3 
2 2 1 3 2 2 3 3 1 1 
1 2 3 3 3 1 1 2 1 2)";

string ans9_9 = R"(2 3 1 3 2 2 1 1 3 
2 1 2 3 3 3 1 2 1 
1 1 2 1 2 3 3 1 2 
1 2 2 2 1 3 1 3 3 
3 1 1 2 2 1 3 2 3 
3 3 1 1 1 3 2 2 1 
3 2 3 1 3 1 1 2 2 
1 2 3 3 2 1 3 3 1 
2 3 3 2 1 1 2 1 2)";

void solve() {
    cin >> n >> m >> c;

    if (n == 10 && m == 10 && c == 3) {
        cout << ans10_10 << endl;
        return;
    }

    if (n == 10 && m == 9 && c == 3) {
        cout << ans10_9 << endl;
        return;
    }

    if (n == 9 && m == 10 && c == 3) {
        cout << ans9_10 << endl;
        return;
    }

    if (n == 9 && m == 9 && c == 3) {
        cout << ans9_9 << endl;
        return;
    }

    mt19937_64 mt(random_device{}());
    uniform_int_distribution<ll> cd(1, c);
    uniform_int_distribution<ll> nd(0, n - 1);
    uniform_int_distribution<ll> md(0, m - 1);
    uniform_real_distribution<fl> fd;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            fld[i][j] = cd(mt);
        }
    }

    ll curr = f();
    
    fl temp = 10;
    for (ll iter = 0;; iter++) {
        if (iter % 1000 == 0) {
            cerr << "T " << temp << endl;
            cerr << "S " << curr << endl;
        }
        ll i = nd(mt), j = md(mt);
        ll old = fld[i][j];

        while (fld[i][j] == old) fld[i][j] = cd(mt);

        ll news = f();

        if (news == 0) break;

        if (fd(mt) < exp((curr - news) / temp)) {
            curr = news;
        } else {
            fld[i][j] = old;
        }

        temp *= 0.999;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cout << fld[i][j] << ' ';
        }
        cout << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
