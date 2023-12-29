// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <atomic>
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

const ll inf = 1ll << 50;

vector<vector<pair<ll, ll>>> g;
ll n, m;
vector<ll> state;

vector<ll> dji(ll s) {
    vector<ll> d(n, inf);
    set<pair<ll, ll>> q;

    q.insert({0, s});
    d[s] = 0;

    while (!q.empty()) {
        auto [dv, v] = *q.begin();
        q.erase(q.begin());

        for (auto [u, w]: g[v]) {
            if (d[u] > dv + w) {
                q.erase({d[u], u});
                d[u] = dv + w;
                q.insert({d[u], u});
            }
        }
    }

    return d;
}

vector<bool> used;

bool dfs(ll v, ll col) {
    if (state[v] == 0) return true;
    if (state[v] != col) return false;
    if (used[v]) return true;
    used[v] = true;

    ll ans = true;
    for (auto [u, w]: g[v]) {
        ans &= dfs(u, col);
        if (!ans) break;
    }
    return ans;
}

void solve() {
    cin >> n >> m;

    g.resize(n);
    state.resize(n);

    for (ll i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;

        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }

    ll a, b;
    cin >> a >> b;
    a--, b--;

    auto d1 = dji(a), d2 = dji(b);

    for (ll i = 0; i < n; i++) {
        if (d1[i] == d2[i]) {
            state[i] = 0;
        } else if (d1[i] < d2[i]) {
            state[i] = 1;
        } else {
            state[i] = 2;
        }
    }

    used.resize(n);
    bool res = dfs(a, 1);
    used.resize(n);
    res &= dfs(b, 2);

    if (res) {
        for (ll i = 0; i < n; i++) { 
            cout << state[i] << ' ';
        }
    } else {
        cout << -1;
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

