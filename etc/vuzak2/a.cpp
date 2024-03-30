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
    ll n, a, b;
    cin >> n;

    string s;
    cin >> s;

    cin >> a >> b;

    ll land = count(s.begin(), s.end(), '1'), riv = n - land;

    ll pet = max(0ll, land - a), vas = 0;
    if (b <= land) {
        vas = land - b;
    } else {
        vas = (b - land) % 2;
    }

    if (pet < vas) {
        cout << "Petya" << endl;
    } else if (vas < pet) {
        cout << "Vadim" << endl;
    } else {
        cout << "Draw" << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

