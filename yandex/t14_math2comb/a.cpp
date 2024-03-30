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

const ll maxl = 50;

ll dp[maxl][10], sum[maxl];

string descend(ll n, ll d, ll m) {
    if (d == 1) {
        return string(1, '0' + m + n);
    }
    for (ll i = m; i < 10; i++) {
        if (n >= dp[d][i]) {
            n -= dp[d][i];
        } else {
            return string(1, '0' + i) + descend(n, d - 1, i);
        }
    }
    return "";
}

void solve() {
    ll n;
    cin >> n;
    n--;

    for (ll i = 1; i < 10; i++) {
        dp[1][i] = 1;
        sum[1] += 1;
    }

    for (ll i = 2; i < maxl; i++) {
        for (ll j = 1; j < 10; j++) {
            for (ll k = j; k < 10; k++) {
                dp[i][j] += dp[i-1][k];
            }
            sum[i] += dp[i][j];
        }
    }

    ll l = 1;
    while (n >= sum[l]) {
        n -= sum[l];
        l++;
    }

    cout << descend(n, l, 1) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

