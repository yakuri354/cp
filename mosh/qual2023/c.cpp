// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"
#include <assert.h>

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> seq(n);
    vector<pair<ll, ll>> edges;

    for (ll i = 0; i < n; i++) {
        cin >> seq[i].first;
        seq[i].second = i;
    }


    for (;;) {
        sort(seq.begin(), seq.end(), greater<>());

        if (seq[0].first == 0) break;

        for (ll i = 1; i <= seq[0].first; i++) {
            assert(seq[i].first > 0);
            seq[i].first -= 1;
            edges.emplace_back(seq[0].second, seq[i].second);
        }

        seq[0].first = 0;
    }
    
    cout << edges.size() << endl;
    for (auto [a, b] : edges) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t --> 0) solve();
}
