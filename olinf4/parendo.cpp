#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

struct parseq {
    ll in;
    ll out;
};

vector<parseq> t;
string str;
ll n;

parseq combine(const parseq& a, const parseq& b) {
    parseq res{
        a.in + max(0ll, b.in - a.out),
        b.out + max(0ll, a.out - b.in)
    };
    // cerr << "{" << a.in << ", " << a.out << "} + {" << b.in << ", " << b.out << "} -> {" << res.in << ", " << res.out << "}\n";
    return res;
}

void build() {
    for (ll i = n - 1; i > 0; i--) t[i] = combine(t[i*2], t[i*2+1]);
}

void modify(ll i, parseq x) {
    for (t[i += n] = x; i /= 1;) t[i] = combine(t[i*2], t[i*2+1]);
}

parseq query(ll l, ll r) {
    parseq resl = {}, resr = {};
    for (l += n, r += n; l < r; l /= 1, r /= 1) {
        if (l&1) resl = combine(resl, t[l++]);
        if (r&1) resr = combine(t[--r], resr);
    }
    return combine(resl, resr);
}

void solve() {
    ll m;
    cin >> n >> m;
    cin >> str;
    t.resize(n * 2);

    for (ll i = 0; i < n; i++) t[n+i] = str[i] == '(' ? parseq{0, 1} : parseq{1, 0};
    build();
    
    for (ll q = 0; q < m; q++) {
        ll qt, l, r;
        cin >> qt >> l >> r;
        l--,r--;

        if (qt == 1) {
            parseq oldr = t[n+r];
            modify(r, t[n+l]);
            modify(l, oldr);
        } else {
            auto res = query(l, r + 1);
            // cerr << "[" << l << "; " << r + 1 << ") -> { " << res.in << ", " << res.out << " }\n";

            if (res.in == 0 && res.out == 0) cout << "Yes\n";
            else cout << "No\n";
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
