// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

vector<vector<ll>> tree;
vector<ll> dl, dr, c, took;

struct fn {
    ll cost, cap, v;

    fn(ll cost, ll cap, ll v): cost(cost), cap(cap), v(v) {}

    bool operator<(const fn &o) const {
        return make_tuple(cost, cap, v) < make_tuple(o.cost, o.cap, o.v);
    }
};

struct state {
    set<fn> fns;
    ll cost, have;

    state() {
    }
    state(set<fn> &&fns, ll cost, ll have)
        : fns(fns), cost(cost), have(have) {
    }
};

state* dfs(ll v) {
    if (tree[v].empty()) {
        took[v] = dl[v];
        return new state({{c[v], dr[v] - dl[v], v}}, c[v] * dl[v], dl[v]);
    }

    vector<state*> ss;
    for (ll u : tree[v]) {
        ss.push_back(dfs(u));
        if (ss.back() == nullptr)
            return nullptr;
    }

    state* large = *max_element(ss.begin(), ss.end(), [](auto a, auto b) {
        return a->fns.size() < b->fns.size();
    });

    ll have = 0, cost = 0;
    for (auto sp : ss) {
        if (sp != large) {
            for (const auto &ent: sp->fns) {
                large->fns.insert(ent);
            }
        }

        have += sp->have;
        cost += sp->cost;
    }
    
    // insert c[v]

    if (have > dr[v]) {
        return nullptr;
    }

    while (have < dl[v]) {
        if (large->fns.empty() || c[v] <= large->fns.begin()->cost) {
            cost += (dl[v] - have) * c[v];
            took[v] += dl[v] - have;
            have = dl[v];
            large->fns = {{c[v], dr[v] - dl[v], v}};
            break;
        }
        auto nxt = large->fns.begin();
        if (have + nxt->cap >= dl[v]) {
            ll take = dl[v] - have;
            cost += take * nxt->cost;
            have = dl[v];

            took[nxt->v] += take;

            fn mod = {nxt->cost, nxt->cap - take, nxt->v};
            large->fns.erase(nxt);
            large->fns.insert(mod);
        } else {
            have += nxt->cap;
            cost += nxt->cost * nxt->cap;

            took[nxt->v] += nxt->cap;

            large->fns.erase(nxt);
        }
    }

    // large->cost = cost;
    // large->have = have;

    large->fns.insert({c[v], dr[v], v});

    state *res = new state({}, cost, have);

    ll offer = have;
    for (auto ent: large->fns) {
        if (offer >= dr[v]) break;
        if (offer + ent.cap <= dr[v]) {
            res->fns.insert(ent);
            offer += ent.cap;
        } else {
            res->fns.insert({ent.cost, min(dr[v] - offer, ent.cap), ent.v});
            offer = dr[v];
            break;
        }
    }

    return res;
}

void solve() {
    ll n;
    cin >> n;

    tree.assign(n, {});
    dl.assign(n, 0);
    dr.assign(n, 0);
    c.assign(n, 0);
    took.assign(n, 0);

    for (ll i = 1; i < n; i++) {
        ll p;
        cin >> p;
        tree[p - 1].push_back(i);
    }

    for (ll i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (ll i = 0; i < n; i++) {
        cin >> dl[i] >> dr[i];
    }

    state* ans = dfs(0);

    if (ans == nullptr) {
        cout << -1 << '\n';
        return;
    }

    cout << ans->cost << '\n';

    for (ll i = 0; i < n; i++) {
        cout << took[i] << ' ';
    }

    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t-- > 0)
        solve();
}
