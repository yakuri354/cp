// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

struct edge {
    ll a, b, c, i;

    bool operator<(const edge &other) const {
        return make_tuple(a, c, b, i) < make_tuple(other.a, other.c, other.b, other.i);
    }
};

vector<map<ll, vector<edge>>> g, g2;
vector<edge> stack;
vector<unordered_map<ll, ll>> out_colors;

ll dfs2(ll v, ll c, ll init) {
    if (v == init && stack.size() > 0 && c != stack[0].c) {
        return v;
    }

    for (auto &[e_c, es]: g[v]) {
        if (e_c == c) continue;

        while (!es.empty()) {
            edge e = es.back();
            es.pop_back();

            stack.push_back(e);
            ll x = dfs2(e.b, e_c, init);
            if (x != -1) {
                return x;
            }
            stack.pop_back();
        }
    }

    return -1;
}

ll dfs(ll v, ll c) {
    if ((out_colors[v].size() == 1 && out_colors[v].begin()->first != c) || out_colors[v].size() > 1) {
        return v;
    }

    for (auto &[e_c, es]: g[v]) {
        if (e_c == c) continue;

        while (!es.empty()) {
            edge e = es.back();
            es.pop_back();

            out_colors[v][e_c]++;
            ll x = dfs(e.b, e_c);
            if (x != -1) {
                return x;
            }
            out_colors[v][e_c]--;
            if (out_colors[v][e_c] == 0) out_colors[v].erase(e_c);
        }
    }

    return -1;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    g.assign(n, {});

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;

        g[a][c].push_back({a, b, c, i});
    }
    
    g2 = g;

    ll ans = -1;
    for (ll i = 0; i < n; i++) {
        out_colors.assign(n, {});
        if (dfs(i, -1) != -1) {
            ans = i;
            break;
        }
    }

    if (ans == -1) {
        cout << "-1\n";
        return;
    }

    g = g2;

    stack.clear();
    dfs2(ans, -1, ans);

    cout << stack.size() << '\n';
    for (edge e : stack) {
        cout << e.i + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
