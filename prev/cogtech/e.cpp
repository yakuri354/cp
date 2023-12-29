#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<pair<ll, ll>>> adj;
vector<vector<ll>> binup;
vector<vector<ll>> path_v;
vector<ll> tin;
vector<ll> tout;

ll t = 0;

ll lg;

ll prod(ll a, ll b) {
    if (a * b > ll(1e9)) {
        return ll(1e9) + 1;
    } else {
        return a * b;
    }
}

void dfs(ll v, ll ew, ll p) {
    path_v[v][0] = ew;
    if (p != -1)
        binup[v][0] = p;
    for (ll i = 1; i < lg; i++) {
        binup[v][i] = binup[binup[v][i - 1]][i - 1];
        path_v[v][i] = prod(path_v[v][i - 1], path_v[binup[v][i - 1]][i - 1]);
    }
    for (auto [u, w] : adj[v]) {
        if (u == p)
            continue;
        dfs(u, w, v);
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;

    lg = 22;

    adj.assign(n, {});
    binup.assign(n, vector<ll>(lg));
    path_v.assign(n, vector<ll>(lg));

    for (ll i = 0; i < n - 1; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll root = 0;

    for (ll i = 0; i < lg; i++) {
        binup[root][i] = root;
        path_v[root][i] = 1;
    }

    dfs(root, 1, -1);

    for (ll v1 = 0; v1 < n; v1++) {
        if (v1 == root) continue;
        ll v = v1;
        ll ans = 1;
        ll len = 0;

        for (ll i = lg - 1; i >= 0; i--) {
            if (ans * path_v[v][i] <= k && binup[v][i] != root) {
                len += 1 << i;
                ans *= path_v[v][i];
                v = binup[v][i];
            }
        }

        if (v != root && ans * path_v[v][0] <= k) {
            len += 1;
        }

        cout << len << ' ';
    }

    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t-- > 0)
        solve();
}
