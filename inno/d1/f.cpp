// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;
using fl = long double;

const ll maxn = 1e5;

vector<pair<ll, ll>> t[maxn * 2];
vector<ll> ps[maxn * 2];
ll f[maxn];

ll n;

ll mod(ll x) {
    return x % (ll(1e9) + 7);
}

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i].resize(t[i*2].size() + t[i*2+1].size());
        ps[i].resize(t[i].size());
        merge(t[i*2].begin(), t[i*2].end(), t[i*2+1].begin(), t[i*2+1].end(), t[i].begin()); // ????? 
        ps[i][0] = mod(t[i][0].second);
        for (ll j = 1; j < t[j].size(); j++) {
            ps[i][j] = mod(ps[i][j-1] + t[i][j].second);
        }
    }
}

ll prefix(ll i, ll hi) {
    auto lb = lower_bound(t[i].begin(), t[i].end(), make_pair(hi, 0ll));
    if (lb == t[i].begin()) return 0;
    return ps[i][(lb - t[i].begin()) - 1];
}

ll query(ll l, ll r, ll hi) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += prefix(l++, hi);
        if (r & 1) res += prefix(--r, hi);
    }
    return res;
}

void solve() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        t[i + n] = {{x, 0ll}};
        ps[i+n] = {x};
    }
    
    t[n][0].second = 1;

    build();
    
    for (ll i = 1; i < n; i++) {
        
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
