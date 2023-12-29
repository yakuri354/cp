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

vector<vector<ll>> g;
vector<bool> used;
vector<ll> sz;

ll find_centroid(ll v, ll p, ll s) {
    for (ll u: g[v]) {
        if (used[u] || u == p) continue;
        if (sz[u] > s / 2) {
            return find_centroid(u, v, s);
        }
    }

    return v;
}

void sizes(ll v, ll p) {
    sz[v] = 1;
    for (ll u: g[v]) {
        if (u == p || used[u]) continue;
        sizes(u, v);
        sz[v] += sz[u];
    }
}

struct path {
    ll l, v, q;
};

vector<path> ps;

void dfs1(ll v, ll p, ll q, set<) {
    ps.push_back({l, v, q});

    for (ll u: g[v]) {
        if (u == p || used[u]) continue;

        dfs1(u, v, q, l + 1, del);
    }
}

void ctr(ll v) {
    sizes(v, -1);


}

void solve() {

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

