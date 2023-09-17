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
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
 
const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll lg = 17;
 
ll M;

ll mod(ll x) {
    return x % M;
}
 
ll a[1 << 17];

struct node {
    vector<ll> suff, pref;
    ll l, r;
    
    node() {};
    
    void init(ll l, ll r) {
        this->l = l;
        this->r = r;

        ll m = (l + r) / 2;
        suff.resize(m - l);
        pref.resize(r - m);
        
        if (suff.size() > 0) suff[0] = a[m - 1];
        for (ll i = 1; i < suff.size(); i++) {
            suff[i] = mod(suff[i-1] * a[m - i - 1]);
        }
        
        if (pref.size() > 0) pref[0] = a[m];
        for (ll i = 1; i < pref.size(); i++) {
            pref[i] = mod(pref[i-1] * a[m + i]);
        }
    }
    
    ll ans(ll ql, ll qr) {
        ll m = (l + r) / 2;

        assert(l <= ql && ql <= m && m <= qr && qr <= r);
        
        ll ans = 1; // id

        if (ql < m) ans = mod(suff[m - ql] * ans);
        if (qr > m) ans = mod(pref[qr - m - 1] * ans);

        return ans;
    }
};

// node t[(1 << (lg + 1)) + 1];

void build(ll i, ll l, ll r) {
    if (l - r < 1) return;

    t[i].init(l, r);    
    
    ll m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m, r);
}
 
ll query(ll l, ll r) {
    ll node = 
}
 
void solve() {
    ll m, u, v, n;
    cin >> n >> M >> m;
    cin >> a[0] >> u >> v;
     
    for (ll i = 1; i < n; i++) {
        a[i] = (23 * a[i-1] + 21563) % 16714589;
    }
    
    ll ext_n = 1 << (sizeof(ll) * 8 - __builtin_clz(n) - 1);
    build(1, 0, ext_n);
     
    ll r = 0;
    for (ll i = 0; i < m; i++) {
        // cout << "query " << u << ' ' << v << " = ";
        r = query(min(u, v) - 1, max(u, v));
        // cout << r << endl;
 
        if (i == m - 1) break;
        u = (17 * u + 751 + r + 2 * (i + 1)) % n + 1;
        v = (13 * v + 593 + r + 5 * (i + 1)) % n + 1;
    }
     
    cout << u << ' ' << v << ' ' << r << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}