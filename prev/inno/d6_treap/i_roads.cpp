// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> y_dist(INT64_MIN, INT64_MAX);

template <typename T>
struct node {
    ll x, y, sz = 1;
    T v;
    ll sum;

    node *l, *r;

    node(ll x, T v) : v(v), x(x), y(y_dist(mt)), sum(x) {}

    void upd() {
        sum = x;
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

template <typename T>
pair<node<T>*, node<T>*> split_n(node<T>* t, ll n) {
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

template <typename T>
node<T>* merge(node<T>* l, node<T>* r) {  // sus?
    if (!l)
        return r;
    if (!r)
        return l;

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
template <typename T>
pair<node<T>*, node<T>*> split_x(node<T>* t, ll x) {  // sus?
    if (!t)
        return {0, 0};

    if (t->x > x) {
        auto [l1, l2] = split_x(t->l, x);
        t->l = l2;
        t->upd();
        return {l1, t};
    } else {
        auto [r1, r2] = split_x(t->r, x);
        t->r = r1;
        t->upd();
        return {t, r2};
    }
}

struct vx {};

struct comp {
    node* arr;
};

node < *insert_set(node* t, node* x) {
    auto [l, r] = split_x(t, x->x);
}

vector<vector<ll>> adj;

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;

    adj.resize(n);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
