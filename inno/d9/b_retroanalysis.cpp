// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <system_error>
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

const ll inf = INT32_MAX;

enum class st {
    draw = 0,
    win = 1,
    lose = 2,
};

vector<vector<ll>> g_or, g;
vector<ll> win_cnt;
vector<st> state;
vector<bool> used;
ll n, m;

void dfs(ll v) {
    used[v] = true;

    for (ll u : g[v]) {
        if (used[u]) continue;

        if (state[v] == st::lose) state[u] = st::win;
        else if (state[v] == st::win && ++win_cnt[u] >= g_or[u].size()) state[u] = st::lose;
        else continue;

        dfs(u);
    }
}

void solve() {
    if (!(cin >> n >> m)) exit(0);
    
    g.assign(n, {});
    g_or.assign(n, {});
    win_cnt.assign(n, 0);
    state.assign(n, st::draw);
    used.assign(n, false);

    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        
        g_or[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
    }
    
    for (ll i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());

        sort(g_or[i].begin(), g_or[i].end());
        g_or[i].erase(unique(g_or[i].begin(), g_or[i].end()), g_or[i].end());
    }
    
    for (ll i = 0; i < n; i++) {
        if (g_or[i].size() == 0) {
            state[i] = st::lose;
            dfs(i);
        }
    }
        
    for (ll i = 0; i < n; i++) {
        if (state[i] == st::draw) {
            cout << "DRAW";
        } else if (state[i] == st::win) {
            cout << "FIRST";
        } else if (state[i] == st::lose) {
            cout << "SECOND";
        }

        cout << '\n';
    }

    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    while (true) solve();
}
