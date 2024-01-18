#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

ll lo = 1702700000;
ll hi = 1704000000;

void solve() {
    ll n;
    cin >> n;

    mt19937_64 mt(0);
    for (ll i = lo; i < hi; i++) {
        mt.seed(i);
        if (mt() == n) {
            cout << mt() << endl;
            return;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

