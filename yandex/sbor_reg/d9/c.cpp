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
#include <queue>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 5e5 + 1;
const ll inf = 1ll << 40;

vector<ll> g[maxn];
ll dist[maxn], p0[maxn], p1[maxn];

vector<bool> used;

const ll M = 1e9 + 7;

ll mod(ll x) {
    return x % M;
}

void dfs(ll v) {
    if (used[v]) return;
    used[v] = true;
    p0[v] = 0;
    p1[v] = 0;

    // direct
    for (ll u: g[v]) {
        if (dist[u] != dist[v] - 1) continue;
        if (!used[u]) dfs(u);

        p0[v] = mod(p0[v] + p0[u]);
        p1[v] = mod(p1[v] + p1[u]);
    }

    // shit
    for (ll u: g[v]) {
        if (dist[u] != dist[v]) continue;
        if (!used[u]) dfs(u);

        p1[v] = mod(p0[u] + p1[v]);
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    queue<ll> q;
    for (ll i = 1; i < n; i++) dist[i] = inf;
    q.push(0);
    
    while (!q.empty()) {
        ll v = q.front();
        q.pop();

        for (ll u: g[v]) {
            if (dist[u] == inf) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }

    p0[0] = 1;
    used.assign(n, false);
    used[0] = true;

    for (ll i = 1; i < n; i++) {
        if (!used[i]) dfs(i);
    }

    for (ll i = 0; i < n; i++) {
        cout << mod(p1[i] + p0[i]) << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

