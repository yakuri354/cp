#ifndef DBG
#pragma GCC optimize("Ofast")
#else
#define _GLIBCXX_DEBUG
#endif
#include "bits/stdc++.h"

using namespace std;
using ll = unsigned long long;

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

template<typename T> T maxa(T &a, const T &b) {
    if (a < b) a = b;
    return a;
}

template<typename T> T mina(T &a, const T &b) {
    if (a > b) a = b;
    return a;
}

map<ll, set<ll>> setswith;
set<ll> sets[100001];

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    for (ll i = 0; i < k; i++) {
        string ty;
        cin >> ty;
        if (ty == "ADD") {
            ll e, s;
            cin >> e >> s;

            sets[s].insert(e);
            if (!setswith.count(e)) setswith[e] = {};
            setswith[e].insert(s);
        }
        if (ty == "DELETE") {
            ll e, s;
            cin >> e >> s;

            sets[s].erase(e);
            setswith[e].erase(s);
        }
        if (ty == "CLEAR") {
            ll s;
            cin >> s;

            for (auto e : sets[s]) {
                setswith[e].erase(s);
            }
            sets[s].clear();
        }
        if (ty == "LISTSET") {
            ll s;
            cin >> s;

            if (sets[s].size() == 0) {
                cout << "-1\n";
                continue;
            }

            for (auto e : sets[s]) {
                cout << e << ' ';
            }
            cout << '\n';
        }
        if (ty == "LISTSETSOF") {
            ll e;
            cin >> e;
            if (!setswith.count(e)) {
                cout << "-1\n";
                continue;
            }

            for (auto s : setswith[e]) {
                cout << s << ' ';
            }
            cout << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
