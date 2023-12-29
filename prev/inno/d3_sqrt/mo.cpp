#pragma GCC optimize("Ofast")
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 3e5;
const ll maxc = 1e6 + 1;

ll a[maxn], qans[maxn];

struct qr {
    ll l, r, i;
};

qr qs[maxn];

void solve() {
    ll n, q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll bs = ceil(sqrt(n)) + 1;

    for (ll i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--;
        qs[i].r--;
        qs[i].i = i;
    }

    sort(qs, qs + q, [bs](qr l, qr r) {
        if (l.l / bs == r.l / bs) {
            if ((l.l / bs) % 2 == 0) return l.r < r.r;
            else return l.r > r.r;
        }
        return l.l / bs < r.l / bs;
    });

    ll l = 0, r = -1, s = 0;
    vector<ll> mp(maxc);
    for (ll i = 0; i < q; i++) {
        auto qq = qs[i];
        while (qq.r > r) { // r ->
            r++;
            s -= mp[a[r]] * mp[a[r]] * a[r];
            mp[a[r]]++;
            s += mp[a[r]] * mp[a[r]] * a[r];
        }
        while (qq.l < l) { // <- l
            l--;
            s -= mp[a[l]] * mp[a[l]] * a[l];
            mp[a[l]]++;
            s += mp[a[l]] * mp[a[l]] * a[l];
        }
        while (qq.r < r) { // r <-
            s -= mp[a[r]] * mp[a[r]] * a[r];
            mp[a[r]]--;
            s += mp[a[r]] * mp[a[r]] * a[r];
            r--;
        }
        while (qq.l > l) { // -> l
            s -= mp[a[l]] * mp[a[l]] * a[l];
            mp[a[l]]--;
            s += mp[a[l]] * mp[a[l]] * a[l];
            l++;
        }

        qans[qq.i] = s;
    }

    for (ll i = 0; i < q; i++) cout << qans[i] << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
