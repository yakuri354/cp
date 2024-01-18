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
using ll = __int128;
using l1 = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1ll << 62;
const ll RB = 1ll << 60;
const ll LB = -RB;

struct linf {
    ll k, b;

    ll operator()(ll x) const {
        return k * x + b;
    }
};

class li_chao {
    unordered_map<l1, linf> t;

    void add(ll i, ll l, ll r, linf f) {
        if (!t.count(i)) {
            t[i] = f;
            return;
        }

        ll m = (l + r) / 2;

        bool lb = f(l) < t[i](l);
        bool mb = f(m) < t[i](m);

        if (mb) swap(f, t[i]);

        if (r - l <= 1) {
            return;
        }

        if (lb != mb) {
            add(i * 2, l, m, f);
        } else {
            add(i * 2 + 1, m, r, f);
        }
    }

    ll get(ll i, ll l, ll r, ll x) {
        if (!t.count(i)) return inf;
        ll y = t[i](x);

        ll m = (l + r) / 2;

        if (r - l <= 1) {
            return y;
        }

        if (x < m) {
            return min(y, get(i * 2, l, m, x));
        } else {
            return min(y, get(i * 2 + 1, m, r, x));
        }
    }

public:
    void add(linf f) {
        add(1, LB, RB, f);
    }

    ll get(ll x) {
        return get(1, LB, RB, x);
    }
};

void solve() {
    l1 n;
    cin >> n;

    vector<l1> a(n), b(n);

    for (l1 &i: a) cin >> i;
    for (l1 &i: b) cin >> i;

    if (n == 1) {
        cout << 0 << endl;
        return;
    }

    li_chao t;

    t.add({b[0], 0});

    vector<ll> d(n);

    for (ll i = 1; i < n; i++) {
        d[i] = t.get(a[i]);

        t.add({b[i], d[i]});
    }

    if (d[n-1] == inf) {
        exit(-1);
    }

    cout << l1(d[n - 1]) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

