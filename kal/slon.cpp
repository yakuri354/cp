// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 100000;

vector<vector<pair<ll, ll>>> adj;
ll z[maxn];

void solve() {
    ll n, m;
    cin >> n >> m;
    adj.resize(n);

    for (ll i = 0; i < n; i++) cin >> z[i];

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        adj[a].emplace_back(b, z[a] != z[b]);
        adj[b].emplace_back(a, z[a] != z[b]);
    }

    set<pair<ll, ll>> q;
    vector<ll> d(n, inf);
    vector<ll> p(n, -1);
    d[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [w, u] = *q.begin();
        q.erase(q.begin());
        d[u] = w;

        for (auto [v, w2] : adj[u]) {
            if (d[v] > w + w2) {
                q.erase({d[v], v});
                q.emplace(w + w2, v);
                p[v] = u;
            }
        }
    }

    if (d[n-1] == inf) {
        cout << "impossible" << endl;
        return;
    }

    cout << d[n-1] << ' ';

    vector<ll> path;
    ll xx = n - 1;
    while (xx != -1) {
        path.push_back(xx);
        xx = p[xx];
    }

    reverse(path.begin(), path.end());

    cout << path.size() << endl;

    for (ll x : path) {
        cout << x + 1 << ' ';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
