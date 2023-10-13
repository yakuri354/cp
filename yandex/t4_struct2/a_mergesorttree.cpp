// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> t;
ll n;

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i].resize(t[i*2].size() + t[i*2+1].size());

        merge(t[i*2].begin(), t[i*2].end(),
                t[i*2+1].begin(), t[i*2+1].end(),
                t[i].begin());
    }
}

ll between(vector<ll> &v, ll l, ll r) {
    return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
}

ll query(ll l, ll r, ll ql, ll qr) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += between(t[l++], ql, qr);
        if (r & 1) res += between(t[--r], ql, qr);
    }
    
    return res;
}

void solve() {
    ll m;
    cin >> n >> m;
    
    t.resize(n * 2, {});
    
    for (ll i = 0; i < n; i++) {
        t[n + i].resize(1);
        cin >> t[n + i][0];
    }
    
    build();
    
    for (ll i = 0; i < m; i++) {
        ll l, r, ql, qr;
        cin >> l >> r >> ql >> qr;
        
        cout << query(l - 1, r, ql, qr) << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
