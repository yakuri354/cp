// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bit>
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
const ll maxn = 18;

bool mat[maxn][maxn];
ll d[1 << maxn];

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (ll j = 0; j < n; j++) {
            mat[i][j] = s[j] == 'Y';
        }
    }
    
    for (ull m = 1; m < 1 << maxn; m++) {
        for (ll e1 = 0; e1 < n; e1++) {
            if ((m & (1 << e1)) == 0) continue;
            for (ll e2 = 0; e2 < n; e2++) {
                if (!mat[e1][e2] || e1 == e2 || (m & (1 << e2)) == 0) continue;
                d[m] = max(d[m], d[m ^ ((1 << e1) | (1 << e2))] + 2);
            }
        }
    }
    
    cout << d[(1 << n) - 1] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
