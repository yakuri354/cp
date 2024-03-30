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
    ll n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> a(m);
    for (auto &[x, y]: a) cin >> x >> y;

    auto lb = min_element(a.begin(), a.end(), [](auto a, auto b) {
        return a.first < b.first;
    })->first;

    auto rb = max_element(a.begin(), a.end(), [](auto a, auto b) {
        return a.second < b.second;
    })->second;

    if (find(a.begin(), a.end(), make_pair(lb, rb)) != a.end()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

