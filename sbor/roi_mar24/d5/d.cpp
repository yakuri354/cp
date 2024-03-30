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
using pll = pair<ll, ll>;

vector<ll> dx, tout, lc, rc;
vector<vector<ll>> bup;

const ll lgn = 20;

ll timer = 0;

void dfs0(ll l, ll r) {
    ll v = timer++;

    for (ll i = 1; i < lgn; i++) {
        bup[v][i] = bup[bup[v][i-1]][i-1];
    }

    if (r - l <= 1) {
        tout[v] = timer;
        return;
    }

    lc[v] = timer;
    bup[timer][0] = v;
    dfs0(l, dx[v]);
    rc[v] = timer;
    bup[timer][0] = v;
    dfs0(dx[v], r);
    tout[v] = timer;
}

bool is_ancestor(ll v, ll u) {
    return v <= u && tout[u] <= tout[v];
}

ll dist(ll v, ll u) {
    if (v == u) return 0;

    ll ans = 0;

    for (ll i = lgn - 1; i >= 0; i--) {
        if (!is_ancestor(bup[v][i], u)) {
            ans += 1 << i;
            v = bup[v][i];
        }
    }

    for (ll i = lgn - 1; i >= 0; i--) {
        if (!is_ancestor(bup[u][i], v)) {
            ans += 1 << i;
            u = bup[u][i];
        }
    }
    
    if (is_ancestor(v, u) || is_ancestor(u, v)) ans += 1;
    else ans += 2;
    
    return ans;
}

ll dfs2(ll v, ll l, ll r, ll ql, ll qr, ll u) {
    if (ql <= l && r <= qr) {
        return dist(v, u);
    }
    
    if (ql >= r || qr <= l) {
        return 0;
    }

    return dfs2(lc[v], l, dx[v], ql, qr, u) + dfs2(rc[v], dx[v], r, ql, qr, u);
}

void solve() {
    ll n;
    cin >> n;

    dx.resize(n - 1);
    bup.resize(4*n, vector<ll>(lgn));
    rc.resize(4*n);
    lc.resize(4*n);
    tout.resize(4*n);
    for (ll &i: dx) cin >> i;

    dfs0(0, n);


    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll l, r, v;
        cin >> l >> r >> v;

        cout << dfs2(0, 0, n, l - 1, r, v - 1) << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
