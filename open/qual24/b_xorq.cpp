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
using ull = long long;
using fl = long double;

const ll maxp = 20;
const ll N = 1 << maxp;

ull t[2 * N];
ull c[2 * N];

ull a[N];

void build() {
    for (ull i = 0; i < N; i++) {
        t[N + i] = a[i];
        c[N + i] = -1;
    }
    for (ull i = N - 1; i > 0; i--) {
        t[i] = t[i * 2] + t[i * 2 + 1];
        c[i] = -1;
    }
}

void push(ull v, ll nl, ll nr) {
    if (c[v] != -1) {
        t[v] = c[v] * (nr - nl);
        if (v < N) {
            c[v * 2] = c[v];
            c[v*2+1] = c[v];
        }
        c[v] = -1;
    }
}

ll sum_q(ll v, ll nl, ll nr, ll depth, ll l, ll r, ll k) {
    ll vx = ((v << (maxp - depth)) ^ k) >> (maxp - depth);
    push(vx, nl, nr);
    if (l <= nl && nr <= r) {
        return t[vx];
    }

    if (l >= nr || r <= nl) {
        return 0;
    }

    ll m = (nl + nr) / 2;

    return sum_q(v * 2, nl, m, depth + 1, l, r, k) 
        + sum_q(v * 2 + 1, m, nr, depth + 1, l, r, k);
}

void set_q(ll v, ll nl, ll nr, ll depth, ll l, ll r, ll k, ll value) {
    ll vx = ((v << (maxp - depth)) ^ k) >> (maxp - depth);
    push(vx, nl, nr);
    if (l <= nl && nr <= r) {
        c[vx] = value;
        push(vx, nl, nr);
        return;
    }

    if (l >= nr || r <= nl) {
        return;
    }

    ll m = (nl + nr) / 2;
    set_q(v * 2, nl, m, depth + 1, l, r, k, value);
    set_q(v * 2 + 1, m, nr, depth + 1, l, r, k, value);

    t[vx] = t[vx * 2] + t[vx * 2 + 1];
}

void solve() {
    ll p;
    cin >> p;
    ll n = 1 << p;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    build();

    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++) {
        ll ty;
        cin >> ty;
        
        if (ty == 1) {
            ll l, r, k, v;
            cin >> l >> r >> k >> v;

            set_q(1, 0, N, 0, l, r + 1, k, v);
        }

        if (ty == 2) {
            ll l, r, k;
            cin >> l >> r >> k;

            ull ans = sum_q(1, 0, N, 0, l, r + 1, k);

            cout << ans << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
