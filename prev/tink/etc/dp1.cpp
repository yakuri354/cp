#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

struct dpe {
    ll xpl;
    ll ypl;
    ll m1x;
    ll m1y;
    ll msq;
};

const ll logn = 11;

bool a[3001][3001];
bool s[3001][3001][logn + 1];

bool query(ll x, ll y, ll sz) {
    ll lg = __lg(sz);
    ll pw = 1 << lg;
    bool ans = s[x][y][lg];
    ans &= s[x + sz - pw][y][lg];
    ans &= s[x][y + sz - pw][lg];
    ans &= s[x + sz - pw][y + sz - pw][lg];
    return ans;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            // cin >> a[i][j];
            s[i][j][0] = a[i][j];
        }
    }

    for (ll lg = 1; lg <= logn; lg++) {
        for (ll x = 0; x < n - (1 << lg) + 1; x++) {
            for (ll y = 0; y < m - (1 << lg) + 1; y++) {
                s[x][y][lg] = s[x][y][lg-1];
                s[x][y][lg] &= s[x + (1 << (lg - 1))][y][lg-1];
                s[x][y][lg] &= s[x][y + (1 << (lg - 1))][lg-1];
                s[x][y][lg] &= s[x + (1 << (lg - 1))][y + (1 << (lg - 1))][lg-1];
            }
        }
    }

    ll ans = 0, ax = 0, ay = 0;

    for (ll x = 0; x < n; x++) {
        for (ll y = 0; y < m; y++) {
            if (!a[x][y]) continue;
            ll lo = 1, hi = min(n - x, m - y) + 1;
            while (lo + 1 < hi) {
                ll m = (lo + hi) / 2;
                if (query(x, y, m)) {
                    lo = m;
                } else {
                    hi = m;
                }
            }
            if (lo > ans) {
                ans = lo;
                ax = x;
                ay = y;
            }
        }
    }

    cout << ans << endl;
    cout << ax + 1 << ' ' << ay + 1 << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
