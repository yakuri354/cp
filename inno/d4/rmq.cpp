// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
#include <strings.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

using el = ll;
el el_id = inf;

el op(el a, el b) {
    return min(a, b);
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

const ll maxn = 1e5;
const ll lg = 18;

ll s[lg][maxn];
ll mod;

void build_sparse(ll n) {
    for (ll l = 1; l < lg; l++) {
        for (ll i = 0; i + (1 << l) <= n; i++) {
            s[l][i] = min(s[l-1][i], s[l-1][i + (1 << (l - 1)) - 1]);
        }
    }
}

void solve() {
    ll m, u, v;
    cin >> n >> mod >> m >> s[0][0] >> u >> v;
    
    for (ll i = 1; i < n; i++) {
        s[0][i] = (23 * s[0][i-1] + 21563) % 16714589;
    }
    
    build_sparse(n);
    
    ll r = 0;
    for (ll i = 0; i < m; i++) {
        // cout << "query " << u << ' ' << v << " = ";
        // r = query(min(u, v) - 1, max(u, v));
        ll l = min(u, v) - 1, r = max(u, v);
        ll ql = __lg(r - l + 1);
        r = min(s[l][ql], s[r - (1 << ql)][ql]);
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
