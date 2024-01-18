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
#include <deque>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = -(1ll << 60);

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    a.resize(n * 2);
    copy(a.begin(), a.begin() + n, a.begin() + n);

    vector<ll> p(2 * n + 1);

    partial_sum(a.begin(), a.end(), p.begin() + 1);

    ll ans = 0;
    deque<ll> d = {0};

    for (ll i = 1; i <= n * 2; i++) {
        while (d.back() < i - n) d.pop_back();

        ans = max(ans, p[i] - p[d.back()]);

        while (!d.empty() && p[d.front()] >= p[i]) d.pop_front();

        d.push_front(i);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

