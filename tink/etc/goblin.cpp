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

deque<ll> ld;
deque<ll> rd;

void fix() {
    while (ld.size() > rd.size()) {
        auto el = ld.back();
        rd.push_front(el);
        ld.pop_back();
    }
    if (rd.size() > ld.size() + 1) {
        auto el = rd.front();
        ld.push_back(el);
        rd.pop_front();
    }
}

void solve() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        string qt;
        cin >> qt;

        if (qt == "+") {
            ll x;
            cin >> x;
            ld.push_front(x);
        }
        if (qt == "*") {
            ll x;
            cin >> x;
            if (rd.size() == ld.size()) {
                rd.push_front(x);
            } else {
                ld.push_back(x);
            }
        }
        if (qt == "-") {
            cout << rd.back() << '\n';
            rd.pop_back();
        }
        fix();
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
