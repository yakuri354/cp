// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct dr {
    ll a, t;
};

const ll maxn = 2 * 1e5;

dr a[maxn];
ll n, T;

bool chk(ll x) {
    ll cnt = 0, sum = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i].a < x) continue;
        if (sum > T) return false;
        if (cnt >= x) return true;
        sum += a[i].t;
        cnt++;
    }

    if (sum > T) return false;
    if (cnt >= x) return true;

    return false;
}

void solve() {
    cin >> n >> T;

    for (ll i = 0; i < n; i++) {
        cin >> a[i].a >> a[i].t;
    }

    sort(a, a + n, [](auto a, auto b) {
        return a.t < b.t;
    });

    ll lo = 0, hi = n + 1;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;
        if (chk(m)) lo = m;
        else hi = m;
    }

    cout << lo << '\n' << lo << '\n';

    ll cnt = 0, sum = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i].a < lo) continue;
        if (sum > T) break;
        if (cnt >= lo) break;
        sum += a[i].t;
        cnt++;
        cout << i + 1 << ' ';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
