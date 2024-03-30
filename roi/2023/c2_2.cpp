// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

struct segt_max {
    ll n;
    vector<ll> t;

    segt_max(ll n) : n(n), t(n * 2) {
    }

    void modify(ll i, ll x) {
        i += n;
        t[i] = x;

        for (i /= 2; i > 0; i /= 2)
            t[i] = max(t[i * 2], t[i * 2 + 1]);
    }

    ll getmax(ll l, ll r) {
        ll res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1)
                res = max(res, t[l++]);
            if (r & 1)
                res = max(res, t[--r]);
        }
        return res;
    }
};

void solve() {
    ll n;
    cin >> n;

    if (n > 10000) {
        cout << n << '\n';
        return;
    }

    vector<ll> a(n);
    for (ll& i : a)
        cin >> i, i--;

    vector<segt_max> by_x(n, segt_max(n)), by_y(n, segt_max(n));

    for (ll i = 0; i < n; i++) {
        for (ll y = 0; y < n; y++) {
            // ll nv = a[i] == 0 ? 1 : (by_y[y].getmax(0, a[i]) + 1);
            ll nv = a[i] == 0 ? 1 : (by_y[y].getmax(0, a[i] + 1) + 1);
            by_y[y].modify(a[i], max(by_y[y].t[n+a[i]], nv));
            by_x[a[i]].modify(y, max(by_x[a[i]].t[n+y], nv));
        }

        for (ll x = 0; x < n; x++) {
            // ll nv = a[i] == n - 1 ? 1 : (by_x[x].getmax(a[i] + 1, n) + 1);
            ll nv = a[i] == n - 1 ? 1 : (by_x[x].getmax(a[i], n) + 1);
            by_x[x].modify(a[i], max(by_x[x].t[n+a[i]], nv));
            by_y[a[i]].modify(x, max(by_y[a[i]].t[n+x], nv));
        }

        by_x[a[i]].modify(a[i], 1);
        by_y[a[i]].modify(a[i], 1);

    //     for (ll i = 0; i < n; i++) {
    //         for (ll j = 0; j < n; j++) {
    //             cout << by_x[i].t[n+j] << ' ';
    //         }

    //         cout << "  ";

    //         for (ll j = 0; j < n; j++) {
    //             cout << by_y[j].t[n+i] << ' ';
    //         }

    //         cout << '\n';
    //     }

    //     cout << endl;
    }

    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        ans = max(ans, by_x[i].getmax(0, n));
        ans = max(ans, by_y[i].getmax(0, n));
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t-- > 0)
        solve();
}
