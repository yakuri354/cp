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

const ll maxn = 3e5 + 1;
ll t[maxn * 2], n;

void st_build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

ll st_get(ll l, ll r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += t[l++];
        if (r & 1) res += t[--r];
    }
    return res;
}

void st_add(ll x, ll i) {
    for (i += n; i > 0; i >>= 1) t[i] += x;
}

void first() {
    ll s;
    cin >> n >> s;

    vector<ll> a(s);
    for (ll &i: a) cin >> i;

    ll curr = 0, curr_min = 0;
    for (ll i = 0; i < s; i++) {
        curr += -a[i] + 1 + n - a[i];
        curr_min = min(curr_min, curr);
    }

    ll invs = 0;
    for (ll i: a) {
        invs += st_get(i, n);
        st_add(1, i - 1);
    }

    cout << invs << ' ' << curr_min << ' ' << curr << endl;
}

void second() {
    ll s, f_invs, f_delta, f_curr;
    cin >> n >> s;

    vector<ll> a(s);
    for (ll &i: a) cin >> i;

    cin >> f_invs >> f_delta >> f_curr;

    ll curr = f_curr, curr_min = f_delta;
    for (ll i = 0; i < s; i++) {
        curr += -a[i] + 1 + n - a[i];
        curr_min = min(curr_min, curr);
    }

    vector<bool> in_1(n, true);

    for (ll i = 0; i < s; i++) {
        in_1[a[i] - 1] = false;
    }

    for (ll i = 0; i < n; i++) {
        if (in_1[i]) st_add(1, i);
    }

    ll invs = f_invs;
    for (ll i: a) {
        invs += st_get(i, n);
        st_add(1, i - 1);
    }

    cout << min(invs, invs + curr_min) << endl;
}

void solve() {
    string t;
    cin >> t;

    if (t == "first") first();
    else second();
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

