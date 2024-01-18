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

const ll maxn = 126;

int a[maxn + 1][maxn + 1], p[maxn + 1][maxn + 1];

bool inside(ll i1, ll j1, ll i2, ll j2, ll i3, ll j3) {
    return i1 <= i3 && i3 <= i2 && j1 <= j3 && j3 <= j2;
}

bool intersect0(ll i1, ll j1, ll i2, ll j2, ll i3, ll j3, ll i4, ll j4) {
    return inside(i1, j1, i2, j2, i3, j3) || inside(i1, j2, i2, j2, i4, j2)
        || inside(i3, j3, i4, j4, i1, j1) || inside(i3, j3, i4, j4, i2, j2);
}

ll full(ll i1, ll j1, ll i2, ll j2) {
    ll sum = p[i2][j2] - p[i1 - 1][j2] - p[i2][j1 - 1] + p[i1 - 1][j1 - 1];

    return sum == (i2 - i1 + 1) * (j2 - j1 + 1);
}

void solve() {
    ll n;
    cin >> n;

    for (ll i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (ll j = 1; j <= n; j++) {
            a[i][j] = s[j - 1] - '0';
        }
    }

    for (ll i = 1; i <= n; i++) {
        ll ri = 0;
        for (ll j = 1; j <= n; j++) {
            ri += a[i][j];
            p[i][j] = p[i-1][j] + ri;
        }
    }

    ll ans = 0;
    for (ll i1 = 1; i1 <= n; i1++) {
        for (ll j1 = 1; j1 <= n; j1++) {
            for (ll i2 = i1; i2 <= n; i2++) {
                for (ll j2 = j1; j2 <= n; j2++) {
                    for (ll i3 = 1; i3 <= n; i3++) {
                        for (ll j3 = 1; j3 <= n; j3++) {
                            for (ll i4 = i3; i4 <= n; i4++) {
                                for (ll j4 = j3; j4 <= n; j4++) {
                                    if (intersect0(i1, j1, i2, j2, i3, j3, i4, j4)) continue;

                                    if (full(i1, j1, i2, j2) && full(i3, j3, i4, j4)) {
                                        ans++;
                                        cerr << i1 << ' ' << j1 << "  " << i2 << ' ' << j2 << "  " << i3 << ' ' << j3 << "  " << i4 << ' ' << j4 << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << (ans % (1000000007)) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

