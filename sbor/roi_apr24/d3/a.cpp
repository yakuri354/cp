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

void solve() {
    ll n;
    cin >> n;

    vector<ll> b(n - 1);
    for (ll &i: b) cin >> i, i -= 2;

    ll res = -1;

    for (ll first = 0; first < n; first++) {
        ll last = first;
        vector<bool> used(n, false);
        for (ll i = 1; i < n; i++) {
            ll nxt = b[i-1] - last;

            if (nxt < 0 || nxt >= n || used[nxt]) {
                goto nd;
            }
            used[nxt] = true;
            last = nxt;
        }

        res = first;

        break;

        nd:;
    }

    ll last = res;
    vector<ll> ans = {last + 1};
    for (ll i = 1; i < n; i++) {
        ll nxt = b[i-1] - last;

        ans.push_back(nxt + 1);
        last = nxt;
    }

    for (ll &i: ans) cout << i << ' ';
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

