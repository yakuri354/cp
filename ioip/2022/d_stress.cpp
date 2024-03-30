#include <chrono>
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

const ll BIT = 7;

struct node {
    ll ass = -1, shift = 0;
    array<ll, BIT> sums = {0};
};

vector<node> t;
vector<ll> a;

void push(ll i, ll l, ll r) {
    if (t[i].ass != -1 && t[i].shift != 0) {
        exit(-1);
    }

    if (t[i].sums[0] < 0) {
        exit(-1);
    }

    if (t[i].ass != -1) {
        if (t[i].ass < 0) {
            exit(-1);
        }
        t[i].sums.fill(0);

        ll x = t[i].ass;
        if (r - l < 0) {
            exit(-1);
        }
        for (ll j = 0; j < BIT; j++) {
            t[i].sums[j] = x * (r - l);
            x = __builtin_popcountll(x);
        }

        if (r - l > 1) {
            t[i * 2 + 1].ass = t[i].ass;
            t[i * 2 + 1].shift = 0;
            t[i * 2 + 2].ass = t[i].ass;
            t[i * 2 + 2].shift = 0;
        }

        t[i].ass = -1;
        t[i].shift = 0;
    }

    while (t[i].shift > 0) {
        rotate(t[i].sums.begin(), t[i].sums.begin() + 1, t[i].sums.end());
        t[i].sums[BIT - 1] = t[i].sums[BIT - 2];
        t[i].shift--;

        if (r - l > 1) {
            ll m = (l + r) / 2;
            push(i * 2 + 1, l, m);
            t[i * 2 + 1].shift++;
            push(i * 2 + 2, m, r);
            t[i * 2 + 2].shift++;
        }
    }
}

node cmb(node l, node r) {
    node x = {};
    x.sums.fill(0);

    for (ll i = 0; i < BIT; i++) {
        x.sums[i] = l.sums[i] + r.sums[i];
        if (x.sums[i] < 0) {
            exit(-1);
        }
    }

    return x;
}

void build(ll i, ll l, ll r) {
    if (r - l <= 1) {
        t[i] = node{.ass = a[l]};
        push(i, l, r);

        return;
    }

    ll m = (l + r) / 2;

    build(i * 2 + 1, l, m);
    build(i * 2 + 2, m, r);

    t[i] = cmb(t[i * 2 + 1], t[i * 2 + 2]);
}

node query(ll i, ll l, ll r, ll ql, ll qr) {
    push(i, l, r);

    if (qr <= l || r <= ql) {
        node x{};
        x.sums.fill(0);

        return x;
    }

    if (ql <= l && r <= qr) {
        return t[i];
    }

    ll m = (l + r) / 2;

    return cmb(query(i * 2 + 1, l, m, ql, qr), query(i * 2 + 2, m, r, ql, qr));
}

void modify(ll i, ll l, ll r, ll ql, ll qr, ll ass, ll shift) {
    push(i, l, r);

    if (qr <= l || r <= ql) {
        return;
    }

    if (ql <= l && r <= qr) {
        t[i].ass = ass;
        t[i].shift = shift;

        push(i, l, r);

        return;
    }

    ll m = (l + r) / 2;

    modify(i * 2 + 1, l, m, ql, qr, ass, shift);
    modify(i * 2 + 2, m, r, ql, qr, ass, shift);

    t[i] = cmb(t[i * 2 + 1], t[i * 2 + 2]);
}

void solve() {
    // ll n;
    // cin >> n;
    const ll n = 2;

    t.resize(n * 4);
    a.resize(n);

    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> xd(0, 10);

    for (ll& i : a)
        i = 0;

    build(0, 0, n);

    for (ll it = 0;; it++) {
        if (it % 10000 == 0) {
            cout << "-> " << it << endl << endl;
        }

        ll l = uniform_int_distribution<ll>(1, n)(mt);
        ll r = uniform_int_distribution<ll>(1, n)(mt);

        if (r < l) swap(l, r);

        l--;

        if (it % 2 == 1) {
            ll ans_s = query(0, 0, n, l, r).sums[0];
            ll ans_d = 0;

            for (ll i = l; i < r; i++) {
                ans_d += a[i];
            }

            if (ans_s != ans_d) {
                cout << "kal" << endl;
                auto res = query(0, 0, n, l, r);
                exit(-1);
            }

            continue;
        }

        ll ty = uniform_int_distribution<ll>(2, 3)(mt);

        if (ty == 2) {
            ll x = xd(mt);
            // if (uniform_int_distribution<ll>(0, 1)(mt)) {
            //     x = 0;
            // }

            modify(0, 0, n, l, r, x, 0);

            for (ll i = l; i < r; i++) {
                a[i] = x;
            }
        }

        if (ty == 3) {
            modify(0, 0, n, l, r, -1, 1);

            for (ll i = l; i < r; i++) {
                a[i] = __builtin_popcountll(a[i]);
            }
        }

        // for (ll i = 0; i < n; i++) {
        //     if (a[i] != query(0, 0, n, i, i + 1).sums[0]) {
        //         cout << "kal 2" << endl;
        //         exit(-1);
        //     }
        // }
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
