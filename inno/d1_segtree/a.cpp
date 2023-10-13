#include <algorithm>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 3e5;
const ll maxc = 1e9 + 1;

unordered_map<ll, ll> t;

ll tt(ll i) {
    if (t.count(i)) return t[i];
    else return 0;
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += maxc, r += maxc; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += tt(l++);
        if (r & 1) res += tt(--r);
    }
    return res;
}

void set_point(ll i, ll x) {
    t[i += maxc] = x;
    for (; i > 1; i >>= 1) {
        // t[i] = tt(i*2) + tt(i*2 + 1);
        t[i >> 1] = tt(i) + tt(i ^ 1);
    }
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> vals;

    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        string qt;
        cin >> qt;
        if (qt == "+") {
            ll x;
            cin >> x;
            if (ans != 0) x = (x + ans) % ll(1e9);
            set_point(x, x);
            ans = 0;
        }
        if (qt == "?") {
            ll l, r;
            cin >> l >> r;
            ans = query(l, r + 1);
            cout << ans << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
