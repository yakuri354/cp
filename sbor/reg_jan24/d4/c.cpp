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

ll find_centroid(ll v, ll S) {
    for (auto e: g[v]) {
        if (!deleted[e.v] && sz[e.v] > S / 2) return find_centroid(e.v, S);
    }
    return v;
}

pair<ll, ll> step_1(ll v, ll p) {
    ll paths = 1, sum = 0;
    for (auto e: g[v]) {
        if (deleted[e.v] || e.v == p) continue;

        auto [p1, s1] = step_1(e.v, v);

        sum += s1 + p1 * e.w;
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

ll ans_path = 0, ans_sum = 0;

void decompose(ll v) {
    if (deleted[v]) return;
    recalc_sz(v, -1);
    v = find_centroid(v, sz[v]);
    deleted[v] = true;

    map<ll, ll> path_sum, path_cnt;
    ll all_path_sum = 0, all_path_cnt = 0;

    for (auto e: g[v]) {
        auto [p1, s1] = step_1(e.v, v);

        s1 += p1 * e.w;

        path_sum[e.v] = s1;
        path_cnt[e.v] = p1;

        all_path_cnt += p1;
        all_path_sum += s1;
    }

    ll clean_path_sum = 0, clean_path_cnt = 0;

    for (auto e: g[v]) {
        auto [p2, s2] = step_2(e.v, v, e.w, all_path_cnt - path_cnt[e.v], all_path_sum - path_sum[e.v], e.clean);

        clean_path_cnt += p2;
        clean_path_sum += s2;
    }

    clean_path_cnt /= 2;
    clean_path_sum /= 2;

    auto [pc, sc] = step_2(v, v, 0, 1, 0, false);

    clean_path_cnt += pc;
    clean_path_sum += sc;

    ans_path += clean_path_cnt;
    ans_sum += clean_path_sum;

    for (auto e: g[v]) {
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

    cout << fixed << setprecision(10) << fl(ans_sum) / fl(ans_path) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
