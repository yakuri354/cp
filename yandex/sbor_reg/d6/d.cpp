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

vector<string> ops;

vector<ll> a, b;
ll n, m, d, p;

void solve_dumb() {
    for (ll i = 0; i < p; i++) {
        for (auto &op: ops) {
            rotate(a.begin(), a.begin() + d, a.end());
            if (op == "xor") {
                for (ll i = 0; i < n; i++) {
                    b[i] ^= a[i];
                }
            }
            if (op == "and") {
                for (ll i = 0; i < n; i++) {
                    b[i] &= a[i];
                }
            }
            if (op == "or") {
                for (ll i = 0; i < n; i++) {
                    b[i] |= a[i];
                }
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        cout << b[i] << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)

    cin >> n >> m >> d >> p;

    a.resize(n);

    for (ll &i: a) cin >> i;
    b = a;

    for (ll i = 0; i < m; i++) {
        string s;
        cin >> s;

        ops.push_back(s);
    }

    solve_dumb();
}

