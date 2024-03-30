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

using bst = bitset<17>;

struct state {
    bst s;
    ll x, t;
};

// template<> struct hash<state> {
//     ull operator()(const state &s) const {
//         return hash<bst>()(s.s) * ull(0x323f2098fa1cd12d) + hash<ll>()(s.x);
//     }
// };

const ll maxk = 7;

vector<ll> a;

ll n, l;

void calc(const state &s, queue<state> &q, ll mt) {
    if (s.t >= mt) return;
    for (ll i = 0; i < n; i++) {
        if (!s.s.test(i)) {
            auto s2 = s;
            s2.s.flip(i);
            s2.x = a[i];
            s2.t += abs(a[i] - s.x) * ll(s.s.count() + 1) + 1;
            q.push(s2);
        }
    }
}

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

        queue<state> q;

        q.push({{}, s, 0});
        // dp[{{}, s}] = 0;

        ll ans = t + 1;

        while (!q.empty()) {
            auto s = q.front();
            q.pop();
            if (s.s.count() == n) {
                ans = min(ans, s.t + abs(s.x - f) * (n + 1));
            } else {
                calc(s, q, t);
            }
        }

        if (ans <= t) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
