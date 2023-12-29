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

using sll = set<ll>;
sll by_v;
multimap<ll, sll::iterator, greater<>> by_i;
map<ll, set<ll>> idxs;

ll a[500001];

void solve() {
    ll n, k, p, ans = 0;
    cin >> n >> k >> p;
    for (ll i = 0; i < p; i++) {
        cin >> a[i];
        if (!idxs.count(a[i])) idxs[a[i]] = {};
        idxs[a[i]].insert(i);
    }
    for (ll i = 0; i < p; i++) {
        if (by_v.count(a[i])) {
            idxs[a[i]].erase(i);
            continue;
        }
        ans++;
        if (by_v.size() == k) {
            auto it = by_i.begin();
            if (it != by_i.end()) {
                by_v.erase(it->second);
                by_i.erase(it);
            }
        }
        auto [it2, b] = by_v.insert(a[i]);
        idxs[a[i]].erase(i);
        auto nextit = idxs[a[i]].begin();
        ll nexti = INT64_MAX;
        if (nextit != idxs[a[i]].end()) nexti = *nextit;
        by_i.insert({nexti, it2});
    }
    cout << ans << '\n';
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
