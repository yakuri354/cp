#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
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

struct qq {
    ll l, r, i;
};

vector<ll> add(const vector<ll> &x, const vector<ll> &y) {
    vector<ll> z(x.size());
    for (ll i = 0; i < x.size(); i++) {
        z[i] = y[x[i] - 1];        
    }
    return z;
}

vector<ll> inv(const vector<ll> &x) {
    vector<ll> z(x.size());
    for (ll i = 0; i < x.size(); i++) {
        z[x[i] - 1] = i + 1;
    }
    return z;
}

ll mass_c(const vector<ll> &x) {
    ll ans = 0;
    for (ll i = 0; i < x.size(); i++) {
        ans += x[i] * (i + 1);
    }
    return ans;
}

vector<ll> _id_perm(ll m) {
    vector<ll> z(m);
    iota(z.begin(), z.end(), 1);
    return z;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    
    const auto id_p = _id_perm(m);
    
    vector<vector<ll>> a(n, vector<ll>(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    vector<vector<ll>> p(n, vector<ll>(m));

    vector<ll> curr = id_p;
    for (ll i = 0; i < n; i++) {
        curr = add(curr, a[i]);
        p[i] = curr;
    }
    
    ll q;
    cin >> q;
    
    vector<unordered_map<ll, ll>> cache(n);
    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--, r--;
        
        if (cache[l].count(r)) {
            cout << cache[l][r] << '\n';
        } else {
            ll ans;
            if (l == 0) {
                ans = mass_c(p[r]);
            } else {
                ans = mass_c(add(inv(p[l-1]), p[r]));
            }
            
            cache[l][r] = ans;

            cout << ans << '\n';
        }
    }
    
    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
