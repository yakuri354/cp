// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 1e5;

ll a[maxn], qa[maxn];

struct qr {
    ll l, r, x, i;
};

qr qs[maxn];

unordered_map<ll, ll> mp;

void add(ll x) {
    if (mp.count(x)) mp[x]++;
    else mp[x] = 1;
}

void solve() {
    ll n, m, bs;
    cin >> n >> m;
    bs = sqrt(n);

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        a[i] = x - i - 1;
    }

    for (ll i = 0; i < m; i++) {
        cin >> qs[i].l >> qs[i].r >> qs[i].x;
        qs[i].l--;
        qs[i].r--;
        qs[i].i = i;
    }

    sort(qs, qs + m, [&](auto a, auto b) -> bool {
             if (a.l / bs == b.l / bs) return (a.r < b.r) ^ ((a.l / bs) & 1);
             return a.l / bs < b.l / bs;
         });

    ll l = 0, r = -1;
    for (ll i = 0; i < m; i++) {
        auto q = qs[i];
        while (l > q.l) add(a[--l]);
        while (r < q.r) add(a[++r]);
        while (l < q.l) mp[a[l++]]--;
        while (r > q.r) mp[a[r--]]--;
        
        qa[q.i] = mp[q.x - q.l - 1];
    }

    for (ll i = 0; i < m; i++) {
        cout << qa[i] << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
