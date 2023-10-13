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
using ll = int;
using lo = long long;
using ull = unsigned long long;
using fl = long double;
 
const ll inf = INT32_MAX;
 
using el = ll;
el el_id = 1;

long long M;

long long mod(long long x) {
    return x % M;
}
 
el op(el a, el b) {
    return el(mod(lo(a) * lo(b)));
}
 
vector<el> st;
ll n;
 
void build() {
    for (ll i = n - 1; i > 0; i--) {
        st[i] = op(st[i*2], st[i*2+1]);
    }
}
 
el query(ll l, ll r) {
    el res_l = el_id, res_r = el_id;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res_l = op(res_l, st[l++]);
        if (r & 1) res_r = op(st[--r], res_r);
    }
    return op(res_l, res_r);
}
 
void set_el(ll i, el x) {
    for (st[i += n] = x, i >>= 1; i > 0; i >>= 1) {
        st[i] = op(st[i*2], st[i*2+1]);
    }
}
 
void solve() {
    ll m, u, v;
    cin >> n >> M >> m;
    st.resize(n * 2);
    cin >> st[n] >> u >> v;
     
    for (ll i = 1; i < n; i++) {
        st[n + i] = (23 * st[n + i-1] + 21563) % 16714589;
    }
     
    build();
     
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