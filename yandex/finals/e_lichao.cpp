// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <chrono>
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
// using l1 = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1ll << 42;
const ll RB = 1ll << 20;
const ll LB = -RB;

struct linf {
    ll k, b;

    linf(ll k, ll b): k(k), b(b) {}

    ll operator()(ll x) const {
        return k * x + b;
    }
};

struct lichao {
    linf f;
    lichao *l = 0, *r = 0;

    lichao(linf f): f(f), l(0), r(0) {}

    ll get(ll nl, ll nr, ll x) {
        ll y = f(x);

        ll m = (nl + nr) / 2;

        if (nr - nl <= 1) {
            return y;
        }

        if (x < m) {
            return min(y, l ? l->get(nl, m, x) : inf);
        } else {
            return min(y, r ? r->get(m, nr, x) : inf);
        }
    }
};

lichao *add(lichao *t, ll nl, ll nr, linf f1) {
    t = new lichao(*t);
    ll m = (nl + nr) / 2;

    bool lb = f1(nl) < t->f(nl);
    bool mb = f1(m) < t->f(m);

    if (mb) swap(f1, t->f);

    if (nr - nl <= 1) {
        return t;
    }

    if (lb != mb) {
        if (!t->l) t->l = new lichao(f1);
        else t->l = add(t->l, nl, m, f1);
    } else {
        if (!t->r) t->r = new lichao(f1);
        else t->r = add(t->r, m, nr, f1);
    }

    return t;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<lichao*> roots(n);

    for (ll i = 0; i < n; i++) {
        roots[i] = new lichao({0, inf});
    }

    for (ll qi = 0; qi < m; qi++) {
        string qt;
        cin >> qt;

        if (qt == "#") {
            ll from, to;
            cin >> from >> to;
            from--, to--;

            roots[to] = roots[from];
        }

        if (qt == "+") {
            ll ix, b, k;
            cin >> ix >> b >> k;

            ix--, k *= -1;

            roots[ix] = add(roots[ix], LB, RB, {k, b});
        }

        if (qt == "?") {
            ll ix, x;
            cin >> ix >> x;
            ix--;

            cout << -roots[ix]->get(LB, RB, x) << '\n';
        }
    }

    cout << flush;
}

void stress() {
    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    while (1) {
        auto r = new lichao({0, inf});
        vector<linf> fs;
        for (ll i = 0; i < 100; i++) {
            ll k = uniform_int_distribution<ll>(-1000, 1000)(mt);
            ll b = uniform_int_distribution<ll>(-1000, 1000)(mt);
            r = add(r, LB, RB, {k, b});
            fs.push_back({k, b});

            for (ll j = 0; j < 100; j++) {
                ll x = uniform_int_distribution<ll>(-1000000, 1000000)(mt);
                ll ans = inf;
                for (auto &f: fs) ans = min(ans, f(x));
                ll ans2 = r->get(LB, RB, x);
                
                if (ans != ans2) {
                    cout << "KAL" << endl;
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}


