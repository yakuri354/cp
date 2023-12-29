// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> adj;
vector<vector<ll>> rev_adj;
vector<set<ll>> comp_adj;
vector<vector<ll>> comps;
vector<ll> comp;
vector<bool> used;
vector<ll> topo;

void dfs1(ll v) {
    if (used[v]) return;
    used[v] = true;

    for (ll u : adj[v]) {
        dfs1(u);
    }

    topo.push_back(v);
}

void dfs2(ll v, ll c) {
    if (comp[v] != -1) return;
    comp[v] = c;
    comps[c].push_back(v);

    for (ll u : rev_adj[v]) {
        dfs2(u, c);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    adj.assign(n, {});
    rev_adj.assign(n, {});
    comp.assign(n, -1);
    comps.assign(n, {});
    used.assign(n, false);

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;

        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    for (ll i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    ll c = 0;
    reverse(topo.begin(), topo.end());
    for (ll i : topo) {
        if (comp[i] == -1) {
            dfs2(i, c++);
        }
    }

    comp_adj.assign(c, {});
    for (ll i = 0; i < c; i++) {
        for (ll j : comps[i]) {
            for (ll v : adj[j]) {
                if (comp[v] != i)
                    comp_adj[i].insert(comp[v]);
            }
        }
    }

    ll ans = 0;
    for (auto &i : comp_adj) {
        ans += i.size();
    }
    // cout << ans << endl;
    cout << c << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
