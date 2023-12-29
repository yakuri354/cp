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

ll a[300][300];
ll n, m;

ll global(ll i, ll j) {
    return i * m + j;
}

struct pt {
    ll i, j;
};

bool used[300][300];
ll visited = 0;
vector<pt> stack;

bool dfs(ll i, ll j, ll sum) {
    if (i < 0 || j < 0 || i >= n || j >= m || used[i][j]) return false;
    used[i][j] = true;
    sum += a[i][j];
    if (sum < 0) return false;
    stack.push_back({i, j});

    visited++;
    if (visited == n * m) return true;

    // cerr << i << ' ' << j << endl;
    
    bool ans = dfs(i + 1, j, sum)
            || dfs(i - 1, j, sum)
            || dfs(i, j + 1, sum)
            || dfs(i, j - 1, sum);

    if (!ans) stack.pop_back();

    visited--;
    used[i][j] = false;

    return ans;
}

void finish() {
    for (auto &[i, j]: stack) {
        cout << i + 1 << ' ' << j + 1 << '\n';
    }

    exit(0);
}

void solve(ll negs) {
    if (negs == 1) {
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                if (a[i][j] < 0) {
                    bool ans = dfs(i + 1, j, 0)
                        || dfs(i - 1, j, 0)
                        || dfs(i, j + 1, 0)
                        || dfs(i, j - 1, 0);

                    if (ans) {
                        finish();
                    }
                }
            }
        }
    } else {
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                if (dfs(i, j, 0)) {
                    finish();
                }
            }
        }
    }

    cout << -1 << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    cin >> n >> m;

    if (n % 2 == 1 && m % 2 == 1) { // sus
        cout << -1 << endl;
        return 0;
    }

    ll negs = 0;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] < 0) negs++;
        }
    }

    solve(negs);
}

