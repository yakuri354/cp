// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll logn = __lg(maxn) + 1;

ll up[maxn][logn + 1], tin[maxn], tout[maxn], uebok, sum[maxn], z[maxn];
vector<ll> adj[maxn];

void dfs(ll v) {
    for (ll l = 1; l <= logn; l++) {
        up[v][l] = up[up[v][l-1]][l-1];
    }

    tin[v] = uebok++;
    sum[v] = sum[up[v][0]] + z[v];

    for (ll u : adj[v]) {
        if (u == up[v][0]) continue;
        up[u][0] = v;
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

    for (ll i = 0; i < n; i++) {
        cin >> z[i];
    }

    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;

        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    ll m;

    cin >> m;

    dfs(0);

    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        x--, y--;

        ll anc = lca(x, y);

        cout << sum[x] + sum[y] - 2 * sum[anc] + z[anc] << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
