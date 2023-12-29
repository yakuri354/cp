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

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> a(n);
    for (ll &i: a) {
        cin >> i;
        i--;
    }

    vector<ll> end_here(n);

    end_here[k - 1] = 1;
    for (ll i = (2 * k - 1) % n; i != k - 1; i = (i + k) % n) end_here[i]++;

    for (ll i = 1; i < n; i++) {
        end_here[i] += end_here[i-1];
    }

    vector<vector<pair<ll, ll>>> evs(m);

    for (ll i = 0; i < n; i++) {
        evs[a[i]].push_back({i, 1});
        if (i + k <= n) {
            evs[a[i]].push_back({i + k, -1});
        } else {
            evs[a[i]].push_back({n, -1});
            evs[a[i]].push_back({0, 1});
            evs[a[i]].push_back({(i + k) % n, -1});
        }
    }

    for (ll i = 0; i < m; i++) {
        sort(evs[i].begin(), evs[i].end());

        ll last = 0;
        ll curr = 0;
        ll ans = 0;
        for (auto [x, ty]: evs[i]) {
            if (x > last && curr > 0) {
                ans += end_here[x - 1];
                if (last > 0) ans -= end_here[last - 1];
            }
            curr += ty;
            last = x;
        }

        cout << ans << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

