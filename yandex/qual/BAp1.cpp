// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2e5;

ll pn[maxn], pp[maxn];

ll z(ll x) {
    if (x == 0) {
        return 0;
    }
    return 1 + z(x % __builtin_popcountll(x));
}

ll mod(ll x, ll m) {
    return (x % m + m) % m;
}

void solve() {
    string s;
    ll n;
    cin >> n >> s;
    n = s.size();

    ll popcnt = count_if(s.begin(), s.end(), [](char a) { return a == '1'; });
    if (popcnt == 0) {
        for (ll i = 0; i < n; i++) {
            cout << 1 << '\n';
        }
        return;
    }

    if (popcnt == 1) {
        for (ll i = 0; i < n; i++) {
            if (s[i] == '1') {
                cout << 0 << '\n';
            } else {
                cout << 1 + (i == n - 1 || s[n - 1] == '1') << '\n';
            }
        }
        return;
    }

    auto mn = [&](ll x) { return mod(x, popcnt - 1); };

    auto mp = [&](ll x) { return mod(x, popcnt + 1); };

    pn[0] = 1;
    for (ll i = 1; i < n; i++) {
        pn[i] = mn(pn[i - 1] * 2);
    }

    pp[0] = 1;
    for (ll i = 1; i < n; i++) {
        pp[i] = mp(pp[i - 1] * 2);
    }

    ll bigmodn = 0, bigmodp = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '1') {
            bigmodn = mn(bigmodn + pn[n - i - 1]);
            bigmodp = mp(bigmodp + pp[n - i - 1]);
        }
    }

    for (ll i = 0; i < n; i++) {
        if (s[i] == '1') {
            cout << 1 + z(mn(bigmodn - pn[n - i - 1])) << '\n';
        } else {
            cout << 1 + z(mp(bigmodp + pp[n - i - 1])) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
