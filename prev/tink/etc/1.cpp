#ifndef DBG
// #pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

unordered_map<int, vector<int>> pos;
unordered_map<int, ll> cache;

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        pos[x].push_back(i);
    }

    for (ll i = 0; i < m; i++) {
        ll x;
        cin >> x;
        if (cache.count(x) > 0) {
            cout << cache[x] << '\n';
            continue;
        }
        if (pos.count(x) == 0) {
            cout << 0 << '\n';
            continue;
        }
        ll ans = 0;
        for (ll j = 0; j < pos[x].size(); j++) {
            ll rem = pos[x].size() - j - 1;
            ll remall = n - pos[x][j] - 1;
            maxa(ans, (j + 1) * (remall - rem));
        }

        cache[x] = ans;

        cout << ans << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
