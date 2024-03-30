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

// struct edge {
//     ll v, l;
// };

// struct path_body {
//     ll base, cyc;
// };

vector<vector<pll>> g;
vector<ll> p;
vector<bool> is_file;

vector<set<pll>> heads;
vector<ll> dist;

vector<ll> tin, tout;

ll timer = 0;
ll n, m, k, s;

void dfs_time(ll v, ll p) {
    tin[v] = timer++;

    for (auto [u, l] : g[v]) {
        if (u == p)
            continue;
        dfs_time(u, v);
    }

    tout[v] = timer;
}

bool is_ancestor(ll par, ll child) {
    return tin[par] <= tin[child] && tout[child] <= tout[par];
}

void dfs_children(ll v, ll p, ll dist_root, ll dist_from, ll from) {
    if (is_file[v])
        return;  // todo

    if (dist_root + s <= k) {
        heads[from].erase({dist_root + s, 0});
        heads[from].insert({dist_root + s, dist_from + s});
    }

    for (auto [u, l] : g[v]) {
        if (u == p)
            continue;
        dfs_children(u, v, dist_root + l, dist_from + l, from);
    }
}

void dfs_dir(ll v, ll p, ll pl, ll dist_rt) {
    heads[v].insert({dist_rt, 0});
    if (p != -1) {
        for (auto [base, cyc] : heads[p]) {
            if (base + pl <= k)
                heads[v].insert({base + pl, cyc});
        }
    }

    if (is_file[v]) return;  // todo

    for (ll i = 0; i < n; i++) {
        if (dist[i] + s <= k && !is_file[i])
            heads[v].insert({dist[i] + s, 0});
    }

    if (dist_rt + s <= k) {
        heads[v].erase({dist_rt + s, 0});
        heads[v].insert({dist_rt + s, s});
    }

    for (auto [u, l]: g[v]) {
        if (u == p) continue;

        dfs_children(u, v, dist_rt + l, dist_rt, v);
    }

    for (auto [u, l]: g[v]) {
        if (u == p) continue;

        dfs_dir(u, v, l, dist_rt + l);
    }
}

void dfs_dist(ll v, ll p, ll d) {
    dist[v] = d;

    for (auto [u, l]: g[v]) {
        if (u == p) continue;

        dfs_dist(u, v, d + l);
    }
}

bool check(ll v) {
    for (auto [base, cyc]: heads[v]) {
        if ((base == k) || (base < k && cyc != 0 && (k - base) % cyc == 0)) {
            return true;
        }
    }

    return false;
}

void solve() {
    cin >> n >> m >> k >> s;
    s += 1;  // sus
    k += 1;

    g.resize(n + m + 1);
    tin.resize(n + m + 1);
    tout.resize(n + m + 1);
    p.resize(n + m + 1);
    is_file.resize(n + m + 1, false);
    dist.resize(n + m + 1);
    heads.resize(n + m + 1);

    for (ll i = 0; i < n; i++) {
        ll par, l;
        cin >> par >> l;
        g[par].push_back({i + 1, l + 1});
        p[i + 1] = par;
    }

    for (ll i = 0; i < m; i++) {
        ll par, l;
        cin >> par >> l;
        g[par].push_back({i + n + 1, l + 1});
        p[i + n + 1] = par;

        is_file[i + n + 1] = true;
    }

    n += m + 1;

    dfs_dist(0, -1, 1);
    dfs_time(0, -1);

    dfs_dir(0, -1, 1, 1);

    for (ll i = 0; i < n; i++) {
        if (!is_file[i]) continue;
        if (check(i)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
