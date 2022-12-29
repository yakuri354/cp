#ifndef DBG
#pragma GCC optimize("Ofast")
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

void cleart(int i);
tree* gett(int i);

struct tree {
    uint32_t li = 0, ri = 0;
    bool v = false;
    int lb, rb;

    tree(ll l, ll r): lb(l), rb(r) {}
    tree(): lb(0), rb(0) {}
};

tree t[8000000];
ll lastt = 0;

uint32_t newnode(ll lb, ll rb) {
    t[lastt++] = tree(lb, rb);
    if (lastt > 8000000) assert(false);
    return lastt;
}

void ext(ll i) {
    if (t[i].lb + 1 >= t[i].rb || t[i].li) return;
    ll m = t[i].lb + (t[i].rb - t[i].lb) / 2;
    t[i].li = newnode(t[i].lb, m);
    t[i].ri = newnode(m, t[i].rb);
}

void push(ll i) {
    if (t[i].lb + 1 >= t[i].rb) return;
    t[i].li ^= 1;
    t[i].ri ^= 1;
    t[i].v = false;
}

void setv(ll i, ll ql, ll qr) {
    if (ql <= t[i].lb && t[i].rb <= qr) {
        t[i].v ^= 1;
        return;
    }
    if (ql >= t[i].rb || t[i].lb >= qr) {
        return;
    }
    ext(i);
    push(i);
    ll m = t[i].lb + (t[i].rb - t[i].lb) / 2;
    setv(t[i].li, ql, qr);
    setv(t[i].ri, ql, qr);
}

bool query(ll i, ll p) {
    if (t[i].lb + 1 >= t[i].rb) return t[i].v;
    if (t[i].li) push(i);
    ll m = t[i].lb + (t[i].rb - t[i].lb) / 2;
    if (p < m) {
        if (t[i].li)
            return query(t[i].li, p) ^ t[i].v;
        return t[i].v;
    } else {
        if (t[i].ri)
            return query(t[i].ri, p) ^ t[i].v;
        return t[i].v;
    }
}



ll n, m, k, q;

void solve() {
    cin >> n >> m >> k >> q;
    
    ll txi = newnode(0, n), tyi = newnode(0, m);

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
            setv(txi, 0, x1 + 1);
            setv(txi, x2 + 1, n);
            setv(tyi, y1 + 1, y2 + 1);
        } else {
            ll x, y;
            cin >> x >> y;
            x--;y--;
            bool ans = query(txi, x) ^ query(tyi, y) ^ st.count({x, y});
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

