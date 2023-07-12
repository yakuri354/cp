// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll P = 31;

mt19937_64 mt(0xDEADBEEFDEADBEEF);
uniform_int_distribution<ll> id(INT64_MIN, INT64_MAX);

const ll maxn = 3e6 + 11;
ull p[maxn + 1];

struct node {
    node *l = nullptr, *r = nullptr;
    ll y;
    ull s = 1;
    ull c;
    ull h;

    ull ghs(node *t) {
        return t ? t->h : 0;
    }

    ull gsz(node *t) {
        return t ? t->s : 0;
    }

    explicit node(ull c) : y(id(mt)), c(c), h(c) {}

    void upd() {
        s = 1 + gsz(l) + gsz(r);
        h = ghs(l) + c * p[gsz(l)] + ghs(r) * p[1 + gsz(l)];
    }
};

ull ghs(node *t) {
    return t ? t->h : 0;
}

ull gsz(node *t) {
    return t ? t->s : 0;
}

node *merge(node *l, node *r) {
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

pair<node *, node *> split_n(node *t, ull n) {
    if (!t)
        return {0, 0};

    if (gsz(t->l) + 1 <= n) {
        auto [m, r] = split_n(t->r, n - gsz(t->l) - 1);
        t->r = m;
        t->upd();
        return {t, r};
    } else {
        auto [l, m] = split_n(t->l, n);
        t->l = m;
        t->upd();
        return {l, t};
    }
}

void dfs(node *t) {
    if (t->l) dfs(t->l);
    cerr << t->c;
    if (t->r) dfs(t->r);
}

void solve() {
    string s;
    cin >> s;

    p[0] = 1;
    for (ull i = 1; i <= maxn; i++) {
        p[i] = p[i-1] * P;
    }

    node *t = nullptr;

    for (char c : s) {
        t = merge(t, new node(c - '0'));
    }

    ll q;
    cin >> q;
    while (q--) {
        string ty;
        cin >> ty;
        if (ty == "-") {
            ll ix;
            cin >> ix;

            auto [l, r1] = split_n(t, ix - 1);
            auto [m, r] = split_n(r1, 1);

            t = merge(l, r);
        }
        if (ty == "?") {
            ll l1, l2, len;
            cin >> l1 >> l2 >> len;

            ull h1, h2;
            {
                auto [l, r1] = split_n(t, l1 - 1);
                auto [m, r] = split_n(r1, len);
                h1 = ghs(m);
                t = merge(merge(l, m), r);
            }
            {
                auto [l, r1] = split_n(t, l2 - 1);
                auto [m, r] = split_n(r1, len);
                h2 = ghs(m);
                t = merge(merge(l, m), r);
            }

            if (h1 == h2) {
                cout << "ia\n";
            } else {
                cout << "jok\n";
            }
        }

        dfs(t);
        cerr << endl;
    }
    cout << flush;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
