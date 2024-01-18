// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
#include <iostream>
#include <utility>
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

const ll maxn = 1e5 + 1;
const ll inf = 1ll << 60;
const ll MOD = 1e9 + 7;

#define inv(x) { if (!(x)) exit(-1); }

void wait(ll ms, ull c1) {
    volatile ull x = 0;
    while (fl(clock() - c1) / CLOCKS_PER_SEC < fl(ms) / 1000) x++;
}

void wait(ll ms) {
    auto c1 = clock();
    wait(ms, c1);
}

ll mod(ll x) {
    return ((x % MOD) + MOD) % MOD;
    // if (x >= MOD) exit(-1);
    // return x % MOD;
}

struct edge {
    ll v, d;
};

vector<edge> g[maxn];

ll n, m;

vector<ll> dijkstra(ll s) {
    vector<ll> d(n, inf);

    d[s] = 0;

    set<pair<ll, ll>> q;

    q.insert({0, s});

    while (!q.empty()) {
        auto [dv, v] = *q.begin();
        q.erase(q.begin());

        for (edge e: g[v]) {
            if (dv + e.d < d[e.v]) {
                if (d[e.v] != inf) q.erase({d[e.v], e.v});

                d[e.v] = dv + e.d;
                q.insert({d[e.v], e.v});
            }
        }
    }

    return d;
}

vector<bool> used;
vector<ll> ds, dt;

ll ps[maxn], pt[maxn], D;

void dfs_pt(ll v) {
    if (used[v]) return;
    used[v] = true;

    for (edge e: g[v]) {
        if (ds[v] + dt[e.v] + e.d != D || ds[e.v] < ds[v]) continue;

        dfs_pt(e.v);

        pt[v] = mod(pt[v] + pt[e.v]);
    }
}

void dfs_ps(ll v) {
    if (used[v]) return;
    used[v] = true;

    for (edge e: g[v]) {
        if (dt[v] + ds[e.v] + e.d != D || dt[e.v] < dt[v]) continue;

        dfs_ps(e.v);

        ps[v] = mod(ps[v] + ps[e.v]);
    }
}

ll ans = 0;

void dfs1(ll v) {
    if (used[v]) return;
    used[v] = true;

    if (ds[v] == dt[v]) {
        ll th = mod(ps[v] * pt[v]);
        ans = mod(ans - mod(th * th));
    }

    for (edge e: g[v]) {
        if (ds[v] + dt[e.v] + e.d != D || ds[e.v] < ds[v]) continue;

        inv(ds[v] + e.d == ds[e.v]);

        if (ds[v] * 2 < D && D < 2 * (ds[v] + e.d)) { // bad edge
            ll th = mod(ps[v] * pt[e.v]);
            ans = mod(ans - mod(th * th));
        }

        dfs1(e.v);
    }
}

void solve() {
    cin >> n >> m;

    ll s, t;
    cin >> s >> t;
    s--, t--;

    for (ll i = 0; i < m; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;

        g[a].push_back({b, d});
        g[b].push_back({a, d});
    }

    ds = dijkstra(s);
    dt = dijkstra(t);

    D = ds[t];

    pt[t] = 1;   
    ps[s] = 1;

    used.assign(n, false);
    used[s] = true;

    dfs_ps(t);

    used.assign(n, false);
    used[t] = true;

    dfs_pt(s);

    inv(pt[s] == ps[t]);

    ans = mod(pt[s] * pt[s]);

    used.assign(n, false);

    dfs1(s);

    // ll inv_2 = 500000004ll;

    cout << mod(ans) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

