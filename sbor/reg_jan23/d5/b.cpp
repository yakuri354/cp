// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 + 1;

ll a[maxn];
vector<ll> t[maxn * 2];

void cmb(vector<ll> &x, vector<ll> &l, vector<ll> &r) {
    ll lp = 0, rp = 0;

    x.resize(0);
    x.reserve(l.size() + r.size());

    while (lp < l.size() && rp < r.size()) {
        while (lp < l.size() && rp < r.size() && l[lp] <= r[rp]) x.push_back(l[lp++]);
        while (lp < l.size() && rp < r.size() && l[lp] >= r[rp]) x.push_back(r[rp++]);
    }
    while (lp < l.size()) x.push_back(l[lp++]);
    while (rp < r.size()) x.push_back(r[rp++]);
}

ll n;

void build() {
    for (ll i = n - 1; i > 0; i--) cmb(t[i], t[i*2], t[i*2+1]);
}

ll cnt(ll x, vector<ll> &v) {
    return upper_bound(v.begin(), v.end(), x) - lower_bound(v.begin(), v.end(), x);
}

ll query(ll l, ll r, ll x) {
    ll res = 0;
    for (l += n, r += n; r > l; l >>= 1, r >>= 1) {
        if (l & 1) res += cnt(x, t[l++]);
        if (r & 1) res += cnt(x, t[--r]);
    }
    return res;
}

void solve() {
    ll q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        t[n+i] = {x - i - 1};
    }

    build();

    for (ll i = 0; i < q; i++) {
        ll l, r, x;
        cin >> l >> r >> x;
        ll z = x - l;
        cout << query(l - 1, r, z) << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
