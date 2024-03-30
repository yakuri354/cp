#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <queue>
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

const ll inf = 1e10;

const ll mthrough = 200;
const ll maxn = 1e5 + 1;

int dists[mthrough][maxn];

vector<vector<ll>> g;
ll n, m, q;

vector<ll> bfs(ll s) {
    vector<ll> d(n, inf);
    queue<ll> q;

    q.push(s);
    d[s] = 0;

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto u: g[v]) {
            if (d[u] == inf) {
                d[u] = d[v] + 1;
                q.push(u);
            }
        }
    }

    return d;
}

void solve() {
    cin >> n >> m >> q;

    ll through = min(mthrough, n);

    g.resize(n);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    mt19937_64 mt(0xab0ba);

    vector<ll> sel(n);
    iota(sel.begin(), sel.end(), 0);
    shuffle(sel.begin(), sel.end(), mt);

    for (ll i = 0; i < through; i++) {
        auto d1 = bfs(sel[i]);
        copy(d1.begin(), d1.end(), dists[i]);
    }

    for (ll i = 0; i < q; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        int ans = 1 << 30;
        for (ll j = 0; j < through; j++) {
            ans = min(ans, dists[j][u] + dists[j][v]);
        }

        cout << ans << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

