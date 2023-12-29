#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

random_device rd{};
mt19937_64 mt(rd());
uniform_real_distribution<fl> dist;

struct tree {
    ll x, s, minx, maxx, vol, cnt, rcnt;

    tree *l = nullptr, *r = nullptr;

    tree(ll x, ll cnt): x(x), rcnt(cnt), cnt(cnt), s(1), minx(x), maxx(x), vol(0) {}

    void upd() {
        s = 1;
        rcnt = cnt;
        maxx = minx = x;
        if (l) {
            rcnt += l->rcnt;
            s += l->s;
            minx = l->minx;
        }
        if (r) {
            rcnt += r->rcnt;
            s += r->s;
            maxx = r->maxx;
        }

        vol = 0;
        if (l) vol += l->vol + (x - l->maxx) * l->rcnt;
        if (r) vol += r->vol + (maxx - x) * ((l ? l->rcnt : 0) + cnt);
    }

    void print() {
        if (l) l->print();
        cout << x << ' ';
        if (r) r->print();
    }
};

tree *merge(tree *l, tree *r) {
    if (!l) return r;
    if (!r) return l;

    if (dist(mt) < fl(l->s) / fl(l->s + r->s)) {
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }
}

pair<tree *, tree *> split_by(tree *t, ll x) {
    if (!t) return {0, 0};

    if (x <= t->x) {
        auto [l, r] = split_by(t->l, x);
        t->l = r;
        t->upd();
        return {l, t};
    } else {
        auto [l, r] = split_by(t->r, x);
        t->r = l;
        t->upd();
        return {t, r};
    }
}

pair<tree *, tree *> split_n(tree *t, ll n) {
    if (!t) return {0, 0};

    ll ls = t->l ? t->l->s : 0;
    if (ls >= n) {
        auto [l, r] = split_n(t->l, n);
        t->l = r;
        t->upd();
        return {l, t};
    } else {
        auto [l, r] = split_n(t->r, n - ls - 1);
        t->r = l;
        t->upd();
        return {t, r};
    }
}

pair<tree *, tree *> split_vol(tree *t, ll vol, ll nl, ll lv, ll maxl) {
    if (!t) return {0, 0};

    ll fullv = nl * (t->x - maxl) + lv;
    if (t->l) fullv += t->l->vol + (t->x - t->l->maxx) * t->l->rcnt;
    if (fullv <= vol) {
        auto [l, r] = split_vol(t->r, vol, nl + (t->l ? t->l->rcnt : 0) + t->cnt, fullv, t->x);
        t->r = l;
        t->upd();
        return {t, r};
    } else {
        auto [l, r] = split_vol(t->l, vol, nl, lv, maxl);
        t->l = r;
        t->upd();
        return {l, t};
    }
}
// 
pair<ll, ll> a[100000];
tree *ptr[100001];

void dbg(string s, tree *t) {
    // cerr << s << " ";
    // if (!t) cerr << "<null>";
    // else t->print();
    // cerr << endl;
}

void solve() {
    ll n, q;
    map<ll, vector<ll>> st;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (st.count(x)) st[x].push_back(i);
        else st[x] = {i};
    }

    tree *dd = nullptr;

    for (auto [k, v]: st) {
        auto *t = new tree(k, v.size());
        for (auto x: v) {
            ptr[x] = t;
        }
        dd = merge(dd, t);
    }
    
    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;

        if (qt == 1) {
            ll p, x;
            cin >> p >> x;
            p--;

            auto tgt = ptr[p];

            // cerr << "tgt->x = " << tgt->x << endl;
            auto [l, r1] = split_by(dd, tgt->x);
            auto [v, r] = split_n(r1, 1);
            if (v->cnt > 1) {
                v->cnt--;
                v->upd();
                r = merge(v, r);
                v = new tree(x, 1);
                ptr[p] = v;
            }

            dd = merge(l, r);
            // dbg("dd", dd);
            // dbg("v", v);
            
            v->x = x;
            v->upd();

            auto [l2, r2] = split_by(dd, x);
            auto [v2, r3] = split_n(r2, 1);
            if (v2 && v2->x == x) {
                v2->cnt++;
                v2->upd();
                dd = merge(l2, merge(v2, r3));
                ptr[p] = v2;
            } else {
                dd = merge(l2, merge(v, merge(v2, r3)));
            }
            // dbg("dd", dd);
            // cerr << endl;
        } else if (qt == 2) {
            ll v;
            cin >> v;

            auto [l, r] = split_vol(dd, v, 0, 0, 0);
            cout << max(fl(l->maxx), fl(l->maxx) + fl(v - l->vol) / fl(l->rcnt)) << endl;
            dd = merge(l, r);
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(6);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
