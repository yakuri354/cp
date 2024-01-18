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

const ll inf = 1ll << 50;

struct el {
    ll mn, mx;
    bool is_s;
};

el op(el l, el r) {
    if (l.mn == -inf) return r;
    if (r.mn == -inf) return l;

    return {
        min(l.mn, r.mn),
        max(l.mx, r.mx),
        l.is_s && r.is_s && l.mx <= r.mn
    };
}

const el el_id = {-inf, -inf, 1};

vector<el> t;
vector<el> a;

void build(ll i, ll l, ll r) {
    if (r - l <= 1) {
        t[i] = a[l];
        return;
    }

    ll m = (l + r) / 2;

    build(i * 2 + 1, l, m);
    build(i * 2 + 2, m, r);

    t[i] = op(t[i*2+1], t[i*2+2]);
}

void modify(ll i, ll l, ll r, ll p, el x) {
    if (r - l <= 1) {
        t[i] = x;
        return;
    }

    ll m = (l + r) / 2;

    if (p < m) {
        modify(i * 2 + 1, l, m, p, x);
    } else {
        modify(i * 2 + 2, m, r, p, x);
    }

    t[i] = op(t[i*2+1], t[i*2+2]);
}

void solve() {
    ll n, q;
    cin >> n >> q;

    a.resize(n);

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        a[i] = {x, x, true};
    }

    t.resize(n * 4, el_id);
    build(0, 0, n);

    for (ll i = 0; i < q; i++) {
        string ty;
        cin >> ty;

        if (ty == "!") {
            ll i, x;
            cin >> i >> x;

            modify(0, 0, n, i-1, el{x, x, true});
        } else if (ty == "?") {
            if (t[0].is_s) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
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

