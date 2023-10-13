// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <signal.h>
#include <algorithm>
#include <array>
#include <cstdint>
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

#ifdef SIGTRAP
#define breakpoint() raise(SIGTRAP)
#else
#define breakpoint() raise(SIGABRT)
#endif

#ifdef DBG
#define inv(x)                                                       \
    if (!(x)) {                                                      \
        cerr << "invariant " #x " violated at " << __LINE__ << endl; \
        breakpoint();                                                \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

const ll inf = INT32_MAX;
const ll as = 26;

struct node {
    // ll c[as] = {0};
    array<ll, as> c = {0};

    ll sort = -1;

    ll sum() {
        return accumulate(c.begin(), c.end(), 0ll);
    }
};

node merge(node l, node r) {
    node a = {};

    for (ll i = 0; i < as; i++) {
        a.c[i] = l.c[i] + r.c[i];
    }

    return a;
}

vector<node> t;

pair<node, node> split(node c, ll ls, ll sort) {  // sus
    node l = {}, r = {};
    ll full_sum = c.sum();
    ll left = 0;

    if (sort == 0) {  // weakly decreasing
        for (ll i = as - 1; i >= 0 && left < ls; i--) {
            ll delta = min(c.c[i], ls - left);
            c.c[i] -= delta;
            l.c[i] += delta;
            left += delta;
        }

        for (ll i = as - 1; i >= 0; i--) {
            r.c[i] += c.c[i];
        }
    } else if (sort == 1) {  // weakly increasing
        for (ll i = 0; i < as && left < ls; i++) {
            ll delta = min(c.c[i], ls - left);
            c.c[i] -= delta;
            l.c[i] += delta;
            left += delta;
        }

        for (ll i = 0; i < as; i++) {
            r.c[i] += c.c[i];
        }
    }

    l.sort = c.sort;
    r.sort = c.sort;

    inv(l.sum() == min(ls, full_sum));

    return {l, r};
}

void push(ll n, ll nl, ll nr) {
#ifdef DBG
    inv(t[n].sum() == nr - nl);
#endif
    if (nr - nl < 2) {
        t[n].sort = -1;
        return;
    }

    if (t[n].sort == -1) {
        return;
    }

    ll m = (nl + nr) / 2;

    auto [l, r] = split(t[n], m - nl, t[n].sort);

    t[n].sort = -1;

    t[n * 2 + 1] = l;
    t[n * 2 + 2] = r;
}

ll modify(ll n, ll nl, ll nr, ll ql, ll qr, node x) {
    push(n, nl, nr);

    if (ql <= nl && nr <= qr) {
        inv(x.sum() >= nr - nl);

        auto [l, _r] = split(x, nr - nl, x.sort);

        t[n] = l;

        return nr - nl;
    }

    if (nl >= qr || nr <= ql) {
        return 0;
    }

    ll m = (nl + nr) / 2;

    ll ls = modify(n * 2 + 1, nl, m, ql, qr, x);

    auto [_l, r] = split(x, ls, x.sort);

    ll rs = modify(n * 2 + 2, m, nr, ql, qr, r);

    t[n] = merge(t[n * 2 + 1], t[n * 2 + 2]);

    return ls + rs;
}

node query(ll n, ll nl, ll nr, ll ql, ll qr) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        return t[n];
    }

    if (nl >= qr || nr <= ql) {
        return node{};
    }

    ll m = (nl + nr) / 2;

    return merge(query(n * 2 + 1, nl, m, ql, qr),
                 query(n * 2 + 2, m, nr, ql, qr));
}

string s;

void build(ll n, ll nl, ll nr) {
    if (nr - nl < 2) {
        t[n] = node{};
        t[n].c[s[nl] - 'a'] = 1;
        return;
    }

    ll m = (nl + nr) / 2;

    build(n * 2 + 1, nl, m);
    build(n * 2 + 2, m, nr);

    t[n] = merge(t[n * 2 + 1], t[n * 2 + 2]);
}

void dfs(ll n, ll nl, ll nr) {
    ll m = (nl + nr) / 2;
    if (t[n].sort == -1 && nr - nl > 1) {
        dfs(n * 2 + 1, nl, m);
        dfs(n * 2 + 2, m, nr);
    } else if (t[n].sort == 1 || nr - nl < 2) {
        for (ll i = 0; i < as; i++) {
            for (ll j = 0; j < t[n].c[i]; j++) {
                cout << char(i + 'a');
            }
        }
    } else if (t[n].sort == 0) {
        for (ll i = as - 1; i >= 0; i--) {
            for (ll j = 0; j < t[n].c[i]; j++) {
                cout << char(i + 'a');
            }
        }
    }
}

void solve() {
    ll n, q;
    cin >> n >> q;

    cin >> s;

    t.resize(n * 4);
    build(0, 0, n);

    for (ll i = 0; i < q; i++) {
        ll l, r, sort;
        cin >> l >> r >> sort;
        l--, r--;

        node seg = query(0, 0, n, l, r + 1);

        seg.sort = sort;

        modify(0, 0, n, l, r + 1, seg);
    }

    dfs(0, 0, n);
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
