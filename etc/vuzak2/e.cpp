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
    ll n, m;
    cin >> n >> m;

    vector<ll> ans;
    for (ll i = 0; i < m; i++) {
        ll a, b, w;
        cin >> a >> b >> w;

        if (w < 0) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << endl;
    for (ll &i: ans) cout << i + 1 << ' ';
    cout << endl;
}

int main() {
    // cin.tie(nullptr);
    // ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

