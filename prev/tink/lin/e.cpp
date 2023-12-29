// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 + 1;

ll a[4][maxn];

void solve() {
    ll n[4];

    for (ll i = 0; i < 4; i++) {
        cin >> n[i];

        for (ll j = 0; j < n[i]; j++) {
            cin >> a[i][j];
        }
        sort(a[i], a[i] + n[i]);
    }

    ll md = inf, p[4] = {0};

    auto nxt = [&]() {
        for (ll i = 0; i < 4; i++) {
            if (p[i] >= n[i]) return false;
        }
        return true;
    };

    auto mxa = [&]() {
        ll m = -inf;
        for (ll i = 0; i < 4; i++) {
            m = max(m, a[i][p[i]]);
        }
        return m;
    };

    auto mna = [&]() {
        ll m = inf;
        for (ll i = 0; i < 4; i++) {
            m = min(m, a[i][p[i]]);
        }
        return m;
    };

    ll ans[4] = {0};

    while (nxt()) {
        if (mxa() - mna() < md) {
            md = mxa() - mna();
            for (ll i = 0; i < 4; i++) {
                ans[i] = a[i][p[i]];
            }
        }
        for (ll i = 0; i < 4; i++) {
            if (a[i][p[i]] == mna()) {
                p[i]++;
                break;
            }
        }
    }

    for (ll i = 0; i < 4; i++) {
        cout << ans[i] << ' ';
    }

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
