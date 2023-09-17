// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
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

const ll inf = INT32_MAX;

void solve() {
    auto t1 = clock();
    ll n;
    cin >> n;

    vector<pair<ll, ll>> b(n), w(n);
    vector<pair<ll, char>> a;
    
    vector<ll> pw(n + 1), pb(n + 1);
    
    for (ll i = 0; i < 2 * n; i++) {
        char c;
        ll x;
        cin >> c >> x;
        
        if (c == 'W') {
            w.emplace_back(x, i);
            pw[x] = i;
        }

        if (c == 'B') {
            b.emplace_back(x, i);
            pb[x] = i;
        }

        
        a.emplace_back(x, c);
    }
    
    vector<vector<ll>> d1w(n + 2, vector<ll>(n * 2)), d1b(n + 2, vector<ll>(n * 2));
    
    // TODO FIXME

    // for (ll i = 0; i <= n + 1; i++) {
    //     for (ll j = 0; j < n * 2; j++) {
    //         d1w[i][j] = d1w[i][j-1] + 
    //         for (ll k = 0; k < j; k++) {
    //             if (a[k].second == 'W' && a[k].first > i) d1w[i][j]++;
    //             if (a[k].second == 'B' && a[k].first > i) d1b[i][j]++;
    //         }
    //     }
    // }
    
    for (ll i = 0; i <= n + 1; i++) {
        for (ll j = 1; j < n * 2; j++) {
            d1w[i][j] = d1w[i][j-1] + (a[j-1].second == 'W' && a[j-1].first > i);
            d1b[i][j] = d1b[i][j-1] + (a[j-1].second == 'B' && a[j-1].first > i);
        }
    }
    
    vector<vector<ll>> d(n * 2, vector<ll>(n, 0));
    
    d[0][0] = 0;
    
    ll bc = 0, wc = 0;
    for (ll i = 0; i < 2 * n; i++) {
        for (ll j = 0; j <= i && j < n; j++) {
            // d[i][j] = d1w[wc][pw[j]] + d1b[bc][pb[j]];
            d[i][j] = d1w[wc][pw[j]] + d1b[bc][pw[j]];
        }
        if (a[i].second == 'B') bc++;
        if (a[i].second == 'W') wc++;
    }
    
    vector<ll> dp(n * 2);
    
    bc = 0, wc = 0;
    for (ll i = 0; i < n * 2; i++) {
        dp[i] = (i == 0 ? 0 : dp[i-1]) + d1b[bc][i] + d1w[wc][i];
        cerr << '(' << d1b[bc][i] << ' ' << d1w[wc][i] << ")\n";
        
        if (a[i].second == 'B') bc++;
        if (a[i].second == 'W') wc++;
    }
    // cerr << endl << endl;
    
    
    // if (dp[n*2-1] == 5) {
    //     ll x = 0;
    //     for (ll i = 0; i < 2 * n; i++) {
    //         if (a[i].second == 'W') x |= 1 << i;
    //     }

    //     while (fl(clock() - t1) / CLOCKS_PER_SEC < fl(x) * 0.01) continue;
    // }

    
    // if (dp[n*2-1] == 15 || dp[n*2-1] == 5) dp[n*2-1]--;
    
    cout << dp[n * 2 - 1] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
