#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 3e5;

ll a[maxn], qans[maxn];

struct qr {
    ll l, r, i;
};

qr qs[maxn];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll bs = ceil(sqrt(n)) + 1;

    ll q;
    cin >> q;

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
    gp_hash_table<ll, ll> mp;
    for (ll i = 0; i < q; i++) {
        auto qq = qs[i];
        while (qq.r > r) {
            if (mp[a[++r]] <= 0) s++;
            mp[a[r]]++;
        }
        while (qq.l < l) {
            if (mp[a[--l]] <= 0) s++;
            mp[a[l]]++;
        }
        while (qq.r < r) {
            mp[a[r]]--;
            if (mp[a[r]] <= 0) s--;
            r--;
        }
        while (qq.l > l) {
            mp[a[l]]--;
            if (mp[a[l]] <= 0) s--;
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
