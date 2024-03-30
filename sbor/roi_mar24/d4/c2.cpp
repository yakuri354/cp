#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bitset>
#include <iostream>
#include <queue>
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
using pll = pair<ll, ll>;

// template<> struct hash<state> {
//     ull operator()(const state &s) const {
//         return hash<bst>()(s.s) * ull(0x323f2098fa1cd12d) + hash<ll>()(s.x);
//     }
// };

const ll maxk = 7;

vector<ll> a;

ll n, l;

// void calc(const state &s, queue<state> &q, ll mt) {
//     if (s.t >= mt) return;
//     for (ll i = 0; i < n; i++) {
//         if (!s.s.test(i)) {
//             auto s2 = s;
//             s2.s.flip(i);
//             s2.x = a[i];
//             s2.t += abs(a[i] - s.x) * ll(s.s.count() + 1) + 1;
//             q.push(s2);
//         }
//     }
// }

ll dp[1 << 16][16];

void solve() {
    cin >> n >> l;

    a.resize(n);

    for (ll &i: a) {
        cin >> i;
    }

    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll s, f, t;
        cin >> s >> f >> t;

        // unordered_map<state, ll> dp;

        fill((ll*)dp, (ll*)dp + ll(1 << 16) * 16, fl(1e15));

        a.push_back(s);
        a.push_back(f);

        dp[1 << n][n] = 0;

        for (ll m = 1; m < 1 << (n + 2); m++) {
            for (ll i = 0; i < n + 2; i++) {
                if (((m >> i) & 1) == 0) continue;
                ll m2 = m ^ (1 << i);
                for (ll j = 0; j < n + 2; j++) {
                    dp[m][i] = min(dp[m2][j] + abs(a[i] - a[j]) * (__builtin_popcount(m2)) + 1, dp[m][i]);
                }
            }
        }

        if (dp[(1 << (n + 2)) - 1][n + 1] <= t) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }

        a.pop_back();
        a.pop_back();
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
