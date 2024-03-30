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

mt19937_64 mt(0xab0ba);

uniform_int_distribution<ll> yd(INT64_MIN, INT64_MAX);

struct fn {
    ll cost, cap, v;

    fn(ll cost, ll cap, ll v): cost(cost), cap(cap), v(v) {}

    bool operator<(const fn &o) const {
        return make_tuple(cost, cap, v) < make_tuple(o.cost, o.cap, o.v);
    }
};

struct node {
    fn x;
    ll y, v = 0;
    ll sum = 0, sz = 1;

    node *l = 0, *r = 0;

    node(fn x, ll v): x(x), y(yd(mt)), sum(v), sz(1) {}

    void upd() {
        sum = v;
        sz = 1;
        if (l) {
            sum += l->sum;
            sz += l->sz;
        }
        if (r) {
            sum += r->sum;
            sz += r->sz;
        }
    }
};

pair<node *, node *> split_n(node* t, ll n) {
    if (!t)
        return {0, 0};

    ll ls = t->l ? t->l->sz : 0;
    if (ls >= n) {
        auto [l1, l2] = split_n(t->l, n);
        t->l = l2;
        t->upd();
        return {l1, t};
    } else {
        auto [r1, r2] = split_n(t->r, n - ls - 1);
        t->r = r1;
        t->upd();
        return {t, r2};
    }
}

node* merge(node* l, node* r) {  // sus?
    if (!l) return r;
    if (!r) return l;

    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }
}

// invariant: tree is sorted
pair<node *, node *> split_sum(node* t, ll s) {  // sus?
    if (!t) return {0, 0};

    ll ls = t->l ? t->l->sum : 0;

    if (s <= ls) {
        auto [l1, l2] = split_sum(t->l, s);
        t->l = l2;
        t->upd();
        return {l1, t};
    } else if (ls < s && s < ls + t->v) {
        // we must split the node
        // ultra sus
        node *lt = new node(t->x, s - ls);
        node *rt = new node(t->x, t->v - lt->v);

        return {merge(t->l, lt), merge(rt, t->r)};
    } else {
        auto [r1, r2] = split_sum(t->r, s - ls - t->v);
        t->r = r1;
        t->upd();
        return {t, r2};
    }
}

// invariant: tree is sorted
pair<node*, node*> split_x(node* t, fn x) {  // sus?
    if (!t) return {0, 0};

    if (t->x < x) {
        auto [r1, r2] = split_x(t->r, x);
        t->r = r1;
        t->upd();
        return {t, r2};
    } else {
        auto [l1, l2] = split_x(t->l, x);
        t->l = l2;
        t->upd();
        return {l1, t};
    }
}


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
