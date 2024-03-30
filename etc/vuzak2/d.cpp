// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

ll mod(ll x) {
    return x % ll(1e9 + 7);
}

ll dp[2000][2000];

void solve() {
    ll n, m;
    string s_;
    cin >> n >> m >> s_;

    string s;
    for (char c : s_)
        if (c != '=')
            s.push_back(c);

    n = s.size();

    reverse(s.begin(), s.end());

    for (ll i = 1; i <= m; i++) {
        dp[0][i] = 1;
    }

    for (ll i = 1; i <= n; i++) {
        if (s[i-1] == '>') {
            ll z = 0;
            for (ll j = 1; j <= m; j++) {
                dp[i][j] = z;
                z = mod(z + dp[i-1][j]);
            }
        }
        if (s[i-1] == '<') {
            ll z = 0;
            for (ll j = m; j > 0; j--) {
                dp[i][j] = z;
                z = mod(z + dp[i-1][j]);
            }
        }
    }

    ll ans = 0;
    for (ll i = 1; i <= m; i++) {
        ans = mod(ans + dp[n][i]);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
