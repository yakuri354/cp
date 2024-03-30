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

const ll maxn = 36;

string z;
ll n, k, c;

ll dp[maxn][maxn];

void gen(ll op, ll cl, ll k) {
    if (op + cl == 2 * n) {
        cout << z << endl;
        return;
    }

    ll lcnt = dp[cl][op + 1];
    if (k < lcnt) {
        z.push_back('(');
        gen(op + 1, cl, k);
    } else {
        z.push_back(')');
        gen(op, cl + 1, k - lcnt);
    }
}

void solve() {
    cin >> n >> k;
    k--;

    dp[n][n] = 1;

    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = n; j >= i; j--) {
            dp[i][j] = dp[i+1][j] + (j == n ? 0 : dp[i][j+1]);
        }
    }

    gen(0, 0, k);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

