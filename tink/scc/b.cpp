// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> tadj;
vector<ll> ldr;
vector<ll> sz;

ll comp;

ll leader(ll v) {
    return (ldr[v] == v) ? v : ldr[v] = leader(ldr[v]);
}

void unite(ll a, ll b) {
    a = leader(a), b = leader(b);
    if (a == b) return;

    if (sz[a] < sz[b]) swap(a, b);

    ldr[b] = a;
    sz[a] += sz[b];
    comp--;
}

void dfs(ll v, ll c) {
    unite(v, c);

    for (ll u : tadj[v]) {
        dfs(u, c);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    comp = n;

    tadj.resize(n);
    ldr.resize(n);
    sz.assign(n, 1);
    iota(ldr.begin(), ldr.end(), 0);

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        tadj[b].push_back(a);
    }

    for (ll i = 0; i < n; i++) {
        dfs(i, i);
    }

    cout << comp << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
