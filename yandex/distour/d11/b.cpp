#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

#include "ext/pb_ds/assoc_container.hpp"

namespace pbds {
    using namespace __gnu_pbds;
};

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

inline ll mod(ll x) {
    return x % ll(1e9+7);
}

const ll LGC = 31;

pbds::cc_hash_table<ll, ll> t;

ll sum_q(ll v, ll nl, ll nr, ll depth, ll l, ll r, ll k) {
    if (l <= nl && nr <= r) {
        ll vx = v ^ (k >> (LGC - depth));
        auto fi = t.find(vx);
        if (fi == t.find_end()) return 0;
        else return fi->second;
    }

    if (l >= nr || r <= nl) {
        return 0;
    }

    ll m = (nl + nr) / 2;

    return mod(sum_q(v * 2, nl, m, depth + 1, l, r, k) 
        + sum_q(v * 2 + 1, m, nr, depth + 1, l, r, k));
}

void add_q(ll v, ll nl, ll nr, ll p, ll x) {
    if (nr - nl <= 1) {
        t[v] = mod(t[v] + x);
        return;
    }

    ll m = (nl + nr) / 2;
    if (p < m) {
        t[v] -= t[v*2];
        add_q(v * 2, nl, m, p, x);
        t[v] += t[v*2];
    } else {
        t[v] -= t[v*2+1];
        add_q(v * 2 + 1, m, nr, p, x);
        t[v] += t[v*2+1];
    }

    // t[v] = t[v*2] + t[v*2+1];
}

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;
    
    vector<ll> psx(n);
    psx[0] = a[0];
    for (ll i = 1; i < n; i++) {
        psx[i] = psx[i-1] ^ a[i];
    }

    vector<pll> qs(k);
    for (auto &[l, r]: qs) cin >> l >> r, r++;

    vector<ll> l0(n), l1;

    for (ll i = 0; i < n; i++) {
        if (qs[0].first <= psx[i] && psx[i] < qs[0].second) {
            l0[i] = 1;
        }
    }

    for (ll layer = 1; layer < k; layer++) {
        l1.assign(n, 0);
        t.clear();
        for (ll i = 1; i < n; i++) {
            add_q(1, 0, 1ll << LGC, psx[i - 1], l0[i - 1]);

            l1[i] = sum_q(1, 0, 1ll << LGC, 0, qs[layer].first, qs[layer].second, psx[i]);
        }
        swap(l0, l1);
    }

    cout << l0[n - 1] << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

