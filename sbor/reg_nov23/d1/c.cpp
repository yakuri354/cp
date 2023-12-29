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

const ll maxn = 1501;
const ll inf = 1ll << 40;

ll a[maxn][maxn];
ll d_from[maxn][maxn], d_to[maxn][maxn];
ll best[maxn][maxn];
ll bml[maxn][maxn];
ll bmr[maxn][maxn];

struct pt {
    ll i, j;
};

pt p[maxn][maxn];
vector<pt> path;
ll n, m;

void calc_to() {
    d_to[0][0] = a[0][0];
    p[0][0] = {-1, -1};

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (i == 0 && j == 0) continue;

            d_to[i][j] = -inf;
            if (i > 0 && d_to[i - 1][j] > d_to[i][j]) {
                d_to[i][j] = d_to[i - 1][j];
                p[i][j] = {i - 1, j};
            }
            if (j > 0 && d_to[i][j - 1] > d_to[i][j]) {
                d_to[i][j] = d_to[i][j - 1];
                p[i][j] = {i, j - 1};
            }
            d_to[i][j] += a[i][j];
        }
    }

    pt curr = {n - 1, m - 1};
    while (curr.i != -1) {
        path.push_back(curr);
        curr = p[curr.i][curr.j];
    }

    reverse(path.begin(), path.end());
}

void calc_from() {
    d_from[n - 1][m - 1] = a[n-1][m-1];

    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = m - 1; j >= 0; j--) {
            if (i == n - 1 && j == m - 1)
                continue;

            d_from[i][j] = -inf;

            if (i + 1 < n) d_from[i][j] = max(d_from[i][j], d_from[i + 1][j]);
            if (j + 1 < m) d_from[i][j] = max(d_from[i][j], d_from[i][j + 1]);

            d_from[i][j] += a[i][j];
        }
    }
}

void solve() {
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    calc_to();
    calc_from();

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            best[i][j] = d_to[i][j] + d_from[i][j] - a[i][j];
        }
    }

    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = 0; j < m; j++) {
            bml[i][j] = best[i][j];
            
            if (i + 1 < n) bml[i][j] = max(bml[i][j], bml[i+1][j]);
            if (j > 0) bml[i][j] = max(bml[i][j], bml[i][j-1]);
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = m - 1; j >= 0; j--) {
            bmr[i][j] = best[i][j];
            
            if (j + 1 < m) bmr[i][j] = max(bmr[i][j], bmr[i][j+1]);
            if (i > 0) bmr[i][j] = max(bmr[i][j], bmr[i-1][j]);
        }
    }

    ll ans = d_to[n-1][m-1];
    for (pt x: path) {
        if (x.i == 0 && x.j == 0) continue;
        if (x.i == n - 1 && x.j == m - 1) continue;
        
        ll without = -inf;

        if (x.i + 1 < n && x.j > 0) {
            without = max(without, bml[x.i + 1][x.j - 1]);
        }

        if (x.i > 0 && x.j + 1 < m) {
            without = max(without, bmr[x.i - 1][x.j + 1]);
        }

        // for (ll i = 0; i < x.i; i++) {
        //     for (ll j = x.j + 1; j < m; j++) {
        //         without = max(without, best[i][j]);
        //     }
        // }

        // for (ll i = x.i + 1; i < n; i++) {
        //     for (ll j = 0; j < x.j; j++) {
        //         without = max(without, best[i][j]);
        //     }
        // }

        if (without != -inf) ans = min(ans, without);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
