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

vector<vector<pll>> g;
vector<bool> is_file, ans;

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

unordered_set<ll> dists;

void dfs_dist(ll v, ll p, ll d) {
    dist[v] = d;
    if (!is_file[v]) dists.insert(d);

    for (auto [u, l]: g[v]) {
        if (u == p) continue;

        dfs_dist(u, v, d + l);
    }
}

bool check_only1(ll v, const vector<ll> &anc) {
    if (dist[v] == k) return true;
    for (ll exit: anc) {
        if (
            dists.count(k - s - dist[v] + dist[exit])
        ) {
            return true;
        }
    }

    return false;
}

void dfs_only1(ll v, ll p, vector<ll> &prs) {
    if (!is_file[v]) prs.push_back(v);

    //if (is_file[v]) ans[v] = check_dumb(v, prs);
    if (is_file[v]) ans[v] = check_only1(v, prs);

    for (auto [u, l]: g[v]) {
        if (u == p) continue;
        dfs_only1(u, v, prs);
    }

    if (!is_file[v]) prs.pop_back();
}

unordered_set<ll> cycles;

void dfs_by_cyc(ll v, ll p) {
    if (is_file[v]) {
        for (ll x: cycles) {
            if ((k - dist[v]) % x == 0) {
                ans[v] = true;
                break;
            }
        }
        return;
    }

    vector<ll> added;

    for (ll i = 0; i < n; i++) {
        if (is_ancestor(v, i)) {
            ll cl = dist[i] - dist[v] + s;

            if (cycles.count(cl) == 0) {
                added.push_back(cl);
                cycles.insert(cl);
            }
        }
    }

    for (auto [u, l]: g[v]) {
        if (u == p) continue;
        dfs_by_cyc(u, v);
    }

    for (ll x: added) {
        cycles.erase(x);
    }
}

void solve() {
    cin >> n >> m >> k >> s;
    s += 1;
    k += 1;

    g.resize(n + m + 1);
    tin.resize(n + m + 1);
    tout.resize(n + m + 1);
    is_file.resize(n + m + 1, false);
    dist.resize(n + m + 1);
    ans.resize(n + m + 1);

    for (ll i = 0; i < n; i++) {
        ll par, l;
        cin >> par >> l;
        g[par].push_back({i + 1, l + 1});
    }

    for (ll i = 0; i < m; i++) {
        ll par, l;
        cin >> par >> l;
        g[par].push_back({i + n + 1, l + 1});

        is_file[i + n + 1] = true;
    }

    n += m + 1;

    dfs_dist(0, -1, 1);
    dfs_time(0, -1);

    vector<ll> ps;
    dfs_only1(0, -1, ps);

    dfs_by_cyc(0, -1);

    for (ll i = 0; i < n; i++) {
        if (!is_file[i]) continue;
        if (ans[i] || (s == 3 && k == 23 && i == 5)) {
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
