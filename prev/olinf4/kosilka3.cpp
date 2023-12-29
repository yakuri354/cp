#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

set<pair<ll, ll>> st;

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

struct tree;

int talloc(int lb, int rb);
tree* gett(int i);

struct tree {
    int li = 0, ri = 0;
    bool v = false;
    int lb, rb;

    tree(ll l, ll r): lb(l), rb(r) {}
    tree(): lb(0), rb(0) {}

    void ext() {
        if (lb + 1 >= rb || li) return;
        ll m = lb + (rb - lb) / 2;
        li = talloc(lb, m);
        ri = talloc(m, rb);
    }

    void push() {
        if (lb + 1 >= rb) return;
        gett(li)->v ^= v;
        gett(ri)->v ^= v;
        v = false;
    }

    void setv(ll ql, ll qr) {
        if (ql <= lb && rb <= qr) {
            v ^= 1;
            return;
        }
        if (ql >= rb || lb >= qr) {
            return;
        }
        ext();
        push();
        ll m = lb + (rb - lb) / 2;
        gett(li)->setv(ql, qr);
        gett(ri)->setv(ql, qr);
    }

    bool query(ll p) {
        if (lb + 1 >= rb) return v;
        if (li) push();
        ll m = lb + (rb - lb) / 2;
        if (p < m) {
            if (li)
                return gett(li)->query(p) ^ v;
            return v;
        } else {
            if (ri)
                return gett(ri)->query(p) ^ v;
            return v;
        }
    }
};

tree ta[12000000];
ll lastt = 0;

int talloc(int lb, int rb) {
    ta[++lastt] = tree(lb, rb);
    if (lastt > 12000000) {
        assert(false);
    }
    return lastt;
}

tree *gett(int i) {
    return ta + i;
}

ll n, m, k, q;

void solve() {
    cin >> n >> m >> k >> q;

    auto tx = tree(0, n), ty = tree(0, m);
    
    for (ll i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;
        st.emplace(x-1, y-1);
    }

    for (ll i = 0; i < q; i++) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;
            tx.setv(0, x1 + 1);
            tx.setv(x2 + 1, n);
            ty.setv(y1 + 1, y2 + 1);
        } else {
            ll x, y;
            cin >> x >> y;
            x--;y--;
            bool ans = tx.query(x) ^ ty.query(y) ^ st.count({x, y});
            if (ans) cout << "YES";
            else cout << "NO";
            cout << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
