// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
#include <random>
#include <set>
#include <tuple>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll k = 420;
const ll maxn = 50000;
const ll inf = 1e18;

struct edge {
    ll u, v, w, i;

    bool operator<(const edge &o) const {
        return make_tuple(w, u, v, i) < make_tuple(o.w, o.u, o.v, o.i);
    }

    bool operator>(const edge &o) const {
        return make_tuple(w, u, v, i) > make_tuple(o.w, o.u, o.v, o.i);
    }
};

vector<edge> el;

struct query {
    ll ty, i;
    ll ei, v, w;
};

vector<query> qs;
vector<ll> q_ans;

struct dsu {
    vector<ll> p, sz, bcp;

    ll comps;

    dsu(ll n) : p(n), sz(n, 1), bcp(), comps(n) {
        iota(p.begin(), p.end(), 0);
    }

    ll par(ll v) {
        return p[v] == v ? v : par(p[v]);
    }

    ll snapshot() {
        return bcp.size();
    }

    void unite(ll a, ll b) {
        a = par(a), b = par(b);

        if (a == b)
            return;

        if (sz[a] < sz[b])
            swap(a, b);

        p[b] = a;
        sz[a] += sz[b];
        bcp.push_back(b);
        comps--;
    }

    bool undo() {
        if (bcp.empty())
            return false;

        ll v = bcp.back();
        bcp.pop_back();

        comps++;
        sz[p[v]] -= sz[v];
        p[v] = v;
        return true;
    }

    void rollback(ll state) {
        while (bcp.size() > state) undo();
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;

        el.push_back({u - 1, v - 1, w, i});
    }

    ll q;
    cin >> q;

    q_ans.resize(q, -1);

    for (ll i = 0; i < q; i++) {
        ll ty;
        cin >> ty;

        if (ty == 1) {
            ll ei, w;
            cin >> ei >> w;

            qs.push_back(query{.ty = 1, .i = i, .ei = ei - 1, .w = w});
        } else {
            ll v, w;

            cin >> v >> w;

            qs.push_back(query{.ty = 2, .i = i, .v = v - 1, .w = w});
        }
    }

    set<edge, greater<edge>> sorted_edges(el.begin(), el.end());

    for (ll l = 0, r = min(q, k); l < q; l += k, r = min(q, l + k)) {
        vector<bool> used(m);
        dsu d(n);
        vector<pair<ll, edge>> local;
        for (ll i = l; i < r; i++) {
            if (qs[i].ty == 1 && !used[qs[i].ei]) {
                local.push_back({-1, el[qs[i].ei]});
            }
            if (qs[i].ty == 1) {
                used[qs[i].ei] = true;
                auto e1 = el[qs[i].ei];
                e1.w = qs[i].w;
                local.push_back({qs[i].i, e1});
            }
        }

        sort(local.begin(), local.end(), [](auto a, auto b) {
            return a.first < b.first;
        });

        stable_sort(qs.begin() + l, qs.begin() + r, [](auto a, auto b) {
            return a.w > b.w;
        });

        auto it = sorted_edges.begin();
        for (ll i = l; i < r; i++) {
            if (qs[i].ty == 1) continue;

            while (it != sorted_edges.end() && it->w >= qs[i].w) {
                if (!used[it->i]) {
                    d.unite(it->u, it->v);
                }
                it++;
            }

            map<ll, ll> edge_w_final;

            for (ll j = 0; j < local.size() && local[j].first < qs[i].i; j++) {
                if (local[j].second.w >= qs[i].w) {
                    edge_w_final[local[j].second.i] = local[j].second.w;
                }
            }

            ll state = d.snapshot();
            for (auto &[k, v]: edge_w_final) {
                if (v >= qs[i].w) {
                    d.unite(el[k].u, el[k].v);
                }
            }

            q_ans[qs[i].i] = d.sz[d.par(qs[i].v)];

            d.rollback(state);
        }

        for (ll i = l; i < r; i++) {
            if (qs[i].ty == 1) {
                el[qs[i].ei].w = qs[i].w;
            }
        }

        sorted_edges = set<edge, greater<edge>>(el.begin(), el.end());
    }

    for (ll i = 0; i < q; i++) {
        if (q_ans[i] != -1) cout << q_ans[i] << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
