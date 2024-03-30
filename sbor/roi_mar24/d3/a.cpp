#pragma GCC optimize("Ofast")
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
using pll = pair<ll, ll>;
using ull = unsigned long long;
using uint = unsigned int;
using fl = long double;

const ll maxn = 100001;
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

#ifdef DBG
const ll maxnode = 100;
#else
const ll maxnode = 40 * maxn;
#endif

node narr[maxnode];
ll last = 0;

node *alloc() {
    if (last >= maxnode) {
        volatile ull x = 0;
        while (1) x++;
    }
    return narr + last++;
}

node *clone(node *x) {
    node *y = alloc();
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

void solve() {
    ll n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    vector<ll> uncomp = a;
    sort(uncomp.begin(), uncomp.end());
    uncomp.erase(unique(uncomp.begin(), uncomp.end()), uncomp.end());

    unordered_map<ll, ll> comp;
    for (ll i = 0; i < uncomp.size(); i++) {
        comp[uncomp[i]] = i;
    }

    const ll maxa = uncomp.size() + 20;

    p[0] = 1;
    for (ll i = 1; i <= maxa; i++) {
        p[i] = p[i-1] * P;
    }

    vector<node*> hist = {nullptr};

    for (ll i = 0; i < n; i++) {
        hist.push_back(add(hist.back(), 0, maxa, comp[a[i]], 1));
    }

    for (ll qi = 0; qi < q; qi++) {
        ll l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        
        auto comp1 = compound(hist[l1 - 1], hist[r1], 0, maxa);
        auto comp2 = compound(hist[l2 - 1], hist[r2], 0, maxa);

        if (comp1.hash() == comp2.hash()) {
            cout << "NO\n";
            continue;
        }

        auto e = seconderror(comp1, comp2);

        if (e.e1.first == -1 || e.e2.first == -1 || abs(e.e1.second) > 1 || abs(e.e2.second) > 1 || e.e1.second + e.e2.second != 0) {
            cout << "NO\n";
            continue;
        }
        
        cout << "YES\n";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}