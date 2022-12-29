// #pragma GCC optimize("Ofast")
#include <numeric>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll a[100000];
ll ps[100000];
pair<ll, ll> pm[100000];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    partial_sum(a, a + n, ps, [](ll a, ll b) {return a + b;});

    ll li = 0;
    for (ll i = 1; i < n; i++) {
        if (ps[i-1] < pm[li].first) {
            pm[i].first = ps[i-1];
            pm[i].second = i;
            li = i;
        } else {
            pm[i] = pm[li];
        }
    }

    ll ms = a[0], mi = 0, me = 0;
    for (ll i = 1; i < n; i++) {
        if (ps[i] - pm[i].first > ms) {
            mi = pm[i].second;
            me = i;
            ms = ps[i] - pm[i].first;
        }
    }

    cout << mi + 1 << ' ' << me + 1 << ' ' << ms << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
