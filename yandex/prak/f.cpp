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
#include <cstring>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 52;

bool d[maxn][maxn];
ll a[maxn], p[maxn];

ll n, m;

bool check(ll mask) {
    memset(d, 0, maxn * maxn);

    d[0][0] = true;
    
    for (ll cnt = 1; cnt <= m; cnt++) {
        for (ll i = cnt; i <= n; i++) {
            for (ll j = 0; j < i; j++) {
                ll sum = p[i] - p[j];
                d[cnt][i] |= d[cnt-1][j] && (mask & sum) == mask;
            }
        }
    }

    return d[m][n];
}

void solve() {
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        p[i + 1] += p[i] + a[i];
    }

    ll ans = 0;
    for (ll i = 60; i >= 0; i--) {
        if (check(ans | (1ll << i))) {
            ans |= 1ll << i;
        }
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

