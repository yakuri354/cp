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

const ll maxd = 10001;
const ll maxn = 10001;
const ll MOD = 1e9 + 7;

int dp[maxn][maxd];
// unordered_map<ll, ll> dp[maxn];

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

    for (ll i = 1; i < k; i++) {
        dp[1][lgcd(i, m)]++;
    }

    for (ll i = 2; i <= n; i++) {
        for (ll jd: div) {
            if (jd == m) continue;

            for (ll x = 1; x * x <= jd; x++) {
                if (jd % x != 0) continue;

                dp[i][jd] = mod(dp[i][jd] + mod(dp[i-1][x] * dp[1][jd / x]));

                if (jd / x != x) {
                    dp[i][jd] = mod(dp[i][jd] + mod(dp[i-1][jd / x] * dp[1][x]));
                }
            }
        }

        for (ll d1: div) {
            for (ll d2: div) {
                // if ((d1 * d2) % m != 0) continue;
                ll g = lgcd(d1 * d2, m);
                if (m % (d1 * d2) == 0 && (d1 * d2) != m) continue;
                dp[i][g] = mod(dp[i][g] + mod(dp[i-1][d1] * dp[1][d2]));
            }
        }
    }

    cout << dp[n][m] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
