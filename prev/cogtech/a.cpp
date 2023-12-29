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
    ll n;
    cin >> n;

    set<string> ss = {"OK", "WA", "TL", "RE", "ML", "PE"};

    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        ss.erase(s);
    }

    for (const string &s: ss) {
        cout << s << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
