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
#include <sstream>

using namespace std;
using ll = long long;
using li = __int128;
using ull = unsigned long long;
using fl = long double;

const li inf = 1e18 + 1;

vector<li> d, fac;

ll fin(vector<ll> &l, ll i) {
    if (l[i] == i || l[i] == -1) {
        return i;
    } else {
        return fin(l, l[i]);
    }
}

vector<ll> nperm(li n, li k) {
    set<ll> free;

    for (int i = 0; i < n; ++i) {
        free.insert(i);
    }
    
    vector<ll> to(n + 1, -1);

    for (ll i = 1; i <= n; i++) {
        for (ll x: free) {
            if (i != x && i != fin(to, x)) {
                li cnt = fac[max(n - i - 1, li(0))];
                if (k < cnt) {
                    to[i] = x;
                    free.erase(x);
                    break;
                } else {
                    k -= cnt;
                }
            }
        }

        if (to[i] == -1) {
            return {};
        }
    }

    to[0] = ll(n);
    return to;
}

vector<ll> res;

bool descend(li n, li k, ll fst) {
    if (n == 0) {
        for (ll i: res) {
            cout << i << ' ';
        }
        cout << endl;
        return true;
    }

    for (ll i = 1; i <= n; i++) {
        ll ps = max(0ll, i - 2);
        li cnt = d[n-i] * fac[ps];

        if (k < cnt) {
            auto pr = nperm(i - 1, k / d[n-i]);

            if (pr.empty()) {
                return false;
            }

            for (ll x: pr) {
                res.push_back(x + fst);
            }

            if (descend(n - i, k % d[n-i], fst + i)) return true;
        } else {
            k -= cnt;
        }
    }

    return false;
}

void solve() {
    ll _n, _k;
    cin >> _n >> _k;
    li n = _n, k = _k;
    k--;

    d.assign(50, 0);
    fac.assign(50, 0);
    res.clear();

    fac[0] = 1;
    for (ll i = 1; i <= 20; i++) {
        fac[i] = fac[i-1] * i;
    }

    for (ll i = 21; i < 50; i++) {
        fac[i] = inf;
    }

    d[0] = 1;
    d[1] = 1;

    for (ll i = 2; i <= 22; i++) {
        for (ll j = 1; j <= i; j++) {
            d[i] += fac[max(0ll, j-2)] * d[i-j];
        }
    }

    for (ll i = 23; i < 50; i++) {
        d[i] = inf;
    }

    if (!descend(n, k, 1)) {
        cout << -1 << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

