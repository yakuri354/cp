// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

mt19937_64 mt(random_device {}());
uniform_int_distribution<ll> id(INT64_MIN, INT64_MAX);

struct node {
    node *l = 0, *r = 0;
    ll x, s = 1, y, sum = 0;

    explicit node(ll x) : sum(x), x(x), y(id(mt)) {}

    void upd() {
        s = 1;
        sum = x;
        if (l) s += l->s;
        if (l) sum += l->sum;
        if (r) s += r->s;
        if (r) sum += r->sum;
    }
};

void printBT(const std::string& prefix, const node* n, bool isLeft) {
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

void printBT(const node* n) {
    if (!n) {
        cout << "null" << endl;
    } else {
        printBT("", n, false);
    }
}

node *merge(node *l, node *r) {
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

pair<node*, node*> split_by(node *t, ll x) {
    if (!t) return {0, 0};

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

pair<node*, node*> split_n(node* t, ll n) {
    if (!t) return {0, 0};

    ll ls = t->l ? t->l->s : 0;
    if (n > ls) { // ?
        auto [m, r] = split_n(t->r, n - ls - 1);
        t->r = m;
        t->upd();
        return {t, r};
    } else {
        auto [l, m] = split_n(t->l, ls);
        t->l = m;
        t->upd();
        return {l, t};
    }
}

ll leftmost(node *t) {
    if (!t->l) return t->x;
    else return leftmost(t->l);
}

ll rightmost(node *t) {
    if (!t->r) return t->x;
    else return rightmost(t->r);
}

void add_set(node* &t, ll x) {
    cout << "adding " << x << " tree " << endl;
    printBT(t);
    cout << endl;
    if (t && t->x == x) return;
    auto [l, r] = split_by(t, x);
    cout << "split on add" << endl;
    printBT(l);
    cout << " --- " << endl;
    printBT(r);
    cout << endl << endl;
    if ((r && leftmost(r) == x) || (l && rightmost(l) == x)) {
        t = merge(l, r);
    } else {
        t = merge(merge(l, new node(x)), r);
    }
}

ll sum_set(node* &t, ll lb, ll rb) {
    auto [l, t2] = split_by(t, lb);
    auto [m, r] = split_by(t2, rb + 1);

    ll result;
    if (m) result = m->sum;
    else result = 0;

    t = merge(merge(l, m), r);

    return result;
}

void solve() {
    mt19937_64 mt(random_device{}());
    uniform_int_distribution vd(0, 1000);

    for (;;) {
        node *t = nullptr;
        for (;;) {
            ll x;
            cin >> x;
            if (x == -1) break;
            add_set(t, x);

            cout << sum_set(t, 0, inf) << endl << endl;
        }
    }

    for (;;) {
        vector<ll> pts;
        node *t = nullptr;
        for (ll it = 0; it < 10; it++) {
            if (uniform_int_distribution<ll>(0, 10)(mt) == 0) {
                ll x = vd(mt);
                add_set(t, x);
                if (count(pts.begin(), pts.end(), x) > 0) continue;
                pts.push_back(x);
            } else {
                ll lb = vd(mt), rb = vd(mt);
                if (rb < lb) swap(lb, rb);
                ll smart = sum_set(t, lb, rb);
                ll dumb = 0;
                for (ll x : pts) {
                    if (lb <= x && x <= rb) dumb += x;
                }

                if (smart != dumb) {
                    cout << "error" << endl;
                    for (ll x : pts) cout << x << ' ';
                    cout << endl;
                    cout << "smart " << smart << endl;
                    cout << "dumb " << dumb << endl;

                    printBT(t);
                }
            }
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
