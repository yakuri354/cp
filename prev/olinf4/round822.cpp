// #include <cstdint>
// #ifndef DBG
#pragma GCC optimize("Ofast")
// #else
// #define _GLIBCXX_DEBUG
// #endif
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

void solve() {
    ll n, ans = 0;
    string bs;
    cin >> n >> bs;

    vector<bool> vis(n + 1, false);
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j += i) {
            if (vis[j]) continue;
            if (bs[j-1] == '0') {
                vis[j] = true;
                ans += i;
            } else {
                break;
            }
        }
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
