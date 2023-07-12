// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    string s;
    cin >> s;

    set<char> ss;

    for (char c : s) {
        ss.insert(c);
    }

    if (ss.size() == 1) {
        cout << -1 << endl;
    } else {
        cout << s.size() - 1 << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
