#include <cstdint>
#include <queue>
// #ifndef DBG
// #pragma GCC optimize("Ofast")
// #else
// #define _GLIBCXX_DEBUG
// #endif
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

const ll inf = INT32_MAX;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

struct edge {
    ll v;
    ll h;

    bool operator>(edge& a) {
        return this->h > a.h;
    }
};

vector<vector<edge>> adj;
vector<bool> vis;

ll n, m, a, b, bestph = INT64_MIN;

ll dji(ll s, ll e) {
    vector<ll> d(n, -1);
    d[s] = inf;

    priority_queue<pair<ll, ll>> q;
    q.push({inf, s});

    while (!q.empty()) {
        auto [cd, v] = q.top();
        q.pop();

        if (cd < d[v]) continue;

        for (auto &e : adj[v]) {
            if (d[e.v] < min(d[v], e.h)) {
                d[e.v] = min(d[v], e.h);
                q.push({d[e.v], e.v});
            }
        }
    }

    return d[e];
}

void solve() {
    cin >> n >> m;
    n++;
    adj.resize(n);
    vis.resize(n);
    
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    cin >> a >> b;

    cout << dji(a, b) << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
