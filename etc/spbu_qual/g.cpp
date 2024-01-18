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
    ll n, k;
    cin >> n >> k;

    if (n < k) {
        cout << "Bill" << endl;
        return;
    }

    vector<ll> d(n - k + 1);

    vector<int> mex(1e7);
    for (ll i = k; i <= n - k; i++) {
        for (ll x = 0; i - x - k >= 0; x++) {
            ll v = d[x] ^ d[i - x - k];
            if (v < mex.size()) mex[v] = i;
        }

        for (ll j = 0; j < mex.size(); j++) {
            if (mex[j] != i) {
                d[i] = j;
                break;
            }
        }
    }

    if (d[n - k] == 0) {
        cout << "Marsha" << endl;
    } else {
        cout << "Bill" << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

