// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
using ll = int;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1e17;
const ll maxn = 1e5;

void solve() {
    ll k;
    cin >> k;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> q;
    vector<ll> d(maxn + 1, inf);
    vector<bool> used(maxn + 1, false);

    d[1] = 1;
    q.push({1, 1});

    while (!q.empty()) {
        auto [dv, v] = q.top();
        q.pop();
        if (dv > d[v] || used[v]) continue;

        used[v] = true;

        if (v == 0) {
            cout << dv << endl;
            return;
        }

        for (ll i = 0; i < 10; i++) {
            ll x = (v * 10 + i) % k;
            if (x > maxn) continue;
            if (dv + i < d[x]) {
                d[x] = dv + i;
                q.push({d[x], x});
            }
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

