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

const ll inf = INT32_MAX;
const ll maxn = 1e5;

ll a[maxn], t[maxn * 2], n;

ll op(ll l, ll r) {
    if (l == -1) return r;
    if (r == -1) return l;

    if (a[l] > a[r]) return l;
    else return r;
}

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i] = op(t[i*2], t[i*2+1]);
    }
}

ll query(ll l, ll r) {
    ll res = -1;

    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = op(res, t[l++]);
        if (r & 1) res = op(res, t[--r]);
    }
    
    return res;
}

ll check_right(ll p, ll k) {
    if (n - k < p) return 0;
    
    ll m = p + k;
    
    if (m != n) {
        if (a[m] < a[p]) return 0;

        ll real_m = query(p, m + 1);

        if (m != real_m) {
            if (m == query(real_m + 1, m + 1) && a[query(p, real_m)]) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    
    ll prev_m = query(p, m);

    // todo check starting from prev_m

    return m - prev_m - (prev_m == p);
}

ll check_left(ll p, ll k) {
    if (p + 1 < k) return 0;
    
    ll m = p - k;
    
    if (m != -1) {
        if (a[m] < a[p]) return 0;

        ll real_m = query(m, p + 1);

        if (m != real_m) {
            if (m == query(m, real_m) && a[query(real_m + 1, p + 1)]) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    ll prev_m = query(m + 1, p + 1);

    return prev_m - m - (prev_m == p);
}

void solve() {
    ll q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        t[n + i] = i;
    }
    
    build();

    for (ll i = 0; i < q; i++) {
        ll p, k;
        cin >> p >> k;
        
        p--;
        
        if (k == 1) {
            cout << 1 << '\n';
        } else {
            cout << check_left(p, k) + check_right(p, k) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
