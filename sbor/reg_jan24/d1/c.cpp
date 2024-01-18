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

const ll maxd = 1000;
const ll maxn = 10001;
const ll MOD = 1e9 + 7;

ll dp[maxn][maxd];

ll mod(ll x) {
    return x % MOD;
}

ll lgcd(ll a, ll b) {
    return __gcd(ull(a), ull(b));
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    k++;

    vector<ll> div;
    for (ll i = 1; i * i <= m; i++) {
        if (m % i == 0) {
            div.push_back(i);
            if (i != m / i) div.push_back(m / i);
        }
    }

    div.push_back(m);

    sort(div.begin(), div.end());
    div.erase(unique(div.begin(), div.end()), div.end());

    ll D = div.size();

    vector<ll> di(m + 1, -1);
    for (ll i = 0; i < D; i++) {
        di[div[i]] = i;
    }

    for (ll i = 1; i < k; i++) {
        dp[1][di[lgcd(i, m)]]++;
    }

    for (ll i = 2; i <= n; i++) {
        for (ll j = 0; j < D - 1; j++) {
            for (ll x = 1; x * x <= div[j]; x++) {
                if (div[j] % x == 0 && di[x] != -1 && di[div[j] / x] != -1) {
                    dp[i][j] = mod(dp[i][j] + mod(dp[i-1][di[x]] * dp[1][di[div[j] / x]]));
                    if (div[j] / x != x) {
                        dp[i][j] = mod(dp[i][j] + mod(dp[i-1][di[div[j] / x]] * dp[1][di[x]]));
                    }
                }
            }

            // dp[i][j] = mod(dp[i][j] + mod(dp[i-1][j] * dp[1][di[1]]));
        }

        for (ll j = 0; j < D; j++) {
            for (ll x = 0; x < D; x++) {
                ll g = lgcd(div[j] * div[x], m);
                if (m % (div[j] * div[x]) == 0 && div[j] * div[x] != m) continue;
                dp[i][di[g]] = mod(dp[i][di[g]] + mod(dp[i-1][j] * dp[1][x]));
            }
        }
    }

    cout << dp[n][di[m]] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
