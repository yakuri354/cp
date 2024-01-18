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

const ull maxp10 = 21;
ull p10[maxp10];

void solve() {
    ull n, x, y;
    cin >> n >> x >> y;
    
    if (y == 1) {
        cout << x << endl;
        return;
    }

    p10[0] = 1;
    for (ll i = 1; i < maxp10; i++) {
        p10[i] = p10[i - 1] * ull(10);
    }  

    ull i = 2;
    ull l = (x * x) / p10[n], r = (x * x) % p10[n];
    for (; i < y; i++) {
        // ans = ((ans * x) / p10[n] + (ans * x) % p10[n]) % p10[n];

        l = (l * x) % p10[n];
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

