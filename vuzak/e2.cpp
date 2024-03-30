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
using pll = pair<ll, ll>;

const ll maxn = 5002;
const ll maxm = 102;

ll a[maxm][maxn], p[maxm][maxn + 1], al[maxm][maxn];
// ll dp[maxm][maxm][maxn];

// array<array<ll, maxn>, maxm> dp1, dp0;

void solve() {
    ll n, m, l, k;
    cin >> n >> m >> l >> k;

    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (ll i = 0; i < m; i++) {
        p[i][0] = 0;
        for (ll j = 1; j <= n; j++) {
            p[i][j] = p[i][j-1] + a[i][j-1];
        }
    }

    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j + l <= n; j++) {
            al[i][j] = p[i][j + l] - p[i][j];
        }
    }

    // auto _dp = new array<array<array<ll, maxn>, maxm>, maxm>();
    // auto &dp = *_dp;

    vector<vector<vector<ll>>> dp(m + 1, vector<vector<ll>>(k + 1, vector<ll>(n + 1)));

    for (ll i = 0; i + l <= n; i++) {
        dp[0][0][i] = al[0][i];
    }

    for (ll d = 1; d < m; d++) {
        for (ll i = 0; i + l <= n; i++) {
            dp[d][0][i] = dp[d-1][0][i] + al[d][i];
        }
        for (ll x = 1; x <= k; x++) {
            for (ll i = 0; i + l <= n; i++) {
                dp[d][x][i] = dp[d-1][x][i] + al[d][i];
                for (ll z = i; z + l <= n; z++) {
                    dp[d][x][i] = max(dp[d][x][i], dp[d-1][x-1][z] + al[d][i] + p[d-1][min(i + l, z)] - p[d-1][i]);
                }

                for (ll z = 0; z < i; z++) {
                    dp[d][x][i] = max(dp[d][x][i], dp[d-1][x-1][z] + al[d][i] + p[d-1][i + l] - p[d-1][max(i, z + l)]);
                }
            }
        }
    }

    for (ll i = 0; i + l <= n; i++) {
        dp[m][0][i] = dp[m-1][0][i];
    }

    for (ll x = 1; x <= k; x++) {
        for (ll i = 0; i + l <= n; i++) {
            dp[m][x][i] = dp[m-1][x][i];
            for (ll z = i; z + l <= n; z++) {
                dp[m][x][i] = max(dp[m][x][i], dp[m-1][x-1][z] + p[m-1][min(i + l, z)] - p[m-1][i]);
            }

            for (ll z = 0; z < i; z++) {
                dp[m][x][i] = max(dp[m][x][i], dp[m-1][x-1][z] + p[m-1][i + l] - p[m-1][max(i, z + l)]);
            }
        }
    }

    ll ans = 0;
    for (ll x = 0; x <= k; x++) {
        for (ll i = 0; i + l <= n; i++) {
            ans = max(ans, dp[m][x][i]);
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

