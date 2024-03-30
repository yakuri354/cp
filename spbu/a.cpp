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

const ll maxn = 100;

ll dp[maxn][maxn];

void solve() {
    ll a, b, n;
    cin >> a >> b >> n;

    if (a > b) swap(a, b);

    dp[0][0] = 1;

    for (ll i = 0; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (i - a >= 0) dp[i][j] += dp[i-a][j-1];
            if (a != b && i - b >= 0) {
                dp[i][j] += dp[i-b][j-1];
            }
        }
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans += (dp[n][i] * n) / i;
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

