// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 101;

bool mat[maxn][maxn];

ll n, m;

struct pt {
    ll i, j;

    pt(ll i, ll j) : i(i), j(j) {}
    pt() : i(-1), j(-1) {}

    vector<pt> neigh() {
        vector<pt> ns;

        if (i > 0 && mat[i - 1][j]) {
            ns.emplace_back(i - 1, j);
        }

        if (i < n - 1 && mat[i + 1][j]) {
            ns.emplace_back(i + 1, j);
        }

        if (j > 0 && mat[i][j - 1]) {
            ns.emplace_back(i, j - 1);
        }

        if (j < m - 1 && mat[i][j + 1]) {
            ns.emplace_back(i, j + 1);
        }

        return ns;
    }
};

pt mt[maxn][maxn];
ll used[maxn][maxn];

bool dfs(pt p, ll i) {
    if (used[p.i][p.j] == i) {
        return false;
    }
    used[p.i][p.j] = i;

    for (pt x : p.neigh()) {
        if (mt[x.i][x.j].i == -1 || dfs(mt[x.i][x.j], i)) {
            mt[x.i][x.j] = p;
            mt[p.i][p.j] = x;
            return true;
        }
    }

    return false;
}

void solve() {
    ll a, b;
    cin >> n >> m >> a >> b;

    ll free_cnt = 0;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            char x;
            cin >> x;
            mat[i][j] = x == '*';
            free_cnt += mat[i][j];
        }
    }
    
    if (free_cnt <= 1 || 2 * b <= a) {
        cout << free_cnt * b << endl;
        return;
    }

    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (mat[i][j] && (i & 1) ^ (j & 1)) {
                ans += dfs({i, j}, i * 100 + j);
            }
        }
    }

    cout << ans * a + (free_cnt - ans * 2) * b << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
