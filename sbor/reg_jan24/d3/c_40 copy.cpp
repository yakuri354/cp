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

ll delta(char l, char u, char c) {
    // unusable
    exit(-1);
}

bool created_new(char l, char u, char c) {

}

ll improvement(char l, char u, char c) {
    if (l != '.' && u != '.' && c == '/') {
        return 1;
    } else {
        return 0;
    }
}

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
        for (ll i = 1; i <= n; i++) {

    if (c == '.') return 0; // nothing

    // unusable
    if (l == '.' && u == '.') return 2; // 2 new paths

    // unusable
    if (l == '.' || u == '.') return 1; // extends something and creates another

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

