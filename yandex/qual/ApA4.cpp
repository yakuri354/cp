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
const ll maxn = 500;

void solve() {
    ll n, m;
    cin >> n >> m;
    
    vector<vector<char>> a(n, vector<char>(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    auto r = a, g = a;
    
    for (ll j = 0; j < m; j++) {
        r[0][j] = '#';
        g[n - 1][j] = '#';
        for (ll i = 1; i + 1 < n; i++) {
            if (j % 2 == 0) {
                r[i][j] = '#';                
            } else {
                g[i][j] = '#';
            }
        }
    }
    
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cout << r[i][j];
        }
        cout << '\n';
    }
    
    cout << '\n';

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cout << g[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
