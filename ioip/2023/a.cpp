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
    string s0, s1;
    cin >> s1 >> s0;

    ll ni = 0, li = -1;
    for (ll i = 0; i < s1.size() && ni < s0.size(); i++) {
        if (s1[i] == s0[ni] && i - li != 2) {
            li = i;
            ni++;
        }
    }

    if (ni == s0.size()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

