#include <algorithm>
#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

vector<vector<ll>> adj;

ll n, xt, yt;

pair<ll, ll> p[21][21];

#define next(x1, y1) \
    if (x1 <= n && x1 > 0 && y1 <= n && y1 > 0 && \
            p[x1][y1] == make_pair<ll, ll>(0, 0)) { \
        p[x1][y1] = {x, y}; \
        q.emplace(x1, y1, l + 1); \
    }

ll bfs(ll xs, ll ys) {
    queue<tuple<ll, ll, ll>> q;
    q.emplace(xs, ys, 0);

    while (!q.empty()) {
        auto [x, y, l] = q.back();
        q.pop();
        if (x > n || x < 1) continue;
        if (y > n || y < 1) continue;
        if (x == xt && y == yt) return l;
        next(x - 1, y - 2);
        next(x - 1, y + 2);
        next(x - 2, y - 1);
        next(x - 2, y + 1);
        next(x + 1, y - 2);
        next(x + 1, y + 2);
        next(x + 2, y - 1);
        next(x + 2, y + 1);
    }
    return -1;
}

void solve() {
    ll x, y;
    cin >> n >> x >> y >> xt >> yt;
    p[x][y] = {-1, -1};
    bfs(x, y);
    vector<pair<ll, ll>> path;
    while (p[xt][yt].first != -1) {
        path.emplace_back(xt, yt);
        auto zz = p[xt][yt];
        xt = zz.first;
        yt = zz.second;
    }
    cout << path.size() << endl;
    path.emplace_back(xt, yt);
    for (ll i = path.size() - 1; i >= 0; i--) {
        cout << path[i].first << ' ' << path[i].second << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
