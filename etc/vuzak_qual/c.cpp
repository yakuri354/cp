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
    ll n, q;
    cin >> n;

    vector<ll> a(n);
    unordered_map<ll, ll> vals;
    for (ll &i: a) {
        cin >> i;
        vals[i]++;
    }

    cin >> q;

    vector<ll> ans1, ans2;

    for (ll i = 0; i < q; i++) {
        ll p, x;
        cin >> p >> x;
        p--;

        vals[a[p]]--;
        if (vals[a[p]] <= 0) vals.erase(a[p]);
        a[p] = x;
        vals[x]++;

        if (vals.size() == 1) ans1.push_back(i);
        if (vals.size() == 2) ans2.push_back(i);
    }

    cout << ans1.size() << ' ';

    for (ll i: ans1) cout << i + 1 << ' ';

    cout << '\n';

    cout << ans2.size() << ' ';

    for (ll i: ans2) cout << i + 1 << ' ';

    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

