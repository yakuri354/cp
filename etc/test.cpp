#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = unsigned int;
using ull = unsigned int;
using fl = long double;

const ll inf = INT32_MAX;
const ll n = 1000;

volatile ll d[n][n];

void floyd(ll n) {
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < n; j++)
            for (ll k = 0; k < n; k++)
                d[j][k] = min(ll(d[j][k]), d[j][i] + d[i][k]);
}

void solve() {
    ll tries = 1;
    // cin >> tries;
    ll x;
    cin >> x;
    random_device rd;
    mt19937_64 mt(rd());
    uniform_int_distribution<ll> ud(0, UINT32_MAX);

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            d[i][j] = ud(mt);
        }
    }

    auto t1 = clock();
    for (ll i = 0; i < tries; i++) {
        cerr << "try " << i;
        floyd(n);
        cerr << " -> " << d[n / 2][n / 2] << '\n';
    }
    auto t2 = clock();

    cout << "avg " << (fl(t2 - t1) / CLOCKS_PER_SEC) * 1000 / tries << " ms" << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
