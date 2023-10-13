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
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 5 * 1e5;

struct node {
    ll ln, rn, mn;
    bool full;
};

node op(node l, node r) {
    if (l.full && r.full) {
        return {
            l.ln + r.ln,
            l.ln + r.ln,
            l.ln + r.ln,
            true,
        };
    }
    if (l.full) {
        return {
            l.mn + r.ln,
            r.rn,
            max(l.mn + r.ln, r.mn),
            false,
        };
    }
    if (r.full) {
        return {
            l.ln,
            r.mn + l.rn,
            max(r.mn + l.rn, l.mn),
            false,
        };
    }

    return {
        l.ln,
        r.rn,
        max(max(l.mn, r.mn), l.rn + r.ln),
        false,
    };
}

node t[maxn * 2];
ll n;

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i] = op(t[i << 1], t[i << 1 | 1]);
    }
}

node query(ll l, ll r) {
    node la = {}, ra = {};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            la = op(la, t[l++]);
        }
        if (r & 1) {
            ra = op(t[--r], ra);
        }
    }
    return op(la, ra);
}

void upd(ll i, node x) {
    t[i + n] = x;
    for (i += n; i > 1; i >>= 1) {
        t[i >> 1] = op(t[i & ~1], t[i | 1]);
    }
}

void solve() {
    cin >> n;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (x == 0) {
            t[i + n] = {1, 1, 1, true};
        } else {
            t[i + n] = {};
        }
    }

    build();

    ll k;
    cin >> k;
    for (ll i = 0; i < k; i++) {
        string qt;
        cin >> qt;
        if (qt[0] == 'U') {
            ll i, x;
            cin >> i >> x;
            node y = {};
            if (x == 0) {
                y = {1, 1, 1, true};
            }
            upd(i - 1, y);
        } else {
            ll l, r;
            cin >> l >> r;
            node ans = query(l - 1, r);
            cout << ans.mn << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}