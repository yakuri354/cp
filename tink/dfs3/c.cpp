// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll logn = __lg(maxn) + 1;

ll up[maxn][logn + 1], ss[maxn][logn + 1], tin[maxn], tout[maxn], uebok, z[maxn];
vector<pair<ll, ll>> adj[maxn];

void dfs(ll v) {
    for (ll l = 1; l <= logn; l++) {
        up[v][l] = up[up[v][l-1]][l-1];
        ss[v][l] = min(ss[v][l-1], ss[up[v][l-1]][l-1]);
    }

    tin[v] = uebok++;

    for (auto [u, w] : adj[v]) {
        if (u == up[v][0]) continue;
        up[u][0] = v;
        ss[u][0] = w;
        dfs(u);
    }

    tout[v] = uebok;
}

bool ispar(ll p, ll c) {
    return tin[c] >= tin[p] && tout[c] <= tout[p];
}

ll lca(ll a, ll b) {
    if (ispar(a, b)) return a;
    if (ispar(b, a)) return b;
    for (ll l = logn; l >= 0; l--) {
        if (!ispar(up[a][l], b)) {
            a = up[a][l];
        }
    }

    return up[a][0];
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n - 1; i++) {
        ll x, y;
        cin >> x >> y;
        x--;
        adj[x].emplace_back(i+1, y);
        adj[i+1].emplace_back(x, y);
    }

    ll m;

    cin >> m;

    ss[0][0] = inf;
    dfs(0);

    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        x--, y--;

        ll anc = lca(x, y);
        ll xs = inf, ys = inf;

        for (ll l = logn; l >= 0; l--) {
            if (!ispar(up[x][l], anc)) {
                xs = min(ss[x][l], xs);
                x = up[x][l];
            }
        }

        if (x != anc) xs = min(ss[x][0], xs);

        for (ll l = logn; l >= 0; l--) {
            if (!ispar(up[y][l], anc)) {
                ys = min(ys, ss[y][l]);
                y = up[y][l];
            }
        }

        if (y != anc) ys = min(ss[y][0], ys);

        cout << min(xs, ys) << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
