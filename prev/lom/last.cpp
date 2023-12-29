// #pragma GCC optimize("Ofast")
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
using fl = long double;

vector<ll> t, c;

void push(ll n, ll nl, ll nr) {
    if (c[n] != 0) {
        t[n] += c[n];
        if (nr - nl > 1) {
            c[n*2+1] = c[n];
            c[n*2+2] = c[n];
        }
        c[n] = 0;
    }
}

void modify(ll n, ll nl, ll nr, ll l, ll r, ll x) {
    push(n, nl, nr);
    if (l <= nl && nr <= r) {
        c[n] += x;
        push(n, nl, nr);
        return;
    } else if (nr <= l || nl >= r) {
        return;
    }

    ll m = (nl + nr) / 2;
    modify(n * 2 + 1, nl, m, l, r, x);
    modify(n * 2 + 2, m, nr, l, r, x);
    // push(n * 2 + 1, nl, m);
    // push(n * 2 + 1, m, nr);
    t[n] = t[n*2+1] + t[n*2+2];
}

ll sumq(ll n, ll nl, ll nr, ll l, ll r) {
    push(n, nl, nr);
    if (l <= nl && nr <= r) {
        return t[n];
    }
    if (nr <= l || nl >= r) {
        return 0;
    }

    ll m = (nl + nr) / 2;
    return sumq(n * 2 + 1, nl, m, l, r) +
        sumq(n * 2 + 2, m, nr, l, r);
}

struct qr {
    ll l, r, t;

    ll ty, x;
};

void solve() {
    ll k;
    cin >> k;
    k++;

    t.resize(4 * k);
    c.resize(4 * k);

    ll n;
    cin >> n;

    vector<qr> qs;

    for (ll i = 0; i < n; i++) {
        ll l, r, t, v;
        cin >> l >> r >> t >> v;

        qs.push_back({l, r, t, 1, v});
    }

    ll m;
    cin >> m;

    for (ll i = 0; i < m; i++) {
        ll l, r, t;
        cin >> l >> r >> t;

        qs.push_back({l, r, t, 2, 0});
    }

    sort(qs.begin(), qs.end(), [](qr a, qr b) {
        if (a.t == b.t) {
            return a.ty < b.ty;
        }
        return a.t < b.t;
    });

    for (qr q: qs) {
        if (q.ty == 1) {
            modify(0, 0, k + 1, q.l, q.r + 1, q.x);
        }
        if (q.ty == 2) {
            cout << sumq(0, 0, k + 1, q.l, q.r + 1) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}