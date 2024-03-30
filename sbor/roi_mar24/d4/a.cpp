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

struct edge {
    ll u, w;
};

vector<vector<edge>> g, gT;

const ll inf = 1e17;

ll n, m;

vector<ll> dijkstra(ll s, const vector<vector<edge>> &g) {
    vector<ll> d(n, inf);
    d[s] = 0;

    set<pll> q;
    q.insert({0, s});

    while (!q.empty()) {
        auto [d1, v1] = *q.begin();
        q.erase(q.begin());

        if (d1 > d[v1]) continue;

        for (auto [u, w]: g[v1]) {
            if (d[u] > d[v1] + w) {
                if (d[u] != inf) {
                    q.erase({d[u], u});
                }
                d[u] = d[v1] + w;
                q.insert({d[u], u});
            }
        }
    }

    return d;
}

void solve() {
    ll s, t, d, k;
    cin >> n >> m >> s >> t >> d >> k;
    s--, t--;

    g.resize(n);
    gT.resize(n);
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    auto ds = dijkstra(s, g);
    auto dt = dijkstra(t, g);   

    if (ds[t] != dt[s]) exit(-1);

    vector<ll> t_ord(n);
    iota(t_ord.begin(), t_ord.end(), 0);

    sort(t_ord.begin(), t_ord.end(), [&](ll a, ll b) {
        return dt[a] < dt[b];
    });

    if (dt[s] <= k) {
        cout << (n * (n - 1)) / 2 << endl;
        return;
    }

    // from s
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        auto it = upper_bound(t_ord.begin(), t_ord.end(), 0, [&](ll _, ll v) {
            return ds[i] + dt[v] + d > k;
        });

        ans += it - t_ord.begin();
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

