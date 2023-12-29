#include <random>
#ifndef DBG
// #pragma GCC optimize("Ofast")
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
using ull = unsigned long long;

const ull X = 307;
ull P = 1e9+7;
ull N, M;

ull p[100002];
string input;

struct hstr {
    ull len;
    ull dh;
    ull rh;
};

hstr t[200002];

hstr combine(const hstr &l, const hstr &r) {
    return hstr {
        .len = l.len + r.len,
        .dh = (l.dh + (r.dh * p[l.len]) % P) % P,
        .rh = ((l.rh * p[r.len]) % P + r.rh) % P
    };
}

hstr news(char c) {
    return hstr {1, ull(c - 'a'), ull(c - 'a')};
}

void build() {
    for (ull i = N - 1; i > 0; i--) t[i] = combine(t[i<<1], t[i<<1|1]);
}

void modify(ull p, char c) {
    input[p] = c;
    for (t[p += N] = news(c); p > 1; p >>= 1) t[p>>1] = combine(t[p], t[p^1]);
}

mt19937 prng;

bool query(ull l, ull r) {
    ll st = l;
    if (r - l == 1) return true;
    hstr resl = {}, resr = {};
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l&1) resl = combine(resl, t[l++]);
        if (r&1) resr = combine(t[--r], resr);
    }

    auto ans = combine(resl, resr);

    if (ans.dh != ans.rh) return false;

    ll m = ans.len / 2;
    uniform_int_distribution<ull> dist(0, m - 1);

    for (ll i = 0; i < 100; i++) {
        ll pos = dist(prng);

        if (ans.len % 2 == 0) {
            if (input[st + m - 1 - pos] != input[st + m + pos]) {
                return false;
            }
        } else {
            if (input[st + m - 1 - pos] != input[st + m + 1 + pos]) {
                return false;
            }
        }
    }

    return true;
}

void solve() {
    cin >> input >> M;
    N = input.length();

    random_device rd;
    prng.seed(rd());

    p[0] = 1;
    for (ull i = 1; i <= N; i++) p[i] = (p[i-1] * X) % P;

    for (ull i = 0; i < N; i++) t[N+i] = news(input[i]);

    build();

    for (ull q = 0; q < M; q++) {
        string ty;
        cin >> ty;

        if (ty[0] == 'c') {
            ll p;
            char c;
            cin >> p >> c;
            modify(p - 1, c);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << (query(l - 1, r) ? "Yes" : "No") << endl;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
