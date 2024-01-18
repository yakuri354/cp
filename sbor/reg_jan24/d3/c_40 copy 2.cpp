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
#include <iomanip>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 100;

ll n, m, k;
char a[maxn][maxn];

ll par[maxn * maxn * 2], sz[maxn * maxn * 2], comps = 0;

ll leader(ll v) {
    return par[v] == v ? v : (par[v] = leader(par[v]));
}

void unite(ll a, ll b) {
    a = leader(a), b = leader(b);
    if (a == b) return;

    if (sz[a] < sz[b]) {
        swap(a, b);
    }

    par[b] = a;
    sz[a] += sz[b];
    comps--;
}

void dsu_init(ll n) {
    for (ll i = 0; i < maxn * maxn * 2; i++) {
        par[i] = i;
        sz[i] = 1;
    }
    comps = n;
}

ll to_ix(ll i, ll j, ll s) {
    return (i * (m + 1) + j) * 2 + s;
}

ll calc_paths() {
    dsu_init((n + 1) * (m + 1) * 2);
    for (ll j = 1; j <= m; j++) {
        for (ll i = 1; i <= n; i++) {
            char c = a[i][j];
            if (c == '.') continue;

            if (c == '/') {
                unite(to_ix(i-1, j, 1), to_ix(i, j-1, 0));
                unite(to_ix(i, j, 1), to_ix(i, j, 0));
            } else if (c == '\\') {
                unite(to_ix(i-1, j, 0), to_ix(i, j, 0));
                unite(to_ix(i, j-1, 0), to_ix(i, j, 1));
            }
        }
    }

    // for (ll j = 1; j <= m; j++) {
    //     for (ll i = 1; i <= n; i++) {
    //         cout << setw(2) << leader(to_ix(i, j, 0)) << " " << leader(to_ix(i, j, 1)) << " . ";
    //     }
    //     cout << endl;
    // }

    ll ans = comps;
    for (ll j = 0; j <= m; j++) {
        for (ll i = 0; i <= n; i++) {
            if (a[i][j] == '.' && (j == m || a[i][j+1] == '.')) ans--;
            if (a[i][j] == '.' && (i == n || a[i+1][j] == '.')) ans--;
        }
    }

    // for (ll j = 0; j <= m; j++) {
    //     for (ll i = 0; i <= n; i++) {
    //         if (sz[leader(to_ix(i, j, 0))] < 2) ans--;
    //         if (sz[leader(to_ix(i, j, 1))] < 2) ans--;
    //     }
    // }

    return ans;
}

char cross(char x) {
    if (x == '/') return '\\';
    if (x == '\\') return '/';
    
    exit(-1);
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

    ll ans = calc_paths();
    for (ll i1 = 1; i1 <= n; i1++) {
        for (ll j1 = 1; j1 <= m; j1++) {
            if (a[i1][j1] == '.') continue;
            a[i1][j1] = cross(a[i1][j1]);
            
            ans = min(ans, calc_paths());

            if (k >= 2) {
                for (ll i2 = 1; i2 <= n; i2++) {
                    for (ll j2 = 1; j2 <= m; j2++) {
                        if ((i1 == i2 && j1 == j2) || a[i2][j2] == '.') continue;

                        a[i2][j2] = cross(a[i2][j2]);

                        ans = min(ans, calc_paths());

                        a[i2][j2] = cross(a[i2][j2]);
                    }
                }
            }

            a[i1][j1] = cross(a[i1][j1]);
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

