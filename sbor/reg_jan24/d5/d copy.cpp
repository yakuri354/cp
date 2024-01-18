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

struct edge {
    ll v;
    char ch;
};

vector<ll> topo;
vector<vector<edge>> g1;

pair<vector<ll>, vector<ll>> skuf(string &s) {
    ll n = s.size();

    vector<ll> cls(n);
    for (ll i = 0; i < n; i++) {
        cls[i] = s[i];
    }

    for (ll l = 1; l < n * 2; l *= 2) {
        vector<pair<ll, ll>> z;
        for (ll i = 0; i < n; i++) {
            z.push_back({cls[i] * 1000000000ll + cls[(i + l) % n], i});
        }

        sort(z.begin(), z.end());

        ll c = 0;
        cls[z[0].second] = 0;
        for (ll i = 1; i < n; i++) {
            if (z[i].first != z[i - 1].first) {
                c++;
            }
            cls[z[i].second] = c;
        }
    }

    vector<ll> p(n);
    for (ll i = 0; i < n; i++) {
        p[cls[i]] = i;
    }

    return {p, cls};
}

string bmbs;

void dfs_bambuk(ll v, ll p) {
    for (edge e: g1[v]) {
        if (e.v == p) continue;
        bmbs.push_back(e.ch);
        dfs_bambuk(e.v, v);
    }
}

vector<ll> max_ed;
vector<bool> used;

void dfs_dist_dag(ll v) {
    if (used[v]) return;
    used[v] = true;

    max_ed[v] = 0;

    for (edge e: g1[v]) {
        dfs_dist_dag(e.v);
        max_ed[v] = max(max_ed[v], max_ed[e.v] + 1);
    }
}


string lex_res, lex_res2;

void lex_min_end(ll v) {
    if (used[v]) return;
    used[v] = true;

    if (max_ed[v] == 0 && lex_res < lex_res2) {
        lex_res2 = lex_res;
    }

    for (edge e: g1[v]) {
        if (e.ch != g1[v][0].ch || max_ed[e.v] != max_ed[v] - 1 || used[e.v]) continue;

        lex_res.push_back(e.ch);
        lex_min_end(e.v);
        lex_res.pop_back();
    }
}

vector<string> min_out;

string bg_stack;

string ans;

void lex_min_begin(ll v) {
    if (used[v]) return;
    used[v] = true;

    if (bg_stack + min_out[v] < ans) {
        ans = bg_stack + min_out[v];
    }

    if (min_out[v] + bg_stack < ans) {
        ans = min_out[v] + bg_stack;
    }

    for (edge e: g1[v]) {
        if (max_ed[e.v] != max_ed[v] - 1 || used[e.v]) continue;

        bg_stack.push_back(e.ch);
        lex_min_begin(e.v);
        bg_stack.pop_back();
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;

    g1.resize(n);

    for (ll i = 0; i < m; i++) {
        ll a, b;
        string c;
        cin >> a >> b >> c;
        a--, b--;

        g1[a].push_back({b, c[0]});
        // g1[b].push_back({a, c[0]});
    }

    for (ll v = 0; v < n; v++) {
        sort(g1[v].begin(), g1[v].end(), [](edge a, edge b) {
            return a.ch < b.ch;
        });
    }

    if (m == n - 1) {
        ll maj = 0;
        for (ll i = 0; i < n; i++) {
            maj = max(maj, ll(g1[i].size()));
        }

        if (maj <= 2) {
            // bamboo

            dfs_bambuk(0, -1);

            auto [p, cls] = skuf(bmbs);

            rotate(bmbs.begin(), bmbs.begin() + p[0], bmbs.end());

            cout << bmbs << endl;

            return;
        }
    }

    max_ed.assign(n, 0);
    used.assign(n, false);
    dfs_dist_dag(0);

    string kal(1, 'z' + 1);
    min_out.resize(n);
    for (ll v = 0; v < n; v++) {
        lex_res = "";
        lex_res2 = kal;

        used.assign(n, false);
        lex_min_end(v);

        min_out[v] = lex_res2;
    }

    ans = kal;

    used.assign(n, false);
    lex_min_begin(0);

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

