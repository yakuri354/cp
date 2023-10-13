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

#ifdef DBG
#define inv(x)                                                       \
    if (!(x)) {                                                      \
        cerr << "invariant " #x " violated at " << __LINE__ << endl; \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

vector<ll> t, a;

void build(ll i, ll l, ll r) {
    if (r - l < 2) {
        t[i] = (a[l] == 0);
        return;
    }

    ll m = (l + r) / 2;

    build(i * 2 + 1, l, m);
    build(i * 2 + 2, m, r);

    t[i] = t[i * 2 + 1] + t[i * 2 + 2];
}

void modify(ll i, ll l, ll r, ll p) {
    if (r - l < 2) {
        t[i] = (a[l] == 0);
        return;
    }

    ll m = (l + r) / 2;

    if (p < m) {
        modify(i * 2 + 1, l, m, p);
    } else {
        modify(i * 2 + 2, m, r, p);
    }

    t[i] = t[i * 2 + 1] + t[i * 2 + 2];
}

ll descend(ll i, ll l, ll r, ll k) {
    inv(t[i] >= k);

    if (r - l < 2) {
        return l;
    }

    ll m = (l + r) / 2;

    if (k <= t[i * 2 + 1]) {
        return descend(i * 2 + 1, l, m, k);
    } else {
        return descend(i * 2 + 2, m, r, k - t[i * 2 + 1]);
    }
}

ll sum(ll i, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) {
        return t[i];
    }

    if (ql >= r || qr <= l) {
        return 0;
    }

    ll m = (l + r) / 2;

    return sum(i * 2 + 1, l, m, ql, qr) + sum(i * 2 + 2, m, r, ql, qr);
}

void solve() {
    ll m, n;
    cin >> n;

    t.resize(n * 4, 0);
    a.resize(n);

    for (ll& i : a) {
        cin >> i;
    }

    build(0, 0, n);

    cin >> m;

    for (ll i = 0; i < m; i++) {
        string ty;
        cin >> ty;
        if (ty[0] == 's') {
            ll l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            
            if (sum(0, 0, n, l, r + 1) < k) {
                cout << "-1\n";
                continue;
            }
            
            if (l > 0) {
                k += sum(0, 0, n, 0, l);
            }
            
            cout << descend(0, 0, n, k) + 1 << '\n';
        } else if (ty[0] == 'u') {
            ll i, x;
            cin >> i >> x;
            i--;
            a[i] = x;
            modify(0, 0, n, i);
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
