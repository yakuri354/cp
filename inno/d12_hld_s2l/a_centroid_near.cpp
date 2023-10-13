#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <new>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1;  // todo

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> yd(INT64_MIN, INT64_MAX);

struct node;

// using np = unique_ptr<node>;
#define np unique_ptr<node>
#define mv std::move

struct node {
    ll x, y;

    ll s, cnt;

    np l = nullptr, r = nullptr;

    explicit node(ll x, ll cnt) : x(x), y(yd(mt)), s(cnt), cnt(cnt) {
    }

    void upd() {
        s = cnt;
        if (l) {
            s += l->s;
        }
        if (r) {
            s += r->s;
        }
    }
};

pair<np, np> split_x(np t, ll x) {
    if (!t) {
        return {nullptr, nullptr};
    }

    if (t->x < x) {
        auto [l, r] = split_x(mv(t->r), x);
        t->r = mv(l);
        t->upd();
        return {mv(t), mv(r)};
    } else {
        auto [l, r] = split_x(mv(t->l), x);
        t->l = mv(r);
        t->upd();
        return {mv(l), mv(t)};
    }
}

np merge(np l, np r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }

    if (l->y > r->y) {
        auto r1 = merge(mv(l->r), mv(r));
        l->r = mv(r1);
        l->upd();
        return l;
    } else {
        auto l1 = merge(mv(l), mv(r->l));
        r->l = mv(l1);
        r->upd();
        return r;
    }
}

void insert(np &t, ll x) {
    auto [l, r1] = split_x(mv(t), x);
    auto [m, r] = split_x(mv(r1), x + 1);

    if (!m) {
        m = make_unique<node>(x, 1);
    } else {
        m->cnt++;
        m->upd();
    }

    t = merge(mv(l), merge(mv(m), mv(r)));
}

ll less_than(np &t, ll x) {
    auto [l, r] = split_x(mv(t), x);
    ll ans = l ? l->s : 0;
    t = merge(mv(l), mv(r));
    return ans;
}

struct edge {
    ll v, w;

    edge(ll v, ll w) : v(v), w(w) {
    }
};

class pt2d {
    vector<np> pts;

   public:
    explicit pt2d(ll s) : pts(s + 1) {
    }

    void add(ll l, ll w) {
        if (l <= 0) {
            return;
        }
        for (; l < pts.size(); l += l & (-l)) {
            insert(pts[l], w);
        }
    }

    ll count(ll l, ll w) {
        ll ans = 0;
        l = min(l, ll(pts.size())) - 1;
        for (; l > 0; l -= l & (-l)) {
            ans += less_than(pts[l], w);
        }
        return ans;
    }
};

vector<vector<edge>> g;
vector<ll> sz;
vector<bool> used;
ll n, max_l, max_w;

void sizes(ll v, ll p) {
    sz[v] = 1;

    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) {
            continue;
        }
        sizes(u, v);
        sz[v] += sz[u];
    }
}

ll centroid(ll v, ll s, ll p) {
    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) {
            continue;
        }
        if (sz[u] > s / 2) {
            return centroid(u, s, v);
        }
    }

    return v;
}

void add_paths(ll v, ll p, ll pl, ll pw, pt2d& s) {
    s.add(pl, pw);

    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) {
            continue;
        }

        add_paths(u, v, pl + 1, pw + w, s);
    }
}

ll count_paths(ll v, ll p, ll pl, ll pw, pt2d& all, pt2d& here) {
    if (pl > max_l || pw > max_w) {
        return 0;
    }
    // 2 because we divide by 2 later :(
    ll ans = 2 + all.count(max_l - pl + 1, max_w - pw + 1) -
             here.count(max_l - pl + 1, max_w - pw + 1);

    for (auto [u, w] : g[v]) {
        if (u == p || used[u]) {
            continue;
        }

        ans += count_paths(u, v, pl + 1, pw + w, all, here);
    }

    return ans;
}

ll decompose(ll v) {
    sizes(v, -1);
    ll cs = sz[v];
    ll c = centroid(v, cs, -1);
    used[c] = true;

    ll ans = 0;

    {
        pt2d all(cs);

        add_paths(c, -1, 0, 0, all);

        ll paths = 0;

        for (auto [u, w] : g[c]) {
            if (used[u]) {
                continue;
            }
            pt2d here(cs);

            add_paths(u, c, 1, w, here);

            paths += count_paths(u, c, 1, w, all, here);
        }

        ans += paths / 2;
    }

    for (auto [u, w] : g[c]) {
        if (used[u]) {
            continue;
        }

        ans += decompose(u);
    }

    return ans;
}

void solve() {
    cin >> n >> max_l >> max_w;
    g.resize(n);
    sz.resize(n);
    used.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        ll pi, wi;
        cin >> pi >> wi;

        g[i + 1].emplace_back(pi - 1, wi);
        g[pi - 1].emplace_back(i + 1, wi);
    }

    cout << decompose(0) << endl;
}

int main() {
    #ifndef DBG
    freopen("close-vertices.in", "r", stdin);
    freopen("close-vertices.out", "w", stdout);
    #endif
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
