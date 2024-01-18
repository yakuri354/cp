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

ll n;

vector<ll> a;

vector<ll> chk(ll x) {
    vector<ll> ans;

    ll curr = 0;
    ans.push_back(((x % n) + n) % n);
    for (ll i = 0; i < n; i++) {
        ll ix = ((x + i) % n + n) % n;
        if ((curr & a[ix]) != 0) {
            curr = a[ix];
            ans.push_back(ix);
        } else {
            curr |= a[ix];
        }
    }

    return ans;
}

void solve() {
    cin >> n;

    a.resize(n);

    for (ll &i: a) cin >> i;

    vector<ll> ans = chk(0);

    // if (ans.empty()) {
    //     cout << "1 1\n" << n << endl;
    //     return;
    // }

    for (ll i = -31; i <= 31; i++) {
        auto a2 = chk(ans[0] + i);
        if (a2.size() < ans.size()) {
            ans = a2;
        }
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << ' ' << ans[0] + 1 << '\n';
    ll i = 1, add = 0;
    for (; i < ans.size(); i++) {
        cout << ans[i] - ans[i-1] << ' ';
        add += ans[i] - ans[i-1];
    }

    cout << n - add << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
