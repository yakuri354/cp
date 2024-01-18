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
        g1[b].push_back({a, c[0]});
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

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

