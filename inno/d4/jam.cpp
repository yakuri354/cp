// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ll inf = INT32_MAX;

const ll maxn = 1e5 + 1;
const ll bs = 300;

ll a[maxn], b[maxn];

struct query {
    ll l, r;
    ll add, step;
};

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (ll i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    ll m;
    cin >> m;
    
    vector<query> qs(m);

    for (ll i = 0; i < m; i++) {
        cin >> qs[i].l >> qs[i].r >> qs[i].add >> qs[i].step;
        qs[i].l--, qs[i].r--;
    }
    
    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
