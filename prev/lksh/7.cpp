// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

mt19937_64 mt(1337);
uniform_int_distribution<ll> id(INT64_MIN, INT64_MAX);

struct node {
    node *l = nullptr, *r = nullptr;
    ll x, s = 1, y, sum = 0;

    explicit node(ll x) : x(x), y(id(mt)), sum(x * x) {}

    void upd() {
        s = 1;
        sum = x * x;
        if (l)
            s += l->s;
        if (l)
            sum += l->sum;
        if (r)
            s += r->s;
        if (r)
            sum += r->sum;

    }
};

void printBT(const std::string &prefix, const node *n, bool isLeft) {
    if (n != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the n
        std::cout << "x " << n->x << "; sum " << n->sum << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), n->l, true);
        printBT(prefix + (isLeft ? "│   " : "    "), n->r, false);
    }
}

void printBT(const node *n) {
    if (!n) {
        cout << "null" << endl;
    } else {
        printBT("", n, false);
    }
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

pair<node *, node *> split_by(node *t, ll x) {
    if (!t)
        return {0, 0};

    if (x > t->x) {
        auto [m, r] = split_by(t->r, x);
        t->r = m;
        t->upd();
        return {t, r};
    } else {
        auto [l, m] = split_by(t->l, x);
        t->l = m;
        t->upd();
        return {l, t};
    }
}

pair<node *, node *> split_n(node *t, ll n) {
    if (!t)
        return {0, 0};

    ll ls = t->l ? t->l->s : 0;
    if (n > ls) {  // ?
        auto [m, r] = split_n(t->r, n - ls - 1);
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

ll leftmost(node *t) {
    if (!t->l) {
        return t->x;
    } else {
        return leftmost(t->l);
    }
}

ll rightmost(node *t) {
    if (!t->r) {
        return t->x;
    } else {
        return rightmost(t->r);
    }
}

void add_set(node* &t, ll x) {
    if (t && t->x == x)
        return;
    auto [l, r] = split_by(t, x);
    if ((r && leftmost(r) == x) || (l && rightmost(l) == x)) {
        t = merge(l, r);
    } else {
        t = merge(merge(l, new node(x)), r);
    }
}

ll sum_set(node * &t, ll lb, ll rb) {
    auto [l, t2] = split_by(t, lb);
    auto [m, r] = split_by(t2, rb + 1);

    ll result;
    if (m) {
        result = m->sum;
    } else {
        result = 0;
    }

    t = merge(merge(l, m), r);

    return result;
}

void dfs(node *t) {
    if (t->l) dfs(t->l);
    cout << t->x << ' ';
    if (t->r) dfs(t->r);
}

ll a[100000], dec[100000], inc[100000];

void solve() {
    ll n, p;
    cin >> n >> p;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    node *t = nullptr;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        t = merge(t, new node(x));
    }

    ll k;
    cin >> k;

    // cout << "--> ";
    // dfs(t);
    // cout << endl;

    cout << t->sum << '\n';
    // cout << endl << endl;
    for (ll i = 0; i < k; i++) {
        // printBT(t);
        // cout << endl << endl;
        ll qt, c;
        cin >> qt >> c;

        if (qt == 1) {
            if (c == 1) {
                auto [l1, r1] = split_n(t, 1);
                auto [m, r2] = split_n(r1, 1);
                m->x += l1->x;
                m->upd();
                t = merge(m, r2);
                
            } else if (c == t->s) {
                auto [l1, r] = split_n(t, t->s-1);
                auto [l, m] = split_n(l1, l1->s-1);
                m->x += r->x;
                m->upd();
                t = merge(l, m);
            } else {
                auto [l2, r1] = split_n(t, c - 1);
                auto [m, r2] = split_n(r1, 1);

                auto [l, ml] = split_n(l2, l2->s - 1);
                auto [mr, r] = split_n(r2, 1);

                ml->x += m->x / 2;
                mr->x += m->x - (m->x/2);

                ml->upd();
                mr->upd();

                // delete m;

                t = merge(l, merge(merge(ml, mr), r));
            }
        } else {
            auto [l, r1] = split_n(t, c - 1);
            auto [m, r] = split_n(r1, 1);

            auto mr = new node(m->x - m->x/2);
            m->x /= 2;

            m->upd();

            t = merge(l, merge(merge(m, mr), r));
        }
        // cout << "--> ";
        // dfs(t);
        // cout << endl;
        n = t->s;
        cout << t->sum << endl;
        // cout << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

