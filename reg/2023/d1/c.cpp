// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll miny = -1e14 + 1;
const ll maxy = 1e14 + 1;

struct ev {
    ll ty;
    ll x;
    ll hi, lo;
};

vector<ev> evs;

struct node {
    int mel;
    ll mcnt;
};

node cmb(node a, node b) {
    if (a.mel == b.mel) {
        return node {
            a.mel,
            a.mcnt + b.mcnt
        };
    } else if (a.mel < b.mel) {
        return node {
            a.mel,
            a.mcnt
        };
    } else {
        return node {
            b.mel,
            b.mcnt
        };
    }
}

struct tree {
    tree *l = 0, *r = 0;
    int add = 0;
    node n;

    explicit tree(node n) : n(n) {}

    void extend(ll nl, ll nr) {
        ll m = (nl + nr) / 2;
        if (!this->l) {
            this->l = new tree(node {
                0, m - nl
            });
        }

        if (!this->r) {
            this->r = new tree(node {
                0, nr - m
            });
        }
    }

    void push(ll nl, ll nr) {
        this->n.mel += this->add;
        if (nr - nl > 1) {
            this->extend(nl, nr);
            this->l->add += this->add;
            this->r->add += this->add;
        }
        this->add = 0;
    }
};


node query(tree *t, ll nl, ll nr, ll ql, ll qr) {
    t->push(nl, nr);
    if (ql <= nl && nr <= qr) {
        return t->n;
    } else if (nl >= qr || ql >= nr) {
        return node { inf, 0 };
    }

    ll m = (nl + nr) / 2;
    return cmb(query(t->l, nl, m, ql, qr), query(t->r, m, nr, ql, qr));
}

void add_segt(tree *t, ll nl, ll nr, ll ql, ll qr, ll v) {
    t->push(nl, nr);
    if (ql <= nl && nr <= qr) {
        t->add += v;
        t->push(nl, nr);
        return;
    } else if (nl >= qr || ql >= nr) {
        return;
    }

    ll m = (nl + nr) / 2;

    add_segt(t->l, nl, m, ql, qr, v);
    add_segt(t->r, m, nr, ql, qr, v);

    t->n = cmb(t->l->n, t->r->n);
}

void solve() {
    ll k, n;
    cin >> k >> n;

    ll curx = 0, cury = 0;

    for (ll i = 0; i < n; i++) {
        char ty;
        ll d;
        cin >> ty >> d;

        if (ty == 'N' || ty == 'S') {
            ev zzz = {
                .ty = 1,
                .x = curx,
                .hi = k - 1 + (ty == 'N' ? cury + d : cury),
                .lo = ty == 'N' ? cury : cury - d,
            };

            evs.push_back(zzz);
            zzz.x += k;
            zzz.ty = -1;
            evs.push_back(zzz);
        } else {
            ev zzz = {
                .ty = 1,
                .x = ty == 'W' ? curx - d : curx,
                .hi = cury + k - 1,
                .lo = cury,
            };

            evs.push_back(zzz);
            zzz.x = k + (ty == 'W' ? curx : curx + d);
            zzz.ty = -1;
            evs.push_back(zzz);
        }

        if (ty == 'N') {
            cury += d;
        } else if (ty == 'S') {
            cury -= d;
        } else if (ty == 'W') {
            curx -= d;
        } else if (ty == 'E') {
            curx += d;
        }
    }

    sort(evs.begin(), evs.end(), [](ev a, ev b) {
             return a.x < b.x;
         });

    ll lx = -inf, state = 0, ans = 0;

    auto root = new tree(node {
        0, maxy - miny
    });

    for (ev e : evs) {
        ans += (e.x - lx) * state;

        add_segt(root, miny, maxy, e.lo, e.hi + 1, e.ty);

        state = maxy - miny - root->n.mcnt;
        lx = e.x;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
