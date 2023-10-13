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

vector<ll> t;

ll n, lg;

void clear_st() {
    for (ll i = 0; i < n * 2; i++) {
        t[i] = -1;
    }
}

ll query_st(ll i) {
    ll ans = -1;
    for (i += n; i > 0; i >>= 1) {
        if (t[i] != -1) ans = t[i];
    }
    return ans;
}

void assign_st(ll l, ll r, ll x) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) t[l++] = x;
        if (r & 1) t[--r] = x;
    }
}

vector<unordered_set<ll>> g;
vector<ll> w;
vector<vector<ll>> bup;

void calc_binup(ll v) {
    for (ll i = 0; i < lg; i++) {
        bup[v][i] = bup[bup[v][i-1]][i-1];
    }
    
    for (ll u : g[v]) {
        bup[u][0] = v;
        calc_binup(u);
    }
}

vector<pair<ll, ll>> state;

void rebuild() {
    
}

void solve() {
    ll q;
    cin >> n >> q;

    g.resize(n);
    t.resize(n * 2);
    
    lg = 64 - __builtin_clzll(n) + 1;
    
    for (ll i = 0; i < n - 1; i++) {
        ll x;
        cin >> x;
        g[x - 1].insert(i);
    }
    
    for (ll i = 0; i < n - 1; i++) {
        ll x;
        cin >> x;
        w[i] = x;
    }
    
    ll bs = sqrt(n);
    
    for (ll i = 0; i < q; i++) {
        ll u, v;
        cin >> u >> v;

        
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
