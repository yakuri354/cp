// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    string s;
    ll n, graph[3][3];
    cin >> s;
    n = s.length();

    for (ll i = 0; i < n - 1; i++) {
        graph[s[i] - 'a'][s[i+1] - 'a']++;
    }

    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll g, t; cin >> g >> t; while (t --> 0)
    solve();
}
