// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll maxm = 3 * 1e5;

ll lead[maxn];
ll sz[maxn];

struct edge {
    ll u, v, w;
    
    bool operator<(const edge &other) {
        return this->w < other.w;
    }
};

vector<vector<ll>> mst;
edge el[maxm];

ll ldr(ll v) {
    return (lead[v] == v) ? v : lead[v] = ldr(v);
}

void unite(ll a, ll b) {
    a = ldr(a), b = ldr(b);
    if (sz[a] > sz[b]) swap(a, b);
    sz[b] += sz[a];
    lead[a] = b;
}

void solve() {
    ll n, m, x;
    cin >> n >> m >> x;

    edge tgt = {-1, -1, -1};

    for (ll i = 0; i < m; i++) {
        cin >> el[i].u >> el[i].v >> el[i].w;
        el[i].u--;
        el[i].v--;
        if ()
    }

    sort(el, el + m);

    for (ll i = 0; i < m; i++) {
        if (ldr(el[i].u) != ldr(el[i].v)) {
            mst[el[i].u].push_back(el[i].v);
            mst[el[i].v].push_back(el[i].u);
            unite(el[i].u, el[i].v);
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
