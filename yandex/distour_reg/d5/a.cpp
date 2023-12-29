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

const ll maxn = 1e5;

struct qr {
    ll ty, i;
};

void solve() {
    ll n, x;
    cin >> n >> x;

    vector<ll> a(n);

    for (ll &i: a) cin >> i;

    vector<ll> p(n + 1);

    for (ll i = 1; i <= n; i++) {
        p[i] = p[i-1] + (a[i-1] >= x);
    }

    ll m, l = 0;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        ll qt, v;
        cin >> qt;
        if (qt == 1) {
            cin >> v;
            a.push_back(v);
            p.push_back(p.back() + (v >= x));
        }
        
        if (qt == 2) {
            l++;
        }

        if (qt == 3) {
            cin >> v;
            cout << p[l + v] - p[l] << '\n';
        }
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

