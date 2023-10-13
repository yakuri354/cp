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

const ll inf = INT32_MAX;

struct M {
    ll me, mcnt;

    M operator+(const M& other) const {
        if (me == other.me) {
            return M{me, mcnt + other.mcnt};
        } else if (me < other.me) {
            return *this;
        } else {
            return other;
        }
    }
};

const M id = {inf, 0};

vector<M> t;
vector<ll> m;

void push(ll n, ll nl, ll nr) {
    t[n].me += m[n];

    if (nr - nl > 1) {
        m[n * 2 + 1] += m[n];
        m[n * 2 + 2] += m[n];
    }

    m[n] = 0;
}

void add(ll n, ll nl, ll nr, ll ql, ll qr, ll x) {
    push(n, nl, nr);
    if (ql <= nl && nr <= qr) {
        m[n] += x;
        push(n, nl, nr);
        return;
    }

    if (nl >= qr || nr <= ql) {
        return;
    }

    ll m = (nl + nr) / 2;

    add(n * 2 + 1, nl, m, ql, qr, x);
    add(n * 2 + 2, m, nr, ql, qr, x);

    t[n] = t[n * 2 + 1] + t[n * 2 + 2];
}

vector<ll> yc;
unordered_map<ll, ll> cy;

void build(ll n, ll nl, ll nr) {
    if (nr - nl < 2) {
        t[n] = {
            .me = 0,
            .mcnt = nr == yc.size() ? 0 : yc[nr] - yc[nl]  // sus
        };
        return;
    }

    ll m = (nl + nr) / 2;

    build(n * 2 + 1, nl, m);
    build(n * 2 + 2, m, nr);

    t[n] = t[n * 2 + 1] + t[n * 2 + 2];
}

struct ev {
    ll x, lo, hi, ty;

    ev(ll x, ll lo, ll hi, ll ty) : x(x), lo(lo), hi(hi), ty(ty) {
    }

    auto t() {
        return make_tuple(x, ty, lo, hi);
    }
};

struct sq {
    ll x1, y1, x2, y2;
};

void solve() {
    ll n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return;
    }

    set<ll> ycs;

    vector<ev> evs;

    vector<sq> qs(n);

    for (auto& [x1, y1, x2, y2] : qs) {
        cin >> x1 >> y1 >> x2 >> y2;

        ycs.insert(y1);
        ycs.insert(y2);
    }

    yc.assign(ycs.begin(), ycs.end());

    for (ll i = 0; i < yc.size(); i++) {
        cy[yc[i]] = i;
    }

    evs.reserve(qs.size() * 2 + 1);

    for (auto& [x1, y1, x2, y2] : qs) {
        evs.emplace_back(x1, cy[y1], cy[y2], 1);
        evs.emplace_back(x2, cy[y1], cy[y2], -1);
    }

    sort(evs.begin(), evs.end(), [](ev a, ev b) { return a.t() < b.t(); });

    t.resize(yc.size() * 4);
    m.resize(yc.size() * 4);
    build(0, 0, yc.size());

    ll ans = 0, last = -inf;

    for (ev e : evs) {
        ans += (e.x - last) *
               (t[0].me > 0 ? t[0].mcnt : yc.back() - yc.front() - t[0].mcnt);

        add(0, 0, yc.size(), e.lo, e.hi, e.ty);

        last = e.x;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
