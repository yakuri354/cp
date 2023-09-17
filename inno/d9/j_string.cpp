// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    
    vector<ll> pc;
    
    vector<vector<ll>> d(n + 1, vector<ll>(n));

    for (ll i = 1; i + 1 < n; i++) {
        if (s[i-1] == s[i+1]) pc.push_back(i);
    }
    
    for (ll i = 0; i < n; i++) {
        
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
