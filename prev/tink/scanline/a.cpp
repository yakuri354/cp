// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct ev {
    ll ty, x, yl, yh;

    ev(ll ty, ll x, ll yl, ll yh) : ty(ty), x(x), yl(yl), yh(yh) {}
};

vector<pair<ll, ll>> t;
vector<ll> mut;

pair<ll, ll> cmb(pair<ll, ll> l, pair<ll, ll> r) {
    if (l.first >= r.first) {
        return l;
    } else {
        return r;
    }
}

void build(ll n, ll nl, ll nr) {
    if (nr - nl <= 1) {
        t[n] = {0, nl};
        return;
    }

    ll m = (nl + nr) / 2;
    build(n*2+1, nl, m);
    build(n*2+2, m, nr);

    t[n] = cmb(t[n*2+1], t[n*2+2]);
}

void push(ll n, ll nl, ll nr) {
    if (nr - nl > 1) {
        t[n*2+1].first += mut[n];
        t[n*2+2].first += mut[n];
    }

    t[n].first += mut[n];
    mut[n] = 0;
}

pair<ll, ll> query(ll n, ll nl, ll nr, ll ql, ll qr) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        return t[n];
    }
    if (ql >= nr || qr <= nl) {
        return {-inf, -1};
    }

    ll m = (nl + nr) / 2;

    return cmb(query(n*2+1, nl, m, ql, qr),
               query(n*2+2, m, nr, ql, qr));
}

void add(ll n, ll nl, ll nr, ll ql, ll qr, ll v) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        mut[n] += v;
        push(n, nl, nr);
        return;
    }

    if (ql >= nr || qr <= nl) {
        return;
    }

    ll m = (nl + nr) / 2;

    add(n*2+1, nl, m, ql, qr, v);
    add(n*2+2, m, nr, ql, qr, v);

    t[n] = cmb(t[n*2+1], t[n*2+2]);
}

void solve() {
    ll n;
    cin >> n;

    vector<ev> evs;
    vector<ll> crdy;

    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        crdy.push_back(y1);
        crdy.push_back(y2);

        evs.emplace_back(1, x1, y1, y2);
        evs.emplace_back(-1, x2, y1, y2);
    }

    sort(crdy.begin(), crdy.end());
    crdy.erase(unique(crdy.begin(), crdy.end()), crdy.end());

    unordered_map<ll, ll> compress;

    for (ll i = 0; i < ll(crdy.size()); i++) {
        compress[crdy[i]] = i;
    }

    sort(evs.begin(), evs.end(), [](auto a, auto b) {
             if (a.x == b.x) return a.ty > b.ty;
             return a.x < b.x;
         });

    t.resize(4 * crdy.size());
    mut.resize(4 * crdy.size());

    build(0, 0, crdy.size());

    auto ans = make_pair(-inf, -1ll);
    ll ansx = 0;
    for (ev e : evs) {
        add(0, 0, crdy.size(), compress[e.yl], compress[e.yh] + 1, e.ty);
        if (ans.first < t[0].first) {
            ans = t[0];
            ansx = e.x;
        }
    }

    cout << ans.first << endl;
    cout << ansx << ' ' << crdy[ans.second] << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
