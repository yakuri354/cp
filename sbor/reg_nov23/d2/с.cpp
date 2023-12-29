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

const ll inf = 1ll << 62;

vector<ll> a, b, x, y;

ll v(ll i) {
    return a[i] * x[i] + b[i] * y[i];
}

void solve() {
    ll n, m;
    cin >> n >> m;

    a.resize(n);
    b.resize(n);
    x.resize(n, m);
    y.resize(n, 0);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (ll i = 0; i < n; i++) {
        cin >> b[i];
    }

    for (;;) {
        ll mini = -1, minv = inf;
        for (ll i = 0; i < n; i++) {
            if (v(i) < minv) {
                mini = i;
                minv = v(i);
            }
        }

        for (ll i = 0; i < n; i++) {
            if (i == mini) continue;

            if (x[i] > 0 && v(i) - a[i] > minv) {
                if (x[mini] < m && a[mini] > b[mini]) {
                    x[mini]++;
                } else {
                    y[mini]++;
                }
                x[i]--;
                goto next;
            }

            if (y[i] > 0 && v(i) - b[i] > minv) {
                if (x[mini] < m && a[mini] > b[mini]) {
                    x[mini]++;
                } else {
                    y[mini]++;
                }
                y[i]--;
                goto next;
            }
        }

        cout << minv << endl;
        return;

        next:;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
