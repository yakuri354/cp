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
#include <unordered_map>
#include <vector>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
 
const ll k = 420;
const ll inf = 1e18;
 
const ll MODIFY = 1;
const ll QUERY = 2;
 
struct edge {
    ll u, v, w, i;
 
    bool operator<(const edge &o) const {
        return make_tuple(w, u, v, i) < make_tuple(o.w, o.u, o.v, o.i);
    }
 
    bool operator>(const edge &o) const {
        return make_tuple(w, u, v, i) > make_tuple(o.w, o.u, o.v, o.i);
    }
};
 
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
 
struct query {
    ll ty, q_i;
    ll idx, w;
};
 
vector<query> orig_queries;
vector<ll> q_ans;
 
void solve() {
    ll n, m;
    cin >> n >> m;
 
    vector<edge> orig_el;
 
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
 
        orig_el.push_back({u - 1, v - 1, w, i});
    }
 
    auto el = orig_el;
 
    ll q;
    cin >> q;
 
    q_ans.resize(q, -1);
 
    for (ll i = 0; i < q; i++) {
        ll ty;
        cin >> ty;
 
        if (ty == MODIFY) {
            ll ei, w;
            cin >> ei >> w;
 
            orig_queries.push_back(query{.ty = MODIFY, .q_i = i, .idx = ei - 1, .w = w});
        } else if (ty == QUERY) {
            ll v, w;
            cin >> v >> w;
 
            orig_queries.push_back(query{.ty = QUERY, .q_i = i, .idx = v - 1, .w = w});
        }
    }
 
    auto qs = orig_queries;
 
    for (ll l = 0, r = min(k, q); l < q; l += k, r = min(r + k, q)) {
        dsu d(n);
 
        set<ll> used;
        set<edge, greater<>> edges(el.begin(), el.end());
        for (ll i = l; i < r; i++) {
            if (qs[i].ty == MODIFY) {
                used.insert(qs[i].idx);
                edges.erase(el[qs[i].idx]);
            }
        }
 
        stable_sort(qs.begin() + l, qs.begin() + r, [](query a, query b) {
            return a.w > b.w;
        });
 
        for (ll i = l; i < r; i++) {
            auto qq = qs[i];
            if (qq.ty != QUERY) continue;
 
            while (!edges.empty() && edges.begin()->w >= qq.w) {
                auto e = *edges.begin();
                edges.erase(edges.begin());
                d.unite(e.u, e.v);
                // cerr << "perm unite " << e.u + 1 << " <-> " << e.v + 1 << " [" << e.w << "]" << endl;
            }
 
            unordered_map<ll, ll> mut;
 
            for (auto u_e : used) {
                mut[u_e] = el[u_e].w;
            }
 
            for (ll j = l; j < r; j++) {
                query q2 = orig_queries[j];
                if (q2.q_i > qq.q_i) break;
                if (q2.ty == MODIFY) {
                    mut[q2.idx] = q2.w;
                }
            }
 
            ll state = d.snapshot();
            for (auto &[k, v]: mut) {
                if (v >= qq.w) {
                    d.unite(el[k].u, el[k].v);
                }
            }
 
            q_ans[qq.q_i] = d.sz[d.par(qq.idx)];
 
            d.rollback(state);
        }
 
        for (ll i = l; i < r; i++) {
            if (qs[i].ty == MODIFY) {
                el[qs[i].idx].w = qs[i].w;
            }
        }
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