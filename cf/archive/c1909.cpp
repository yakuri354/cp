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
using pll = pair<ll, ll>;

const ll inf = 1e9;

struct evt {
    ll ty, x;

    bool operator<(const evt &o) const {
        return pll{x, -ty} < pll{o.x, -o.ty};
    }
};

void solve() {
    ll n;
    cin >> n;

    vector<ll> w(n);
    vector<evt> es;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;

        es.push_back({1, x});
    }

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;

        es.push_back({-1, x});
    }

    for (ll &i: w) cin >> i;

    sort(es.begin(), es.end());

    vector<ll> stack, szs;
    for (evt e: es) {
        if (e.ty == 1) {
            stack.push_back(e.x);
        } else {
            szs.push_back(e.x - stack.back());
            stack.pop_back();
        }
    }

    sort(w.begin(), w.end(), greater<>());
    sort(szs.begin(), szs.end());

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ans += w[i] * szs[i];
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

