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

const ll inf = 1ll << 40;

struct lis_state {
    ll n, l = 0;
    vector<ll> d;
    vector<tuple<ll, ll, bool>> stack;

    lis_state(ll n): n(n), d(n, inf) {
        d[0] = -inf;
    }
    
    void add(ll x) {
        ll p = lower_bound(d.begin(), d.end(), x) - d.begin();
        stack.push_back({p, d[p], p > l});
        d[p] = x;
        if (p > l) l++;
    }

    void pop() {
        if (stack.empty()) return;

        auto [p, x, t] = stack.back();
        stack.pop_back();

        d[p] = x;
        if (t) l--;
    }
};

vector<ll> a;
vector<ll> res;
vector<vector<ll>> g;

void dfs(ll v, ll p, lis_state &s) {
    s.add(a[v]);
    res[v] = s.l;

    for (ll u: g[v]) {
        if (p == u) continue;
        dfs(u, v, s);
    }

    s.pop();
}

void solve() {
    ll n;
    cin >> n;

    a.resize(n);
    res.resize(n);
    g.resize(n);

    for (ll &x: a) cin >> x;

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    lis_state s(n);
    dfs(0, -1, s);

    for (ll i = 0; i < n; i++) {
        cout << res[i] << '\n';
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

