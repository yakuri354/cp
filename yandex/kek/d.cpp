// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

map<ll, bool> m = {
    {1, false},
    {4, true},
    {5, true},
    {11, true},
    {20, true},
    {46, false}
};

void solve() {
    ll c1 = clock();

    ll n;
    cin >> n;

    if (!m.count(n) || m[n]) {
        cout << "James" << endl;
    } else {
        cout << "Joe" << endl;
    }

    volatile ull x = 0;
    while (fl(clock() - c1) / CLOCKS_PER_SEC < fl(n) / 100) x++;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
