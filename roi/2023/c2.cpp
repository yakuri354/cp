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

const ll inf = 1e12;

struct segt_max {
    ll n;
    vector<ll> t;

    segt_max(ll n, ll v) : n(n), t(n * 2, v) {
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
        cin >> i;

    vector<segt_max> by_x(n + 2, segt_max(n + 2, -inf)), by_y(n + 2, segt_max(n + 2, -inf));
    // vector<segt_max> by_x(n + 2, segt_max(n + 2, 0)), by_y(n + 2, segt_max(n + 2, 0));

    // by_x[0].modify(n + 1, 0);
    // by_y[n + 1].modify(0, 0);

    for (ll i = 0; i < n; i++) {
        for (ll y = 0; y <= n + 1; y++) {
            ll nv = by_y[y].getmax(0, a[i]) + 1;
            by_y[y].modify(a[i], nv);
            by_x[a[i]].modify(y, nv);
        }

        for (ll x = 0; x <= n + 1; x++) {
            ll nv = by_x[x].getmax(a[i] + 1, n + 2) + 1;
            by_x[x].modify(a[i], nv);
            by_y[a[i]].modify(x, nv);
        }

        // by_x[a[i]].modify(a[i], 1);
        // by_y[a[i]].modify(a[i], 1);

        // for (ll i = 0; i < n + 2; i++) {
        //     for (ll j = 0; j < n + 2; j++) {
        //         if (by_x[i].t[n+2+j] == -inf) cout << "_ ";
        //         else cout << by_x[i].t[n+2+j] << ' ';
        //     }

        //     cout << "  ";

        //     for (ll j = 0; j < n + 2; j++) {
        //         if (by_y[j].t[n+2+i] == -inf) cout << "_ ";
        //         else cout << by_y[j].t[n+2+i] << ' ';
        //     }

        //     cout << '\n';
        // }

        // cout << endl;
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
