#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
using pll = pair<ll, ll>;
using ull = unsigned long long;
using uint = unsigned int;
using fl = long double;

const ll maxn = 200001;
const ull P = 1e9 + 7;

ull p[maxn];

struct node {
    node *l = 0, *r = 0;
    ull x = 0;
    ll cnt = 0;

    void recalc(ll nl, ll nr) {
        if (nr - nl < 2) {
            x = cnt;
            return;
        }

        ull lh = l ? l->x : 0;
        ull rh = r ? r->x : 0;

        cnt = (l ? l->cnt : 0) + (r ? r->cnt : 0);

        x = p[nr - (nl + nr) / 2] * lh + rh;
    }
};

struct compound {
    node *from = 0, *to = 0;
    ll nl = 0, nr = 0;

    compound(node *from, node *to, ll nl, ll nr) : from(from), to(to), nl(nl), nr(nr) {}
    compound() {}

    compound l() const {
        ll m = (nl + nr) / 2;
        return compound(from ? from->l : 0, to ? to->l : 0, nl, m);
    }

    compound r() const {
        ll m = (nl + nr) / 2;
        return compound(from ? from->r : 0, to ? to->r : 0, m, nr);
    }

    ll size() const {
        return nr - nl;
    }

    ull hash() const {
        ull h1 = from ? from->x : 0;
        ull h2 = to ? to->x : 0;

        return (h2 - h1) * p[nl];
    }

    ll cnt() const {
        ll c1 = from ? from->cnt : 0;
        ll c2 = to ? to->cnt : 0;

        return c2 - c1;
    }
};

// #ifdef DBG
// // const ll maxnode = 100;
// #else
// const ll maxnode = 20 * maxn;
// // #endif

// node narr[maxnode];
// ll last = 0;

node *alloc() {
    // if (last >= maxnode) {
    //     // volatile ull x = 0;
    //     exit(0);
    //     // while (1) x++;
    // }

    // return narr + last++;

    return new node();
}

node *clone(node *x) {
    node *y = alloc();
    *y = {};
    *y = *x;
    return y;
}

node *add(node *t, ll nl, ll nr, ll p, ll x) {
    if (!t) t = alloc();
    else t = clone(t);

    if (nr - nl < 2) {
        t->cnt += x;
        t->recalc(nl, nr);
        return t;
    }

    ll m = (nl + nr) / 2;

    if (p < m) {
        t->l = add(t->l, nl, m, p, x);
    } else {
        t->r = add(t->r, m, nr, p, x);
    }

    t->recalc(nl, nr);

    return t;
}

struct err2 {
    pll e1 = {-1, 0}, e2 = {-1, 0};
};

pll firsterror(compound s1, compound s2) {
    if (s1.hash() == s2.hash()) return {-1, 0};

    if (s1.size() <= 1) {
        return {s1.nl, s2.cnt() - s1.cnt()};
    }

    bool leq = s1.l().hash() == s2.l().hash();
    bool req = s1.r().hash() == s2.r().hash();


    if (!leq && !req) {
        return {-1, 0};
    } else if (!leq) {
        return firsterror(s1.l(), s2.l());
    } else if (!req) {
        return firsterror(s1.r(), s2.r());
    } else {
        exit(-1);
    }
}

err2 seconderror(compound s1, compound s2) {
    if (s1.size() <= 1) {
        return err2();
    }

    if (s1.hash() == s2.hash()) return err2();

    bool leq = s1.l().hash() == s2.l().hash();
    bool req = s1.r().hash() == s2.r().hash();

    if (!leq && !req) {
        return {firsterror(s1.l(), s2.l()), firsterror(s1.r(), s2.r())};
    } else if (!leq) {
        return seconderror(s1.l(), s2.l());
    } else if (!req) {
        return seconderror(s1.r(), s2.r());
    } else {
        exit(-1);
    }
}


void stress() {
    ll n, q;
    cin >> n >> q;

    random_device rd;
    mt19937_64 mt(rd());

    while (1) {
        const ll maxa = 11;

        vector<ll> a(n);
        for (ll &i: a) {
            i = uniform_int_distribution<ll>(1, maxa - 1)(mt);
        }

        p[0] = P;
        for (ll i = 1; i <= ll(1e5); i++) {
            p[i] = p[i-1] * P;
        }

        vector<node*> hist = {nullptr};

        for (ll i = 0; i < n; i++) {
            hist.push_back(add(hist.back(), 0, maxa, a[i], 1));
        }

        auto solvedumb = [a](ll l1, ll r1, ll l2, ll r2) {
            unordered_map<ll, ll> cnt;
            l1--, l2--;

            for (ll i = l1; i < r1; i++) {
                cnt[a[i]]--;
            }

            for (ll i = l2; i < r2; i++) {
                cnt[a[i]]++;
            }

            ll es = 0;
            for (auto [k, v]: cnt) {
                if (abs(v) >= 2) {
                    return false;
                }
                if (abs(v) == 1) {
                    es++;
                }
            }

            return es == 2;
        };

        auto solvesmart = [hist](ll l1, ll r1, ll l2, ll r2) {
            auto comp1 = compound(hist[l1 - 1], hist[r1], 0, maxa);
            auto comp2 = compound(hist[l2 - 1], hist[r2], 0, maxa);

            if (comp1.hash() == comp2.hash()) {
                return false;
            }

            auto e = seconderror(comp1, comp2);

            if (e.e1.first == -1 || e.e2.first == -1 || abs(e.e1.second) > 1 || abs(e.e2.second) > 1 || e.e1.second + e.e2.second != 0) {
                return false;
            }

            // ll bcp = last;
            node *s1 = add(hist[r2], 0, maxa, e.e1.first, -e.e1.second);
            node *s2 = add(s1, 0, maxa, e.e2.first, -e.e2.second);
            // last = bcp;

            return compound(hist[l1 - 1], hist[r1], 0, maxa).hash() == compound(hist[l2 - 1], s2, 0, maxa).hash();
        };

        // cout << "START" << endl;
        for (ll qi = 0; qi < q; qi++) {
            if (qi > 0 && qi % 10000 == 0) {
                cout << "-> " << qi << endl;
            }

            ll l1, r1, l2, r2;
            ll qsize = uniform_int_distribution<ll>(1, n)(mt);

            l1 = uniform_int_distribution<ll>(1, n - qsize + 1)(mt);
            r1 = l1 + qsize - 1;

            l2 = uniform_int_distribution<ll>(1, n - qsize + 1)(mt);
            r2 = l2 + qsize - 1;

            bool sm1 = solvesmart(l1, r1, l2, r2);
            bool du1 = solvedumb(l1, r1, l2, r2);
            
            if (sm1 != du1) {
                cout << "PROLAPS" << endl;
                solvedumb(l1, r1, l2, r2);
                solvesmart(l1, r1, l2, r2);
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    stress();
}