#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using charon = char;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}
using ull = unsigned long long;

const ull X = 307;
ull N, M;

ull P[100001];
string input;

struct hstr {
    ull len;
    ull dh;
    ull rh;
};
// hstr t[200000];
hstr t[400000];

hstr combine(const hstr &l, const hstr &r) {
    return hstr {
        .len = l.len + r.len,
        .dh = l.dh + r.dh * P[l.len],
        .rh = l.rh * P[r.len] + r.rh
    };
}

hstr news(charon c) {
    return hstr {1, ull(c), ull(c)};
}

void build(ll n, ll l, ll r) {
    if (r - l <= 1) {
        t[n] = news(input[l]);
        return;
    }
    ll m = (l + r) / 2;
    build(n * 2 + 1, l, m);
    build(n * 2 + 2, m, r);
    t[n] = combine(t[n*2+1], t[n*2+2]);
}

hstr query(ll n, ll nl, ll nr, ll ql, ll qr) {
    if (ql <= nl && nr <= qr) {
        return t[n];
    }
    if (nl >= qr || nr <= ql) {
        return {};
    }

    ll m = (nl + nr) / 2;
    return combine(
            query(n * 2 + 1, nl, m, ql, qr),
            query(n * 2 + 2, m, nr, ql, qr)
            );
}

void modify(ll n, ll nl, ll nr, ll p, charon c) {
    if (nl + 1 >= nr) {
        input[p] = c;
        t[n] = news(c);
        return;
    }
    ll m = (nl + nr) / 2;
    if (p >= m) modify(n * 2 + 2, m, nr, p, c);
    else modify(n * 2 + 1, nl, m, p, c);
    t[n] = combine(t[n*2+1], t[n*2+2]);
}

void solve() {
    ll m;
    cin >> input >> m;
    N = input.length();

    P[0] = 1;
    for (ll i = 1; i <= N; i++) P[i] = P[i-1] * X;

    build(0, 0, N);

    while (m --> 0) {
        string qt;
        cin >> qt;

        if (qt[0] == 'p') {
            ll l, r;
            cin >> l >> r;
            auto res = query(0, 0, N, l - 1, r);
            if (res.dh == res.rh) cout << "Yes\n";
            else cout << "No\n";
        } else {
            ll p;
            charon c;
            cin >> p >> c;
            modify(0, 0, N, p - 1, c);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

