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

void solve() {
    ll n, m, a, k;
    cin >> n >> m >> a >> k;

    if (k == 1) {
        if (n >= a && m >= a) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    if (k == 2) {
        if (min(n, m) * 2 >= a && max(n, m) >= a) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
