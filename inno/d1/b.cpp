// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxc = 2e5;
const ll maxn = maxc * 2 + 100;

struct node {
    ll maxv, idx;
};

node op(node a, node b) {
    if (a.maxv > b.maxv) return a;
    else return b;
}

const node n_id = node{-inf, 0};

node t[maxn * 4];
ll mod[maxn * 4];

void build(ll n, ll nl, ll nr) {
    if (nr - nl <= 1) {
        t[n] = {0, nl};
        return;
    }

    ll m = (nl + nr) / 2;
    build(n * 2 + 1, nl, m);
    build(n * 2 + 2, m, nr);

    t[n] = op(t[n * 2 + 1], t[n * 2 + 2]);
}

void push(ll n, ll nl, ll nr) {
    if (nr - nl > 1) {
        mod[n * 2 + 1] += mod[n];
        mod[n * 2 + 2] += mod[n];
    }

    t[n].maxv += mod[n];
    mod[n] = 0;
}

node query(ll n, ll nl, ll nr, ll ql, ll qr) {
    push(n, nl , nr);

    if (ql <= nl && nr <= qr) {
        return t[n];
    }

    if (qr <= nl || ql >= nr) {
        return n_id;
    }

    ll m = (nl + nr) / 2;
    return op(
        query(n * 2 + 1, nl, m, ql, qr),
        query(n * 2 + 2, m, nr, ql, qr)
    );
}

void add_mut(ll n, ll nl, ll nr, ll ql, ll qr, ll x) {
    push(n, nl , nr);

    if (ql <= nl && nr <= qr) {
        mod[n] += x;
        push(n, nl, nr);
        return;
    }

    if (qr <= nl || ql >= nr) {
        return;
    }

    ll m = (nl + nr) / 2;

    add_mut(n * 2 + 1, nl, m, ql, qr, x);
    add_mut(n * 2 + 2, m, nr, ql, qr, x);

    t[n] = op(t[n * 2 + 1], t[n * 2 + 2]);
}

struct ev {
    ll ty, x, ly, ry;
};

void solve() {
    ll n;
    cin >> n;

    build(0, 0, maxn);

    vector<ev> evs;

    for (ll i = 0; i < n; i++) {
        ll lx, ly, hx, hy;
        cin >> lx >> ly >> hx >> hy;
        lx += maxc;
        ly += maxc;
        hx += maxc;
        hy += maxc;
        evs.push_back({
            1, lx, ly, hy + 1
        });
        evs.push_back({
            -1, hx + 1, ly, hy + 1
        });
    }

    sort(evs.begin(), evs.end(), [](auto a, auto b) {
        return make_pair(a.x, a.ty) < make_pair(b.x, b.ty);
    });

    ll best = -inf;
    ll ax = 0, ay = 0;
    for (ev e : evs) {
        add_mut(0, 0, maxn, e.ly, e.ry, e.ty);
        if (e.ty == -1) continue;
        auto state = query(0, 0, maxn, 0, maxn);
        if (state.maxv > best) {
            best = state.maxv;
            ax = e.x;
            ay = state.idx;
        }
    }

    cout << best << endl;
    cout << ax - maxc << ' ' << ay - maxc << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
