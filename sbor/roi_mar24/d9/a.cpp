// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll M = 1e9 + 7;

ll mod(ll x) {
    return x % M;
}

vector<vector<ll>> g;
ll n, c;

ll ans = 1;

ll C2(ll n, ll k) {
    ll res = 1;
    for (ll i = 0; i < k; i++) {
        res = mod(res * (n - i));
    }
    return res;
}

void dfs(ll v, ll p, ll d) {
    ans = mod(ans * C2(c - d, ll(g[v].size()) - 1 + (v == 0)));

    for (ll u: g[v]) {
        if (u == p) continue;
        dfs(u, v, 2);
    }
}

void solve() {
    cin >> n >> c;

    g.resize(n);
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ans = mod(c);

    dfs(0, 0, 1);

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
