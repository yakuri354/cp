#ifndef DBG
#pragma GCC optimize("Ofast")
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

ll a[150000];

void solve() {
    ll n, k;
    cin >> n >> k;

    for (ll i = 0; i < n; i++) cin >> a[i];

    // priority_queue<pair<ll, ll>, deque<pair<ll, ll>>, greater<>> queue;
    set<pair<ll, ll>> q;

    for (ll i = 0; i < k - 1; i++) {
        // queue.emplace(a[i], i);
        q.emplace(a[i], i);
    }

    for (ll i = 0; i <= n - k; i++) {
        while (q.begin()->second < i) q.erase(q.begin());
        // while (queue.top().second < i) queue.pop();
        q.emplace(a[i + k - 1], i + k - 1);
        // queue.emplace(a[i + k - 1], i + k - 1);
        // cout << queue.top().first << ' ';
        cout << q.begin()->first << ' ';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
