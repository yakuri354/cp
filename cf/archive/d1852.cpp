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
using pll = pair<ll, ll>;

void solve() {
    ll n, k;
    cin >> n >> k;
    
    string s;
    cin >> s;

    ll x = 0;
    for (ll i = 0; i + 1 < n; i++) {
        if (s[i] != s[i+1]) {
            x += 2;
        }
    }

    if (x > k || (k - x) % 2 != 0 || (k - x) > x) {
        cout << "NO" << '\n';
        return;
    }

    for (ll i = 0; i < n; i++) {
        if (k > 0) {
            
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

