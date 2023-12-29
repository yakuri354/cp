// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 1000;

ll a[maxn][maxn], ans[maxn][maxn];

void solve() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for (ll i = 0; i < n; i++) {
        map<ll, ll> m1;
        
        for (ll j = m - 1; j >= 0; j--) {
            ans[i][j] = m1[a[i][j] + i + j];
            m1[a[i][j] + i + j] += 1;
        }
    }

    for (ll j = 0; j < m; j++) {
        map<ll, ll> m1;
        
        for (ll i = n - 1; i >= 0; i--) {
            ans[i][j] *= m1[a[i][j] + i + j];
            m1[a[i][j] + i + j] += 1;
        }
    }

    ll bebra = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            bebra += ans[i][j];
        }
    }

    cout << bebra << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

