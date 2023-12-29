// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <mutex>
#include <tuple>
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

const ll maxn = 1e6;

ll parent[maxn];
ll sz[maxn];
ll sum[maxn];
ll a[maxn];

ll leader(ll v) {
    return parent[v] == v ? v : (parent[v] = leader(parent[v]));
}

void unite(ll a, ll b) {
    a = leader(a), b = leader(b);

    if (a == b) return;

    if (sz[a] < sz[b]) swap(a, b);

    parent[b] = a;
    sz[a] += sz[b];
    sum[a] += sum[b];
}

struct edge {
    ll v, u, w, i;

    bool operator<(const edge &other) const {
        return make_tuple(w, i) < make_tuple(other.w, other.i);
    }
};

void solve() {
    ll n, m, test_group;
    cin >> n >> m >> test_group;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        parent[i] = i;
        sz[i] = 1;
    }

    set<edge> el;

    for (ll i = 0; i < m; i++) {
        ll v, u, w;
        cin >> v >> u >> w;
        v--, u--;

        el.insert({v, u, w, i});
    }

    vector<edge> ans;
    for (ll i = 0; i < m; i++) {
        for (auto it = el.begin(); it != el.end(); it++) {
            edge e = *it;
            if (leader(e.u) != leader(e.v) && sum[leader(e.u)] + sum[leader(e.v)] >= e.w) {
                ans.push_back(e);
                unite(e.u, e.v);
                sum[leader(e.u)] -= e.w;
                el.erase(it);
                goto next;
            }
        }

        if (sz[leader(0)] != n) {
            cout << -1 << endl;
            return;
        } else {
            break;
        }

        next:;
    }
    
    cout << ans.size() << endl;

    for (edge e: ans) {
        cout << e.i + 1 << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
