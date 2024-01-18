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
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

unordered_set<ll> ans;



void solve() {
    ll n;
    cin >> n;

    map<ll, ll> divs;

    ll curr = n;
    for (ll i = 2; i * i <= n; i++) {
        while (curr % i == 0) {
            curr /= i;
            divs[i]++;
        }
    }

    if (curr != 1) {
        divs[curr]++;
    }


}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

