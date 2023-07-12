// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e4 + 10;

vector<ll> g[maxn], t[maxn];
vector<ll> order;
bool used[maxn];
ll component[maxn];
ll cnt_components = 0;

void dfs1(ll v) {
    used[v] = true;
    for (ll u : g[v]) {
        if (!used[u]) 
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(ll v) {
    component[v] = cnt_components;
    for (ll u : t[v])
        if (component[u] == -1)
            dfs2(u);
}

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        t[v].push_back(u);
    }

    for (ll i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    for (ll i = 0; i < n; i++)
        component[i] = -1;

    reverse(order.begin(), order.end());
    for (ll v : order)
        if (component[v] == -1)
            dfs2(v), cnt_components++;

    if (cnt_components == 1) {
        cout << 0 << endl;
    } else {
        vector<ll> lf(cnt_components, 1);
        vector<ll> src(cnt_components, 1);

        for (ll u = 0; u < n; ++u) {
            for (ll v : g[u]) {
                if (component[u] != component[v]) {
                    lf[component[u]] = 0;
                }
            }
        }

        ll a1 = accumulate(lf.begin(), lf.end(), 0ll);

        for (ll u = 0; u < n; ++u) {
            for (ll v : g[u]) {
                if (component[u] != component[v]) {
                    src[component[v]] = 0;
                }
            }
        }

        ll a2 = accumulate(src.begin(), src.end(), 0ll);

        cout << max(a1, a2) << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
