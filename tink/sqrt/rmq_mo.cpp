// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct query {
    ll l, r, i;
};

const ll maxn = 100000;
const ll sqrtn = 317;

query qs[maxn];
pair<ll, ll> ans[maxn];
ll a[maxn];

set<pair<ll, ll>, greater<>> wrks;

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll k;
    cin >> k;

    for (ll i = 0; i < k; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--;
        qs[i].r--;
        qs[i].i = i;
    }

    sort(qs, qs + k, [](query &a, query &b) {
             if (a.l / sqrtn == b.l / sqrtn) {
                 if (a.r == b.r) {
                     return a.l < b.l;
                 } else {
                    return a.r < b.r;
                 }
             } else {
                return a.l / sqrtn < b.l / sqrtn;
             }
         });

    ll l = 0;
    ll r = -1;
    for (ll i = 0; i < k; i++) {
        while (r < qs[i].r) r++, wrks.emplace(a[r], r);
        while (r > qs[i].r) wrks.erase(wrks.find(make_pair(a[r], r))), r--;
        while (l > qs[i].l) l--, wrks.emplace(a[l], l);
        while (l < qs[i].l) wrks.erase(wrks.find(make_pair(a[l], l))), l++;
        ans[qs[i].i] = *wrks.begin();
    }

    for (ll i = 0; i < k; i++) {
        cout << ans[i].first << ' ' << ans[i].second + 1 << '\n';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
