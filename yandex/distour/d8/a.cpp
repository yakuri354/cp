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
#include <optional>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1ll << 55;

struct bounds {
    ll lo, hi;

    bounds operator*(const bounds &o) const {
        return {max(lo, o.lo), min(hi, o.hi)};
    }

    bounds operator+(const bounds &o) const {
        return {lo + o.lo, hi + o.hi};
    }

    bounds operator-(const bounds &o) const {
        return {lo - o.lo, hi - o.hi};
    }

    bool ok() const {
        return lo <= hi;
    }

    bool operator==(const bounds &o) const {
        return lo == o.lo && hi == o.hi;
    }
};

const bounds inf_bounds = {-inf, inf};
const bounds shit_bounds = {inf, -inf};

vector<bounds> arr;
vector<bounds> dp, dp2;
vector<vector<ll>> graph;

bounds dfs1_nodp(ll v, ll p) {
    bounds curr = inf_bounds;

    for (ll u : graph[v]) {
        if (u == p) continue;

        auto nxt = dfs1_nodp(u, v);
        if (nxt == inf_bounds) nxt = {0, 0};
        nxt = nxt + arr[u];

        curr = curr * nxt;
        if (!curr.ok()) {
            return shit_bounds;
        }
    }

    if (!curr.ok()) return shit_bounds;

    return curr;
}

void dfs1(ll v, ll p) {
    bounds curr = inf_bounds;

    dp[v] = shit_bounds;
    dp2[v] = inf_bounds;

    for (ll u : graph[v]) {
        if (u == p) continue;

        dfs1(u, v);
    }

    for (ll u : graph[v]) {
        if (u == p) continue;

        curr = curr * dp[u];
        if (!dp[u].ok() || !curr.ok()) {
            dp2[v] = shit_bounds;
            dp[v] = shit_bounds;
            return;
        }
    }

    dp2[v] = curr;

    if (curr == inf_bounds) {
        curr = {0, 0};
    }

    curr = curr + arr[v];

    dp[v] = curr;
}

vector<bool> ans;

void dfs2(ll v, ll p, bounds up) {
    if (!dp2[v].ok() || !up.ok()) return;
    // sus 

    


    auto up2 = p == -1 ? inf_bounds : (dfs1_nodp(p, v) + arr[p]);
    auto down = dfs1_nodp(v, p);
 
    // shit
    ans[v] = down.ok() && (up2 * down).ok();




    //up = p == -1 ? inf_bounds : dfs1_nodp(p, v);
    // ans[v] = (up * dp2[v]).ok();
    //auto down = dfs1_nodp(v, p);
    //auto down = dp2[v];

    //ans[v] = (down * up).ok();
    
    vector<bounds> suff(graph[v].size());
    {
        auto curr = inf_bounds;

        for (ll i = graph[v].size() - 1; i >= 0; i--) {
            suff[i] = curr;
            if (graph[v][i] == p) continue;
            curr = curr * dp[graph[v][i]];
        }
    }

    auto pref = inf_bounds;
    for (ll i = 0; i < graph[v].size(); i++) {
        ll u = graph[v][i];
        if (u == p) continue;

        if (!suff[i].ok()) continue;

        bounds nxt = up * pref * suff[i] + arr[v];
        dfs2(u, v, nxt);

        pref = pref * dp[u];
        if (!pref.ok()) break;
    }
}

void dumb_dfs1(ll v, ll p, bounds up) {
    auto down = dp2[v];

    if (p != -1) {
        up = up + arr[p];
    }
 
    ans[v] = down.ok() && (up * down).ok();
 
    for (ll u : graph[v]) {
        if (u == p) continue;

        bounds kal = up;

        for (ll z : graph[v]) {
            if (z == u || z == p) continue;

            auto nxt = dp2[z];
            if (nxt == inf_bounds) nxt = {0, 0};
            nxt = nxt + arr[z];

            kal = kal * nxt;
            if (!kal.ok()) {
                kal = shit_bounds;
                break;
            }
        }
 
        dumb_dfs1(u, v, kal);
    }
}

void solve() {
    ll n;
    cin >> n;

    arr.resize(n);
    graph.resize(n);
    ans.resize(n);
    dp.resize(n, shit_bounds);
    dp2.resize(n, shit_bounds);

    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (ll i = 0; i < n; i++) {
        cin >> arr[i].lo >> arr[i].hi;
    }

    dfs1(0, -1);
    //dfs2(0, -1, inf_bounds);
    // dumb_dfs3(0, 1, inf_bounds);
    dumb_dfs1(0, -1, inf_bounds);

    for (bool x: ans) {
        cout << x << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

