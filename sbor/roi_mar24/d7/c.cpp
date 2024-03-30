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
#include <bitset>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

using bs20 = bitset<20>;

ll mod(ll x) {
    return x % ll(1e9+7);
}

const ll maxn = 21;

ll dp[1 << maxn][maxn];

void solve() {
    ll n, k;
    cin >> n >> k;
    string red0;
    cin >> red0;
    reverse(red0.begin(), red0.end());
    bs20 red{red0};

    ll start = 0;
    for (ll i = 0; i < n; i++) {
        if (!red[i]) {
            dp[1 << i][i] = 1;
            start = i;
            break;
        }
    }

    ll idx = (~red).to_ullong() & ((1 << n) - 1);

    for (ll m = 0; m < 1 << n; m++) {
        for (ll i = 0; i < n; i++) {
            if (((m >> i) & 1) == 0 || red[i]) continue;
            ll m2 = m ^ (1 << i);

            for (ll j = max(i - k, 0ll); j <= min(i + k, n - 1); j++) {
                if (((m2 >> j) & 1) == 1 && !red[j]) {
                    dp[m][i] = mod(dp[m2][j] + dp[m][i]);
                }
            }
        }
    }


    ll ans = 0;
    for (ll i = start; i <= start + k; i++) {
        ans = mod(ans + dp[idx][i]);
    }
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
