// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

vector<ll> children[maxn], euler, t;
ll tin[maxn], tout[maxn], depth[maxn], uebok = 0, el;

ll cmb(ll a, ll b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (depth[a] < depth[b])
        return a;
    else
        return b;
}

void build() {
    for (ll i = el - 1; i > 0; i--) t[i] = cmb(t[i*2], t[i*2+1]);
}

ll query(ll l, ll r) {
    ll res = -1;
    for (l += el, r += el; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = cmb(res, t[l++]);
        if (r & 1) res = cmb(res, t[--r]);
    }
    return res;
}

void dfs(ll v, ll d) {
    depth[v] = d;
    tin[v] = uebok++;
    euler.push_back(v);
    for (ll u : children[v]) {
        dfs(u, d + 1);
        euler.push_back(v);
        uebok++;
    }
    tout[v] = uebok;
}

void solve() {
    ll m, n;
    cin >> n >> m;

    for (ll i = 0; i < n - 1; i++) {
        ll p;
        cin >> p;
        children[p].push_back(i + 1);
    }

    dfs(0, 0);
    el = euler.size();

    t.assign(el, 0);
    for (ll i : euler) {
        t.push_back(i);
    }

    build();

    ll a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;

    ll ans = 0, pa = 0;
    for (ll i = 0; i < m; i++) {
        ll v1 = tout[(a1 + pa) % n] - 1, v2 = tin[a2];
        pa = query(min(v1, v2), max(v1, v2) + 1);
        ans += pa;
        ll a3 = (x * a1 + y * a2 + z) % n;
        ll a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3, a2 = a4;
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
