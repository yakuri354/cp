#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

// void build(ll n, ll nl, ll nr) {
//     if (nr - nl <= 1) {
//         t[n] = 0;
//     }

//     ll m = (nl + nr) / 2;

//     build(n*2+1, nl, m);
//     build(n*2+2, m, nr);

//     t[n] = cmb(t[n*2+1], t[n*2+2]);
// }

struct node {
    ll mx, cnt;
};

node cmb(node a, node b) {
    if (a.mx == b.mx) {
        return {a.mx, a.cnt + b.cnt};
    } else if (a.mx > b.mx) {
        return a;
    } else {
        return b;
    }
}

struct segt {
    vector<ll> add;
    vector<node> t;

    segt(ll n) : add(n * 4), t(n * 4, {0, 0}) {
        build(0, 0, n);
    }

    void build(ll n, ll nl, ll nr) {
        if (nr - nl <= 1) {
            t[n] = {0, 1};
            return;
        }

        ll m = (nl + nr) / 2;

        build(n * 2 + 1, nl, m);
        build(n * 2 + 2, m, nr);

        t[n] = cmb(t[n*2+1], t[n*2+2]);
    }

    void push(ll n, ll nl, ll nr) {
        t[n].mx += add[n];
        if (nr - nl > 1) {
            add[n * 2 + 1] += add[n];
            add[n * 2 + 2] += add[n];
        }
        add[n] = 0;
    }

    node query(ll n, ll nl, ll nr, ll ql, ll qr) {
        push(n, nl, nr);
        if (ql <= nl && nr <= qr) {
            return t[n];
        }
        if (ql >= nr || qr <= nl) {
            return {0, nr - nl};
        }

        ll m = (nl + nr) / 2;

        return cmb(query(n * 2 + 1, nl, m, ql, qr),
                   query(n * 2 + 2, m, nr, ql, qr));
    }

    void add_segt(ll n, ll nl, ll nr, ll ql, ll qr, ll v) {
        push(n, nl, nr);
        if (ql <= nl && nr <= qr) {
            add[n] += v;
            push(n, nl, nr);
            return;
        }
        if (ql >= nr || qr <= nl) {
            return;
        }

        ll m = (nl + nr) / 2;

        add_segt(n * 2 + 1, nl, m, ql, qr, v);
        add_segt(n * 2 + 2, m, nr, ql, qr, v);

        t[n] = cmb(t[n * 2 + 1], t[n * 2 + 2]);
    }
};

struct evt {
    ll ty, x, yl, yh;
};

pll solve1(const vector<ll>& a, const vector<ll>& b, ll k) {
    const ll n = a.size();

    vector<ll> binv(n);
    for (ll i = 0; i < n; i++) {
        binv[b[i]] = i;
    }

    vector<evt> es;
    for (ll i = 0; i < n; i++) {
        es.push_back({1, max(0ll, i - k + 1), max(0ll, binv[a[i]] - k + 1), binv[a[i]] + 1});
        es.push_back({-1, i + 1, max(0ll, binv[a[i]] - k + 1), binv[a[i]] + 1});
    }

    segt t(n);

    ll ans = 0, cnt = 0;

    sort(es.begin(), es.end(), [](auto a, auto b) {
        return pll{a.x, a.ty} < pll{b.x, b.ty};
    });

    ll last = 0;
    for (auto e : es) {
        t.add_segt(0, 0, n, e.yl, e.yh, e.ty);
        if (t.t[0].mx > ans) {
            ans = t.t[0].mx;
            cnt = t.t[0].cnt;
        } else if (t.t[0].mx == ans && e.x > last) {
            cnt += t.t[0].cnt * (e.x - last);
        }

        last = e.x;
    }

    return {ans, cnt};
}

void solve() {
    ll n, k, q;
    cin >> n >> k >> q;

    vector<ll> a(n), b(n);
    for (ll &i: a) cin >> i, i--;
    for (ll &i: b) cin >> i, i--;

    auto s0 = solve1(a, b, k);
    cout << s0.first << ' ' << s0.second << '\n';

    for (ll i = 0; i < q; i++) {
        ll p;
        cin >> p;
        p--;

        swap(a[p], a[p+1]);

        auto s0 = solve1(a, b, k);
        cout << s0.first << ' ' << s0.second << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
