// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct poly {
    ll lx, ly, rx, ry;

    bool x(const poly &other) const {
        return max(other.lx, lx) <= min(other.rx, rx) && max(other.ly, ly) <= min(other.ry, ry);
    }
};

vector<vector<ll>> graph;
ll n, maxx, maxy;

void dfs(ll v, ll l, ll r, vector<bool> &used) {
    if (used[v]) return;
    used[v] = true;

    for (ll u : graph[v]) {
        if ((l <= u && u <= r) || u >= n) {
            dfs(u, l, r, used);
        }
    }
}

void solve() {
    cin >> n >> maxx >> maxy;

    vector<poly> ps(n);
    graph.resize(n + 2);

    for (ll i = 0; i < n; i++) {
        cin >> ps[i].lx >> ps[i].ly >> ps[i].rx >> ps[i].ry;
    }

    ps.push_back({0, 0, 0, maxy});
    ps.push_back({maxx, 0, maxx, maxy});

    for (ll i = 0; i < n + 2; i++) {
        for (ll j = 0; j < n + 2; j++) {
            if (i == j) continue;

            if (ps[i].x(ps[j])) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    auto ans = make_pair(0ll, inf);
    for (ll i = 0; i < n; i++) {
        for (ll j = i; j < n; j++) {
            if (j - i > ans.second - ans.first) break;
            vector<bool> used(n+2);
            dfs(n, i, j, used);
            if (used[n+1]) {
                if (j - i < ans.second - ans.first) {
                    ans = {i, j};
                } else if (j - i == ans.second - ans.first) {
                    ans = min(ans, {i, j});
                }
            }
        }
    }

    if (ans.second == inf) {
        cout << "-1" << endl;
    } else {
        cout << get<0>(ans) + 1 << ' ' << get<1>(ans) + 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

