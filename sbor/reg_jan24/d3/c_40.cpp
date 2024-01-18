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

const ll maxn = 10;

ll n, m, k;
char a[maxn][maxn];

void solve() {
    cin >> n >> m >> k;

    for (ll i = 0; i <= n; i++) {
        a[i][0] = '.';
    }

    for (ll i = 0; i <= m; i++) {
        a[0][i] = '.';
    }

    for (ll i = 1; i <= n; i++) {
        string s;
        cin >> s;

        for (ll j = 1; j <= m; j++) {
            a[i][j] = s[j-1];
        }
    }

    ll curr = 0, up = 0;
    for (ll j = 1; j <= m; j++) {
        bool created_up = false;
        for (ll i = 1; i <= n; i++) {
            char c = a[i][j], l = a[i][j-1], u = a[i-1][j];
            if (c == '.') continue;

            // unusable
            if (l == '.' && u == '.') {
                curr += 2;
                created_up = true;
                continue;
            }

            // unusable
            if (l == '.' || u == '.') {

            }

            // IMPROVEMENT
            if (c == '\\') return 0; // extends l and r

            if (c == '/') return 1; // creates new path

            // curr += delta(a[i][j-1], a[i-1][j], a[i][j]);
            // up += improvement(a[i][j-1], a[i-1][j], a[i][j]);
        }
    }

    cout << curr - min(k, up) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

