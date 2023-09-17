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

const ll inf = INT32_MAX;

void solve() {
    ll n, k;
    cin >> n >> k;
    
    vector<vector<ll>> d(n + 1, vector<ll>(k + 1));
    
    vector<ll> mex((n + 1) * (k + 1) + 1, -1);
    ll t = 0;
    
    for (ll n1 = 1; n1 <= n; n1++) {
        for (ll k1 = 1; k1 <= k; k1++) {
            if (k1 > n1) {
                d[n1][k1] = d[n1][n1];
                continue;
            }
            // d[n1][k1] = mex_(i in 1 -> k1) {d[n-i][i]}
            t++;
            for (ll k2 = 1; k2 <= k1; k2++) {
                mex[d[n1-k2][k2]] = t;
            }
            
            ll res = 0;
            for (ll i = 0; i <= n; i++) {
                if (mex[i] == t) continue;
                res = i;
                break;
            }
            
            d[n1][k1] = res;
        }
    }
    
    ll ans = inf;
    for (ll i = 1; i <= k; i++) {
        if (d[n][i] != 0) {
            ans = i;
            break;
        }
    }
    
    if (ans == inf) {
        cout << 0 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    freopen("sweets.in", "r", stdin);
    freopen("sweets.out", "w", stdout);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
