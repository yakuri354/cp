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
#include <fstream>

using namespace std;

#ifndef DBG
#define cerr if (0) cerr
#endif

using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll lgn = 25;

vector<ll> val, c1, c2;
vector<vector<ll>> g;
vector<vector<ll>> bup;
vector<ll> tin, tout;

ll timer = 0;

void dfs_calc(ll v, ll par) {
    tin[v] = timer++;
    c1[v] = c1[par] + (val[v] == 1);
    c2[v] = c2[par] + (val[v] == 2);

    bup[v][0] = par;
    for (ll i = 1; i < lgn; i++) {
        bup[v][i] = bup[bup[v][i-1]][i-1];
    }

    for (ll u: g[v]) {
        if (u == par) continue;
        dfs_calc(u, v);
    }
    tout[v] = timer;
}

bool ancestor_or_same(ll a, ll b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

ll lca(ll a, ll b) {
    if (a == b) return a;
    if (ancestor_or_same(a, b)) return a;
    if (ancestor_or_same(b, a)) return b;

    for (ll i = lgn - 1; i >= 0; i--) {
        if (!ancestor_or_same(bup[a][i], b)) {
            a = bup[a][i];
        }
    }

    return bup[a][0];
}

void solve() {
    ll n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    val.resize(n);

    for (ll i = 0; i < n; i++) {
        val[i] = s[i] == 'H' ? 1 : 2;
    }

    bup.resize(n, vector<ll>(lgn));
    tin.resize(n);
    tout.resize(n);
    g.resize(n);
    c1.resize(n);
    c2.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs_calc(0, 0);

    string ans;

    for (ll i = 0; i < m; i++) {
        ll a, b;
        string _c;
        cin >> a >> b >> _c;
        a--, b--;

        ll c = _c == "H" ? 1 : 2;

        ll l = lca(a, b);
        if (l == 0) {
            if (c == 1 && (c1[a] > 0 || c1[b] > 0)) {
                ans.push_back('1');
                continue;
            }
            if (c == 2 && (c2[a] > 0 || c2[b] > 0)) {
                ans.push_back('1');
                continue;
            }

            ans.push_back('0');
        } else {
            ll v = c == 1 ? c1[a] + c1[b] - 2 * c1[bup[l][0]] : c2[a] + c2[b] - 2 * c2[bup[l][0]];
            ans.push_back('0' + min(v, 1ll));
        }
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

