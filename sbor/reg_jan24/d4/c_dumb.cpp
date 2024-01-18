// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iomanip>
#include <iostream>
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

const ll maxn = 1e5 + 1;

struct edge {
    ll v, w;
    bool clean;
};

vector<edge> g[maxn];
vector<bool> deleted;

ll sz[maxn];

void recalc_sz(ll v, ll p) {
    sz[v] = 1;
    for (auto e: g[v]) {
        if (e.v == p || deleted[e.v]) continue;
        recalc_sz(e.v, v);
        sz[v] += sz[e.v];
    }
}

ll find_centroid(ll v, ll S, ll p) {
    for (auto e: g[v]) {
        if (!deleted[e.v] && e.v != p && sz[e.v] > S / 2) return find_centroid(e.v, S, v);
    }
    return v;
}

pair<ll, ll> step_1(ll v, ll p, ll depth) {
    ll paths = 1, sum = depth;
    for (auto e: g[v]) {
        if (deleted[e.v] || e.v == p) continue;

        auto [p1, s1] = step_1(e.v, v, depth + e.w);

        sum += s1;
        paths += p1;
    }

    return {paths, sum};
}

pair<ll, ll> step_2(ll v, ll p, ll depth, ll c_paths, ll c_sum, bool clean) {
    ll paths = 0, sum = 0;

    if (clean) {
        paths += c_paths;
        sum += c_sum + c_paths * depth;
    }

    for (auto e: g[v]) {
        if (deleted[e.v] || e.v == p) continue;

        auto [p1, s1] = step_2(e.v, v, depth + e.w, c_paths, c_sum, clean || e.clean);

        sum += s1;
        paths += p1;
    }

    return {paths, sum};
}

pair<ll, ll> step_3(ll v, ll p, ll depth, ll c_paths, ll c_sum, bool clean) {
    ll paths = 0, sum = 0;

    if (!clean) {
        paths += c_paths;
        sum += c_sum + c_paths * depth;
    }

    for (auto e: g[v]) {
        if (deleted[e.v] || e.v == p) continue;

        auto [p1, s1] = step_3(e.v, v, depth + e.w, c_paths, c_sum, clean || e.clean);

        sum += s1;
        paths += p1;
    }

    return {paths, sum};
}

ll ans_path = 0, ans_sum = 0;

void decompose(ll v) {
    if (deleted[v]) return;
    recalc_sz(v, -1);
    v = find_centroid(v, sz[v], -1);
    deleted[v] = true;

    ll clean_path_sum = 0, clean_path_cnt = 0;
    map<ll, ll> path_sum_c, path_cnt_c;

    // clean0
    for (auto e: g[v]) {
        if (deleted[e.v]) continue;

        auto [p2, s2] = step_2(e.v, v, e.w, 1, 0, e.clean);

        path_sum_c[e.v] = s2;
        path_cnt_c[e.v] = p2;

        clean_path_cnt += p2;
        clean_path_sum += s2;
    }

    ll path_c1 = 0, sum_c1 = 0, path_c2 = 0, sum_c2 = 0;

    // clean2
    for (auto e: g[v]) {
        if (deleted[e.v]) continue;

        auto [p2, s2] = step_2(e.v, v, e.w, clean_path_cnt - path_cnt_c[e.v], clean_path_sum - path_sum_c[e.v], e.clean);

        path_c2 += p2;
        sum_c2 += s2;
    }

    // clean1
    for (auto e: g[v]) {
        if (deleted[e.v]) continue;

        auto [p2, s2] = step_3(e.v, v, e.w, clean_path_cnt - path_cnt_c[e.v], clean_path_sum - path_sum_c[e.v], e.clean);

        path_c1 += p2;
        sum_c1 += s2;
    }

    // fixme

    path_c2 /= 2;
    sum_c2 /= 2;

    ans_path += path_c2;
    ans_path += path_c1;

    ans_sum += sum_c2;
    ans_sum += sum_c1;

    auto [pc, sc] = step_2(v, v, 0, 1, 0, false);

    ans_path += pc;
    ans_sum += sc;

    for (auto e: g[v]) {
        if (deleted[e.v]) continue;
        decompose(e.v);
    }
}

void solve() {
    ll n;
    cin >> n;

    deleted.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        ll a, b, w, d;
        cin >> a >> b >> w >> d;
        a--, b--;

        g[a].push_back({b, w, bool(d)});
        g[b].push_back({a, w, bool(d)});
    }

    decompose(0);

    if (ans_path == 0) {
        cout << 0 << endl;
        return;
    }

    cout << fixed << setprecision(10) << fl(ans_sum) / fl(ans_path) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

