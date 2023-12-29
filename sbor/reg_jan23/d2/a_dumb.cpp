// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct ent {
    ll boys0, boys1, len, idx;

    bool operator<(const ent &other) {
        return this->idx < other.idx;
    }
};

void solve() {
    ll n;
    cin >> n;

    vector<string> a(n);
    vector<ent> b(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = {0, 0, 0, i};
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < a[i].length(); j++) {
            if (a[i][j] == 'B') {
                b[i].boys0 += j % 2 == 0;
                b[i].boys1 += j % 2 == 1;
            }
        }
        b[i].len = a[i].length();
    }

    ll ans = -inf;
    while (next_permutation(b.begin(), b.end())) {
        ll prefix = 0, boys = 0;
        for (ll i = 0; i < n; i++) {
            if (prefix % 2 == 0) boys += b[i].boys0;
            else boys += b[i].boys1;
            prefix += b[i].len;
        }
        ans = max(ans, boys);
    }
    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
