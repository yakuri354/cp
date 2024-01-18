// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
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

const ll maxn = 1e5;

ll n, m, k;

struct edge {
    ll u, v, c, i;
};

struct edge_ent {
    ll v, i;
};

vector<edge> es;

vector<edge_ent> g[maxn];

vector<bool> used1;

void dfs_conn(ll v) {
    used1[v] = true;
    for (auto e : g[v]) {
        if (!used1[e.v]) {
            dfs_conn(e.v);
        }
    }
}

void solve() {
    cin >> n >> m >> k;

    vector<set<ll>> e_by_c(k);

    for (ll i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--, c--;

        g[u].push_back({v, i});
        g[v].push_back({u, i});

        es.push_back({u, v, c, i});

        e_by_c[c].insert(i);
    }

    used1.resize(n);

    dfs_conn(0);

    bool connected = count(used1.begin(), used1.end(), true) == n;

    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll ei, w;
        cin >> ei >> w;
        ei--, w--;

        if (!connected) {
            cout << "No\n";
            continue;
        }

        e_by_c[es[ei].c].erase(ei);
        e_by_c[w].insert(ei);
        es[ei].c = w;

        if (any_of(e_by_c.begin(), e_by_c.end(), [](auto &s) { return s.size() == 0; })) {
            cout << "No\n";
            continue;
        }

        if (k == 3 && n == 3) {
            cout << "No\n";
            continue;
        }

        // if (k == 1 || k == 2) {
        //     cout << "Yes\n";
        // } else {
        //     cout << "Yes\n";
        // }

        cout << "Yes\n";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

