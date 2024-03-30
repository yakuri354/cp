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
using ull = unsigned long long;
using uint = unsigned int;
using fl = long double;

const ll maxn = 450'001;

struct node {
    node *l = 0, *r = 0;
    ll x = 0;
};

#ifdef DBG
const ll maxnode = 100;
#else
const ll maxnode = 20 * maxn;
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
        t->x += x;
        return t;
    }

    ll m = (nl + nr) / 2;

    if (p < m) {
        t->l = add(t->l, nl, m, p, x);
    } else {
        t->r = add(t->r, m, nr, p, x);
    }

    t->x = (t->l ? t->l->x : 0) + (t->r ? t->r->x : 0);

    return t;
}

ll desc(node *from, node *to, ll nl, ll nr, ll k) {
    if (nr - nl < 2) {
        return nl;
    }

    ll lsz = (to ? (to->l ? to->l->x : 0) : 0) - (from ? (from->l ? from->l->x : 0) : 0);

    ll m = (nl + nr) / 2;

    if (lsz > k) {
        return desc(from ? from->l : 0, to ? to->l : 0, nl, m, k);
    } else {
        return desc(from ? from->r : 0, to ? to->r : 0, m, nr, k - lsz);
    }
}

ll sum(node *t, ll nl, ll nr, ll ql, ll qr) {
    if (!t) return 0;

    if (ql <= nl && nr <= qr) {
        return t->x;
    }

    if (ql >= nr || qr <= nl) {
        return 0;
    }

    ll m = (nl + nr) / 2;

    return sum(t->l, nl, m, ql, qr) + sum(t->r, m, nr, ql, qr);
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    vector<ll> uncomp = a;
    sort(uncomp.begin(), uncomp.end());
    uncomp.erase(unique(uncomp.begin(), uncomp.end()), uncomp.end());

    unordered_map<ll, ll> comp;
    for (ll i = 0; i < uncomp.size(); i++) {
        comp[uncomp[i]] = i;
    }

    const ll maxa = uncomp.size() + 1;

    vector<node*> hist = {nullptr};

    for (ll i = 0; i < n; i++) {
        hist.push_back(add(hist.back(), 0, maxa, comp[a[i]], 1));
    }

    ll m;
    cin >> m;

    ll prev = 0, ans = 0;
    for (ll qi = 0; qi < m; qi++) {
        ll lp, rp, k;
        cin >> lp >> rp >> k;

        ll l = (lp + prev) % n, r = (rp + prev) % n;

        ll res = desc(hist[l], hist[r + 1], 0, maxa, k - 1);
        res = uncomp[res];
        ans += res;
        prev = res;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}