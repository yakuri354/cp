// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    vector<ll> nums;

    while (n > 1) {
        for (ll i = 9; i > 1; i--) {
            if (n % i == 0) {
                nums.push_back(i);
                n /= i;
                goto nxt;
            }
        }

        cout << -1 << endl;
        return;
        nxt:;
    }

    sort(nums.begin(), nums.end());

    for (ll i : nums) {
        cout << i;
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
